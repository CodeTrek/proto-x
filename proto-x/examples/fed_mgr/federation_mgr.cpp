#include <iostream>
#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <fedtime.hh>
#include <RTI.hh>

#include <protox/hla/o_class_type.hpp>

#include "utils/utils.hpp"
#include "utils/fed_amb_util.hpp"
#include "fed_mgr_som.hpp"
#include "obj_fed_amb.hpp"

using namespace boost;

class fed_mgr_fed_amb : public fed_amb_util
{
private:
  enum {NUM_REQUIRED_JOINS = 2};

  RTI::RTIambassador &rti_amb;
  obj_amb_type &obj_amb;
  boost::shared_ptr< RTI::FederateHandleSet > federate_handle_set;
  int num_sync_points_count;

  void register_sync_points()
  {
    assert( federate_handle_set != 0 );
    assert( federate_handle_set->size() == NUM_REQUIRED_JOINS );
    num_sync_points_count = 0;

    try
    {
      rti_amb.registerFederationSynchronizationPoint( "ReadyToPopulate", "", *federate_handle_set );
      rti_amb.registerFederationSynchronizationPoint( "ReadyToRun",      "", *federate_handle_set );
      rti_amb.registerFederationSynchronizationPoint( "ReadyToResign",   "", *federate_handle_set );
    }
    catch(RTI::Exception& ex)
    {
      std::cout << "RTI Exception: " << ex._name << " " << ex._reason << "\n";
    }
  } 

  void update_federate_set()
  {
    assert( federate_handle_set != 0 );
    federate_handle_set->empty();

    obj_amb_type::const_it< federate_type >::type it;

    for( it = obj_amb.begin< federate_type >(); it != obj_amb.end< federate_type >(); ++it )
    {
      const HLAhandle &handle = it->second.a_< HLAfederateHandle >();
      std::string handle_str( handle.begin(),  handle.end() ); 

      if( handle_str.empty() )
      {
        continue;
      }

      RTI::FederateHandle federate_handle = 0;
      try
      {
        federate_handle = boost::lexical_cast< RTI::FederateHandle >( handle_str.c_str() );
      }
      catch( bad_lexical_cast & ) { assert( false ); }

      federate_handle_set->add( federate_handle );
    }
    
    // Have the required number of federates joined?
    if( federate_handle_set->size() < NUM_REQUIRED_JOINS )
    {
      return;
    }
    
    // Now that everyone has joined, register the sync points used to coordinate the life cycle of
    // each joined federate.
    register_sync_points();
  }

public:
  fed_mgr_fed_amb( RTI::RTIambassador &rti_amb, obj_amb_type &obj_amb ) :
    rti_amb( rti_amb ),
    obj_amb( obj_amb ),
    federate_handle_set( RTI::FederateHandleSetFactory::create( 3 ) )
  {}

  ~fed_mgr_fed_amb() {}

  ////////////////////////////////
  // Object Management Services //
  ////////////////////////////////

  virtual void discoverObjectInstance (
          RTI::ObjectHandle          theObject,      // supplied C1
          RTI::ObjectClassHandle     theObjectClass, // supplied C1
    const char*                      theObjectName)  // supplied C4  
  {
    obj_amb.discover_object( theObjectClass, theObject, theObjectName );
    std::cout << "Federate " << theObjectName << " joined\n";
  }

  virtual void reflectAttributeValues (
          RTI::ObjectHandle                 theObject,     // supplied C1
    const RTI::AttributeHandleValuePairSet& theAttributes, // supplied C4
    const RTI::FedTime&                     theTime,       // supplied C1
    const char                             *theTag,        // supplied C4
          RTI::EventRetractionHandle        theHandle)     // supplied C1
  {
    obj_amb.reflect_object( theObject, theAttributes, &theTime, theTag );
    update_federate_set();
  }

  virtual void reflectAttributeValues (
          RTI::ObjectHandle                 theObject,     // supplied C1
    const RTI::AttributeHandleValuePairSet& theAttributes, // supplied C4
    const char                             *theTag)        // supplied C4
  {
    obj_amb.reflect_object( theObject, theAttributes, 0, theTag );
    update_federate_set();
  }

  virtual void removeObjectInstance (
          RTI::ObjectHandle          theObject, // supplied C1
    const RTI::FedTime&              theTime,   // supplied C4
    const char                      *theTag,    // supplied C4
          RTI::EventRetractionHandle theHandle) // supplied C1
  {
    obj_amb.remove_object( theObject );
    update_federate_set();
    std::cout << "Federate removed\n";
  }

  virtual void removeObjectInstance (
          RTI::ObjectHandle          theObject, // supplied C1
    const char                      *theTag)    // supplied C4
  {
    obj_amb.remove_object( theObject );
    update_federate_set();
    std::cout << "Federate removed\n";
  }

  virtual void announceSynchronizationPoint(
    const char *label,
    const char *tag)
  {
    std::string label_str(label);

    if (label_str.empty())
    {
      label = "unknown";
    }

    std::cout << "Sync point " << label_str.c_str() << " announced.\n";

    static int const NUM_REQUIRED_SYNC_POINTS = 3;
    
    ++num_sync_points_count;
    
    if( num_sync_points_count < NUM_REQUIRED_SYNC_POINTS )
    {
      return;
    }
  
    // All of the sync points have been registered and announced,
    // so assert ReadyToPopulate...
    try
    {
      rti_amb.synchronizationPointAchieved( "ReadyToPopulate" );
    }
    catch( RTI::Exception& ex )
    {
      std::cout << "RTI Exception: " << ex._name << " " << ex._reason << std::endl;
    }
  }

  /**
   * Called when all joined federates have achieved a synchronization point.
   */
  virtual void federationSynchronized( const char *label ) 
  {
    if( std::string( "ReadyToPopulate" ) == label )
    {
      rti_amb.synchronizationPointAchieved( "ReadyToRun" );
    }
    else if( std::string( "ReadyToRun" ) == label )
    {
      rti_amb.synchronizationPointAchieved( "ReadyToResign" );
    }
    else if( std::string( "ReadyToResign" ) == label )
    {
      // Reset the federate handle set.
      federate_handle_set->empty();
    }
  }
};

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
  static const char *FEDERATION_NAME = "example_federation";

  using namespace protox::hla;

  RTI::RTIambassador rti_amb;

  create_federation_execution( rti_amb, FEDERATION_NAME, "example.fed" );

  // Join federation
  obj_amb_type obj_amb;
  fed_mgr_fed_amb fed_amb( rti_amb, obj_amb );
	rti_amb.joinFederationExecution( "fed_mgr", FEDERATION_NAME, &fed_amb );
  std::cout << "Federation joined.\n";

  // Initialize handles
  fed_mgr_som::init_handles( rti_amb );
  std::cout << "Handles initialized.\n";

  // subscribe
  federate_type::subscribe( rti_amb );

  // enable time policy
  enable_time_policy( rti_amb, fed_amb );

  while( true )
  {
    advance_time( 1.0, rti_amb, fed_amb );
  }

  return 0;
}
