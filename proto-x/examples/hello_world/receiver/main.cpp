/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#include <iostream>
#include <string>

#include <protox/hla/i_class_type.hpp>
#include <protox/hla/interaction_amb.hpp>

#include <boost/mpl/vector.hpp>

#include "fedlet/fedlet_base.hpp"

#include "hw_fed_amb.hpp"
#include "hw_som.hpp"

#include "inter_fed_amb.hpp"

/**************************************************************************************************/

using namespace boost;

using namespace protox::hla;
using namespace protox::examples;

/**************************************************************************************************/

static bool goodbye = false;

void greeting_handler( const greeting_type &greeting, const RTI::FedTime *, const char * )
{
  std::string str( greeting.p_< Greeting::message >().begin(),
                   greeting.p_< Greeting::message >().end() );

  std::cout << "received " << str.c_str() << "\n";

  if( str == "Goodbye" )
  {
    goodbye = true;
  }
}

/**************************************************************************************************/

class receiver_federate : public fedlet::fedlet_base
{
protected:
  virtual void declare_interests()
  {
    hw_som::init_handles( rti_amb );

    greeting_type::subscribe( rti_amb );

    std::cout << "Subscriptions completed.\n";
  }

  virtual void populate() {}

  virtual void execute()
  {
    while( !goodbye )
    {
      advance_time( 1.0 );
    }
  }

  virtual void resign()
  {
    //rti_amb.resignFederationExecution( RTI::NO_ACTION );
    std::cout << "hw_receiver resigned\n";
  }

public:
  receiver_federate( RTI::RTIambassador &rti_amb, fedlet::fed_amb &fed_amb ) :
    fedlet::fedlet_base(rti_amb, fed_amb)
  {}
};

/**************************************************************************************************/

int main( int argc, char *argv[] )
{
  RTI::RTIambassador rti_amb;

  inter_amb_type inter_amb;
  //inter_amb.set_handler< greeting_type >( greeting_handler );
  inter_amb.set_handler( greeting_handler );

  hw_fed_amb fed_amb( inter_amb );

  receiver_federate federate( rti_amb, fed_amb );
  federate.run( "hw_federation", "hw_receiver" );

  return 0;
}

/**************************************************************************************************/
