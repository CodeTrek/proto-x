#include <iostream>
#include <string>

#include <protox/hla/i_class_type.hpp>
#include <protox/hla/interaction_amb.hpp>

#include <boost/mpl/vector.hpp>

#include "hw_fed_amb.hpp"

#include "hw_som.hpp"

#include "inter_fed_amb.hpp"

#include "utils/utils.hpp"

using namespace protox::hla;
using namespace boost;

static bool goodbye = false;

void greeting_handler
  ( const greeting_type &greeting, const RTI::FedTime *, const char * )
{
  std::string str( greeting.p_< Greeting::message >().begin(),
                   greeting.p_< Greeting::message >().end() );

  std::cout << "received " << str.c_str() << "\n"; 

  if( str == "Goodbye" )
  {
    goodbye = true;
  }
}

int main( int argc, char *argv[] )
{
  RTI::RTIambassador rti_amb;

  inter_amb_type inter_amb;
  inter_amb.set_handler< greeting_type >( greeting_handler );

  // Join federation
  hw_fed_amb fed_amb( inter_amb );

  create_federation_execution( rti_amb, "hw_federation", "hello_world.fed" );

  // Interaction ambassador
	rti_amb.joinFederationExecution( "hw_receiver", "hw_federation", &fed_amb );
  std::cout << "Federation joined.\n";

  // Initialize handles
  hw_som::init_handles( rti_amb );
  std::cout << "Handles initialized.\n";

  register_ready_to_run( rti_amb, fed_amb );

  // Wait for user (i.e., let other federates join before moving on)
  wait_for_user();

  ready_to_run_achieved( rti_amb, fed_amb );

  // enable time policy
  enable_time_policy( rti_amb, fed_amb );

  // Publish/subscribe
  greeting_type::subscribe( rti_amb );
  std::cout << "Subscriptions completed.\n";

  while( !goodbye )
  {
		advance_time( 1.0, rti_amb, fed_amb );
  }

	rti_amb.resignFederationExecution( RTI::NO_ACTION );
  std::cout << "Resigned from federation.\n";

  destroy_federation_execution( rti_amb, "hw_federation" );

	return 0;
}
