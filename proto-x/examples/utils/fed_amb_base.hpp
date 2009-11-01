
/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_EXAMPLES_UTIL_FED_AMB_BASE_HPP
#define PROTOX_EXAMPLES_UTIL_FED_AMB_BASE_HPP

/**************************************************************************************************/

#include <iostream>
#include <string>

#include <fedtime.hh>
#include <RTI.hh>
#include <NullFederateAmbassador.hh>

/**************************************************************************************************/

class fed_amb_base : public NullFederateAmbassador
{
private:
  static double convert_time( const RTI::FedTime &the_time )
  {
    return ((RTIfedTime) the_time).getTime();
  }

public:
  double fed_time;
  double fed_lookahead_time;

  bool is_regulating;
  bool is_constrained;
  bool is_advancing;
  
  fed_amb_base() :
    fed_time( 0.0 ),
    fed_lookahead_time( 1.0 ),
    is_regulating( false ),
    is_constrained( false ),
    is_advancing( false )
  {}

  virtual ~fed_amb_base() throw( RTI::FederateInternalError ) {}
  
  //////////////////////////////////////////////////////////////////////////////
  // Time Callbacks
  //////////////////////////////////////////////////////////////////////////////
  virtual void timeRegulationEnabled( const RTI::FedTime &theFederateTime )
  {
    is_regulating = true;
    fed_time = convert_time( theFederateTime );
  }

  virtual void timeConstrainedEnabled( const RTI::FedTime &theFederateTime )
  {
    is_constrained = true;
    fed_time = convert_time( theFederateTime );
  }

  virtual void timeAdvanceGrant( const RTI::FedTime &theTime )
  {
    is_advancing = false;
    fed_time = convert_time( theTime );
  }
};

/**************************************************************************************************/

#endif

/**************************************************************************************************/
