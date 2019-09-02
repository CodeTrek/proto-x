/*
    Copyright 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_1516_CODEC_TAGS_HPP
#define PROTOX_HLA_1516_CODEC_TAGS_HPP

/**************************************************************************************************/

/**
 * \namespace protox::hla_1516
 *
 * HLA 1516 encoding.
 */
namespace protox {
namespace hla_1516 {

/**************************************************************************************************/

/**
 * Hardware portable encoding.
 */
struct HLAportable {};

/**
 * 16 bit signed, two's complement integer.
 */
struct HLA16BitTwosComplementSigned {};

/**
 * 32 bit signed, two's complement integer.
 */
struct HLA32BitTwosComplementSigned {};

/**
 * 64 bit signed, two's complement integer.
 */
struct HLA64BitTwosComplementSigned {};

/**
 * 32 bit IEEE single precision floating point value.
 */
struct HLA32BitIEEESinglePrecision {};

/**
 * 64 bit IEEE single precision floating point value.
 */
struct HLA64BitIEEEDoublePrecision {};

/**
 * HLA 1516 fixed record encoding.
 */
struct HLAfixedRecord {};

/**
 * HLA 1516 fixed array encoding.
 */
struct HLAfixedArray {};

/**
 * HLA 1516 variable array encoding.
 */
struct HLAvariableArray {};

/**
 * HLA 11516 enumerated value encoding.
 */
struct HLAenumerated {};

/**
 * HLA 11516 variant record encoding.
 */
struct HLAvariantRecord {};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
