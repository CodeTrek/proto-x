/*
    Copyright (c) 2010 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_XDR_STRING_HPP
#define PROTOX_XDR_STRING_HPP

/**************************************************************************************************/

#include <vector>

#include <protox/dtl/variable_array.hpp>

#include <protox/xdr/codec_tags.hpp>
#include <protox/xdr/basic_data_representation_table.hpp>

/**************************************************************************************************/

namespace protox {
namespace xdr {

/**************************************************************************************************/

struct string : protox::dtl::variable_array< std::vector< Opaque >, xdr_string > {};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
