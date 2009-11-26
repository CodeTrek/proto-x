/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#include <iostream>
#include <sstream>
#include <string>

#include <protox/hla/i_class_type.hpp>

#include "fedlet/fedlet_base.hpp"

#include "hw_som.hpp"

/**************************************************************************************************/

using namespace protox::hla;
using namespace protox::examples;

/**************************************************************************************************/

class sender_federate : public fedlet::fedlet_base
{
private:
  typedef i_class_type< hw_som, q_name< Greeting > >::type greeting_type;

protected:
  virtual void declare_interests()
  {
    hw_som::init_handles( rti_amb );

    greeting_type::publish( rti_amb );
    std::cout << "Publications completed.\n";
  }

  virtual void populate()
  {
    std::cout << "TODO: populate\n";
  }

  virtual void execute()
  {
    greeting_type greeter( rti_amb );

    typedef std::vector< ASCIIchar > str_type;

    for( int i = 0; i < 20; ++i )
    {
      std::stringstream hw;
      hw << "Hello, world [" << i << "]";

      const std::string &hw_str = hw.str();

      (str_type &) greeter.p_< Greeting::message >() = str_type( hw_str.begin(), hw_str.end() );

      greeter.send();

		  advance_time( 1.0 );
		  std::cout << "Time Advanced to " << fed_amb.fed_time << std::endl;
    }

    const std::string goodbye("Goodbye");
    (str_type &) greeter.p_< Greeting::message >() = str_type( goodbye.begin(), goodbye.end() );

    greeter.send();
  }

  virtual void resign()
  {
	  //rti_amb.resignFederationExecution( RTI::NO_ACTION );
    std::cout << "hw_sender resigned\n";
  }

public:
  sender_federate( RTI::RTIambassador &rti_amb, fedlet::fed_amb &fed_amb ) :
    fedlet::fedlet_base(rti_amb, fed_amb)
  {}
};

/**************************************************************************************************/

int main( int argc, char *argv[] )
{

  RTI::RTIambassador rti_amb;
  fedlet::fed_amb fed_amb;

  sender_federate federate( rti_amb, fed_amb );
  federate.run( "hw_federation", "hw_sender" );

	return 0;
}

/**************************************************************************************************/
