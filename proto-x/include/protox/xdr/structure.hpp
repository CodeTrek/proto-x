/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_XDR_STRUCTURE_HPP
#define PROTOX_XDR_STRUCTURE_HPP

/**************************************************************************************************/

#include <protox/dtl/fixed_record.hpp>

#include <protox/xdr/codec_tags.hpp>

/**************************************************************************************************/

namespace protox {
namespace xdr {

/**************************************************************************************************/

template< typename FIELD_VECTOR >
struct structure : protox::dtl::fixed_record< FIELD_VECTOR, xdr_structure > {};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
