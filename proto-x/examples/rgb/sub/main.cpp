
/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#include <iostream>
#include <sstream>
#include <string>

#include <protox/hla/o_class_type.hpp>
#include <protox/hla/i_class_type.hpp>

#include "rgb_fed_amb.hpp"
#include "rgb_som.hpp"

#include "fedlet/fedlet_base.hpp"
#include "fedlet/fed_amb.hpp"

/**************************************************************************************************/

using namespace protox::hla;
using namespace protox::examples;

/**************************************************************************************************/

class sub_federate : public fedlet::fedlet_base
{
private:
  typedef i_class_type< rgb_som, q_name< StartMsg > >::type start_msg_type;
  obj_amb_type &obj_amb;

protected:
  virtual void declare_interests()
  {
    rgb_som::init_handles( rti_amb );

    start_msg_type::publish( rti_amb );
    platform_type::subscribe( rti_amb );
    std::cout << "rgb_sub declarations complete.\n";
  }

  virtual void populate()
  {
    start_msg_type start_msg( rti_amb );

    const unsigned NUM_PLATFORMS = 12;

    start_msg.p_< quantity >() = NUM_PLATFORMS;

    start_msg.send();
    std::cout << "Start message sent requesting: " << NUM_PLATFORMS << " platform objects\n";

    while( true )
    {
      if( obj_amb.size< platform_type >() == NUM_PLATFORMS )
      {
        std::cout << "Discovered " << NUM_PLATFORMS << " platform objects\n";
        break;
      }

      advance_time( 1.0 );
    }
  }

  virtual void execute()
  {
    using namespace PositionVector;

    while( true )
    {
      obj_amb_type::const_it< platform_type >::type it;

      for( it = obj_amb.begin< platform_type >(); it != obj_amb.end< platform_type >(); ++it )
      {
        std::cout << "x = " << it->second.a_< Position >().f_< X >() << "\n";
        std::cout << "y = " << it->second.a_< Position >().f_< Y >() << "\n";
      }

      advance_time( 1.0 );
    }
  }

  virtual void resign() {}

public:
  sub_federate( RTI::RTIambassador &rti_amb, fedlet::fed_amb &fed_amb, obj_amb_type &obj_amb ) :
    fedlet::fedlet_base(rti_amb, fed_amb),
    obj_amb(obj_amb)
  {}
};

/**************************************************************************************************/

int main( int argc, char *argv[] )
{
  RTI::RTIambassador rti_amb;

  obj_amb_type obj_amb;
  rgb_fed_amb fed_amb( obj_amb );

  sub_federate federate( rti_amb, fed_amb, obj_amb );

  federate.run( "rgb_federation", "rgb_sub" );

  return 0;
}

/**************************************************************************************************/
