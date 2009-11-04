/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#include <iostream>
#include <sstream>

#include "./fedlet_base.hpp"
#include "./fed_amb.hpp"

using namespace protox::examples;

class test_federate : public fedlet::fedlet_base
{
protected:
  virtual void populate()
  {
    std::cout << "TODO: populate\n";
  }

  virtual void execute()
  {
    std::cout << "TODO: execute\n";
  }

  virtual void resign()
  {
    std::cout << "TODO: resign\n";
  }

public:
  test_federate( RTI::RTIambassador &amb ) : fedlet::fedlet_base(amb) {}
};

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

  test_federate federate( rti_amb );
  fedlet::fed_amb fed_amb;

  federate.run( FEDERATION_NAME, fed_name, fed_amb );

  return 0;
}

/**************************************************************************************************/
