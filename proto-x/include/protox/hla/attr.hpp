/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_HLA_ATTR_HPP
#define PROTOX_HLA_ATTR_HPP

/**********************************************************************************************************************/

#include <string>
#include <set>

#include <RTI.hh>

#include <boost/shared_ptr.hpp>
#include <boost/mpl/empty_base.hpp>

#include <protox/io/byte_data_source.hpp>
#include <protox/io/byte_data_sink.hpp>

/**********************************************************************************************************************/

namespace protox {
namespace hla {

/**********************************************************************************************************************/

enum attr_state { PUBLISHED = 1L << 0, SUBSCRIBED = 1L << 1 };

/**********************************************************************************************************************/

template< typename T >
struct attr_base {

    private:
        bool updated;

        unsigned short &get_state_vector() {
            static unsigned short state_vector = 0;
            return state_vector;
        }

    public:
        typedef T attr_type;
        typename T::value_type value;

        RTI::AttributeHandle handle;

        static char const *name() { return T::name(); }

        attr_base() : updated(false), handle(0) {}

        static void set(attr_state s)    { get_state_vector() |= s; }
        static void clear(attr_state s)  { get_state_vector() &= (~s); }
        static bool is_set(attr_state s) { return ((get_state_vector() & s) != 0); }

        void set_updated(bool f) { updated = f; }

    protected:
        bool is_updated() const { return updated; }

        template< typename S >
        void init_handle(const std::string &class_name) { handle = S::get_attr_handle(class_name, name()); }
  
        void add_handle(RTI::AttributeHandleSet &ahs) { ahs.add(handle); }

        void update_value(boost::shared_ptr< RTI::AttributeHandleValuePairSet > set_ptr) {
            if (!is_updated()) {
                return;
            }

            set_updated(false);

            protox::io::byte_data_sink sink;
            sink.encode(value);
            set_ptr->add(handle, sink.getDataBuffer(), (unsigned long) sink.getDataBufferSize());
        }

        void reflect(const RTI::AttributeHandleValuePairSet &ahv_set, const RTI::FedTime *time) {

            for (RTI::ULong i = 0; i < ahv_set.size(); ++i) {
                RTI::AttributeHandle h = ahv_set.getHandle(i);

                if (h == this->handle) {
                    RTI::ULong length = 0;
                    char *data = ahv_set.getValuePointer(i, length);
                    protox::io::byte_data_source ds(data, length);
                    ds.decode( this->value);

                    return;
                }
            }
        }
};

/**********************************************************************************************************************/

/**
 * Use this template to generate an attribute definition type that can be used as part of an
 * object class definition in an attribute table.
 *
 * \tparam T The attribute's type.
 *
 * Example:
 * \code
 * // Define an attribute called Name of type ASCIIString.
 * struct Name : attr< ASCIIString > {HLA_NAME( "Name" )}
 * \endcode
 *
 * Example use in an attribute table:
 * \code
 * ////// Attribute Table ////////////////
 * //     +------------------------------+-----------+-------------------+----------------------+
 * //     | Name                         | Attribute | Datatype          | String Name          |
 * //     +------------------------------+-----------+-------------------+----------------------+
 *   struct Player {HLA_NAME( "Player" )};
 *                                  struct Name      : attr< ASCIIString > {HLA_NAME( "Name"  )};
 *                                  struct Score     : attr< Count >       {HLA_NAME( "Score" )};
 * //     +------------------------------------------+-------------------+----------------------+
 *
 * \endcode
 *
 */
template< typename T >
struct attr {
    typedef T value_type;
};

/**********************************************************************************************************************/

// Forward declaration
template< typename A, typename B > struct attr_inherit;

/**********************************************************************************************************************/

struct attr_empty_base {

    template< typename T >
    void init_handles(const std::string &class_name) {}

    void update_values(boost::shared_ptr< RTI::AttributeHandleValuePairSet> set_ptr) {}

    template< typename T >
    static void collect_handles(const std::string &, std::set< std::string > *, RTI::AttributeHandleSet &) {}

    static RTI::ULong count_attrs() { return 0; }

    static void set_state( attr_state ) {}

    void collect_updated_attrs(std::vector< RTI::AttributeHandle > &) {}

    void reflect(const RTI::AttributeHandleValuePairSet &, const RTI::FedTime *) {}

    template< typename T >
    inline RTI::AttributeHandle get_attr_handle() { throw RTI::AttributeNotDefined("attribute not defined"); }
};

/**********************************************************************************************************************/

template< typename A >
struct attr_inherit< A, attr_empty_base > : A, attr_empty_base {

    public:
        template< typename T >
        void init_handles(const std::string &class_name) { A::template init_handle< T >(class_name); }

        void update_values(boost::shared_ptr< RTI::AttributeHandleValuePairSet> set_ptr) { A::update_value(set_ptr); }
  
        template< typename T >
        static void collect_handles(const std::string       &class_name,
                                    std::set< std::string > *attr_names,
                                    RTI::AttributeHandleSet &ahs) {
            bool in_set = true;

            if (attr_names != 0) {
                in_set = (attr_names->find(A::name()) != attr_names->end());
            }

            if (in_set) {
                RTI::AttributeHandle handle = T::get_attr_handle(class_name, A::name());
                ahs.add(handle);

                if (attr_names != 0) {
                    attr_names->erase(A::name());
                }
            }
        }
  
        static RTI::ULong count_attrs() { return 1; }

        static void set_state(attr_state s) { A::set(s); }

        void collect_updated_attrs(std::vector< RTI::AttributeHandle > &handles) {
            if (A::is_updated()) {
                handles.push_back(A::handle);
            }
        }

    public:
        template< typename T >
        inline typename T::value_type const &get_attribute() const {
            return (static_cast< attr_base< T > const & >(*this).value);
        }

        template< typename T >
        inline typename T::value_type &get_attribute() {
            static_cast< attr_base< T > & >(*this).set_updated(true);
            return (static_cast< attr_base< T > & >(*this).value);
        }

        template< typename T >
        inline RTI::AttributeHandle get_attr_handle() {
            return (static_cast< attr_base< T > & >(*this).handle);
        }

        void reflect(const RTI::AttributeHandleValuePairSet &ahv_set, const RTI::FedTime *time) {
            A::reflect(ahv_set, time);
        }
};

/**********************************************************************************************************************/

//
// A is an attribute and B is set of predecessor attributes.
//
template< typename A, typename B >
struct attr_inherit : A, B {

    public:
        template< typename T >
        void init_handles(const std::string &class_name) {
            A::template init_handle< T >(class_name);
            B::template init_handles< T >(class_name);
        }

        void update_values(boost::shared_ptr< RTI::AttributeHandleValuePairSet > set_ptr) {
            A::update_value(set_ptr);
            B::update_values(set_ptr);
        }
  
        static RTI::ULong count_attrs() {
            unsigned int total = 1 + B::count_attrs();
            return total;
        }

        template< typename T >
        static void collect_handles(const std::string       &class_name,
                                    std::set< std::string > *attr_names,
                                    RTI::AttributeHandleSet &ahs) {
            bool in_set = true;

            if (attr_names != 0) {
                in_set = (attr_names->find(A::name()) != attr_names->end());
            }

            if (in_set) {
                RTI::AttributeHandle handle = T::get_attr_handle(class_name, A::name());
                ahs.add(handle);

                if (attr_names != 0) {
                  attr_names->erase(A::name());
                }
            }

            B::template collect_handles< T >(class_name, attr_names, ahs);
        }

        static void set_state(attr_state s) {
            A::set(s);
            B::set_state(s);
        }

        void collect_updated_attrs(std::vector< RTI::AttributeHandle > &handles) {
            if (A::is_updated()) {
                handles.push_back(A::handle);
            }

            B::collect_updated_attrs(handles);
        }

    public:
      template< typename T >
      inline typename T::value_type const &get_attribute() const {
          return (static_cast< attr_base< T > const & >(*this).value);
      }

      template< typename T >
      inline typename T::value_type &get_attribute() {
          static_cast< attr_base< T > & >(*this).set_updated(true);
          return (static_cast< attr_base< T > & >(*this).value);
      }
  
      template< typename T >
      inline RTI::AttributeHandle get_attr_handle() { return (static_cast< attr_base< T > & >(*this).handle); }

      void reflect(const RTI::AttributeHandleValuePairSet &ahv_set, const RTI::FedTime *time) {
          A::reflect(ahv_set, time);
          B::reflect(ahv_set, time);
      }
};

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
