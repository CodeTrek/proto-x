
#include <iostream>
#include <string>

#include <boost/shared_ptr.hpp>

#include <fedtime.hh>
#include <RTI.hh>
#include <NullFederateAmbassador.hh>

#include <protox/hla/o_class_type.hpp>

#include "utils/utils.hpp"
#include "fed_mgr_som.hpp"
#include "obj_fed_amb.hpp"

using namespace boost;

class fed_mgr_fed_amb : public NullFederateAmbassador
{
private:
  RTI::RTIambassador &rti_amb;
  obj_amb_type &obj_amb;

public:
  fed_mgr_fed_amb( RTI::RTIambassador &rti_amb,
                   obj_amb_type &obj_amb ) :
    rti_amb( rti_amb ),
    obj_amb( obj_amb )
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
  }

  virtual void reflectAttributeValues (
          RTI::ObjectHandle                 theObject,     // supplied C1
    const RTI::AttributeHandleValuePairSet& theAttributes, // supplied C4
    const RTI::FedTime&                     theTime,       // supplied C1
    const char                             *theTag,        // supplied C4
          RTI::EventRetractionHandle        theHandle)     // supplied C1
  {
    obj_amb.reflect_object( theObject, theAttributes, &theTime, theTag );
  }

  virtual void reflectAttributeValues (
          RTI::ObjectHandle                 theObject,     // supplied C1
    const RTI::AttributeHandleValuePairSet& theAttributes, // supplied C4
    const char                             *theTag)        // supplied C4
  {
    obj_amb.reflect_object( theObject, theAttributes, 0, theTag );
  }

  virtual void removeObjectInstance (
          RTI::ObjectHandle          theObject, // supplied C1
    const RTI::FedTime&              theTime,   // supplied C4
    const char                      *theTag,    // supplied C4
          RTI::EventRetractionHandle theHandle) // supplied C1
  {
    // Ignore time
    removeObjectInstance( theObject, theTag );
  }

  virtual void removeObjectInstance (
          RTI::ObjectHandle          theObject, // supplied C1
    const char                      *theTag)    // supplied C4
  {
    obj_amb.remove_object( theObject );
  }
};

#if 0
class FederationManager : public NullFederateAmbassador
{
private:
  RTI::RTIambassador &rti_amb;
  unsigned long const NUM_REQUIRED_JOINS;
  //int numSyncPointsCount;
  //RTI::FederateHandle federateHandle;
  boost::shared_ptr< RTI::FederateHandleSet > federateHandleSet;
  std::string const fedXName;

  /**
   * Register the required synchronization points.
   */
  void registerSyncPoints()
  {
    assert( federateHandleSet != 0 );
    assert( federateHandleSet->size() == NUM_REQUIRED_JOINS );
    numSyncPointsCount = 0;
     
    try
    {
      rtiAmb->registerFederationSynchronizationPoint( "ReadyToPopulate", "", *federateHandleSet );
      rtiAmb->registerFederationSynchronizationPoint( "ReadyToRun",      "", *federateHandleSet );
      rtiAmb->registerFederationSynchronizationPoint( "ReadyToResign",   "", *federateHandleSet );
    }
    catch(RTI::Exception& ex)
    {
      std::cout << "RTI Exception: " << ex._name << " " << ex._reason << "\n";
    }
  } 
  
  void onFederateJoined( RTI::FederateHandle const fedHandle )
  {
    assert( federateHandleSet != 0 );
    
    if ( federateHandleSet->isMember( fedHandle ) )
      return;
    
    federateHandleSet->add( fedHandle );
    
    // Have the required number of federates joined?
    if ( federateHandleSet->size() < NUM_REQUIRED_JOINS )
      return;
    
    // Now that everyone has joined, register the sync points
    // used to coordinate the lifecycel of each joined federate.
    registerSyncPoints();
  }
  
  virtual void announceSynchronizationPoint(
    const char *label,
    const char *tag
  )
  throw( RTI::FederateInternalError )
  {
    static int const NUM_REQUIRED_SYNC_POINTS = 3;
    
    ++numSyncPointsCount;
    
    if (numSyncPointsCount < NUM_REQUIRED_SYNC_POINTS )
      return;
  
    // All of the sync points have been registered and announced,
    // so assert ReadyToPopulate...
    try
    {
      rtiAmb->synchronizationPointAchieved( "ReadyToPopulate" );
    }
    catch(RTI::Exception& ex)
    {
      std::cout << "RTI Exception: "
                << ex._name << " "
                << ex._reason << std::endl;
    } 
  }
  
  /**
   * This should only be called when a federate joins the federation.
   */
  virtual void reflectAttributeValues(
    RTI::ObjectHandle                       theObject,     // supplied C1
    const RTI::AttributeHandleValuePairSet& theAttributes, // supplied C4
    const RTI::FedTime&                     theTime,       // supplied C1
    const char                             *theTag,        // supplied C4
    RTI::EventRetractionHandle              theHandle)     // supplied C1
  throw(
    RTI::ObjectNotKnown,
    RTI::AttributeNotKnown,
    RTI::FederateOwnsAttributes,
    RTI::InvalidFederationTime,
    RTI::FederateInternalError)
  {
    // Ignore the timestamp.
    FederationManager::reflectAttributeValues( theObject, theAttributes, theTag );
  }
  
  /**
   * This should only be called when a federate joins the federation.
   */
  virtual void reflectAttributeValues(
    RTI::ObjectHandle                       theObject,     // supplied C1
    const RTI::AttributeHandleValuePairSet& theAttributes, // supplied C4
    const char                             *theTag)        // supplied C4
  throw(
    RTI::ObjectNotKnown,
    RTI::AttributeNotKnown,
    RTI::FederateOwnsAttributes,
    RTI::FederateInternalError)
  {
    assert( theAttributes.size() == 1 );
    
    RTI::Handle const attrHandle = theAttributes.getHandle( 0 );
    RTI::Handle const classHandle = rtiAmb->getObjectClass( theObject );
    char const *attrName = rtiAmb->getAttributeName( attrHandle, classHandle );
    assert( std::string("FederateHandle") == attrName );
        
    // Get the joined federate's handle.

    RTI::FederateHandle joinedFederateHandle = 0;
    RTI::ULong sizeInBytes = 0;
    
    char const * const attrData = theAttributes.getValuePointer( 0, sizeInBytes );
    
    try
    {
      joinedFederateHandle = boost::lexical_cast< RTI::FederateHandle >( attrData );
    }
    catch(bad_lexical_cast &)
    {
      assert( false );
    }
    
    onFederateJoined( joinedFederateHandle );
  }
  
  virtual void synchronizationPointRegistrationSucceeded (
    const char *label) // supplied C4)
  throw (RTI::FederateInternalError)
  {
    std::cout << "Synchronization point[ " << label << " ]successfully registered\n";
  }

  virtual void synchronizationPointRegistrationFailed (
    const char *label) // supplied C4)
  throw (RTI::FederateInternalError)
  {
    std::cout << "Synchronization point[ " << label << " ]failed to register\n";
    
    assert( federateHandleSet != 0 );
    assert( federateHandleSet->size() == NUM_REQUIRED_JOINS );

    try
    {
      rtiAmb->registerFederationSynchronizationPoint( label, "", *federateHandleSet );
    }
    catch(RTI::Exception& ex)
    {
      std::cout << "RTI Exception: " << ex._name << " " << ex._reason << "\n";
    }
  }
  
  /**
   * Called when all joined federates have achieved a synchronization point.
   */
  virtual void federationSynchronized(
    const char *label // supplied C4)
  ) 
  throw(
    RTI::FederateInternalError
  )
  {
    if (std::string( "ReadyToPopulate" ) == label) {
      rtiAmb->synchronizationPointAchieved( "ReadyToRun" );

    }
    else if (std::string( "ReadyToRun" ) == label) {
      rtiAmb->synchronizationPointAchieved( "ReadyToResign" );
    }
    else if (std::string( "ReadyToResign" ) == label) {
    
      // Reset the federate handle set.
      federateHandleSet->empty();
      federateHandleSet->add( federateHandle );
    }
  }
  
public:
  FederationManager(
    std::string const &fedName,
    std::string const &xName,
    std::string const &fedFile,
    int numRequiredJoins
  ) :
    rtiAmb( Hla13RtiAmbFactory::newRtiAmb() ),
    NUM_REQUIRED_JOINS(numRequiredJoins),
    numSyncPointsCount(0),
    federateHandle(0),
    federateHandleSet( RTI::FederateHandleSetFactory::create( numRequiredJoins ) ),
    fedXName(xName)
  {
    assert( federateHandleSet != 0 );
    
    createFedEx( *rtiAmb, fedXName.c_str(), fedFile.c_str() );

    try
    {
      federateHandle = rtiAmb->joinFederationExecution(fedName.c_str(), fedXName.c_str(), this);
      federateHandleSet->add( federateHandle );
      
      // This subscription insures that the manager is notified whenever a
      // federate joins.
      std::vector< std::string > const subStr = list_of("Manager.Federate")
                                                         ("FederateHandle");
      Hla13Utils::subscribeAttributes( rtiAmb, subStr );
    }
    catch(RTI::Exception& ex)
    {
      federateHandleSet->empty();
      federateHandle = 0;
      std::cout << "RTI Exception: " << ex._name << " " << ex._reason << "\n";
    }
  }
  
  ~FederationManager()
  {
    rtiAmb->resignFederationExecution( RTI::DELETE_OBJECTS );
    destroyFederation( *rtiAmb, fedXName.c_str() );
  }
  
  void run()
  {
    while( true ) {
      rtiAmb->tick();
      Sleep( 100 );
    }
  }
};
#endif

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

  std::cout << "Publications/subscription completed.\n";

	return 0;
}

