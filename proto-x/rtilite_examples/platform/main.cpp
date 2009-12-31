/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#include <RTI.hh>

#include <vector>
#include <iostream>
#include <string>

#include <boost/foreach.hpp>

#include <protox/hla_1516/basic_data_representation_table.hpp>
#include "protox/hla_1516/enumerated.hpp"
#include <protox/hla_1516/fixed_record.hpp>
#include <protox/hla/attr.hpp>
#include <protox/hla/param.hpp>
#include <protox/hla/keywords.hpp>
#include <protox/hla/name.hpp>
#include <protox/hla/i_class.hpp>
#include <protox/hla/o_class.hpp>
#include <protox/hla/i_class_type.hpp>
#include <protox/hla/o_class_type.hpp>
#include <protox/hla/som.hpp>
#include <protox/hla/interaction_amb.hpp>
#include <protox/hla/object_amb.hpp>

#include <protox/dtl/simple.hpp>
#include "protox/dtl/enum_pp.hpp"

/**************************************************************************************************/

using namespace boost;

using namespace protox;
using namespace protox::hla;
using namespace protox::dtl;
using namespace protox::hla_1516;

/**************************************************************************************************/

//// Simple Datatatype Table ///////////////////////////////////////////////////////////////////////
//   +----------+-------------------------+----------+
//   | Name     | Representation          | Units    |
//   +----------+-------------------------+----------+
struct Distance : simple< HLAfloat32BE,     unitless > {PROTOX_SIMPLE( Distance )};
//   +----------+-------------------------+----------+
struct Int16    : simple< HLAinteger16BE,   unitless > {PROTOX_SIMPLE( Int16    )};
//   +----------+-------------------------+----------+

/**************************************************************************************************/

//      +------------+-----------------------------------------------+------------+--------+
//      | Name       | Representation                                | Enumerator | Values |
//      +------------+-----------------------------------------------+------------+--------+
namespace ColorEnum  { PROTOX_ENUM_TYPE( HLAinteger16BE, hla_1516::enumerated );
//      +------------+-----------------------------------------------+------------+--------+
                                                    PROTOX_ENUM_VALUE( RED,         1     );
//                                                                   +------------+--------+
                                                    PROTOX_ENUM_VALUE( GREEN,       2     );
//                                                                   +------------+--------+
                                                    PROTOX_ENUM_VALUE( BLUE,        3     );
//      +------------+-----------------------------------------------+------------+--------+

PROTOX_ENUM_EQUALITY_OPERATOR;
PROTOX_ENUM_DEFAULT( BLUE );

}

/**************************************************************************************************/

//      +----------------+-----------------------------+------------------------+
//      |                | Field                       |                        |
//      | Record         +-------+---------------------+ Encoding               |
//      | name           | Name  | Type                |                        |
//      +----------------+-------+---------------------+------------------------+
namespace PositionVector {
//      +----------------+-------+---------------------+
                    struct X     : field< Distance > {};
//                       +-------+---------------------+
                    struct Y     : field< Distance > {};
//      +----------------+-------+---------------------+
                                           struct type : hla_1516::fixed_record < mpl::vector< X, Y > > {};}
//      +----------------------------------------------+------------------------+

/**************************************************************************************************/

////// Attribute Table /////////////////////////////////////////////////////////////////////////////
//     +--------------------------------------------+----------------------------+------------------------------+-------------------------------------------+
//     | Name                                       | Attribute                  | Datatype                     | String Name                               |
//     +--------------------------------------------+----------------------------+------------------------------+-------------------------------------------+
  struct HLAobjectRoot {HLA_NAME( "HLAobjectRoot" )};
                                               struct HLAprivilegeToDeleteObject : attr< hla_1516::HLAoctet   >   {HLA_NAME( "HLAprivilegeToDeleteObject" )};
//     +--------------------------------------------+----------------------------+------------------------------+-------------------------------------------+
  struct Platform      {HLA_NAME( "Platform" )};
                                               struct Position                   : attr< PositionVector::type >   {HLA_NAME( "Position"                   )};
//                                                  +----------------------------+------------------------------+-------------------------------------------+
                                               struct Color                      : attr< ColorEnum::Type      >   {HLA_NAME( "Color"                      )};
//     +--------------------------------------------+----------------------------+------------------------------+-------------------------------------------+

/**************************************************************************************************/

//// Object Class Table ////////////////////////////////////////////////////////////////////////////
   struct obj_class_table : o_class< HLAobjectRoot, attrs< HLAprivilegeToDeleteObject >, child<
// +------------------+
// | Class 1          |
// +------------------+
   o_class< Platform,   attrs< Position, Color > > > > {};
// +------------------+

/**************************************************************************************************/

//////// Parameter Table ///////////////////////////////////////////////////////////////////////////
//     +------------------------------------------------------+-----------+-----------------+-------------------------+
//     | Name                                                 | Parameter | Datatype        | String Name             |
//     +------------------------------------------------------+-----------+-----------------+-------------------------+
  struct HLAinteractionRoot {HLA_NAME( "HLAinteractionRoot" )};
//     +------------------------------------------------------+-----------+-----------------+-------------------------+
  struct StartMsg           {HLA_NAME( "StartMsg"           )};
                                                         struct quantity  : param < Int16 >   {HLA_NAME( "quantity" )};
//     +------------------------------------------------------+-----------+-----------------+-------------------------+

/**************************************************************************************************/

//// Interaction Class Table ///////////////////////////////////////////////////////////////////////
   struct inter_class_table : i_class< HLAinteractionRoot, none, child<
// +------------------+
// | Class 1          |
// +------------------+
   i_class< StartMsg,   params< quantity > > > > {};
// +------------------+

/**************************************************************************************************/

typedef protox::hla::som< obj_class_table, inter_class_table > platform_som;

/**************************************************************************************************/

// Platform object class type
typedef o_class_type< platform_som, q_name< Platform > >::type platform_type;

// StartMsg interaction class type
typedef i_class_type< platform_som, q_name< StartMsg > >::type start_msg_type;

/**************************************************************************************************/

static int num_platforms;

void start_msg_handler( const start_msg_type &start_msg, const RTI::FedTime *, const char * )
{
  std::cout << "Start message received. Quantity = " << start_msg.p_< quantity >() << "\n";
  num_platforms = start_msg.p_< quantity >();
}

/**************************************************************************************************/

// An interaction ambassador used to register callbacks that are invoked by interaction class
// type.
typedef hla::interaction_amb< mpl::vector< start_msg_type > >::type inter_amb_type;


// An object ambassador used to manage object's that are discovered during runtime.
typedef hla::object_amb< mpl::vector< platform_type > >::type obj_amb_type;

/**************************************************************************************************/

class fed_amb : public RTI::FederateAmbassador
{
private:
  obj_amb_type   &obj_amb;
  inter_amb_type &inter_amb;

public:
  fed_amb( obj_amb_type &obj_amb, inter_amb_type &inter_amb )
    : obj_amb(obj_amb),
      inter_amb(inter_amb)
  {}

  virtual ~fed_amb() throw( RTI::FederateInternalError ) {}

  //////////////////////////////////////////////////////////////////////////////////////////////////
   // Object Management Services
   //////////////////////////////////////////////////////////////////////////////////////////////////

   virtual void discoverObjectInstance( RTI::ObjectHandle      the_object,
                                        RTI::ObjectClassHandle the_object_class,
                                        const char*            the_object_name )
   throw( RTI::CouldNotDiscover,
          RTI::ObjectClassNotKnown,
          RTI::FederateInternalError )
   {
     obj_amb.discover_object( the_object_class, the_object, the_object_name );
   }

   virtual void reflectAttributeValues( RTI::ObjectHandle                       the_object,
                                        const RTI::AttributeHandleValuePairSet &the_attributes,
                                        const RTI::FedTime&                     the_time,
                                        const char                             *the_tag,
                                        RTI::EventRetractionHandle              the_handle )
   throw( RTI::ObjectNotKnown,
          RTI::AttributeNotKnown,
          RTI::FederateOwnsAttributes,
          RTI::InvalidFederationTime,
          RTI::FederateInternalError )
   {
     obj_amb.reflect_object( the_object, the_attributes, &the_time, the_tag );
   }

   virtual void reflectAttributeValues( RTI::ObjectHandle                       the_object,
                                        const RTI::AttributeHandleValuePairSet &the_attributes,
                                        const char                             *the_tag )
   throw( RTI::ObjectNotKnown,
          RTI::AttributeNotKnown,
          RTI::FederateOwnsAttributes,
          RTI::FederateInternalError )
   {
     obj_amb.reflect_object( the_object, the_attributes, 0, the_tag );
   }

   virtual void removeObjectInstance( RTI::ObjectHandle          the_object,
                                      const RTI::FedTime&        the_time,
                                      const char                *the_tag,
                                      RTI::EventRetractionHandle the_handle )
   throw( RTI::ObjectNotKnown,
          RTI::InvalidFederationTime,
          RTI::FederateInternalError )
   {
     // Ignore time
     removeObjectInstance( the_object, the_tag );
   }

   virtual void removeObjectInstance ( RTI::ObjectHandle the_object, const char *the_tag )
   throw( RTI::ObjectNotKnown,
          RTI::FederateInternalError )
   {
     obj_amb.remove_object( the_object );
   }

  virtual void receiveInteraction( RTI::InteractionClassHandle             theInteraction,
                                   const RTI::ParameterHandleValuePairSet &theParameters,
                                   const RTI::FedTime                     &theTime,
                                   const char                             *theTag,
                                   RTI::EventRetractionHandle              theHandle )
  throw( RTI::InteractionClassNotKnown,
         RTI::InteractionParameterNotKnown,
         RTI::InvalidFederationTime,
         RTI::FederateInternalError )
  {
    inter_amb.recv_interaction( theInteraction, theParameters, &theTime, theTag );
  }

  virtual void receiveInteraction( RTI::InteractionClassHandle theInteraction,
                                   const RTI::ParameterHandleValuePairSet& theParameters,
                                   const char *theTag )
  throw (RTI::InteractionClassNotKnown,
         RTI::InteractionParameterNotKnown,
         RTI::FederateInternalError)
  {
    unsigned count = theParameters.size();
    inter_amb.recv_interaction( theInteraction, theParameters, 0, theTag );
  }
};

/**************************************************************************************************/

static void dump_platforms( obj_amb_type obj_amb )
{
  using namespace PositionVector;

  obj_amb_type::const_it< platform_type >::type it;

  unsigned count = 0;

  for (it = obj_amb.begin< platform_type >(); it != obj_amb.end< platform_type >(); ++it)
  {
    const platform_type &p = it->second;

    // Not stopped?
    if (p.a_< Color >() != ColorEnum::RED::value())
    {
      std::cout << p.get_obj_name().c_str()
                << " @ ("
                << p.a_< Position >().f_< X >()
                << ", "
                << p.a_< Position >().f_< Y >()
                << ")\n";
    }
    else
    {
      std::cout << p.get_obj_name().c_str() << " stopped\n";
    }

    ++count;
  }
}

/**************************************************************************************************/

int main( int argc, char *argv[] )
{
  num_platforms = 0;
  std::vector< platform_type > platforms;

  // The "fake" RTI exec used to mimic HLA data exchanges
  RTI::RTIexec rti_exec;

  obj_amb_type obj_amb;

  // Register the callbacks that get invoked based on interaction class type
  inter_amb_type inter_amb;
  inter_amb.set_handler( start_msg_handler );

  // The sender federate
  RTI::RTIambassador send_rti_amb( rti_exec );
  fed_amb send_fed_amb( obj_amb, inter_amb );

  platform_som::init_handles( send_rti_amb );
  send_rti_amb.joinFederationExecution( "", "platform_sender", &send_fed_amb );

  // The receiver federate
  RTI::RTIambassador recv_rti_amb( rti_exec );
  fed_amb recv_fed_amb( obj_amb, inter_amb );

  recv_rti_amb.joinFederationExecution( "", "platform_receiver", &recv_fed_amb );

  // Declare interests...
  start_msg_type::subscribe( send_rti_amb );
  start_msg_type::publish( recv_rti_amb );

  platform_type::publish( send_rti_amb );
  platform_type::subscribe( recv_rti_amb );

  // Run...
  start_msg_type start_msg( recv_rti_amb );
  start_msg.p_< quantity >() = 7;
  start_msg.send();

  rti_exec.tick();

  platforms.resize( num_platforms );

  int count = 0;

  BOOST_FOREACH( platform_type &p, platforms )
  {
    std::stringstream str;
    str << "Platform." << count;
    ++count;
    std::string name = str.str();

    p.set_rti( send_rti_amb );
    p.register_obj( name.c_str() );
  }

  rti_exec.tick();

  using namespace PositionVector;

  // Initialize platforms
  std::cout << "Initialize the platforms...\n";

  count = 0;

  BOOST_FOREACH( platform_type &p, platforms )
  {
    p.a_< Position >().f_< X >() = (float) (count + 1);
    p.a_< Position >().f_< Y >() = (float) (count + 1);
    p.a_< Color    >()           = ColorEnum::GREEN::value();

    ++count;

    p.update();
  }

  rti_exec.tick();

  dump_platforms( obj_amb );

  // Move the platforms 20 times
  std::cout << "Move the platforms...\n";

  for (int i = 0; i < 20; ++i)
  {
    BOOST_FOREACH( platform_type &p, platforms )
    {
      p.a_< Position >().f_< X >() += 1.0f;
      p.a_< Position >().f_< Y >() += 2.0f;

      p.update();
    }

    rti_exec.tick();

    dump_platforms( obj_amb );
  }

  // Stop all platforms
  std::cout << "Stop the platforms...\n";

  BOOST_FOREACH( platform_type &p, platforms )
  {
    p.a_< Color >() = ColorEnum::RED::value();
    p.update();
  }

  rti_exec.tick();

  dump_platforms( obj_amb );

  // Remove all platforms
  std::cout << "Remove the platforms...\n";

  BOOST_FOREACH( platform_type &p, platforms ) { p.delete_obj(); }

  rti_exec.tick();

  return 0;
}

/**************************************************************************************************/
