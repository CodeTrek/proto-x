/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_13_COMPLEX_TYPE_HPP
#define PROTOX_HLA_13_COMPLEX_TYPE_HPP

/**************************************************************************************************/

#include <protox/dtl/fixed_record.hpp>
#include <protox/hla_13/codec_tags.hpp>

/**************************************************************************************************/

namespace protox {
namespace hla_13 {

/**************************************************************************************************/

template< typename FIELD_VECTOR >
struct complex_type : protox::dtl::fixed_record< FIELD_VECTOR, HLA13complexType > {};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
