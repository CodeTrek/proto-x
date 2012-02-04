/*
    Copyright (c) 2012 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_SDX_RECORD_HPP
#define PROTOX_SDX_RECORD_HPP

/**************************************************************************************************/

#include <protox/dtl/fixed_record.hpp>

#include <protox/sdx/codec_tags.hpp>

/**************************************************************************************************/

namespace protox {
namespace sdx {

/**************************************************************************************************/

template< typename FIELD_VECTOR >
struct record : protox::dtl::fixed_record< FIELD_VECTOR, sdx_record > {};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
