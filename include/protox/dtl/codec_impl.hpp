/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_DTL_CODEC_IMPL_HPP
#define PROTOX_DTL_CODEC_IMPL_HPP

/**********************************************************************************************************************/

namespace protox {
namespace dtl {

/**********************************************************************************************************************/

/**
 * Implementers of encode/decode functionality must define the set of \c CODEC_TAG tags and their associated
 * \c codec_impl implementations. The \c CODEC_TAG types are used to dispatch to the correct \c codec_impl
 * implementation.
 *
 * <b>Important:<\b> All \c codec_impl definitions must be in the <tt>protox::dtl</tt> namespace.
 *
 * @see protox::dtl::codec_interface
 */
template< typename CODEC_TAG > struct codec_impl;

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
