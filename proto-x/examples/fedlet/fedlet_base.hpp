/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_EXAMPLE_FEDLET_FEDLET_BASE_HPP
#define PROTOX_EXAMPLE_FEDLET_FEDLET_BASE_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "./fed_amb.hpp"
#include "./sync_points.hpp"

/**************************************************************************************************/

namespace protox {
namespace examples {
namespace fedlet {

/**************************************************************************************************/

class fedlet_base
{
private:
  // off
  fedlet_base();
  fedlet_base(const fedlet_base &);
  fedlet_base &operator=(const fedlet_base &);

protected:
  RTI::RTIambassador &rti_amb;
  fedlet::fed_amb &fed_amb;

private:
  void enable_time_policy()
  {
    const RTIfedTime fed_time = fed_amb.fed_time;
    const RTIfedTime lookahead = fed_amb.fed_lookahead_time;

    rti_amb.enableTimeRegulation( fed_time, lookahead );

    while (fed_amb.is_regulating == false)
    {
      rti_amb.tick();
    }

    rti_amb.enableTimeConstrained();

    while (fed_amb.is_constrained == false)
    {
      rti_amb.tick();
    }
  }

protected:
  virtual void declare_interests() = 0;
  virtual void populate() = 0;
  virtual void execute() = 0;
  virtual void resign() = 0;

  void advance_time( double timestep )
  {
    // request the advance
    fed_amb.is_advancing = true;
    const RTIfedTime new_time = (fed_amb.fed_time + timestep);
    rti_amb.timeAdvanceRequest( new_time );

    while (fed_amb.is_advancing)
    {
      rti_amb.tick();
    }
  }

public:
  fedlet_base( RTI::RTIambassador &rti_amb, fedlet::fed_amb &fed_amb ) :
    rti_amb(rti_amb),
    fed_amb(fed_amb)
  {}

  virtual ~fedlet_base() {}

  void run( const char *federation_name, const char *federate_name )
  {
    rti_amb.joinFederationExecution( federate_name, federation_name, &fed_amb );
    std::cout << "Federation joined.\n";

    // enable time policy
    enable_time_policy();

    declare_interests();

    bool ready_to_populate_achieved = false;
    bool ready_to_run_achieved      = false;
    bool ready_to_resign_achieved   = false;

    while (true)
    {
      advance_time( 1.0 );

      if ((fed_amb.all_sync_points_announced) && (!ready_to_populate_achieved))
      {
        try
        {
          rti_amb.synchronizationPointAchieved( READY_TO_POPULATE );
          ready_to_populate_achieved = true;
        }
        catch (RTI::Exception& ex)
        {
          std::cout << "RTI Exception: " << ex._name << " " << ex._reason << std::endl;
          break;
        }
      }

      if ((fed_amb.is_ready_to_populate) && (!ready_to_run_achieved))
      {
        populate();

        try
        {
          rti_amb.synchronizationPointAchieved( READY_TO_RUN );
          ready_to_run_achieved = true;
        }
        catch (RTI::Exception& ex)
        {
          std::cout << "RTI Exception: " << ex._name << " " << ex._reason << std::endl;
          break;
        }
      }

      if ((fed_amb.is_ready_to_run) && (!ready_to_resign_achieved))
      {
        execute();

        try
        {
          rti_amb.synchronizationPointAchieved( READY_TO_RESIGN );
          ready_to_resign_achieved = true;
        }
        catch (RTI::Exception& ex)
        {
          std::cout << "RTI Exception: " << ex._name << " " << ex._reason << std::endl;
          break;
        }
      }

      if (fed_amb.is_ready_to_resign)
      {
        resign();
        break;
      }
    }

    try
    {
      rti_amb.resignFederationExecution( RTI::NO_ACTION );
    }
    catch (RTI::Exception& ex)
    {
      std::cout << "RTI Exception: " << ex._name << " " << ex._reason << std::endl;
    }

    std::cout << "Resigned from federation.\n";
  }
};

/**************************************************************************************************/

}}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
