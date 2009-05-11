/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_DTL_CODEC_IMPL_HPP
#define PROTOX_DTL_CODEC_IMPL_HPP

/******************************************************************************/

namespace protox { namespace dtl {

/******************************************************************************/

// Provide concrete implementations of codec_impl to enforce protocol
// specific data encoding standards.
template< typename CODEC_TAG > struct codec_impl;

/******************************************************************************/

}} // protox::dtl

/******************************************************************************/

#endif

/******************************************************************************/
