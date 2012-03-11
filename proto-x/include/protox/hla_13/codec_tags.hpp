/*
    Copyright 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_HLA_13_CODEC_TAGS_HPP
#define PROTOX_HLA_13_CODEC_TAGS_HPP

/**********************************************************************************************************************/

/**
 * \namespace protox::hla_13
 *
 * HLA 1.3 encoding.
 */

namespace protox {
namespace hla_13 {

/**********************************************************************************************************************/

/**
 * Hardware portable encoding.
 */
struct HLA13portable                     {};

/**
 * 16 bit, two's complement signed integer.
 */
struct HLA13_16BitTwosComplementSigned   {};

/**
 * 32 bit, two's complement signed integer.
 */
struct HLA13_32BitTwosComplementSigned   {};

/**
 * 16 bit, two's complement unsigned integer.
 */
struct HLA13_16BitTwosComplementUnsigned {};

/**
 * 32 bit, two's complement unsigned integer.
 */
struct HLA13_32BitTwosComplementUnsigned {};

/**
 * 32 bit IEEE single precision floating point value.
 */
struct HLA13_32BitIEEESinglePrecision    {};

/**
 * 64 bit IEEE single precision floating point value.
 */
struct HLA13_64BitIEEEDoublePrecision    {};

/**
 * HLA 13 complex type encoding.
 */
struct HLA13complexType                  {};

/**
 * HLA 13 fixed array type encoding.
 */
struct HLA13fixedArray                   {};

/**
 * HLA 13 variable array type encoding.
 */
struct HLA13variableArray                {};

/**
 * HLA 13 enumerated type encoding.
 */
struct HLA13enumerated                   {};

/**
 * HLA 13 variant record encoding.
 */
struct HLA13variantRecord                {};

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
