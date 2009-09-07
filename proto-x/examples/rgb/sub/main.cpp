#include <iostream>
#include <sstream>
#include <string>

#include <protox/hla/o_class_type.hpp>
#include <protox/hla/i_class_type.hpp>

#include "rgb_fed_amb.hpp"

#include "rgb_som.hpp"

static void wait_for_user()
{
	std::cout << " >>>>>>>>>> Press Enter to Continue <<<<<<<<<<\n";
	std::string line;
	std::getline( std::cin, line );
}

static void advance_time( double timestep,
                          RTI::RTIambassador &rti_amb,
                          rgb_fed_amb &fed_amb )
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
                                const rgb_fed_amb &fed_amb )
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
  static const char *FEDERATION_NAME = "rgb_federation";

  using namespace protox::hla;

	char *fed_name = "rgb_sub";

	if( argc > 1 )
  {
		fed_name = argv[ 1 ];
  }

  RTI::RTIambassador rti_amb;

  // Create federation
	try
	{
		rti_amb.createFederationExecution( FEDERATION_NAME, "rgb.fed" );
    std::cout << "Federation created.\n";
	}
	catch( RTI::FederationExecutionAlreadyExists )
	{
    std::cout << "Federation already exists.\n";
	}

  // Join federation
  obj_amb_type obj_amb;
  rgb_fed_amb fed_amb( obj_amb );
	rti_amb.joinFederationExecution( fed_name, FEDERATION_NAME, &fed_amb );
  std::cout << "Federation joined.\n";

  // Initialize handles
  rgb_som::init_handles( rti_amb );
  std::cout << "Handles initialized.\n";

  // Publish/subscribe
  typedef i_class_type< rgb_som, q_name< StartMsg > >::type start_msg_type;

  start_msg_type::publish( rti_amb );
  platform_type::subscribe( rti_amb );

  std::cout << "Publications/subscription completed.\n";
 
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


  start_msg_type start_msg( rti_amb );

  const unsigned NUM_PLATFORMS = 12;

  start_msg.p_< quantity >() = NUM_PLATFORMS;

  start_msg.send();

  while( true )
  {
    if( obj_amb.size< platform_type >() == NUM_PLATFORMS )
    {
      std::cout << "Discovered " << NUM_PLATFORMS << " platform objects\n";
      break;
    }

    advance_time( 1.0, rti_amb, fed_amb );
  }

	rti_amb.resignFederationExecution( RTI::NO_ACTION );
  std::cout << "Resigned from federation.\n";

	try
	{
		rti_amb.destroyFederationExecution( FEDERATION_NAME );
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
