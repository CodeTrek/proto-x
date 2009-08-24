
/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_EXAMPLES_HW_FED_AMB
#define PROTOX_EXAMPLES_HW_FED_AMB

/******************************************************************************/

#include <iostream>
#include <string>

#include <RTI.hh>
#include <NullFederateAmbassador.hh>

/******************************************************************************/

class hw_fed_amb : public NullFederateAmbassador
{
public:
  bool is_announced;
  bool is_ready_to_run;
  
  hw_fed_amb() : is_announced( false ), is_ready_to_run( false ) {}

  virtual ~hw_fed_amb() throw( RTI::FederateInternalError ) {} 
  
  virtual void announceSynchronizationPoint( const char *label, const char *tag )
    //throw( RTI::FederateInternalError )
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

/******************************************************************************/

#endif

/******************************************************************************/
