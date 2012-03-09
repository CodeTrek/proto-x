/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_HLA_13_FIXED_ARRAY_CODEC_HPP
#define PROTOX_HLA_13_FIXED_ARRAY_CODEC_HPP

/**********************************************************************************************************************/

#include <cstddef>

#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/not_equal_to.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/multiplies.hpp>

#include <protox/dtl/unknown_static_size.hpp>
#include <protox/dtl/codec_interface.hpp>

#include <protox/hla_13/codec_tags.hpp>

/**********************************************************************************************************************/

namespace protox {
namespace dtl {

/**********************************************************************************************************************/

namespace fixed_array_codec_13 {

/**********************************************************************************************************************/

template< bool Has_Static_Size > struct layout_;

/**********************************************************************************************************************/

// Specialization for arrays with fixed size elements.
template<>
struct layout_< true > {
    // Dynamic size is equal to the static size.
    template< typename T >
    inline static std::size_t dynamic_size(T const &) {
        // Ensure elements of T have a fixed size.
        BOOST_STATIC_ASSERT((
            codec::static_size_in_bytes< typename T::value_type >::value != UNKNOWN_STATIC_SIZE::value
        ));

        return codec::static_size_in_bytes< T >::value;
    }
};

/**********************************************************************************************************************/

// Specialization for arrays with variable size elements.
template<>
struct layout_< false > {
    template< typename T >
    inline static std::size_t dynamic_size(T const &obj) {
        // Ensure elements of T are not fixed size.
        BOOST_STATIC_ASSERT((
            codec::static_size_in_bytes< typename T::value_type >::value == UNKNOWN_STATIC_SIZE::value
        ));

        std::size_t size = 0; // Used to accumulate T's size.

        // For each element i in the array...
        for (std::size_t i = 0; i < T::static_num_elements; ++i) {
            std::size_t const obj_size = codec::dynamic_size(obj[i]);
            size += obj_size;
        }

        return size;
    }
};

/**********************************************************************************************************************/

// Create this array's impl compile type interface.
template< typename T >
struct impl {
    // Is this array's size fixed or dynamic?
    typedef boost::mpl::not_equal_to<
        typename codec::static_size_in_bytes< T >::type,
        UNKNOWN_STATIC_SIZE
    > has_static_size;

    typedef layout_< has_static_size::value > type;
};

/**********************************************************************************************************************/

}

/**********************************************************************************************************************/

template<> struct codec_impl< protox::hla_13::HLA13fixedArray > {
    template< typename T >
    struct octet_boundary {
        typedef typename codec::octet_boundary< typename T::value_type >::type type;
    };

    template< typename T >
    struct static_size_in_bytes {
        // Perform a compile-time operation to compute the total size of the array (in bytes). Note that if the element
        // type T does not have a fixed size, then the total size of the array is computed at run-time.
        typedef typename boost::mpl::if_<
            // Size of T is not fixed?
            boost::mpl::equal_to< typename codec::static_size_in_bytes< typename T::value_type >::type,
                                  UNKNOWN_STATIC_SIZE >,
      
            // true : unknown static size.
            protox::dtl::UNKNOWN_STATIC_SIZE,

            // false : compute the total size of the array in bytes.
            boost::mpl::multiplies<
                boost::mpl::int_< T::static_num_elements >,
                typename codec::static_size_in_bytes< typename T::value_type >::type >
        >::type type;
    };

    template< typename T >
    inline static std::size_t dynamic_size(T const &obj) {
        return fixed_array_codec_13::impl< T >::type::dynamic_size(obj);
    };

    template< typename S, typename A >
    inline static void encode(S &s, A const &obj) {
        s.start_fixed_array();

        // For each element in the array, except for the last ...
        for (int i = 0; i < A::static_num_elements; ++i) {
            codec::encode(s, obj[i]);
        }

        s.end_fixed_array();
    }

    template< typename S, typename A >
    inline static void decode(A &obj, S const &s, std::size_t &offset) {
        typedef typename fixed_array_codec_13::impl< A >::type layout;

        s.start_fixed_array();

        // For each element in the array...
        for (int i = 0; i < A::static_num_elements; ++i) {
            codec::decode(obj[i], s, offset);
        }

        s.end_fixed_array();
    }
};

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
