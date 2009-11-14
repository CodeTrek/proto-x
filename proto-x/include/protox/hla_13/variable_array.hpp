/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_13_VARIABLE_ARRAY_HPP
#define PROTOX_HLA_13_VARIABLE_ARRAY_HPP

/**************************************************************************************************/

#include <protox/dtl/variable_array.hpp>
#include <protox/hla_13/codec_tags.hpp>

/**************************************************************************************************/

namespace protox {
namespace hla_13 {

/**************************************************************************************************/

template< typename T >
struct variable_array : protox::dtl::variable_array< T, HLA13variableArray > {};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
