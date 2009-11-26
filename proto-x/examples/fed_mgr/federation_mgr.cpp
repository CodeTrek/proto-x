/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#include <iostream>
#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <fedtime.hh>
#include <RTI.hh>

#include <protox/hla/o_class_type.hpp>

#include "fedlet/fed_amb.hpp"
#include "fedlet/sync_points.hpp"

#include "object_model/fed_mgr_som.hpp"
#include "obj_fed_amb.hpp"

/**************************************************************************************************/

using namespace boost;
using namespace protox::examples;

/**************************************************************************************************/

class fed_mgr_fed_amb : public fedlet::fed_amb
{
private:
  obj_amb_type &obj_amb;

public:
  fed_mgr_fed_amb( obj_amb_type &obj_amb ) : obj_amb(obj_amb) {}

  ~fed_mgr_fed_amb() throw (RTI::FederateInternalError) {}

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // Object Management Services
  //////////////////////////////////////////////////////////////////////////////////////////////////

  virtual void discoverObjectInstance( RTI::ObjectHandle      theObject,
                                       RTI::ObjectClassHandle theObjectClass,
                                       const char *           theObjectName )
  throw( RTI::CouldNotDiscover, RTI::ObjectClassNotKnown, RTI::FederateInternalError )
  {
    obj_amb.discover_object( theObjectClass, theObject, theObjectName );
    std::cout << "Federate " << theObjectName << " joined\n";
  }

  virtual void reflectAttributeValues( RTI::ObjectHandle                       theObject,
                                       const RTI::AttributeHandleValuePairSet &theAttributes,
                                       const RTI::FedTime                     &theTime,
                                       const char                             *theTag,
                                       RTI::EventRetractionHandle              theHandle )
  throw( RTI::ObjectNotKnown,
         RTI::AttributeNotKnown,
         RTI::FederateOwnsAttributes,
         RTI::InvalidFederationTime,
         RTI::FederateInternalError )
  {
    obj_amb.reflect_object( theObject, theAttributes, &theTime, theTag );
  }

  virtual void reflectAttributeValues( RTI::ObjectHandle                       theObject,
                                       const RTI::AttributeHandleValuePairSet &theAttributes,
                                       const char                              *theTag )
  throw( RTI::ObjectNotKnown,
         RTI::AttributeNotKnown,
         RTI::FederateOwnsAttributes,
         RTI::FederateInternalError )
  {
    obj_amb.reflect_object( theObject, theAttributes, 0, theTag );
  }

  virtual void removeObjectInstance( RTI::ObjectHandle           theObject,
                                     const RTI::FedTime         &theTime,
                                     const char                 *theTag,
                                     RTI::EventRetractionHandle  theHandle )
  throw( RTI::ObjectNotKnown, RTI::InvalidFederationTime, RTI::FederateInternalError )
  {
    obj_amb.remove_object( theObject );
    std::cout << "Federate removed\n";
  }

  virtual void removeObjectInstance( RTI::ObjectHandle theObject, const char *theTag )
  throw( RTI::ObjectNotKnown, RTI::FederateInternalError )
  {
    obj_amb.remove_object( theObject );
    std::cout << "Federate removed\n";
  }

};

static void register_sync_points( RTI::RTIambassador &rti_amb )
{
  rti_amb.registerFederationSynchronizationPoint( READY_TO_POPULATE, "" );
  rti_amb.registerFederationSynchronizationPoint( READY_TO_RUN,      "" );
  rti_amb.registerFederationSynchronizationPoint( READY_TO_RESIGN,   "" );
}

static void advance_time( double timestep,
                          RTI::RTIambassador &rti_amb,
                          fedlet::fed_amb_base &fed_amb )
{
  fed_amb.is_advancing = true;
  const RTIfedTime new_time = (fed_amb.fed_time + timestep);
  rti_amb.timeAdvanceRequest( new_time );

  // wait for the time advance to be granted.
  while (fed_amb.is_advancing)
  {
    rti_amb.tick();
  }
}

static void enable_time_policy( RTI::RTIambassador &rti_amb, const fedlet::fed_amb_base &fed_amb )
{
  const RTIfedTime fed_time = fed_amb.fed_time;
  const RTIfedTime lookahead = fed_amb.fed_lookahead_time;

  rti_amb.enableTimeRegulation( fed_time, lookahead );

  while (fed_amb.is_regulating == false)
  {
    rti_amb.tick();
  }

  rti_amb.enableTimeConstrained();

  while (fed_amb.is_constrained == false)
  {
    rti_amb.tick();
  }
}

static void create_federation_execution( RTI::RTIambassador &rti_amb,
                                         const char *name,
                                         const char *fed_file )
{
  try
  {
    rti_amb.createFederationExecution( name, fed_file );
    std::cout << "Federation created.\n";
  }
  catch (RTI::FederationExecutionAlreadyExists)
  {
    std::cout << "Federation already exists.\n";
  }
  catch (RTI::Exception &ex)
  {
     std::cout <<  ex._name << " " << ex._reason << std::endl;
  }
}

static void destroy_federation_execution( RTI::RTIambassador &rti_amb, const char *name )
{
  try
  {
    rti_amb.destroyFederationExecution( name );
    std::cout << "Federation destroyed.\n";
  }
  catch (RTI::FederationExecutionDoesNotExist)
  {
    std::cout << "Federtion does not exist.\n";
  }
  catch (RTI::FederatesCurrentlyJoined)
  {
    std::cout << "Federation not destroyed - other federates are joined.\n";
  }
}

/**
 * A simple manager federate that uses synchronization points and the managment object model (MOM)
 * to coordinate the initialization, execution, and resignation phases of a HLA federation
 * execution.
 *
 * Note: Start this federate before any other federates.
 *
 * Here is a summary of this federates behavior:
 *
 * 1) Create and join a federation execution.
 *
 * 2) Wait for the expected number of federates to join. When the expected number of federates join,
 *    register these synchronization points: "ReadyToPopulate", "ReadyToRun", and "ReadyToResign"
 *
 * 3) Wait for all of the synchronization points to be announced and then signal
 *    "ReadyToPopulate" achieved.
 *
 * 4) Wait for "ReadyToPopulate" to be achieved by the other joined federates. When all joined
 *    federates achieve "ReadyToPopulate", signal "ReadyToRun".
 *
 * 5) Wait for "ReadyToRun" to be achieved by the other joined federates. When all joined
 *    federates achieve "ReadyToRun", signal "ReadyToResign".
 *
 * 6) Wait for "ReadyToResign" to be achieved by the other joined federates. When all joined
 *    federates achieve "ReadyToResign", terminate execution.
 *
 */
int main( int argc, char* argv[] )
{
  if (argc != 4)
  {
    std::cout << "usage: fed_mgr federation fed_file num_federates\n";
    std::cout << "       federation    - The name of the federation.\n";
    std::cout << "       fed_file      - The federation execution details (FED) file.\n";
    std::cout << "       num_federates - The total number of federates required to join, including"
                                       " this fed_mgr federate.\n";
    std::cout << "\n";
    std::cout << "Example: fed_mgr \"exmaple_federation\" \"./example.fed\" 3\n";

    return -1;
  }

  static const char    *FEDERATION_NAME = argv[ 1 ];
  static const char    *FED_FILE_NAME   = argv[ 2 ];
  static const unsigned NUM_FEDERATES   = atoi( argv[ 3 ] );

  using namespace protox::hla;

  RTI::RTIambassador rti_amb;

  create_federation_execution( rti_amb, FEDERATION_NAME, FED_FILE_NAME );

  // Join federation
  obj_amb_type obj_amb;
  fed_mgr_fed_amb fed_amb( obj_amb );
	rti_amb.joinFederationExecution( "fed_mgr", FEDERATION_NAME, &fed_amb );
  std::cout << "Federation joined.\n";

  // Initialize handles
  fed_mgr_som::init_handles( rti_amb );
  std::cout << "Handles initialized.\n";

  // subscribe
  federate_type::subscribe( rti_amb );

  // enable time policy
  enable_time_policy( rti_amb, fed_amb );

  bool need_to_register_sync_points = true;
  bool ready_to_populate_achieved   = false;
  bool ready_to_run_achieved        = false;
  bool ready_to_resign_achieved     = false;

  while (true)
  {
    advance_time( 1.0, rti_amb, fed_amb );

    if ((obj_amb.size< federate_type >() >= NUM_FEDERATES) && (need_to_register_sync_points))
    {
      try
      {
        register_sync_points( rti_amb );
        need_to_register_sync_points = false;
      }
      catch (RTI::Exception& ex)
      {
        std::cout << "RTI Exception: " << ex._name << " " << ex._reason << "\n";
        break;
      }
    }

    if ((fed_amb.all_sync_points_announced) && (!ready_to_populate_achieved))
    {
      try
      {
        rti_amb.synchronizationPointAchieved( READY_TO_POPULATE );
        ready_to_populate_achieved = true;
      }
      catch (RTI::Exception& ex)
      {
        std::cout << "RTI Exception: " << ex._name << " " << ex._reason << std::endl;
        break;
      }
    }

    if ((fed_amb.is_ready_to_populate) && (!ready_to_run_achieved))
    {
      try
      {
        rti_amb.synchronizationPointAchieved( READY_TO_RUN );
        ready_to_run_achieved = true;
      }
      catch (RTI::Exception& ex)
      {
        std::cout << "RTI Exception: " << ex._name << " " << ex._reason << std::endl;
        break;
      }
    }

    if ((fed_amb.is_ready_to_run) && (!ready_to_resign_achieved))
    {
      try
      {
        rti_amb.synchronizationPointAchieved( READY_TO_RESIGN );
        ready_to_resign_achieved = true;
      }
      catch (RTI::Exception& ex)
      {
        std::cout << "RTI Exception: " << ex._name << " " << ex._reason << std::endl;
        break;
      }
    }

    if (fed_amb.is_ready_to_resign)
    {
      break;
    }
  }

  return 0;
}

/**************************************************************************************************/
