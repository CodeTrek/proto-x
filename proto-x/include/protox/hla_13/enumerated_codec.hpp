/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_HLA_13_ENUMERATED_CODEC_HPP
#define PROTOX_HLA_13_ENUMERATED_CODEC_HPP

/**********************************************************************************************************************/

#include <cstddef>

#include <protox/dtl/codec_interface.hpp>
#include <protox/hla_13/codec_tags.hpp>

/**********************************************************************************************************************/

namespace protox {
namespace dtl {

/**********************************************************************************************************************/

template<> struct codec_impl< protox::hla_13::HLA13enumerated > {
    template< typename T >
    struct octet_boundary {
        typedef typename codec::octet_boundary< typename T::value_type >::type type;
    };

    // Compute the data type's size in bytes from size in bits. If the size in bits is not a multiple of 8, add a
    // padding byte.
    template< typename T >
    struct static_size_in_bytes {
        typedef typename codec::static_size_in_bytes< typename T::value_type >::type type;
    };

    template< typename T >
    inline static std::size_t dynamic_size(T) {
        return static_size_in_bytes<T>::type::value;
    }

    template< typename S, typename T >
    inline static void encode(S &s, T const &obj) {
        s.start_enum();
        codec::encode(s, obj.value);
        s.end_enum();
    }

    template< typename S, typename T >
    inline static void decode(T &obj, S const &s, std::size_t &offset) {
        s.start_enum();
        codec::decode(obj.value, s, offset);
        s.end_enum();
    }
};

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
