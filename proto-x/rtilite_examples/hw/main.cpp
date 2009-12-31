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

#include <protox/hla_1516/basic_data_representation_table.hpp>
#include <protox/dtl/simple.hpp>
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
//     +------------------------------------------------------+-----------+---------------------+--------------------------+
//     | Name                                                 | Parameter | Datatype            | String Name              |
//     +------------------------------------------------------+-----------+---------------------+--------------------------+
  struct HLAinteractionRoot {HLA_NAME( "HLAinteractionRoot" )};
//     +------------------------------------------------------+-----------+---------------------+--------------------------+
  struct Greeting           {HLA_NAME( "Greeting" )
                                                         struct message   : param < ASCIIString > {HLA_NAME( "message" )};};
//     +------------------------------------------------------+-----------+---------------------+--------------------------+
  struct Response           {HLA_NAME( "Response" )
                                                         struct message   : param < ASCIIString > {HLA_NAME( "message" )};};
//     +------------------------------------------------------+-----------+---------------------+--------------------------+

//// Interaction Class Table ///////////////////////////////////////////////////////////////////////
   struct inter_class_table : i_class< HLAinteractionRoot, none, child<
// +------------------+
// | Class 1          |
// +------------------+
   i_class< Greeting,   params< Greeting::message > >,
// +------------------+
   i_class< Response,   params< Response::message > > > > {};
// +------------------+

/**************************************************************************************************/

// The SOM
typedef protox::hla::som< null_o_class, inter_class_table > hw_som;

/**************************************************************************************************/

// A type representing a Greeting interaction
typedef i_class_type< hw_som, q_name< Greeting > >::type greeting_type;

// A type representing a Response interaction
typedef i_class_type< hw_som, q_name< Response > >::type response_type;

/**************************************************************************************************/

// An interaction ambassador used to register callbacks that are invoked by interaction class
// type.
typedef hla::interaction_amb< mpl::vector< greeting_type, response_type > >::type inter_amb_type;

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
    unsigned count = theParameters.size();
    inter_amb.recv_interaction( theInteraction, theParameters, 0, theTag );
  }
};

/**************************************************************************************************/

static void greeting_handler( const greeting_type &greeting, const RTI::FedTime *, const char * )
{
  std::string str( greeting.p_< Greeting::message >().begin(),
                   greeting.p_< Greeting::message >().end() );

  std::cout << "greeting : " << str.c_str() << " ";
}

/**************************************************************************************************/

static void response_handler( const response_type &response, const RTI::FedTime *, const char * )
{
  std::string str( response.p_< Response::message >().begin(),
                   response.p_< Response::message >().end() );

  std::cout << "response : " << str.c_str() << "\n";
}

/**************************************************************************************************/

int main( int argc, char *argv[] )
{
  // The "fake" RTI exec used to mimic HLA data exchanges
  RTI::RTIexec rti_exec;

  // Register the callbacks that get invoked based on interaction class type
  inter_amb_type inter_amb;
  inter_amb.set_handler( greeting_handler );
  inter_amb.set_handler( response_handler );

  // The sender federate
  RTI::RTIambassador send_rti_amb( rti_exec );
  fed_amb send_fed_amb( inter_amb );

  hw_som::init_handles( send_rti_amb );
  send_rti_amb.joinFederationExecution( "", "hw_sender", &send_fed_amb );

  // The receiver federate
  RTI::RTIambassador recv_rti_amb( rti_exec );
  fed_amb recv_fed_amb(inter_amb);

  recv_rti_amb.joinFederationExecution( "", "hw_receiver", &recv_fed_amb );

  // Declare interests...
  greeting_type::publish( send_rti_amb );
  greeting_type::subscribe( recv_rti_amb );

  response_type::publish( recv_rti_amb );
  response_type::subscribe( send_rti_amb );

  // Run...
  greeting_type send_msg( send_rti_amb );
  response_type response_msg( recv_rti_amb );

  typedef std::vector< ASCIIchar > str_type;

  for (int i = 0; i < 5; ++i)
  {
    const std::string what_up = "What, up?";

    (str_type &) send_msg.p_< Greeting::message >() = str_type( what_up.begin(), what_up.end() );

    send_msg.send();
    rti_exec.tick();

    const std::string &not_much = "Not much";

    (str_type &)
      response_msg.p_< Response::message >() = str_type( not_much.begin(), not_much.end() );

    response_msg.send();
    rti_exec.tick();
  }

  return 0;
}

/**************************************************************************************************/
