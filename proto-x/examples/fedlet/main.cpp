#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "utils/utils.hpp"

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
  fed_amb_util fed_amb;
  rti_amb.joinFederationExecution( fed_name, FEDERATION_NAME, &fed_amb );
  std::cout << "Federation joined.\n";

  // enable time policy
  enable_time_policy( rti_amb, fed_amb );

  while( true )
  {
    advance_time( 1.0, rti_amb, fed_amb );
  }

  rti_amb.resignFederationExecution( RTI::NO_ACTION );
  std::cout << "Resigned from federation.\n";

  destroy_federation_execution( rti_amb, FEDERATION_NAME );

  return 0;
}
