/*
    Copyright 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_13_BASIC_DATA_REPRESENTATION_TABLE_HPP
#define PROTOX_HLA_13_BASIC_DATA_REPRESENTATION_TABLE_HPP

/**************************************************************************************************/

#include <protox/dtl/endian_enum.hpp>
#include <protox/dtl/basic.hpp>

#include <protox/hla_13/codec_tags.hpp>

/**************************************************************************************************/

namespace protox {
namespace hla_13 {

/**************************************************************************************************/

/**
 * \class HLA13octet
 * HLA13octet
 */

/**
 * \class HLA13char
 * HLA13char
 */

/**
 * \class HLA13short
 * HLA13short
 */

/**
 * \class HLA13unsigned_short
 * HLA13unsigned_short
 */

/**
 * \class HLA13long
 * HLA13long
 */

/**
 * \class HLA13unsigned_long
 * HLA13unsigned_long
 */

/**
 * \class HLA13float
 * HLA13float
 */

/**
 * \class HLA13double
 * HLA13double
 */

/**************************************************************************************************/

//   +-------------------------------------------------------------------------------------------------------------------------+
//   | Basic data representation table                                                                                         |
//   +--------------------------------------------------+--------------+-------------------+-----------------------------------+
//   | Name                                             | Size in bits | Endian            | Encoding                          |
//   +--------------------------------------------------+--------------+-------------------+-----------------------------------+
struct HLA13octet          : dtl::basic< unsigned char,    8,            dtl::endian::big,   HLA13portable                     > {PROTOX_BASIC( HLA13octet          )};
//   +--------------------------------------------------+--------------+-------------------+-----------------------------------+
struct HLA13char           : dtl::basic< unsigned char,    8,            dtl::endian::big,   HLA13portable                     > {PROTOX_BASIC( HLA13char           )};
//   +--------------------------------------------------+--------------+-------------------+-----------------------------------+
struct HLA13short          : dtl::basic< short,           16,            dtl::endian::big,   HLA13_16BitTwosComplementSigned   > {PROTOX_BASIC( HLA13short          )};
//   +--------------------------------------------------+--------------+-------------------+-----------------------------------+
struct HLA13unsigned_short : dtl::basic< unsigned short,  16,            dtl::endian::big,   HLA13_16BitTwosComplementUnsigned > {PROTOX_BASIC( HLA13unsigned_short )};
//   +--------------------------------------------------+--------------+-------------------+-----------------------------------+
struct HLA13long           : dtl::basic< long,            32,            dtl::endian::big,   HLA13_32BitTwosComplementSigned   > {PROTOX_BASIC( HLA13long           )};
//   +--------------------------------------------------+--------------+-------------------+-----------------------------------+
struct HLA13unsigned_long  : dtl::basic< unsigned long,   32,            dtl::endian::big,   HLA13_32BitTwosComplementUnsigned > {PROTOX_BASIC( HLA13unsigned_long  )};
//   +--------------------------------------------------+--------------+-------------------+-----------------------------------+
struct HLA13float          : dtl::basic< float,           32,            dtl::endian::big,   HLA13_32BitIEEESinglePrecision    > {PROTOX_BASIC( HLA13float          )};
//   +--------------------------------------------------+--------------+-------------------+-----------------------------------+
struct HLA13double         : dtl::basic< double,          64,            dtl::endian::big,   HLA13_64BitIEEEDoublePrecision    > {PROTOX_BASIC( HLA13double         )};
//   +--------------------------------------------------+--------------+-------------------+-----------------------------------+

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
