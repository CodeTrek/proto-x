/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef RTI_LITE_HH
#define RTI_LITE_HH

/**************************************************************************************************/

#include <boost/foreach.hpp>

#include <map>
#include <vector>
#include <string>

/**************************************************************************************************/

class RTI { // Treat this as a namespace

/**************************************************************************************************/

public:

/**************************************************************************************************/

// Basic types...

typedef unsigned short UShort;
typedef short          Short;
typedef unsigned long  ULong;
typedef long           Long;
typedef double         Double;
typedef float          Float;

enum Boolean {RTI_FALSE = 0, RTI_TRUE};

/**************************************************************************************************/

// RTI types...

class Exception
{
public:
  ULong _serial;
  char *_reason;
  const char *_name;
  Exception (const char *reason) {}
  Exception (ULong serial, const char *reason=NULL) {}
  Exception (const Exception &toCopy) {}
  virtual ~Exception () {}
  Exception &operator = (const Exception &) { return *this; }
};

/**************************************************************************************************/

#define RTI_EXCEPT(A)                                                       \
class A : public Exception                                                  \
{                                                                           \
public:                                                                     \
  A (const char *reason) : Exception (reason)  {}                           \
  A (ULong serial, const char *reason=NULL) : Exception (serial, reason) {} \
  A (A const & toCopy) : Exception(toCopy) {}                               \
};

/**************************************************************************************************/

RTI_EXCEPT(ArrayIndexOutOfBounds)
RTI_EXCEPT(AsynchronousDeliveryAlreadyDisabled)
RTI_EXCEPT(AsynchronousDeliveryAlreadyEnabled)
RTI_EXCEPT(AttributeAcquisitionWasNotRequested)
RTI_EXCEPT(AttributeAcquisitionWasNotCanceled)
RTI_EXCEPT(AttributeAlreadyBeingAcquired)
RTI_EXCEPT(AttributeAlreadyBeingDivested)
RTI_EXCEPT(AttributeAlreadyOwned)
RTI_EXCEPT(AttributeDivestitureWasNotRequested)
RTI_EXCEPT(AttributeNotDefined)
RTI_EXCEPT(AttributeNotKnown)
RTI_EXCEPT(AttributeNotOwned)
RTI_EXCEPT(AttributeNotPublished)
RTI_EXCEPT(ConcurrentAccessAttempted)
RTI_EXCEPT(CouldNotDiscover)
RTI_EXCEPT(CouldNotOpenFED)
RTI_EXCEPT(CouldNotRestore)
RTI_EXCEPT(DeletePrivilegeNotHeld)
RTI_EXCEPT(DimensionNotDefined)
RTI_EXCEPT(EnableTimeConstrainedPending)
RTI_EXCEPT(EnableTimeConstrainedWasNotPending)
RTI_EXCEPT(EnableTimeRegulationPending)
RTI_EXCEPT(EnableTimeRegulationWasNotPending)
RTI_EXCEPT(ErrorReadingFED)
RTI_EXCEPT(EventNotKnown)
RTI_EXCEPT(FederateAlreadyExecutionMember)
RTI_EXCEPT(FederateInternalError)
RTI_EXCEPT(FederateLoggingServiceCalls)
RTI_EXCEPT(FederateNotExecutionMember)
RTI_EXCEPT(FederateOwnsAttributes)
RTI_EXCEPT(FederateWasNotAskedToReleaseAttribute)
RTI_EXCEPT(FederatesCurrentlyJoined)
RTI_EXCEPT(FederationExecutionAlreadyExists)
RTI_EXCEPT(FederationExecutionDoesNotExist)
RTI_EXCEPT(FederationTimeAlreadyPassed)
RTI_EXCEPT(HandleValuePairMaximumExceeded)
RTI_EXCEPT(InteractionClassNotDefined)
RTI_EXCEPT(InteractionClassNotKnown)
RTI_EXCEPT(InteractionClassNotPublished)
RTI_EXCEPT(InteractionClassNotSubscribed)
RTI_EXCEPT(InteractionParameterNotDefined)
RTI_EXCEPT(InteractionParameterNotKnown)
RTI_EXCEPT(InvalidExtents)
RTI_EXCEPT(InvalidFederationTime)
RTI_EXCEPT(InvalidHandleValuePairSetContext)
RTI_EXCEPT(InvalidLookahead)
RTI_EXCEPT(InvalidOrderingHandle)
RTI_EXCEPT(InvalidRegionContext)
RTI_EXCEPT(InvalidResignAction)
RTI_EXCEPT(InvalidRetractionHandle)
RTI_EXCEPT(InvalidTransportationHandle)
RTI_EXCEPT(MemoryExhausted)
RTI_EXCEPT(NameNotFound)
RTI_EXCEPT(ObjectClassNotDefined)
RTI_EXCEPT(ObjectClassNotKnown)
RTI_EXCEPT(ObjectClassNotPublished)
RTI_EXCEPT(ObjectClassNotSubscribed)
RTI_EXCEPT(ObjectNotKnown)
RTI_EXCEPT(ObjectAlreadyRegistered)
RTI_EXCEPT(OwnershipAcquisitionPending)
RTI_EXCEPT(RegionInUse)
RTI_EXCEPT(RegionNotKnown)
RTI_EXCEPT(RestoreInProgress)
RTI_EXCEPT(RestoreNotRequested)
RTI_EXCEPT(RTIinternalError)
RTI_EXCEPT(SpaceNotDefined)
RTI_EXCEPT(SaveInProgress)
RTI_EXCEPT(SaveNotInitiated)
RTI_EXCEPT(SpecifiedSaveLabelDoesNotExist)
RTI_EXCEPT(SynchronizationPointLabelWasNotAnnounced)
RTI_EXCEPT(TimeAdvanceAlreadyInProgress)
RTI_EXCEPT(TimeAdvanceWasNotInProgress)
RTI_EXCEPT(TimeConstrainedAlreadyEnabled)
RTI_EXCEPT(TimeConstrainedWasNotEnabled)
RTI_EXCEPT(TimeRegulationAlreadyEnabled)
RTI_EXCEPT(TimeRegulationWasNotEnabled)
RTI_EXCEPT(UnableToPerformSave)
RTI_EXCEPT(ValueCountExceeded)
RTI_EXCEPT(ValueLengthExceeded)

/**************************************************************************************************/

enum ResignAction
{
  RELEASE_ATTRIBUTES = 1,
  DELETE_OBJECTS,
  DELETE_OBJECTS_AND_RELEASE_ATTRIBUTES,
  NO_ACTION
};

/**************************************************************************************************/

class Region;

class FederateAmbassador;

typedef FederateAmbassador *FederateAmbassadorPtr;

typedef Long SpaceHandle;

typedef ULong ObjectClassHandle;

typedef ULong InteractionClassHandle;

typedef ULong ExtentIndex;

typedef ULong Handle;

typedef Handle AttributeHandle;

typedef Handle ParameterHandle;

typedef Handle ObjectHandle;

typedef Handle DimensionHandle;

typedef ULong FederateHandle;

typedef Handle TransportationHandle;

typedef TransportationHandle TransportType;

typedef Handle OrderingHandle;

typedef OrderingHandle OrderType;

typedef ULong FederateID;

typedef ULong UniqueID;

typedef Double TickTime;

typedef ULong RegionToken;

/**************************************************************************************************/

class AttributeHandleValuePairSet
{
private:
  struct pair
  {
    Handle handle;
    std::vector< char > value;
  };

  std::vector< pair > hv_set;

public:
  AttributeHandleValuePairSet( ULong count ) {}

  AttributeHandleValuePairSet( const AttributeHandleValuePairSet &s ) : hv_set(s.hv_set) {}

  virtual ~AttributeHandleValuePairSet() {}

  AttributeHandleValuePairSet &operator=( const AttributeHandleValuePairSet &s )
  {
    hv_set = s.hv_set;
    return *this;
  }

  virtual ULong size() const
  {
    return ((ULong) hv_set.size());
  }

  virtual Handle getHandle( ULong i) const throw (ArrayIndexOutOfBounds)
  {
    return hv_set[ i ].handle;
  }

  virtual ULong getValueLength( ULong i) const throw (ArrayIndexOutOfBounds)
  {
    return ((ULong) hv_set[ i ].value.size());
  }

  virtual void getValue( ULong i, char *buff, ULong &length ) const throw (ArrayIndexOutOfBounds)
  {
    for (ULong it = 0; it < length; ++it)
    {
      buff[ it ] = hv_set[ i ].value[ it ];
    }
  }

  virtual char *getValuePointer( ULong i, ULong &length ) const throw (ArrayIndexOutOfBounds)
  {
    length = (ULong) hv_set[ i ].value.size();
    char *buf = (char *) &hv_set[ i ].value[0];

    return buf;
  }

  virtual TransportType getTransportType( ULong i ) const
  throw (ArrayIndexOutOfBounds, InvalidHandleValuePairSetContext)
  {
    return 0;
  }

  virtual OrderType getOrderType( ULong i ) const
  throw (ArrayIndexOutOfBounds, InvalidHandleValuePairSetContext)
  {
    return 0;
  }

  virtual Region *getRegion( ULong i ) const
  throw (ArrayIndexOutOfBounds, InvalidHandleValuePairSetContext)
  {
    return 0;
  }

  virtual void add( Handle h, const char* buff, ULong valueLength )
  throw (ValueLengthExceeded, ValueCountExceeded)
  {
    pair new_pair;
    new_pair.handle = h;

    for( unsigned i = 0; i < valueLength; ++i )
    {
      new_pair.value.push_back( buff[ i ] );
    }

    hv_set.push_back( new_pair );
  }

  virtual void remove( Handle h ) throw (ArrayIndexOutOfBounds) {}

  virtual void moveFrom( const AttributeHandleValuePairSet &ahvps, ULong &i )
  throw (ValueCountExceeded, ArrayIndexOutOfBounds)
  {}

  virtual void empty() {}

  virtual ULong start() const { return 0; }
  virtual ULong valid( ULong i ) const { return (ULong) (i < hv_set.size()); }
  virtual ULong next( ULong i ) const { return i + 1; }
};

/**************************************************************************************************/

class AttributeSetFactory
{
public:
  static AttributeHandleValuePairSet* create( ULong count )
  throw (MemoryExhausted, ValueCountExceeded, HandleValuePairMaximumExceeded)
  {
    return new AttributeHandleValuePairSet( count );
  }
};

/**************************************************************************************************/

class AttributeHandleSet
{
private:
  const ULong count;

public:
  AttributeHandleSet( ULong count ) : count(count) {}

  virtual ~AttributeHandleSet() {}

  virtual ULong size() const {return count;}

  virtual AttributeHandle getHandle( ULong i ) const throw (ArrayIndexOutOfBounds) {return 0;}

  virtual void add( AttributeHandle h ) throw (ArrayIndexOutOfBounds, AttributeNotDefined) {}

  virtual void remove( AttributeHandle h ) throw (AttributeNotDefined) {}

  virtual void empty() {}

  virtual Boolean isEmpty() const {return RTI::RTI_TRUE;}

  virtual Boolean isMember(AttributeHandle h) const {return RTI::RTI_FALSE;}
};

/**************************************************************************************************/

class AttributeHandleSetFactory
{
public:
  static AttributeHandleSet *create( ULong count ) throw(MemoryExhausted, ValueCountExceeded)
  {
    return new AttributeHandleSet( count );
  }
};

/**************************************************************************************************/

class FederateHandleSet
{
public:
  virtual ULong size() const = 0;
  virtual FederateHandle getHandle( ULong i ) const throw (ArrayIndexOutOfBounds) = 0;
  virtual void add( FederateHandle h ) throw (ValueCountExceeded) = 0;
  virtual void remove( FederateHandle h ) throw (ArrayIndexOutOfBounds) = 0;
  virtual void empty() = 0;
  virtual Boolean isMember(FederateHandle h) const = 0;
};

/**************************************************************************************************/

class FederateHandleSetFactory
{
public:
  static FederateHandleSet* create( ULong count ) throw (MemoryExhausted, ValueCountExceeded);
};

/**************************************************************************************************/

class ParameterHandleValuePairSet
{
private:
  struct pair
  {
    Handle handle;
    std::vector< char > value;
  };

  std::vector< pair > hv_set;

public:
  ParameterHandleValuePairSet( ULong count ) {}

  ParameterHandleValuePairSet( const ParameterHandleValuePairSet &s ) : hv_set(s.hv_set) {}

  virtual ~ParameterHandleValuePairSet() {}

  ParameterHandleValuePairSet &operator=( const ParameterHandleValuePairSet &s )
  {
    hv_set = s.hv_set;
    return *this;
  }

  virtual ULong size() const
  {
    return ((ULong) hv_set.size());
  }

  virtual Handle getHandle( ULong i ) const throw (ArrayIndexOutOfBounds)
  {
    return hv_set[ i ].handle;
  }

  virtual ULong getValueLength( ULong i ) const throw (ArrayIndexOutOfBounds)
  {
    return ((ULong) hv_set[ i ].value.size());
  }

  virtual void getValue( ULong i, char *buff, ULong &length ) const throw (ArrayIndexOutOfBounds)
  {
    for( ULong it = 0; it < length; ++it )
    {
      buff[ it ] = hv_set[ i ].value[ it ];
    }
  }

  virtual char *getValuePointer( ULong i, ULong &length ) const throw (ArrayIndexOutOfBounds)
  {
    length = (ULong) hv_set[ i ].value.size();
    char *buf = (char *) &hv_set[ i ].value[ 0 ];

    return buf;
  }

  virtual TransportType getTransportType() const
  throw (InvalidHandleValuePairSetContext)
  {
    return (TransportType) 0;
  }

  virtual OrderType getOrderType() const
  throw (InvalidHandleValuePairSetContext)
  {
    return (OrderType) 0;
  }

  virtual Region *getRegion() const
  throw (InvalidHandleValuePairSetContext)
  {
    return 0;
  }

  virtual void add( Handle h, const char *buff, ULong length)
  throw (ValueLengthExceeded, ValueCountExceeded)
  {
    pair new_pair;
    new_pair.handle = h;

    for (unsigned i = 0; i < length; ++i)
    {
      new_pair.value.push_back( buff[ i ] );
    }

    hv_set.push_back( new_pair );
  }

  virtual void remove( Handle h ) throw (ArrayIndexOutOfBounds) {}

  virtual void moveFrom( const ParameterHandleValuePairSet &phvps, ULong &i )
  throw (ValueCountExceeded, ArrayIndexOutOfBounds)
  {}

  virtual void empty() {}

  virtual ULong start() const { return 0; }
  virtual ULong valid( ULong i ) const { return (ULong) (i < hv_set.size()); }
  virtual ULong next( ULong i ) const { return i + 1; }
};

/**************************************************************************************************/

class ParameterSetFactory
{
public:
  static ParameterHandleValuePairSet* create( ULong count )
  throw (MemoryExhausted, ValueCountExceeded, HandleValuePairMaximumExceeded)
  {
    return new ParameterHandleValuePairSet(count);
  }
};

/**************************************************************************************************/

class FedTime
{
public:
  virtual ~FedTime() {}
  virtual void setZero() {}
  virtual Boolean isZero() { return RTI_FALSE; }
  virtual void setEpsilon() {}
  virtual void setPositiveInfinity() {};
  virtual Boolean isPositiveInfinity() { return RTI_FALSE; }

  virtual FedTime& operator+=( const FedTime & ) throw (InvalidFederationTime) { return *this; }
  virtual FedTime& operator-=( const FedTime & ) throw (InvalidFederationTime) { return *this; }

  virtual Boolean operator<=( const FedTime & ) const throw (InvalidFederationTime)
  {
    return RTI_FALSE;
  }

  virtual Boolean operator<( const FedTime & ) const throw (InvalidFederationTime)
  {
    return RTI_FALSE;
  }

  virtual Boolean operator>=( const FedTime & ) const throw (InvalidFederationTime)
  {
    return RTI_FALSE;
  }

  virtual Boolean operator>( const FedTime & ) const throw (InvalidFederationTime)
  {
    return RTI_FALSE;
  }

  virtual Boolean operator==( const FedTime & ) const throw (InvalidFederationTime)
  {
    return RTI_FALSE;
  }

  virtual FedTime &operator=( const FedTime & ) throw (InvalidFederationTime) { return *this; }

  //return bytes needed to encode
  virtual int encodedLength() const { return 0; }

  //encode into suppled buffer
  virtual void encode(char *buff) const {}

  virtual int getPrintableLength() const { return 0; }

  virtual void getPrintableString( char * ) {}

};

/**************************************************************************************************/

class FedTimeFactory
{
public:
  static FedTime *makeZero() throw (MemoryExhausted) { return 0; }

  static FedTime *decode( const char *buf ) throw (MemoryExhausted) { return 0; }
};

/**************************************************************************************************/

struct EventRetractionHandle_s
{
  UniqueID       theSerialNumber;
  FederateHandle sendingFederate;
};

/**************************************************************************************************/
typedef struct EventRetractionHandle_s EventRetractionHandle;

/**************************************************************************************************/

/**
 * Object class name to object class handle map type.
 */
typedef std::map< std::string, ObjectClassHandle > name_to_obj_class_handle_map_t;

/**
 * Object instance handle to object class handle map type.
 */
typedef std::map< ObjectHandle, ObjectClassHandle > obj_handle_to_class_handle_map_t;

/**
 * Attribute name to attribute handle map type.
 */
typedef std::map< std::string, AttributeHandle > name_to_attr_handle_map_t;

/**
 * A type used to map an object class handle to an attribute name to attribute handle map.
 */
typedef std::map< ObjectClassHandle, name_to_attr_handle_map_t > obj_class_handle_to_attr_map_map_t;

/**
 * Interaction class name to interaction handle map type.
 */
typedef std::map< std::string, InteractionClassHandle > name_to_inter_class_handle_map_t;

/**
 * Parameter name to parameter handle map type.
 */
typedef std::map< std::string, ParameterHandle > name_to_param_handle_map_t;

/**
 * A type used to map an interaction class handle to a parameter name to parameter handle map.
 */
typedef std::map< InteractionClassHandle, name_to_param_handle_map_t >
  inter_class_handle_to_param_map_map_t;

/**************************************************************************************************/

class RTIambassador;

class RTIexec
{
private:
  friend class RTIambassador;

  struct register_obj
  {
    RTIambassador    *registering_amb;
    ObjectClassHandle obj_class_handle;
    ObjectHandle      obj_handle;
    std::string       obj_name;

    register_obj( RTIambassador     *registering_amb,
                  ObjectClassHandle  obj_class_handle,
                  ObjectHandle       obj_handle,
                  const char        *obj_name )
    : registering_amb(registering_amb),
      obj_class_handle(obj_class_handle),
      obj_handle(obj_handle),
      obj_name(obj_name)
    {}

    register_obj( const register_obj &ro )
    : registering_amb(ro.registering_amb),
      obj_class_handle(ro.obj_class_handle),
      obj_handle(ro.obj_handle),
      obj_name(ro.obj_name)
    {}

    register_obj &operator=( const register_obj &ro )
    {
      registering_amb = ro.registering_amb;
      obj_class_handle = ro.obj_class_handle;
      obj_handle = ro.obj_handle;
      obj_name = ro.obj_name;

      return *this;
    }
  };

  std::vector< register_obj > register_obj_q;

  struct update_obj
  {
    RTIambassador              *updating_amb;
    ObjectHandle                obj_handle;
    AttributeHandleValuePairSet avp_set;

    update_obj( RTIambassador                     *updating_amb,
                ObjectHandle                       obj_handle,
                const AttributeHandleValuePairSet &avp_set )
    : updating_amb(updating_amb),
      obj_handle(obj_handle),
      avp_set(avp_set)
    {}

    update_obj( const update_obj &uo )
    : updating_amb(uo.updating_amb),
      obj_handle(uo.obj_handle),
      avp_set(uo.avp_set)
    {}

    update_obj &operator=( const update_obj &uo )
    {
      updating_amb = uo.updating_amb;
      obj_handle   = uo.obj_handle;
      avp_set      = uo.avp_set;

      return *this;
    }
  };

  std::vector< update_obj > update_obj_q;

  struct send_msg
  {
    RTIambassador              *sending_amb;
    InteractionClassHandle      inter_handle;
    ParameterHandleValuePairSet params;

    send_msg( RTIambassador                    *sending_amb,
              const InteractionClassHandle      inter_handle,
              const ParameterHandleValuePairSet &params )
    : sending_amb(sending_amb),
      inter_handle(inter_handle),
      params(params)
    {}

    send_msg( const send_msg &m )
    : sending_amb(m.sending_amb),
      inter_handle(m.inter_handle),
      params(m.params)
    {}

    send_msg &operator=( const send_msg &m )
    {
      sending_amb = m.sending_amb;
      inter_handle = m.inter_handle;
      params = m.params;

      return *this;
    }
  };

  std::vector< send_msg > send_q;

  ULong next_federate_handle;

  ULong next_class_handle;
  ULong next_attr_handle;
  ULong next_param_handle;

  ULong next_object_handle;

  // Object class and attribute mappings...
  name_to_obj_class_handle_map_t name_to_obj_class_handle_map;
  obj_class_handle_to_attr_map_map_t obj_class_handle_to_attr_map;

  // Object instance mappings...

  obj_handle_to_class_handle_map_t obj_to_class_handle_map;

  // Interaction class and parameter mappings...
  name_to_inter_class_handle_map_t name_to_inter_class_handle_map;
  inter_class_handle_to_param_map_map_t inter_class_handle_to_param_map;

  std::vector< RTIambassador * > rti_amb_vector;

  void add( RTIambassador *amb )
  {
    rti_amb_vector.push_back( amb );
  }

  void send_interaction( RTIambassador                     *sending_amb,
                         InteractionClassHandle             theInteraction,
                         const ParameterHandleValuePairSet &theParameters )
  {
    send_q.push_back( send_msg( sending_amb, theInteraction, theParameters ) );
  }

  ObjectHandle new_object( RTIambassador           *registering_amb,
                           const ObjectClassHandle  object_class,
                           const char              *object_name )
  {
    register_obj_q.push_back( register_obj( registering_amb,
                                            object_class,
                                            next_object_handle,
                                            object_name ) );

    obj_to_class_handle_map[ next_object_handle ] = object_class;

    ++next_object_handle;

    return register_obj_q.back().obj_handle;
  }

  void update_obj_attrs( RTIambassador                     *updating_amb,
                         const ObjectHandle                 obj_handle,
                         const AttributeHandleValuePairSet &avp_set )
  {
    update_obj_q.push_back( update_obj( updating_amb, obj_handle, avp_set ) );
  }

public:
  RTIexec() :
    next_federate_handle(1),
    next_class_handle(1),
    next_attr_handle(1),
    next_param_handle(1),
    next_object_handle(1)
  {}

  void tick()
  {
    // Register objects
    BOOST_FOREACH( const RTI::RTIexec::register_obj &ro, register_obj_q )
    {
      BOOST_FOREACH( RTIambassador *amb, rti_amb_vector )
      {
        amb->register_obj( ro );
      }
    }

    register_obj_q.clear();

    // Update object attributes
    BOOST_FOREACH( const RTI::RTIexec::update_obj &uo, update_obj_q )
    {
      BOOST_FOREACH( RTIambassador *amb, rti_amb_vector )
      {
        amb->update_obj_attrs( uo );
      }
    }

    update_obj_q.clear();

    // Send interactions
    BOOST_FOREACH( const RTI::RTIexec::send_msg &msg, send_q )
    {
      BOOST_FOREACH( RTIambassador *amb, rti_amb_vector )
      {
        amb->recv_inter( msg );
      }
    }

    send_q.clear();
  }
};

/**************************************************************************************************/

/**
 * A very simplistic implementation of some of the services provided by an HLA 1.3 RTI ambassador.
 * This implementation provides the minimum set of services required to test proto-x functionality.
 * The services are not implemented in a standards conforming way. They're behavior is just
 * accurate enough to mimic the behavior of a real HLA RTI.
 *
 * Extreme emphasis is placed on an easy, straightforward implementation of the supplied services.
 *
 */
class RTIambassador
{
private:
  // Off
  RTIambassador();
  RTIambassador( const RTIambassador & );
  RTIambassador &operator=( const RTIambassador & );

private:
  friend class RTIexec;

  RTIexec &rti_exec;

  std::string fed_name;
  FederateHandle fed_handle;
  FederateAmbassadorPtr fed_amb;

  std::vector< ObjectClassHandle >      object_subscription_vector;
  std::vector< InteractionClassHandle > inter_subscription_vector;

private:
  bool is_inter_subscribed( const InteractionClassHandle handle ) const
  {
    BOOST_FOREACH( InteractionClassHandle h, inter_subscription_vector )
    {
      if (h == handle)
      {
        return true;
      }
    }

    return false;
  }

  void recv_inter( const RTIexec::send_msg &msg )
  {
    if (msg.sending_amb == this)
    {
      return;
    }

    if (is_inter_subscribed( msg.inter_handle ))
    {
      fed_amb->receiveInteraction( msg.inter_handle, msg.params, "" );
    }
  }

  bool is_class_subscribed( const ObjectClassHandle handle ) const
  {
    BOOST_FOREACH( ObjectClassHandle h, object_subscription_vector )
    {
      if (h == handle)
      {
        return true;
      }
    }

    return false;
  }

  void register_obj( const RTIexec::register_obj &msg )
  {
    if (msg.registering_amb == this)
    {
      return;
    }

    if (is_class_subscribed( msg.obj_class_handle ))
    {
      fed_amb->discoverObjectInstance( msg.obj_handle, msg.obj_class_handle, msg.obj_name.c_str() );
    }
  }

  void update_obj_attrs( const RTIexec::update_obj &msg )
  {
    if (msg.updating_amb == this)
    {
      return;
    }

    const ObjectClassHandle obj_class_handle = rti_exec.obj_to_class_handle_map[ msg.obj_handle ];

    if (is_class_subscribed( obj_class_handle ))
    {
      fed_amb->reflectAttributeValues( msg.obj_handle, msg.avp_set, "" );
    }
  }

public:
  RTIambassador(RTIexec &rti_exec) : rti_exec(rti_exec), fed_handle(0), fed_amb(0)
  {
    rti_exec.add( this );
  }

  ////////////////////////////////////
  // Federation Management Services //
  ////////////////////////////////////

  /**
   * Caveats:
   *   \a execution_name is ignored.
   *   Does not check to see if the federate is already joined.
   */
  FederateHandle joinFederationExecution( const char           *federate_name,
                                          const char           *execution_name,
                                          FederateAmbassadorPtr federate_ambassador_reference )
  throw (FederateAlreadyExecutionMember,
         FederationExecutionDoesNotExist,
         CouldNotOpenFED,
         ErrorReadingFED,
         ConcurrentAccessAttempted,
         SaveInProgress,
         RestoreInProgress,
         RTIinternalError)
  {
    fed_name = federate_name;

    fed_handle = rti_exec.next_federate_handle;
    ++rti_exec.next_federate_handle;

    fed_amb = federate_ambassador_reference;

    return fed_handle;
  }

  //////////////////////////
  // RTI Support Services //
  //////////////////////////

  /**
   * Returns the handle assigned to the given object class name. Object class handles are assigned
   * when they are requested for the first time.
   *
   * Example:
   *
   * \code
   * getObjectClassHandle( "my_class" ) // first call, assigns 5 to "my_class"
   * ...
   * getObjectClassHandle( "my_class" ) // returns 5
   * \endcode
   *
   * Names must be fully qualified to prevent assignment of multiple handle values to the same
   * class.
   *
   * Example:
   *
   * \code
   * getObjectClassHandle( "a.b.c" ) // first call, assigns 7 to class "a.b.c" returns 7.
   *
   * getObjectClassHandle( "c" ) // Technically, this is the same as class "a.b.c", but this call
   *                             // DOES NOT return 7. Class "c" is treated as a new class and is
   *                             // assigned a new handle value.
   * \endcode
   *
   * \param name A _fully qualified_ object class name.
   *
   * \return The handle assigned to the given object class name.
   */
  ObjectClassHandle getObjectClassHandle( const char *name )
  throw (NameNotFound, FederateNotExecutionMember, ConcurrentAccessAttempted, RTIinternalError)
  {
    // First request for this class' handle?
    if (rti_exec.name_to_obj_class_handle_map.find( name ) == rti_exec.name_to_obj_class_handle_map.end())
    {
      rti_exec.name_to_obj_class_handle_map[ name ] = rti_exec.next_class_handle;
      ++rti_exec.next_class_handle;
    }

    return rti_exec.name_to_obj_class_handle_map[ name ];
  }

  /**
   * \return The handle assigned to the named attribute for the identified object class.
   */
  AttributeHandle getAttributeHandle( const char *name, ObjectClassHandle class_handle )
  throw (ObjectClassNotDefined,
         NameNotFound,
         FederateNotExecutionMember,
         ConcurrentAccessAttempted,
         RTIinternalError)
  {
    // First request made against this handle?
    if (rti_exec.obj_class_handle_to_attr_map.find( class_handle ) ==
        rti_exec.obj_class_handle_to_attr_map.end())
    {
      rti_exec.obj_class_handle_to_attr_map[ class_handle ] = name_to_attr_handle_map_t();
    }

    // First request made for this attribute name?
    if (rti_exec.obj_class_handle_to_attr_map[ class_handle ].find( name )
        == rti_exec.obj_class_handle_to_attr_map[ class_handle ].end())
    {
      rti_exec.obj_class_handle_to_attr_map[ class_handle ][ name ] = rti_exec.next_attr_handle;
      ++rti_exec.next_attr_handle;
    }

    return rti_exec.obj_class_handle_to_attr_map[ class_handle ][ name ];
  }

  /**
   * Returns the handle assigned to the given interaction class name. Interaction class handles are
   * assigned when they are requested for the first time.
   *
   * Example:
   *
   * \code
   * getInteractionClassHandle( "my_class" ) // first call, assigns 5 to "my_class"
   * ...
   * getInteractionClassHandle( "my_class" ) // returns 5
   * \endcode
   *
   * Names must be fully qualified to prevent assignment of multiple handle values to the same
   * class.
   *
   * Example:
   *
   * \code
   * getObjectClassHandle( "a.b.c" ) // first call, assigns 7 to class "a.b.c" returns 7.
   *
   * getObjectClassHandle( "c" ) // Technically, this is the same as class "a.b.c", but this call
   *                             // DOES NOT return 7. Class "c" is treated as a new class and is
   *                             // assigned a new handle value.
   * \endcode
   *
   * \param name A _fully qualified_ interaction class name.
   *
   * \return The handle assigned to the given interaction class name.
   */
  InteractionClassHandle getInteractionClassHandle( const char *name )
  throw (NameNotFound, FederateNotExecutionMember, ConcurrentAccessAttempted, RTIinternalError)
  {
    // First request for this class' handle?
    if (rti_exec.name_to_inter_class_handle_map.find( name ) ==
        rti_exec.name_to_inter_class_handle_map.end())
    {
      rti_exec.name_to_inter_class_handle_map[ name ] = rti_exec.next_class_handle;
      ++rti_exec.next_class_handle;
    }

    return rti_exec.name_to_inter_class_handle_map[ name ];
  }

  /**
   * \return The handle assigned to the named attribute for the identified object class.
   */
  ParameterHandle getParameterHandle( const char *name, InteractionClassHandle class_handle )
  throw (InteractionClassNotDefined,
         NameNotFound,
         FederateNotExecutionMember,
         ConcurrentAccessAttempted,
         RTIinternalError)
  {
    if (rti_exec.inter_class_handle_to_param_map.find( class_handle ) ==
        rti_exec.inter_class_handle_to_param_map.end())
    {
      rti_exec.inter_class_handle_to_param_map[ class_handle ] = name_to_param_handle_map_t();
    }

    if (rti_exec.inter_class_handle_to_param_map[ class_handle ].find( name ) ==
        rti_exec.inter_class_handle_to_param_map[ class_handle ].end())
    {
      rti_exec.inter_class_handle_to_param_map[ class_handle ][ name ] = rti_exec.next_param_handle;
      ++rti_exec.next_param_handle;
    }

    return rti_exec.inter_class_handle_to_param_map[ class_handle ][ name ];
  }

  /////////////////////////////////////
  // Declaration Management Services //
  /////////////////////////////////////

  void publishObjectClass( ObjectClassHandle theClass, const AttributeHandleSet& attributeList )
  throw (ObjectClassNotDefined,
         AttributeNotDefined,
         OwnershipAcquisitionPending,
         FederateNotExecutionMember,
         ConcurrentAccessAttempted,
         SaveInProgress,
         RestoreInProgress,
         RTIinternalError)
  {}

  // 5.3
  void unpublishObjectClass( ObjectClassHandle theClass )
  throw (ObjectClassNotDefined,
         ObjectClassNotPublished,
         OwnershipAcquisitionPending,
         FederateNotExecutionMember,
         ConcurrentAccessAttempted,
         SaveInProgress,
         RestoreInProgress,
         RTIinternalError)
  {}

  void publishInteractionClass( InteractionClassHandle the_interaction )
  throw (InteractionClassNotDefined,
         FederateNotExecutionMember,
         ConcurrentAccessAttempted,
         SaveInProgress,
         RestoreInProgress,
         RTIinternalError)
  {}

  // 5.5
  void unpublishInteractionClass( InteractionClassHandle theInteraction )
  throw (InteractionClassNotDefined,
         InteractionClassNotPublished,
         FederateNotExecutionMember,
         ConcurrentAccessAttempted,
         SaveInProgress,
         RestoreInProgress,
         RTIinternalError)
  {}

  // 5.6
  void subscribeObjectClassAttributes( ObjectClassHandle         the_class,
                                       const AttributeHandleSet &attr_list,
                                       Boolean                   active = RTI_TRUE )
  throw (ObjectClassNotDefined,
         AttributeNotDefined,
         FederateNotExecutionMember,
         ConcurrentAccessAttempted,
         SaveInProgress,
         RestoreInProgress,
         RTIinternalError)
  {
    // Support class level subscription only, for now.
    object_subscription_vector.push_back( the_class );
  }

  // 5.7
  void unsubscribeObjectClas ( ObjectClassHandle theClass )
  throw (ObjectClassNotDefined,
         ObjectClassNotSubscribed,
         FederateNotExecutionMember,
         ConcurrentAccessAttempted,
         SaveInProgress,
         RestoreInProgress,
         RTIinternalError);

  // 5.8
  void subscribeInteractionClass( InteractionClassHandle the_class, Boolean active = RTI_TRUE )
  throw (InteractionClassNotDefined,
         FederateNotExecutionMember,
         ConcurrentAccessAttempted,
         FederateLoggingServiceCalls,
         SaveInProgress,
         RestoreInProgress,
         RTIinternalError)
  {
    inter_subscription_vector.push_back( the_class );
  }

  // 5.9
  void unsubscribeInteractionClass( InteractionClassHandle theClass )
  throw (InteractionClassNotDefined,
         InteractionClassNotSubscribed,
         FederateNotExecutionMember,
         ConcurrentAccessAttempted,
         SaveInProgress,
         RestoreInProgress,
         RTIinternalError);

  ////////////////////////////////
  // Object Management Services //
  ////////////////////////////////

  // 6.2
  ObjectHandle registerObjectInstance( ObjectClassHandle the_class, const char *the_obj )
  throw (ObjectClassNotDefined,
         ObjectClassNotPublished,
         ObjectAlreadyRegistered,
         FederateNotExecutionMember,
         ConcurrentAccessAttempted,
         SaveInProgress,
         RestoreInProgress,
         RTIinternalError)
  {
    return rti_exec.new_object( this, the_class, the_obj );
  }

  ObjectHandle registerObjectInstance( ObjectClassHandle the_class )
  throw (ObjectClassNotDefined,
         ObjectClassNotPublished,
         FederateNotExecutionMember,
         ConcurrentAccessAttempted,
         SaveInProgress,
         RestoreInProgress,
         RTIinternalError)
  {
    return registerObjectInstance( the_class, "" );
  }

  // 6.4
  EventRetractionHandle updateAttributeValues(       ObjectHandle                 the_obj,
                                               const AttributeHandleValuePairSet &the_attrs,
                                               const FedTime                     &the_time,
                                               const char                        *the_tag )
  throw (ObjectNotKnown,
         AttributeNotDefined,
         AttributeNotOwned,
         InvalidFederationTime,
         FederateNotExecutionMember,
         ConcurrentAccessAttempted,
         SaveInProgress,
         RestoreInProgress,
         RTIinternalError)
  {
    updateAttributeValues( the_obj, the_attrs, the_tag );

    return EventRetractionHandle();
  }

  void updateAttributeValues(       ObjectHandle                 the_obj,
                              const AttributeHandleValuePairSet &the_attrs,
                              const char                        *the_tag)
  throw (ObjectNotKnown,
         AttributeNotDefined,
         AttributeNotOwned,
         FederateNotExecutionMember,
         ConcurrentAccessAttempted,
         SaveInProgress,
         RestoreInProgress,
         RTIinternalError)
  {
    rti_exec.update_obj_attrs( this, the_obj, the_attrs );
  }

  // 6.6
  EventRetractionHandle
  sendInteraction(       InteractionClassHandle       the_interaction,
                   const ParameterHandleValuePairSet &the_params,
                   const FedTime                     &the_time,
                   const char                        *the_tag )
  throw (InteractionClassNotDefined,
         InteractionClassNotPublished,
         InteractionParameterNotDefined,
         InvalidFederationTime,
         FederateNotExecutionMember,
         ConcurrentAccessAttempted,
         SaveInProgress,
         RestoreInProgress,
         RTIinternalError)
  {
    sendInteraction( the_interaction, the_params, the_tag );

    return EventRetractionHandle();
  }

  void sendInteraction( InteractionClassHandle             the_interaction,
                        const ParameterHandleValuePairSet &the_params,
                        const char                        *the_tag )
  throw (InteractionClassNotDefined,
         InteractionClassNotPublished,
         InteractionParameterNotDefined,
         FederateNotExecutionMember,
         ConcurrentAccessAttempted,
         SaveInProgress,
         RestoreInProgress,
         RTIinternalError)
  {
    rti_exec.send_interaction( this, the_interaction, the_params );
  }

  // 6.8
  EventRetractionHandle deleteObjectInstance(       ObjectHandle  the_obj,
                                              const FedTime      &the_time,
                                              const char         *the_tag )
  throw (ObjectNotKnown,
         DeletePrivilegeNotHeld,
         InvalidFederationTime,
         FederateNotExecutionMember,
         ConcurrentAccessAttempted,
         SaveInProgress,
         RestoreInProgress,
         RTIinternalError)
  {
    deleteObjectInstance( the_obj, the_tag );

    return EventRetractionHandle();
  }

  void deleteObjectInstance(       ObjectHandle  the_obj,
                             const char         *the_tag )
  throw (ObjectNotKnown,
         DeletePrivilegeNotHeld,
         FederateNotExecutionMember,
         ConcurrentAccessAttempted,
         SaveInProgress,
         RestoreInProgress,
         RTIinternalError)
  {}
};

/**************************************************************************************************/

class FederateAmbassador
{
public:
  virtual void federationSynchronized( const char *label ) throw (FederateInternalError) {}

  ////////////////////////////////
  // Object Management Services //
  ////////////////////////////////

  virtual void discoverObjectInstance(       RTI::ObjectHandle       the_obj,
                                             RTI::ObjectClassHandle  the_obj_class,
                                       const char                   *the_obj_name )
  throw (RTI::CouldNotDiscover,
         RTI::ObjectClassNotKnown,
         RTI::FederateInternalError)
  {}

  virtual void reflectAttributeValues(       RTI::ObjectHandle                 theObject,
                                       const RTI::AttributeHandleValuePairSet &theAttributes,
                                       const RTI::FedTime                     &theTime,
                                       const char                             *theTag,
                                             RTI::EventRetractionHandle        theHandle )
  throw (RTI::ObjectNotKnown,
         RTI::AttributeNotKnown,
         RTI::FederateOwnsAttributes,
         RTI::InvalidFederationTime,
         RTI::FederateInternalError)
  {}

  virtual void reflectAttributeValues(       RTI::ObjectHandle                 theObject,
                                       const RTI::AttributeHandleValuePairSet &theAttributes,
                                       const char                             *theTag )
  throw (RTI::ObjectNotKnown,
         RTI::AttributeNotKnown,
         RTI::FederateOwnsAttributes,
         RTI::FederateInternalError)
  {}

  virtual void receiveInteraction(       RTI::InteractionClassHandle       theInteraction,
                                   const RTI::ParameterHandleValuePairSet &theParameters,
                                   const RTI::FedTime                     &theTime,
                                   const char                             *theTag,
                                         RTI::EventRetractionHandle        theHandle )
  throw (RTI::InteractionClassNotKnown,
         RTI::InteractionParameterNotKnown,
         RTI::InvalidFederationTime,
         RTI::FederateInternalError)
  {}

  virtual void receiveInteraction(       RTI::InteractionClassHandle       theInteraction,
                                   const RTI::ParameterHandleValuePairSet &theParameters,
                                   const char                             *theTag )
  throw (RTI::InteractionClassNotKnown,
         RTI::InteractionParameterNotKnown,
         RTI::FederateInternalError)
  {}
};

/**************************************************************************************************/

};

/**************************************************************************************************/

#endif

/**************************************************************************************************/
