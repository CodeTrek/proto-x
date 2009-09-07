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

static bool waiting_for_quantity;

void start_msg_handler( const start_msg_type &start_msg, const RTI::FedTime *, const char * )
{
  std::cout << "Start msg received. Quantity = " << start_msg.p_< quantity >() << "\n";
  waiting_for_quantity = false;
}

int main( int argc, char *argv[] )
{
  static const char *FEDERATION_NAME = "rgb_federation";

  using namespace protox::hla;

  waiting_for_quantity = true;

	char *fed_name = "rgb_pub";

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

  inter_amb_type inter_amb;
  inter_amb.set_handler< start_msg_type >( start_msg_handler );

  // Join federation
  rgb_fed_amb fed_amb( inter_amb );
	rti_amb.joinFederationExecution( fed_name, FEDERATION_NAME, &fed_amb );
  std::cout << "Federation joined.\n";

  // Initialize handles
  rgb_som::init_handles( rti_amb );
  std::cout << "Handles initialized.\n";

  // Publish/subscribe
  typedef o_class_type< rgb_som, q_name< Platform > >::type platform_type;

  platform_type::publish( rti_amb );
  start_msg_type::subscribe( rti_amb );

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

  while( waiting_for_quantity )
  {
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
