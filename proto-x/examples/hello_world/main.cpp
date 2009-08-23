#include <iostream>

#include <protox/hla/i_class_type.hpp>

#include "hw_fed_amb.hpp"

#include "hw_som.hpp"

int main( int argc, char *argv[] )
{
  using namespace protox::hla;

	char *fed_name = "exampleFederate";

	if( argc > 1 )
  {
		fed_name = argv[ 1 ];
  }

  RTI::RTIambassador rti_amb;

	try
	{
		rti_amb.createFederationExecution( "hw_federation", "hello_world.fed" );
    std::cout << "Federation created.\n";
	}
	catch( RTI::FederationExecutionAlreadyExists )
	{
    std::cout << "Federation already exists.\n";
	}

  hw_fed_amb fed_amb;
	rti_amb.joinFederationExecution( fed_name, "hw_federation", &fed_amb );
  std::cout << "Federation joined.\n";

  hw_som::init_handles( rti_amb );
  std::cout << "Handles initialized.\n";

  typedef i_class_type< hw_som, q_name< Greeting > >::type greeting_type;

  greeting_type::publish( rti_amb );
  std::cout << "Publications completed.\n";

  greeting_type greeter( rti_amb );

  std::cout << "name = " << greeting_type::get_name() << "\n";
  std::cout << "hanlde = " << greeting_type::get_handle() << "\n";
  std::cout << "num params = " << greeting_type::get_num_parameters() << "\n";
  std::cout << "param handle = " << greeter.get_param_handle< Greeting::message >() << "\n";

  const std::string hw("Hello, world");
  for( unsigned i = 0; i < hw.length(); ++i )
  {
    const char c = hw.c_str()[ i ];
    greeter.p_< Greeting::message >().push_back( hw.c_str()[ i ] );
  }

  greeter.send();

	rti_amb.resignFederationExecution( RTI::NO_ACTION );
  std::cout << "Resigned from federation.\n";

	try
	{
		rti_amb.destroyFederationExecution( "hw_federation" );
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

	return 0;
}
