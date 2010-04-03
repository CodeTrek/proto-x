// /////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
//    or http://www.opensource.org/licenses/mit-license.php)

/**************************************************************************************************/

#include <RTI.hh>

#include <vector>
#include <iostream>
#include <string>

#include <protox/dtl/simple.hpp>

#include <protox/hla_1516/basic_data_representation_table.hpp>
#include <protox/hla_1516/variable_array.hpp>

#include <protox/hla/param.hpp>
#include <protox/hla/keywords.hpp>
#include <protox/hla/name.hpp>
#include <protox/hla/i_class.hpp>
#include <protox/hla/som.hpp>
#include <protox/hla/i_class_type.hpp>
#include <protox/hla/interaction_amb.hpp>

/**************************************************************************************************/

using namespace boost;

using namespace protox;
using namespace protox::hla;
using namespace protox::dtl;
using namespace protox::hla_1516;

/**************************************************************************************************/

//// Simple Datatatype Table ///////////////////////////////////////////////////////////////////////
//   +-----------+-------------------+----------+
//   | Name      | Representation    | Units    |
//   +-----------+-------------------+----------+
struct ASCIIchar : simple< HLAoctet,   unitless > {PROTOX_SIMPLE( ASCIIchar )};
//   +-----------+-------------------+----------+

//// Array Table ///////////////////////////////////////////////////////////////////////////////////
//   +-------------+--------------------------------------+-----------------+-------------+
//   | Name        | Encoding                             | Element type    | Cardinality |
//   +-------------+--------------------------------------+-----------------+-------------+
struct ASCIIString : hla_1516::variable_array< std::vector< ASCIIchar > > {}; // Dynamic  |
//   +-------------+--------------------------------------+-----------------+-------------+

//////// Parameter Table ///////////////////////////////////////////////////////////////////////////
//   +------------------------------------------------------+-----------+---------------------+--------------------------+
//   | Name                                                 | Parameter | Datatype            | String Name              |
//   +------------------------------------------------------+-----------+---------------------+--------------------------+
struct HLAinteractionRoot {HLA_NAME( "HLAinteractionRoot" )};
//   +------------------------------------------------------+-----------+---------------------+--------------------------+
struct Greeting           {HLA_NAME( "Greeting" )};
                                                       struct message   : param < ASCIIString > {HLA_NAME( "message" )};
//   +------------------------------------------------------+-----------+---------------------+--------------------------+

//// Interaction Class Table ///////////////////////////////////////////////////////////////////////
struct inter_class_table : i_class< HLAinteractionRoot, none, child<
// +------------------+
// | Class 1          |
// +------------------+
   i_class< Greeting,   params< message > > > > {};
// +------------------+

/**************************************************************************************************/

// The SOM
typedef protox::hla::som< null_o_class, inter_class_table > hw_som;

/**************************************************************************************************/

// A type representing a Greeting interaction
typedef i_class_type< hw_som, q_name< Greeting > >::type greeting_type;

/**************************************************************************************************/

// An interaction ambassador used to register callbacks that are invoked by interaction class
// type.
typedef hla::interaction_amb< mpl::vector< greeting_type > >::type inter_amb_type;

/**************************************************************************************************/

class fed_amb : public RTI::FederateAmbassador
{
private:
  inter_amb_type &inter_amb;

public:
  fed_amb( inter_amb_type &inter_amb ) : inter_amb( inter_amb ) {}

  virtual ~fed_amb() throw( RTI::FederateInternalError ) {}

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
    inter_amb.recv_interaction( theInteraction, theParameters, 0, theTag );
  }
};

/**************************************************************************************************/

static void greeting_handler( const greeting_type &greeting, const RTI::FedTime *, const char * )
{
  std::string str( greeting.p_< message >().begin(), greeting.p_< message >().end() );

  std::cout << "greeting : " << str.c_str() << " ";
}

/**************************************************************************************************/

int main( int argc, char *argv[] )
{
  // The "fake" RTI exec used to mimic HLA data exchanges
  RTI::RTIexec rti_exec;

  // Create an interaction ambassador and register our interaction callback.
  inter_amb_type inter_amb;
  inter_amb.set_handler( greeting_handler );

  // /////////////////////////////////////////////
  // SENDER FEDERATE
  // /////////////////////////////////////////////
  RTI::RTIambassador send_rti_amb( rti_exec );
  fed_amb send_fed_amb( inter_amb );

  //
  // Initialize handles
  //
  hw_som::init_handles( send_rti_amb );

  //
  // Join federation
  //
  send_rti_amb.joinFederationExecution( "", "sender", &send_fed_amb );

  //
  // Publish interaction
  //
  greeting_type::publish( send_rti_amb );

  // /////////////////////////////////////////////
  // RECEIVER FEDERATE
  // /////////////////////////////////////////////
  RTI::RTIambassador recv_rti_amb( rti_exec );
  fed_amb recv_fed_amb(inter_amb);

  //
  // Join federation
  //
  recv_rti_amb.joinFederationExecution( "", "receiver", &recv_fed_amb );

  //
  // Subscribe interaction
  //
  greeting_type::subscribe( recv_rti_amb );

  // /////////////////////////////////////////////
  // RUN...
  // /////////////////////////////////////////////
  greeting_type send_msg( send_rti_amb );

  const std::string what_up = "What up?";

  (ASCIIString::array_type &) send_msg.p_< message >()
    = ASCIIString::array_type( what_up.begin(), what_up.end() );

  send_msg.send();

  rti_exec.tick();

  return 0;
}

/**************************************************************************************************/
