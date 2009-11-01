/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_EXAMPLE_READY_TO_RUN_UTILS_HPP
#define PROTOX_EXAMPLE_READY_TO_RUN_UTILS_HPP

/**************************************************************************************************/

#include <iostream>
#include <string>

#include "fed_amb_util.hpp"

/**************************************************************************************************/

struct READY_TO_RUN { static const char *str() { return "ReadyToRun"; } };

static void register_ready_to_run( RTI::RTIambassador &rti_amb, const fed_amb_util &fed_amb )
{
  rti_amb.registerFederationSynchronizationPoint( READY_TO_RUN::str(), "" );
	
	while( fed_amb.is_announced == false )
	{
		rti_amb.tick();
	}
}

static void ready_to_run_achieved( RTI::RTIambassador &rti_amb, const fed_amb_util &fed_amb )
{
  rti_amb.synchronizationPointAchieved( READY_TO_RUN::str() );

	while( fed_amb.is_ready_to_run == false )
	{
		rti_amb.tick();
	}
}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
