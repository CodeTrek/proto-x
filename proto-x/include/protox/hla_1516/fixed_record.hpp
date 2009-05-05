/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_1516_FIXED_RECORD_HPP
#define PROTOX_HLA_1516_FIXED_RECORD_HPP

/**************************************************************************************************/

#include <protox/dtl/fixed_record.hpp>
#include <protox/hla_1516/codec_tags.hpp>

/**************************************************************************************************/

namespace protox { namespace hla_1516 {

/**************************************************************************************************/

template< typename FIELD_VECTOR >
struct fixed_record : protox::dtl::fixed_record< FIELD_VECTOR, HLAfixedRecord > {};

/**************************************************************************************************/

}} // protox::hla_1516

/**************************************************************************************************/

#endif

/**************************************************************************************************/
