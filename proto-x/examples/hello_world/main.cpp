#include <iostream>

#include "hw_fed_amb.hpp"

#include "hw_som.hpp"

int main( int argc, char *argv[] )
{
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

  std::cout << "Initialize handles.\n";
  hw_som::init_handles( rti_amb );

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
