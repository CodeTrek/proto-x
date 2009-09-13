#include <iostream>
#include <sstream>
#include <string>

#include <protox/hla/o_class_type.hpp>
#include <protox/hla/i_class_type.hpp>

#include "utils/utils.hpp"

#include "rgb_fed_amb.hpp"
#include "rgb_som.hpp"

int main( int argc, char *argv[] )
{
  static const char *FEDERATION_NAME = "rgb_federation";

  using namespace protox::hla;

  RTI::RTIambassador rti_amb;

  create_federation_execution( rti_amb, FEDERATION_NAME, "rgb.fed" );

  // Join federation
  obj_amb_type obj_amb;
  rgb_fed_amb fed_amb( obj_amb );
	rti_amb.joinFederationExecution( "rgb_sub", FEDERATION_NAME, &fed_amb );
  std::cout << "Federation joined.\n";

  // Initialize handles
  rgb_som::init_handles( rti_amb );
  std::cout << "Handles initialized.\n";

  // Publish/subscribe
  typedef i_class_type< rgb_som, q_name< StartMsg > >::type start_msg_type;

  start_msg_type::publish( rti_amb );
  platform_type::subscribe( rti_amb );

  std::cout << "Publications/subscription completed.\n";

  register_ready_to_run( rti_amb, fed_amb );
 
  // Wait for user (i.e., let other federates join before moving on)
  wait_for_user();

  ready_to_run_achieved( rti_amb, fed_amb );

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

  using namespace PositionVector;

  while( true )
  {
    obj_amb_type::const_it< platform_type >::type it;

    for( it = obj_amb.begin< platform_type >(); it != obj_amb.end< platform_type >(); ++it )
    {
      std::cout << "x = " << it->second.a_< Position >().f_< X >() << "\n";
    }

    advance_time( 1.0, rti_amb, fed_amb );
  }

	rti_amb.resignFederationExecution( RTI::NO_ACTION );
  std::cout << "Resigned from federation.\n";

  destroy_federation_execution( rti_amb, FEDERATION_NAME );

	return 0;
}
