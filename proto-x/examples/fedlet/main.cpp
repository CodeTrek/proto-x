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
  virtual void declare_interests()
  {
    std::cout << "TODO: declare_interests\n";
  }

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
  test_federate( RTI::RTIambassador &rti_amb, fedlet::fed_amb &fed_amb ) :
    fedlet::fedlet_base(rti_amb, fed_amb)
  {}
};

/**************************************************************************************************/

int main( int argc, char *argv[] )
{
  if (argc != 3)
  {
    std::cout << "usage: fedlet federation federate\n";
    std::cout << "       federation    - The name of the federation.\n";
    std::cout << "       federate      - The name of the joining federate.\n";
    std::cout << "\n";
    std::cout << "Example: fedlet \"exmaple_federation\" \"fedlet_1\"\n";

    return -1;
  }

  static const char *FEDERATION_NAME = argv[1];
  static const char *FEDERATE_NAME   = argv[2];

  RTI::RTIambassador rti_amb;
  fedlet::fed_amb fed_amb;

  test_federate federate( rti_amb, fed_amb );

  federate.run( FEDERATION_NAME, FEDERATE_NAME );

  return 0;
}

/**************************************************************************************************/
