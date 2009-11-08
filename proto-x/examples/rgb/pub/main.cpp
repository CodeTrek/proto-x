
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

#include <protox/hla/o_class_type.hpp>
#include <protox/hla/i_class_type.hpp>

#include "rgb_fed_amb.hpp"
#include "rgb_som.hpp"

#include "fedlet/fedlet_base.hpp"
#include "fedlet/fed_amb.hpp"

/**************************************************************************************************/

static bool waiting_for_quantity;
static int num_platforms;

/**************************************************************************************************/

void start_msg_handler( const start_msg_type &start_msg, const RTI::FedTime *, const char * )
{
  std::cout << "Start message received. Quantity = " << start_msg.p_< quantity >() << "\n";
  num_platforms = start_msg.p_< quantity >();
  waiting_for_quantity = false;
}

/**************************************************************************************************/

using namespace protox::hla;
using namespace protox::examples;

/**************************************************************************************************/

class pub_federate : public fedlet::fedlet_base
{
private:
  typedef o_class_type< rgb_som, q_name< Platform > >::type platform_type;

  std::vector< platform_type > platforms;

protected:
  virtual void declare_interests()
  {
    rgb_som::init_handles( rti_amb );

    platform_type::publish( rti_amb );
    start_msg_type::subscribe( rti_amb );

    std::cout << "rgb_pub declarations complete.\n";
  }

  virtual void populate()
  {
    using namespace PositionVector;

    std::cout << "Waiting for start message...\n";

    while( waiting_for_quantity )
    {
      advance_time( 1.0 );
    }

    platforms.resize( num_platforms );

    for( unsigned i = 0; i < platforms.size(); ++i )
    {
      std::stringstream str;
      str << "Platform [" << i << "]";
      std::string name = str.str();

      platforms[ i ].set_rti( rti_amb );
      platforms[ i ].register_obj( name.c_str() );
    }
  }

  virtual void execute()
  {
    using namespace PositionVector;

    // Initialize platforms
    for( unsigned i = 0; i < platforms.size(); ++i )
    {
      platforms[ i ].a_< Position >().f_< X >() = 25.5f;
      platforms[ i ].a_< Position >().f_< Y >() = 35.5f;

      platforms[ i ].a_< Color >() = ColorEnum::RED::value();

      platforms[ i ].update();
    }

    // Move platforms...
    while( true )
    {
      advance_time( 1.0 );

      for( unsigned i = 0; i < platforms.size(); ++i )
      {
        platforms[ i ].a_< Position >().f_< X >() += 1.5f;
        platforms[ i ].a_< Position >().f_< Y >() += -1.5f;

        platforms[ i ].update();
      }
    }
  }

  virtual void resign() {}

public:
  pub_federate( RTI::RTIambassador &rti_amb, fedlet::fed_amb &fed_amb ) :
    fedlet::fedlet_base(rti_amb, fed_amb)
  {}
};

/**************************************************************************************************/

int main( int argc, char *argv[] )
{
  RTI::RTIambassador rti_amb;

  inter_amb_type inter_amb;
  inter_amb.set_handler< start_msg_type >( start_msg_handler );

  rgb_fed_amb fed_amb( inter_amb );

  pub_federate federate( rti_amb, fed_amb );

  waiting_for_quantity = true;
  federate.run( "rgb_federation", "rgb_pub" );

  return 0;
}

/**************************************************************************************************/
