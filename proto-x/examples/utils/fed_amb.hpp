
/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_EXAMPLES_UTIL_FED_AMB_HPP
#define PROTOX_EXAMPLES_UTIL_FED_AMB_HPP

/**************************************************************************************************/

#include <iostream>
#include <string>

#include <fedtime.hh>
#include <RTI.hh>
#include <NullFederateAmbassador.hh>

#include "fed_amb_base.hpp"

/**************************************************************************************************/

namespace protox {
namespace examples {
namespace util {

/**************************************************************************************************/

class fed_amb : public fed_amb_base
{
private:
  int num_sync_points_announced;

public:
  bool all_sync_points_announced;
  bool is_ready_to_populate;
  bool is_ready_to_run;
  bool is_ready_to_resign;

  fed_amb() :
    num_sync_points_announced( 0 ),
    all_sync_points_announced( false ),
    is_ready_to_populate( false ),
    is_ready_to_run( false ),
    is_ready_to_resign( false )
  {}

  virtual ~fed_amb() throw( RTI::FederateInternalError ) {}
  
  virtual void announceSynchronizationPoint( const char *label, const char *tag )
  throw (
    RTI::FederateInternalError)
  {
    std::cout << "Synchronization point announced: " << label << std::endl;

    static int const NUM_REQUIRED_SYNC_POINTS = 3;

    ++num_sync_points_announced;
    all_sync_points_announced = (num_sync_points_announced == NUM_REQUIRED_SYNC_POINTS);
  }

  /**
   * Called when all joined federates have achieved a synchronization point.
   */
  virtual void federationSynchronized( const char *label )
  throw (
    RTI::FederateInternalError)
  {
    if( std::string( "ReadyToPopulate" ) == label )
    {
      is_ready_to_populate = true;
    }
    else if( std::string( "ReadyToRun" ) == label )
    {
      is_ready_to_run = true;
    }
    else if( std::string( "ReadyToResign" ) == label )
    {
      is_ready_to_resign = true;
    }
  }
};

/**************************************************************************************************/

}}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
