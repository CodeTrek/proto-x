#include <iostream>
#include <string>

#include <protox/hla/i_class_type.hpp>

#include "hw_fed_amb.hpp"

#include "hw_som.hpp"

static void wait_for_user()
{
	std::cout << " >>>>>>>>>> Press Enter to Continue <<<<<<<<<<\n";
	std::string line;
	std::getline( std::cin, line );
}

static void advance_time( double timestep,
                          RTI::RTIambassador &rti_amb,
                          hw_fed_amb &fed_amb )
{
	// request the advance
	fed_amb.is_advancing = true;
	const RTIfedTime new_time = (fed_amb.fed_time + timestep);
	rti_amb.timeAdvanceRequest( new_time );

	// wait for the time advance to be granted. ticking will tell the
	// LRC to start delivering callbacks to the federate
	while( fed_amb.is_advancing )
	{
		rti_amb.tick();
	}
}

static void enable_time_policy( RTI::RTIambassador &rti_amb,
                                const hw_fed_amb &fed_amb )
{
	////////////////////////////
	// enable time regulation //
	////////////////////////////
	const RTIfedTime fed_time = fed_amb.fed_time;
	const RTIfedTime lookahead = fed_amb.fed_lookahead_time;
	rti_amb.enableTimeRegulation( fed_time, lookahead );

	// tick until we get the callback
	while( fed_amb.is_regulating == false )
	{
    rti_amb.tick();
	}

	/////////////////////////////
	// enable time constrained //
	/////////////////////////////
	rti_amb.enableTimeConstrained();

	// tick until we get the callback
	while( fed_amb.is_constrained == false )
	{
		rti_amb.tick();
	}
}

int main( int argc, char *argv[] )
{
  using namespace protox::hla;

	char *fed_name = "exampleFederate";

	if( argc > 1 )
  {
		fed_name = argv[ 1 ];
  }

  RTI::RTIambassador rti_amb;

  // Create federation
	try
	{
		rti_amb.createFederationExecution( "hw_federation", "hello_world.fed" );
    std::cout << "Federation created.\n";
	}
	catch( RTI::FederationExecutionAlreadyExists )
	{
    std::cout << "Federation already exists.\n";
	}

  // Join federation
  hw_fed_amb fed_amb;
	rti_amb.joinFederationExecution( fed_name, "hw_federation", &fed_amb );
  std::cout << "Federation joined.\n";

  // Initialize handles
  hw_som::init_handles( rti_amb );
  std::cout << "Handles initialized.\n";
 
  // Register sync point 
	const char *READY_TO_RUN = "ReadyToRun";
	rti_amb.registerFederationSynchronizationPoint( READY_TO_RUN, "" );
	
	while( fed_amb.is_announced == false )
	{
		rti_amb.tick();
	}

  // Wait for user (i.e., let other federates join before moving on)
  wait_for_user();

  // Announce sync point achieved
  rti_amb.synchronizationPointAchieved( READY_TO_RUN );
	while( fed_amb.is_ready_to_run == false )
	{
		rti_amb.tick();
	}

  // enable time policy
  enable_time_policy( rti_amb, fed_amb );

  // Publish/subscribe
  typedef i_class_type< hw_som, q_name< Greeting > >::type greeting_type;

  greeting_type::publish( rti_amb );
  std::cout << "Publications completed.\n";

  greeting_type greeter( rti_amb );

  std::cout << "class name = " << greeting_type::get_name() << "\n";
  std::cout << "class handle = " << greeting_type::get_handle() << "\n";
  std::cout << "num params = " << greeting_type::get_num_parameters() << "\n";
  std::cout << "param handle = " << greeter.get_param_handle< Greeting::message >() << "\n";

  for( int i = 0; i < 20; ++i )
  {
    const std::string hw("Hello, world");

    typedef std::vector< ASCIIchar > str_type;
    (str_type &) greeter.p_<Greeting::message >() = str_type( hw.begin(), hw.end() ); 

    greeter.send();

		advance_time( 1.0, rti_amb, fed_amb );
		std::cout << "Time Advanced to " << fed_amb.fed_time << std::endl;
  }

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
