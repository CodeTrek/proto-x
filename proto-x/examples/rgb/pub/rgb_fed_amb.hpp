
/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_EXAMPLES_RGB_FED_AMB
#define PROTOX_EXAMPLES_RGB_FED_AMB

/******************************************************************************/

#include <iostream>
#include <string>

#include <fedtime.hh>
#include <RTI.hh>
#include <NullFederateAmbassador.hh>

#include "utils/fed_amb_util.hpp"

#include "inter_fed_amb.hpp"

/******************************************************************************/

class rgb_fed_amb : public fed_amb_util
{
private:
  inter_amb_type &inter_amb;
  
public:
  
  rgb_fed_amb( inter_amb_type &inter_amb ) : inter_amb( inter_amb ) {}

  virtual ~rgb_fed_amb() throw( RTI::FederateInternalError ) {} 
  
  virtual void receiveInteraction
  ( RTI::InteractionClassHandle theInteraction,
    const RTI::ParameterHandleValuePairSet &theParameters,
    const RTI::FedTime &theTime,
    const char *theTag,
    RTI::EventRetractionHandle        theHandle )
  {
    inter_amb.recv_interaction( theInteraction, theParameters, &theTime, theTag );
  }

  virtual void receiveInteraction
  ( RTI::InteractionClassHandle theInteraction,
    const RTI::ParameterHandleValuePairSet& theParameters,
    const char *theTag )
  {
    unsigned count = theParameters.size();

    inter_amb.recv_interaction( theInteraction, theParameters, 0, theTag );
  }
};

/******************************************************************************/

#endif

/******************************************************************************/
