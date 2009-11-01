/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "utils/utils.hpp"
#include "utils/fed_amb.hpp"

/**************************************************************************************************/

int main( int argc, char *argv[] )
{
  static const char *FEDERATION_NAME = "example_federation";

  char *fed_name = "rgb_pub";

  if( argc > 1 )
  {
    fed_name = argv[ 1 ];
  }

  RTI::RTIambassador rti_amb;

  // Join federation
  protox::examples::util::fed_amb fed_amb;
  rti_amb.joinFederationExecution( fed_name, FEDERATION_NAME, &fed_amb );
  std::cout << "Federation joined.\n";

  // enable time policy
  enable_time_policy( rti_amb, fed_amb );

  bool ready_to_populate_achieved = false;
  bool ready_to_run_achieved      = false;
  bool ready_to_resign_achieved   = false;

  while( true )
  {
    advance_time( 1.0, rti_amb, fed_amb );

    if( (fed_amb.all_sync_points_announced) && (!ready_to_populate_achieved) )
    {
       try
       {
         rti_amb.synchronizationPointAchieved( "ReadyToPopulate" );
         ready_to_populate_achieved = true;
       }
       catch( RTI::Exception& ex )
       {
         std::cout << "RTI Exception: " << ex._name << " " << ex._reason << std::endl;
         break;
       }
    }

     if( (fed_amb.is_ready_to_populate) && (!ready_to_run_achieved) )
     {
       std::cout << "TODO: register initial object instances...\n";

       try
       {
         rti_amb.synchronizationPointAchieved( "ReadyToRun" );
         ready_to_run_achieved = true;
       }
       catch( RTI::Exception& ex )
       {
         std::cout << "RTI Exception: " << ex._name << " " << ex._reason << std::endl;
         break;
       }
     }

     if( (fed_amb.is_ready_to_run) && (!ready_to_resign_achieved) )
     {
       std::cout << "TODO: run federate...\n";

       try
       {
         rti_amb.synchronizationPointAchieved( "ReadyToResign" );
         ready_to_resign_achieved = true;
       }
       catch( RTI::Exception& ex )
       {
         std::cout << "RTI Exception: " << ex._name << " " << ex._reason << std::endl;
         break;
       }
     }

     if( fed_amb.is_ready_to_resign )
     {
       break;
     }
   }

  rti_amb.resignFederationExecution( RTI::NO_ACTION );
  std::cout << "Resigned from federation.\n";

  // destroy_federation_execution( rti_amb, FEDERATION_NAME );

  return 0;
}

/**************************************************************************************************/
