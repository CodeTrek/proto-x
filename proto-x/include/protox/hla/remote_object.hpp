/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_HLA_REMOTE_OBJECT_HPP
#define PROTOX_HLA_REMOTE_OBJECT_HPP

/**********************************************************************************************************************/

#include <map>

#include <RTI.hh>

#include <boost/mpl/empty_base.hpp>

#include <protox/hla/object_event_type.hpp>

/**********************************************************************************************************************/

namespace protox {
namespace hla {

/**********************************************************************************************************************/

/**
 * Maintains a database of discovered objects of type \a T.
 *
 * \tparam T The type of managed object.
 */
template< typename T >
struct remote_object_base {
    typedef T remote_object_type;
    typedef std::map< RTI::ObjectHandle, remote_object_type > map_type;

    /**
     * Used to iterate over objects of type \a T.
     */
    typedef typename map_type::const_iterator const_it;

    map_type objects;

    void (*handler) (const remote_object_type &, object_event_type, const RTI::FedTime *, const char *tag);

    remote_object_base() : handler(0) {}

    bool add_object(RTI::ObjectClassHandle class_handle, RTI::ObjectHandle object_handle, const char *object_name) {
        if (remote_object_type::get_handle() != class_handle) {
            return false;
        }

        objects[object_handle] = remote_object_type();

        if (object_name != 0) {
            objects[object_handle].set_obj_name(std::string(object_name));
        }

        if (handler != 0) {
            (*handler)(objects[object_handle], protox::hla::OBJ_DISCOVERED, 0, 0);
        }

        return true;
    }

    bool delete_object(RTI::ObjectHandle object_handle) {
        if (objects.find(object_handle) != objects.end()) {
            if (handler != 0) {
                (*handler)(objects[object_handle], protox::hla::OBJ_REMOVED, 0, 0);
            }
        }

        return (objects.erase( object_handle ) == 1);
    }

    bool reflect(      RTI::ObjectHandle                 object_handle,
                 const RTI::AttributeHandleValuePairSet &attrs,
                 const RTI::FedTime                     *time,
                 const char                             *tag) {

        typename map_type::iterator it = objects.find(object_handle);

        if (it == objects.end()) {
            return false;
        }

        it->second.reflect(attrs, time);

        if (handler != 0) {
            (*handler)(objects[object_handle], protox::hla::OBJ_REFLECTED, time, tag);
        }

        return true;
    }
};

/**********************************************************************************************************************/

// Forward declaration
template< typename A, typename B > struct remote_object_inherit;

/**********************************************************************************************************************/

template< typename A >
struct remote_object_inherit< A, boost::mpl::empty_base > : A, boost::mpl::empty_base {

    template< typename T >
    inline void set_handler(void (*h)(const T &, object_event_type, const RTI::FedTime *, const char *tag)) {
        static_cast< remote_object_base< T > & >(*this).handler = h;
    }

    void discover_object(      RTI::ObjectClassHandle class_handle,
                               RTI::ObjectHandle      object_handle,
                         const char                  *object_name) {
        bool obj_added = A::add_object(class_handle, object_handle, object_name);

        if (!obj_added) {
            throw RTI::ObjectClassNotKnown("");
        }
    }

    void remove_object(RTI::ObjectHandle object_handle) { A::delete_object(object_handle); }

    void reflect_object(      RTI::ObjectHandle                 object_handle,
                        const RTI::AttributeHandleValuePairSet &attrs,
                        const RTI::FedTime                     *time,
                        const char                             *tag) {
        const bool reflected = A::reflect(object_handle, attrs, time, tag);

        if (!reflected) {
            throw RTI::ObjectNotKnown("");
        }
    }


    template< typename T >
    inline typename remote_object_base< T >::const_it begin() const {
        return (static_cast< remote_object_base< T > const & >(*this).objects.begin());
    }

    template< typename T >
    inline typename remote_object_base< T >::const_it end() const {
        return (static_cast< remote_object_base< T > const & >(*this).objects.end());
    }

    template< typename T >
    inline std::size_t size() const { return (static_cast< remote_object_base< T > const & >(*this).objects.size()); }

    template< typename T >
    inline bool empty() const { return (static_cast< remote_object_base< T > const & >(*this).objects.empty()); }
};

/**********************************************************************************************************************/

/**
 * Defines \c remote_object functions.
 */

// A is remote_object and B is set of predecessor remote_objects.
template< typename A, typename B >
struct remote_object_inherit : A, B {
    template< typename T >
    inline void set_handler(void (*h)(const T &, object_event_type, const RTI::FedTime *, const char *tag)) {
        static_cast< remote_object_base< T > & >(*this).handler = h;
    }

    /**
     * Forward \c RTI::discoverObjectInstance callbacks to this function.
     */
    void discover_object(      RTI::ObjectClassHandle class_handle,
                               RTI::ObjectHandle      object_handle,
                         const char                  *object_name) {
        if (A::add_object(class_handle, object_handle, object_name)) {
            return;
        }

        B::discover_object(class_handle, object_handle, object_name);
    }

    /**
     * Forward \c RTI::removeObjectInstance callbacks to this function.
     */
    void remove_object(RTI::ObjectHandle object_handle) {
        if (A::remove_object(object_handle)) {
            return;
        }

        B::remove_object(object_handle);
    }

    /**
     * Forward \c RTI::reflectAttributeValues callbacks to this function.
     */
    void reflect_object(      RTI::ObjectHandle                 object_handle,
                        const RTI::AttributeHandleValuePairSet &attrs,
                        const RTI::FedTime                     *time,
                        const char                             *tag) {
        if (A::reflect(object_handle, attrs, time, tag)) {
            return;
        }

        B::reflect_object(object_handle, attrs, time, tag);
    }

    template< typename T >
    inline typename remote_object_base< T >::const_it begin() const {
        return (static_cast< remote_object_base< T > const & >(*this).objects.begin());
    }

    template< typename T >
    inline typename remote_object_base< T >::const_it end() const {
        return (static_cast< remote_object_base< T > const & >(*this).objects.end());
    }

    /**
     * \return The number of discovered objects of type \a T.
     */
    template< typename T >
    inline std::size_t size() const { return (static_cast< remote_object_base< T > const & >(*this).objects.size()); }

    /**
     * \return true if there are no objects of the given type \a T
     */
    template< typename T >
    inline bool empty() const { return (static_cast< remote_object_base< T > const & >(*this).objects.empty()); }
};

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
