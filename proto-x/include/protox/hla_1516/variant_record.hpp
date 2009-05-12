/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_HLA_1516_VARIANT_RECORD_HPP
#define PROTOX_HLA_1516_VARIANT_RECORD_HPP

/******************************************************************************/

#include <protox/dtl/variant_record.hpp>
#include <protox/hla_1516/codec_tags.hpp>

/******************************************************************************/

namespace protox { namespace hla_1516 {

/******************************************************************************/

template<
  typename D_Type,
  typename D_Vector,
  typename Other = protox::dtl::discriminant_other_none
>
struct variant_record :
  protox::dtl::variant_record< D_Type, D_Vector, Other, HLAvariantRecord >
{};

/******************************************************************************/

}} // protox::hla_1516

/******************************************************************************/

#endif

/******************************************************************************/
