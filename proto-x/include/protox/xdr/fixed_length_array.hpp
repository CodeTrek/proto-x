/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_XDR_FIXED_LENGTH_ARRAY_HPP
#define PROTOX_XDR_FIXED_LENGTH_ARRAY_HPP

/**************************************************************************************************/

#include <protox/dtl/fixed_array.hpp>

#include <protox/xdr/codec_tags.hpp>

/**************************************************************************************************/

namespace protox {
namespace xdr {

/**************************************************************************************************/

template< typename T, int N >
struct fixed_length_array : protox::dtl::fixed_array< T, N, xdr_fixed_length_array > {};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
