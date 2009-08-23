
/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_EXAMPLES_HW_FED_AMB
#define PROTOX_EXAMPLES_HW_FED_AMB

/******************************************************************************/

#include <RTI.hh>
#include <NullFederateAmbassador.hh>

/******************************************************************************/

class hw_fed_amb : public NullFederateAmbassador
{
public:
  hw_fed_amb() {}
  virtual ~hw_fed_amb() throw( RTI::FederateInternalError ) {} 
};

/******************************************************************************/

#endif

/******************************************************************************/
