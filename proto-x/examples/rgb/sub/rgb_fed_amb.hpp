
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

#include "obj_fed_amb.hpp"

#include "utils/fed_amb_util.hpp"

/******************************************************************************/

class rgb_fed_amb : public fed_amb_util
{
private:
  obj_amb_type &obj_amb;

public:
  rgb_fed_amb( obj_amb_type &obj_amb ) : obj_amb( obj_amb ) {}

  virtual ~rgb_fed_amb() throw( RTI::FederateInternalError ) {} 
  
  ////////////////////////////////
  // Object Management Services //
  ////////////////////////////////

  virtual void discoverObjectInstance (
          RTI::ObjectHandle          theObject,      // supplied C1
          RTI::ObjectClassHandle     theObjectClass, // supplied C1
    const char*                      theObjectName)  // supplied C4  
  {
    obj_amb.discover_object( theObjectClass, theObject, theObjectName );
  }

  virtual void reflectAttributeValues (
          RTI::ObjectHandle                 theObject,     // supplied C1
    const RTI::AttributeHandleValuePairSet& theAttributes, // supplied C4
    const RTI::FedTime&                     theTime,       // supplied C1
    const char                             *theTag,        // supplied C4
          RTI::EventRetractionHandle        theHandle)     // supplied C1
  {}

  virtual void reflectAttributeValues (
          RTI::ObjectHandle                 theObject,     // supplied C1
    const RTI::AttributeHandleValuePairSet& theAttributes, // supplied C4
    const char                             *theTag)        // supplied C4
  {}

  virtual void removeObjectInstance (
          RTI::ObjectHandle          theObject, // supplied C1
    const RTI::FedTime&              theTime,   // supplied C4
    const char                      *theTag,    // supplied C4
          RTI::EventRetractionHandle theHandle) // supplied C1
  {
    // Ignore time
    removeObjectInstance( theObject, theTag );
  }

  virtual void removeObjectInstance (
          RTI::ObjectHandle          theObject, // supplied C1
    const char                      *theTag)    // supplied C4
  {
    obj_amb.remove_object( theObject );
  }
};

/******************************************************************************/

#endif

/******************************************************************************/
