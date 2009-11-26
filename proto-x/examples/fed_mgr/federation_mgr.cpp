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

//#include "utils/utils.hpp"
//#include "utils/fed_amb.hpp"

#include "fedlet/fed_amb.hpp"

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
  fed_mgr_fed_amb(obj_amb_type &obj_amb ) : obj_amb( obj_amb ) {}

  ~fed_mgr_fed_amb() throw( RTI::FederateInternalError )  {}

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
  rti_amb.registerFederationSynchronizationPoint( "ReadyToPopulate", "" );
  rti_amb.registerFederationSynchronizationPoint( "ReadyToRun",      "" );
  rti_amb.registerFederationSynchronizationPoint( "ReadyToResign",   "" );
}

static void advance_time
  ( double timestep, RTI::RTIambassador &rti_amb, fedlet::fed_amb_base &fed_amb )
{
  // request the advance
  fed_amb.is_advancing = true;
  const RTIfedTime new_time = (fed_amb.fed_time + timestep);
  rti_amb.timeAdvanceRequest( new_time );

  // wait for the time advance to be granted. ticking will tell the LRC to start delivering
  // callbacks to the federate
  while( fed_amb.is_advancing )
  {
    rti_amb.tick();
  }
}

static void enable_time_policy( RTI::RTIambassador &rti_amb, const fedlet::fed_amb_base &fed_amb )
{
  ////////////////////////////
  // enable time regulation //
  ////////////////////////////
  const RTIfedTime fed_time = fed_amb.fed_time;
  const RTIfedTime lookahead = fed_amb.fed_lookahead_time;
  rti_amb.enableTimeRegulation( fed_time, lookahead );

  // tick until we get the callback
  while( fed_amb.is_regulating == false )
  {
    rti_amb.tick();
  }

  /////////////////////////////
  // enable time constrained //
  /////////////////////////////
  rti_amb.enableTimeConstrained();

  // tick until we get the callback
  while( fed_amb.is_constrained == false )
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
  catch( RTI::FederationExecutionAlreadyExists )
  {
    std::cout << "Federation already exists.\n";
  }
  catch( RTI::Exception &ex )
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
  catch( RTI::FederationExecutionDoesNotExist )
  {
    std::cout << "Federtion does not exist.\n";
  }
  catch( RTI::FederatesCurrentlyJoined )
  {
    std::cout << "Federation not destroyed - other federates are joined.\n";
  }
}

/**
 * A simple manager federate that uses synchronization points and the
 * managment object model (MOM) to coordinate the initialization, execution,
 * and resignation phases of a HLA federation execution. The behavior of this
 * federate is described in the book: "Creating Computer Simulation Systems"
 * (ISBN 0-13-022511-8). In particular, see pages 116-117.
 *
 * Start this federate before any other federates
 * after starting the remote RTI component (i.e., RTI exec).
 *
 * Here is a summary of this federates behavior:
 *
 * a) This federate creates and joins a federation execution.
 * b) It immediately registers the synchronization points -
 *    "ReadyToPopulate", "ReadyToRun", and "ReadyToResign" and
 *    enters the "awaiting ReadyToPopulate" state.
 * c) It subscribes to the attribute
 *    "ObjectRoot.Manager.Federate.FederateHandle". It does this in order to be
 *    notified when other federates join the federation.
 * d) When the expected number of federates join, it signals the RTI it has
 *    achieved "ReadyToPopulate". Once all the other federates signal that
 *    they have also achieved "ReadyToPopulate", the RTI will inform this
 *    federate that the federation is synchronized on "ReadyToPopulate".
 * e) Having nothing to do in the "ReadyToPopulate" phase, it informs
 *    the RTI that it has achieved "ReadyToRun".
 * f) When this federate hears that the federation is synchronized at
 *    "ReadyToRun", it informs the RTI that it has achieved "ReadyToResign".
 *    Currently, the manager does not participate in time-management, so
 *    it has nothing to do in the "ReadyToRun" phase.
 * g) When this federate hears that the federation is synchronized at
 *    "ReadyToResign", it re-registers the synchronization points from
 *    b) and starts the process all over.
 *
 */
int main( int argc, char* argv[] )
{
  if( argc != 4 )
  {
    std::cout << "usage: fed_mgr federation fed_file num_federates\n";
    std::cout << "       federation    - The name of the federation.\n";
    std::cout << "       fed_file      - The federation execution details (FED) file.\n";
    std::cout << "       num_federates - The total number of federates required to join, including this fed_mgr federate.\n";
    std::cout << "\n";
    std::cout << "Example: fed_mgr \"exmaple_federation\" \"./example.fed\" 3\n";

    return -1;
  }

  static const char *FEDERATION_NAME = argv[ 1 ];
  static const char *FED_FILE_NAME = argv[ 2 ];
  static const unsigned NUM_FEDERATES = atoi( argv[ 3 ] );

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

  while( true )
  {
    advance_time( 1.0, rti_amb, fed_amb );

    if( (obj_amb.size< federate_type >() >= NUM_FEDERATES) && (need_to_register_sync_points) )
    {
      try
      {
        register_sync_points( rti_amb );
        need_to_register_sync_points = false;
      }
      catch( RTI::Exception& ex )
      {
        std::cout << "RTI Exception: " << ex._name << " " << ex._reason << "\n";
        break;
      }
    }

    if( (fed_amb.all_sync_points_announced) && (!ready_to_populate_achieved) )
    {
      try
      {
        rti_amb.synchronizationPointAchieved( "ReadyToPopulate" );
        ready_to_populate_achieved = true;
      }
      catch( RTI::Exception& ex )
      {
        std::cout << "RTI Exception: " << ex._name << " " << ex._reason << std::endl;
        break;
      }
    }

    if( (fed_amb.is_ready_to_populate) && (!ready_to_run_achieved) )
    {
      try
      {
        rti_amb.synchronizationPointAchieved( "ReadyToRun" );
        ready_to_run_achieved = true;
      }
      catch( RTI::Exception& ex )
      {
        std::cout << "RTI Exception: " << ex._name << " " << ex._reason << std::endl;
        break;
      }
    }

    if( (fed_amb.is_ready_to_run) && (!ready_to_resign_achieved) )
    {
      try
      {
        rti_amb.synchronizationPointAchieved( "ReadyToResign" );
        ready_to_resign_achieved = true;
      }
      catch( RTI::Exception& ex )
      {
        std::cout << "RTI Exception: " << ex._name << " " << ex._reason << std::endl;
        break;
      }
    }

    if( fed_amb.is_ready_to_resign )
    {
      break;
    }
  }

  return 0;
}

/**************************************************************************************************/
