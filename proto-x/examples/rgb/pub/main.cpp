#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <protox/hla/o_class_type.hpp>
#include <protox/hla/i_class_type.hpp>

#include "utils/utils.hpp"

#include "rgb_fed_amb.hpp"

#include "rgb_som.hpp"

static bool waiting_for_quantity;
static int num_platforms;

void start_msg_handler( const start_msg_type &start_msg, const RTI::FedTime *, const char * )
{
  std::cout << "Start msg received. Quantity = " << start_msg.p_< quantity >() << "\n";
  num_platforms = start_msg.p_< quantity >();
  waiting_for_quantity = false;
}

int main( int argc, char *argv[] )
{
  static const char *FEDERATION_NAME = "rgb_federation";

  using namespace protox::hla;

  waiting_for_quantity = true;
  num_platforms = 0;

	char *fed_name = "rgb_pub";

	if( argc > 1 )
  {
		fed_name = argv[ 1 ];
  }

  RTI::RTIambassador rti_amb;

  create_federation_execution( rti_amb, FEDERATION_NAME, "rgb.fed" ); 

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

  register_ready_to_run( rti_amb, fed_amb );
 
  // Wait for user (i.e., let other federates join before moving on)
  wait_for_user();

  ready_to_run_achieved( rti_amb, fed_amb );

  // enable time policy
  enable_time_policy( rti_amb, fed_amb );

  while( waiting_for_quantity )
  {
		advance_time( 1.0, rti_amb, fed_amb );
  }

  std::vector< platform_type > platforms( num_platforms );

  using namespace PositionVector;

  for( unsigned i = 0; i < platforms.size(); ++i )
  {
    std::stringstream str;
    str << "Platform [" << i << "]";
    std::string name = str.str();

    platforms[ i ].set_rti( rti_amb );
    platforms[ i ].register_obj( name.c_str() );

    platforms[ i ].a_< Position >().f_< X >() = 25.5f;
    platforms[ i ].a_< Position >().f_< Y >() = 35.5f;

    platforms[ i ].a_< Color >() = ColorEnum::RED::value();

    platforms[ i ].update();
  }

  while( true )
  {
		advance_time( 1.0, rti_amb, fed_amb );
  }

	rti_amb.resignFederationExecution( RTI::NO_ACTION );
  std::cout << "Resigned from federation.\n";

  destroy_federation_execution( rti_amb, FEDERATION_NAME );

	return 0;
}
