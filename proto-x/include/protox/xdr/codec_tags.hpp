/*
    Copyright 2010 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_XDR_CODEC_TAGS_HPP
#define PROTOX_XDR_CODEC_TAGS_HPP

/**************************************************************************************************/

/**
 * \namespace protox::xdr
 *
 * XDR encoding.
 */

namespace protox {
namespace xdr {

/**************************************************************************************************/

/**
 * Uninterpreted data.
 */
struct xdr_opaque {};

/**
 * 32 bit, two's complement signed integer.
 */
struct xdr_twos_complement_signed_integer {};

/**
 * 32 bit, unsigned integer.
 */
struct xdr_unsigned_integer {};

/**
 * 32 bit IEEE single precision floating point value.
 */
struct xdr_ieee_floating_point {};

/**
 * 64 bit IEEE single precision floating point value.
 */
struct xdr_ieee_double_precision {};

struct xdr_fixed_length_opaque {};

struct xdr_variable_length_opaque {};

struct xdr_string {};

struct xdr_enumerated {};

struct xdr_fixed_length_array {};

struct xdr_variable_length_array {};

struct xdr_structure {};

struct xdr_union {};

struct xdr_void {};


/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
