
/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_EXAMPLES_RGB_FED_AMB
#define PROTOX_EXAMPLES_RGB_FED_AMB

/**************************************************************************************************/

#include <iostream>
#include <string>

#include <fedtime.hh>
#include <RTI.hh>
#include <NullFederateAmbassador.hh>

#include "obj_fed_amb.hpp"

#include "fedlet/fed_amb.hpp"

/**************************************************************************************************/

using namespace protox::examples;

/**************************************************************************************************/

class rgb_fed_amb : public fedlet::fed_amb
{
private:
  obj_amb_type &obj_amb;

public:
  rgb_fed_amb( obj_amb_type &obj_amb ) : obj_amb( obj_amb ) {}

  virtual ~rgb_fed_amb() throw( RTI::FederateInternalError ) {} 
  
  //////////////////////////////////////////////////////////////////////////////////////////////////
  // Object Management Services
  //////////////////////////////////////////////////////////////////////////////////////////////////

  virtual void discoverObjectInstance( RTI::ObjectHandle      the_object,
                                       RTI::ObjectClassHandle the_object_class,
                                       const char*            the_object_name )
  {
    obj_amb.discover_object( the_object_class, the_object, the_object_name );
  }

  virtual void reflectAttributeValues( RTI::ObjectHandle                       the_object,
                                       const RTI::AttributeHandleValuePairSet &the_attributes,
                                       const RTI::FedTime&                     the_time,
                                       const char                             *the_tag,
                                       RTI::EventRetractionHandle              the_handle )
  {
    obj_amb.reflect_object( the_object, the_attributes, &the_time, the_tag );
  }

  virtual void reflectAttributeValues( RTI::ObjectHandle                       the_object,
                                       const RTI::AttributeHandleValuePairSet &the_attributes,
                                       const char                             *the_tag )
  {
    obj_amb.reflect_object( the_object, the_attributes, 0, the_tag );
  }

  virtual void removeObjectInstance( RTI::ObjectHandle          the_object,
                                     const RTI::FedTime&        the_time,
                                     const char                *the_tag,
                                     RTI::EventRetractionHandle the_handle )
  {
    // Ignore time
    removeObjectInstance( the_object, the_tag );
  }

  virtual void removeObjectInstance ( RTI::ObjectHandle the_object, const char *the_tag )
  {
    obj_amb.remove_object( the_object );
  }
};

/**************************************************************************************************/

#endif

/**************************************************************************************************/
