/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_EXAMPLE_UTILS_HPP
#define PROTOX_EXAMPLE_UTILS_HPP

/******************************************************************************/

#include <iostream>
#include <string>

#include "fed_amb_util.hpp"

static void wait_for_user()
{
  std::cout << " >>>>>>>>>> Press Enter to Continue <<<<<<<<<<\n";
  std::string line;
  std::getline( std::cin, line );
}

static void advance_time( double timestep,
                          RTI::RTIambassador &rti_amb,
                          fed_amb_util &fed_amb )
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
                                const fed_amb_util &fed_amb )
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

static void create_federation_execution
  ( RTI::RTIambassador &rti_amb, const char *name, const char *fed_file )
{
	try
	{
		rti_amb.createFederationExecution( name, fed_file );
    std::cout << "Federation created.\n";
	}
	catch( RTI::FederationExecutionAlreadyExists )
	{
    std::cout << "Federation already exists.\n";
	}
}

static void destroy_federation_execution
  ( RTI::RTIambassador &rti_amb, const char *name )
{
	try
	{
		rti_amb.destroyFederationExecution( name );
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
}

struct READY_TO_RUN { static const char *str() { return "ReadyToRun"; } };

static void register_ready_to_run
  ( RTI::RTIambassador &rti_amb, const fed_amb_util &fed_amb )
{
  rti_amb.registerFederationSynchronizationPoint( READY_TO_RUN::str(), "" );
	
	while( fed_amb.is_announced == false )
	{
		rti_amb.tick();
	}
}

static void ready_to_run_achieved
  ( RTI::RTIambassador &rti_amb, const fed_amb_util &fed_amb )
{
  rti_amb.synchronizationPointAchieved( READY_TO_RUN::str() );

	while( fed_amb.is_ready_to_run == false )
	{
		rti_amb.tick();
	}
}

/******************************************************************************/

#endif

/******************************************************************************/
