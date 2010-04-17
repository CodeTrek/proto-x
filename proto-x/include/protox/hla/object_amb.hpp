/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_OBJECT_AMB_HPP
#define PROTOX_HLA_OBJECT_AMB_HPP

/**************************************************************************************************/

#include <cstddef>

#include <boost/mpl/inherit_linearly.hpp>
#include <boost/mpl/placeholders.hpp>

#include <RTI.hh>

#include <protox/hla/remote_object.hpp>

/**************************************************************************************************/

namespace protox {
namespace hla {

/**************************************************************************************************/

/**
 * Generates an ambassador that maintains a database of discovered object instances. You can
 * also register type safe callback handlers that is invoked whenever an object is discovered,
 * relfected, or removed.
 *
 * \tparam CLASS_TYPE_VECTOR A vector of object class types to be handled.
 *
 * \sa protox::hla::o_class_type
 * \sa protox::hla::remote_object_inherit
 *
 * Example:
 *
 * \code
 * // Platform object class type
 * typedef o_class_type< platform_som, q_name< Platform > >::type platform_type;
 *
 * // An object ambassador used to manage object's that are discovered during runtime.
 * typedef hla::object_amb< mpl::vector< platform_type > >::type obj_amb_type;
 *
 * obj_amb_type obj_amb;
 *
 * // Define an HLA federate ambassador used to forward object discovery and update events to a
 * // proto-x object ambassador.
 * class fed_amb : public RTI::FederateAmbassador
 * {
 * private:
 *   obj_amb_type   &obj_amb;
 *
 * public:
 *   fed_amb( obj_amb_type &obj_amb, inter_amb_type &inter_amb ) : obj_amb(obj_amb) {}
 *
 *  // /////////////////////////////////////////////////////////////////////////////////////////////
 *  // Object Management Services
 *  // /////////////////////////////////////////////////////////////////////////////////////////////
 *
 *   virtual void discoverObjectInstance( RTI::ObjectHandle      the_object,
 *                                        RTI::ObjectClassHandle the_object_class,
 *                                        const char*            the_object_name )
 *   {
 *     obj_amb.discover_object( the_object_class, the_object, the_object_name );
 *   }
 *
 *   virtual void reflectAttributeValues( RTI::ObjectHandle                       the_object,
 *                                        const RTI::AttributeHandleValuePairSet &the_attributes,
 *                                        const RTI::FedTime&                     the_time,
 *                                        const char                             *the_tag,
 *                                        RTI::EventRetractionHandle              the_handle )
 *   {
 *     obj_amb.reflect_object( the_object, the_attributes, &the_time, the_tag );
 *   }
 *
 *   virtual void removeObjectInstance( RTI::ObjectHandle          the_object,
 *                                      const RTI::FedTime&        the_time,
 *                                      const char                *the_tag,
 *                                      RTI::EventRetractionHandle the_handle )
 *   {
 *     removeObjectInstance( the_object, the_tag );
 *   }
 * };
 *
 * // Use the proto-x object ambassador to iterate over all objects of type platform_type.
 * obj_amb_type::const_it< platform_type >::type it;
 *
 * for (it = obj_amb.begin< platform_type >(); it != obj_amb.end< platform_type >(); ++it)
 * {
 *   const platform_type &p = it->second;
 *
 *   // Print the platform's current position.
 *   cout << "(" << p.a_< Position >().f_< X >() << ", " << p.a_< Position >().f_< Y >() << ")\n";
 * }
 *
 * // Platform object type handler.
 * static void platform_handler( const platform_type &obj,
 *                               hla::object_event_type event,
 *                               const RTI::FedTime *,
 *                               const char *tag )
 * {
 *   switch (event)
 *   {
 *     case protox::hla::OBJ_DISCOVERED:
 *       cout << "object " << obj.get_obj_name().c_str() << " discovered.\n";
 *       break;
 *     case protox::hla::OBJ_REFLECTED:
 *       cout << "object " << obj.get_obj_name().c_str() << " reflected.\n";
 *       break;
 *     case protox::hla::OBJ_REMOVED:
 *       cout << "object " << obj.get_obj_name().c_str() << " removed.\n";
 *       break;
 *   }
 * }
 *
 * // Register our handler with our object ambassador.
 * obj_amb.set_handler( platform_handler );
 * \endcode
 */

/**************************************************************************************************/

template< typename CLASS_TYPE_VECTOR >
struct object_amb
{
  typedef typename boost::mpl::inherit_linearly<
    CLASS_TYPE_VECTOR,
    remote_object_inherit< remote_object_base< boost::mpl::placeholders::_2 >,
                           boost::mpl::placeholders::_1 >
  >::type remote_objects_type;

  struct type : remote_objects_type
  {
    template< typename T >
    struct const_it
    {
      typedef typename remote_object_base< T >::const_it type;
    };
  };
};

/**************************************************************************************************/
  
}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
