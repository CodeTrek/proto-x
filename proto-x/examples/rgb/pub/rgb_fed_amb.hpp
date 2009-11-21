
/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_EXAMPLES_RGB_FED_AMB
#define PROTOX_EXAMPLES_RGB_FED_AMB

/**************************************************************************************************/

#include <fedtime.hh>
#include <RTI.hh>
#include <NullFederateAmbassador.hh>

#include "fedlet/fed_amb.hpp"

#include "inter_fed_amb.hpp"

/**************************************************************************************************/

using namespace protox::examples;

/**************************************************************************************************/

class rgb_fed_amb : public fedlet::fed_amb
{
private:
  inter_amb_type &inter_amb;
  
public:
  
  rgb_fed_amb( inter_amb_type &inter_amb ) : inter_amb( inter_amb ) {}

  virtual ~rgb_fed_amb() throw( RTI::FederateInternalError ) {} 
  
  virtual void receiveInteraction( RTI::InteractionClassHandle             the_interaction,
                                   const RTI::ParameterHandleValuePairSet &the_parameters,
                                   const RTI::FedTime                     &the_time,
                                   const char                             *the_tag,
                                   RTI::EventRetractionHandle              the_handle )
  throw(
    RTI::InteractionClassNotKnown,
    RTI::InteractionParameterNotKnown,
    RTI::InvalidFederationTime,
    RTI::FederateInternalError )
  {
    inter_amb.recv_interaction( the_interaction, the_parameters, &the_time, the_tag );
  }

  virtual void receiveInteraction( RTI::InteractionClassHandle             the_interaction,
                                   const RTI::ParameterHandleValuePairSet &the_parameters,
                                   const char                             *the_tag )
  throw (
    RTI::InteractionClassNotKnown,
    RTI::InteractionParameterNotKnown,
    RTI::FederateInternalError)
  {
    inter_amb.recv_interaction( the_interaction, the_parameters, 0, the_tag );
  }
};

/**************************************************************************************************/

#endif

/**************************************************************************************************/
