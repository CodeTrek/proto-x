
/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_EXAMPLES_FED_AMB_UTIL_HPP
#define PROTOX_EXAMPLES_FED_AMB_UTIL_HPP

/**************************************************************************************************/

#include <iostream>
#include <string>

#include <fedtime.hh>
#include <RTI.hh>
#include <NullFederateAmbassador.hh>

#include "fed_amb_base.hpp"

/**************************************************************************************************/

class fed_amb_util : public fed_amb_base
{
public:
  bool is_announced;
  bool is_ready_to_run;
  
  fed_amb_util() :
    is_announced( false ),
    is_ready_to_run( false )
  {}

  virtual ~fed_amb_util() throw( RTI::FederateInternalError ) {} 
  
  virtual void announceSynchronizationPoint( const char *label, const char *)
  {
    std::cout << "Synchronization point announced: " << label << std::endl;

    if( std::string(label) == "ReadyToRun" )	
    {
      is_announced = true;
    }
  }

  virtual void federationSynchronized( const char *label )
  {
    std::cout << "Federation Synchronized: " << label << std::endl;
    if( std::string(label) == "ReadyToRun" )
    {
      is_ready_to_run = true;
    }
  }
};

/**************************************************************************************************/

#endif

/**************************************************************************************************/
