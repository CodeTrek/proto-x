/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_NULL_VALUE_NULL_VALUE_CODEC_HPP
#define PROTOX_NULL_VALUE_NULL_VALUE_CODEC_HPP

/**********************************************************************************************************************/

#include <cstddef>

#include <boost/mpl/int.hpp>

#include <protox/dtl/codec_interface.hpp>
#include <protox/null_value/null_tag.hpp>

/**********************************************************************************************************************/

namespace protox { namespace dtl {

/**********************************************************************************************************************/

struct null_value_codec_impl {
    template< typename T >
    struct octet_boundary { typedef typename boost::mpl::int_< 1 >::type type; };

    template< typename T >
    struct static_size_in_bytes { typedef typename boost::mpl::int_< 0 >::type type; };

    template< typename T >
    inline static std::size_t dynamic_size(T) { return static_size_in_bytes< T >::type::value; }

    template< typename S, typename T >
    inline static void encode(S &s, const T &obj) {}

    template< typename S, typename T >
    inline static void decode(T &v, const S &s, std::size_t &offset) {}
};

/**********************************************************************************************************************/

template<> struct codec_impl< null_value::null_tag > : null_value_codec_impl {};

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
