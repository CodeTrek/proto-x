/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_HLA_1516_ENUMERATED_HPP
#define PROTOX_HLA_1516_ENUMERATED_HPP

/******************************************************************************/

#include <protox/dtl/enumerated.hpp>
#include <protox/hla_1516/codec_tags.hpp>

/******************************************************************************/

namespace protox { namespace hla_1516 {

/******************************************************************************/

template< typename E, typename T >
struct enumerated : protox::dtl::enumerated< E, T, HLAenumerated >
{
  friend struct protox::dtl::codec_impl<protox::hla_1516::HLAenumerated>;

  enumerated() {}
  enumerated(T const v) : protox::dtl::enumerated< E, T, HLAenumerated >(v) {}
  enumerated(enumerated const &v) :
    protox::dtl::enumerated< E, T, HLAenumerated >(v)
  {}
};

/******************************************************************************/

}} // protox::hla_1516

/******************************************************************************/

#endif

/******************************************************************************/
