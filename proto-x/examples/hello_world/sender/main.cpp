/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

#include <iostream>
#include <sstream>
#include <string>

#include <protox/hla/i_class_type.hpp>

#include "utils/utils.hpp"

#include "hw_fed_amb.hpp"
#include "hw_som.hpp"

int main( int argc, char *argv[] )
{
  using namespace protox::hla;

  RTI::RTIambassador rti_amb;
  hw_fed_amb fed_amb;

  // Create and join the federation
  create_federation_execution( rti_amb, "hw_federation", "hello_world.fed" );
	rti_amb.joinFederationExecution( "hw_sender", "hw_federation", &fed_amb );

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
  typedef i_class_type< hw_som, q_name< Greeting > >::type greeting_type;

  greeting_type::publish( rti_amb );
  std::cout << "Publications completed.\n";

  greeting_type greeter( rti_amb );

  typedef std::vector< ASCIIchar > str_type;

  for( int i = 0; i < 20; ++i )
  {
    std::stringstream hw;
    hw << "Hello, world [" << i << "]";

    const std::string &hw_str = hw.str(); 

    (str_type &) greeter.p_<Greeting::message >() = str_type( hw_str.begin(), hw_str.end() );

    greeter.send();

		advance_time( 1.0, rti_amb, fed_amb );
		std::cout << "Time Advanced to " << fed_amb.fed_time << std::endl;
  }

  const std::string goodbye("Goodbye");
  (str_type &) greeter.p_<Greeting::message >() = str_type( goodbye.begin(), goodbye.end() ); 
  greeter.send();

	rti_amb.resignFederationExecution( RTI::NO_ACTION );
  destroy_federation_execution( rti_amb, "hw_federation" ); 

  std::cout << "Resigned from federation.\n";

	return 0;
}
