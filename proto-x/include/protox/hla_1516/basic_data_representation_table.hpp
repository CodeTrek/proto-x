/*
    Copyright 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_HLA_1516_BASIC_DATA_REPRESENTATION_TABLE_HPP
#define PROTOX_HLA_1516_BASIC_DATA_REPRESENTATION_TABLE_HPP

/******************************************************************************/

#include <protox/dtl/endian_enum.hpp>
#include <protox/dtl/basic.hpp>

#include <protox/hla_1516/codec_tags.hpp>

/******************************************************************************/

namespace protox { namespace hla_1516 {

/******************************************************************************/

//   +---------------------------------------------------------------------------------------------------------------+
//   | Basic data representation table                                                                               |
//   +--------------------------------------------+--------------+--------------------+------------------------------+
//   | Name                                       | Size in bits | Endian             | Encoding                     |
//   +--------------------------------------------+--------------+--------------------+------------------------------+
struct HLAoctet       : dtl::basic< unsigned char,   8,            dtl::endian::big,    HLAportable                  > { PROTOX_BASIC(HLAoctet)       };
//   +--------------------------------------------+--------------+--------------------+------------------------------+
struct HLAoctetPairBE : dtl::basic< unsigned short, 16,            dtl::endian::big,    HLAportable                  > { PROTOX_BASIC(HLAoctetPairBE) };
//   +--------------------------------------------+--------------+--------------------+------------------------------+
struct HLAinteger16BE : dtl::basic< short,          16,            dtl::endian::big,    HLA16BitTwosComplementSigned > { PROTOX_BASIC(HLAinteger16BE) };
//   +--------------------------------------------+--------------+--------------------+------------------------------+
struct HLAinteger32BE : dtl::basic< int,            32,            dtl::endian::big,    HLA32BitTwosComplementSigned > { PROTOX_BASIC(HLAinteger32BE) };
//   +--------------------------------------------+--------------+--------------------+------------------------------+
struct HLAinteger64BE : dtl::basic< long long,      64,            dtl::endian::big,    HLA64BitTwosComplementSigned > { PROTOX_BASIC(HLAinteger64BE) };
//   +--------------------------------------------+--------------+--------------------+------------------------------+
struct HLAfloat32BE   : dtl::basic< float,          32,            dtl::endian::big,    HLA32BitIEEESinglePrecision  > { PROTOX_BASIC(HLAfloat32BE)   };
//   +--------------------------------------------+--------------+--------------------+------------------------------+
struct HLAfloat64BE   : dtl::basic< double,         64,            dtl::endian::big,    HLA64BitIEEEDoublePrecision  > { PROTOX_BASIC(HLAfloat64BE)   };
//   +--------------------------------------------+--------------+--------------------+------------------------------+
struct HLAoctetPairLE : dtl::basic< unsigned short, 16,            dtl::endian::little, HLAportable                  > { PROTOX_BASIC(HLAoctetPairLE) };
//   +--------------------------------------------+--------------+--------------------+------------------------------+
struct HLAinteger16LE : dtl::basic< short,          16,            dtl::endian::little, HLA16BitTwosComplementSigned > { PROTOX_BASIC(HLAinteger16LE) };
//   +--------------------------------------------+--------------+--------------------+------------------------------+
struct HLAinteger32LE : dtl::basic< int,            32,            dtl::endian::little, HLA32BitTwosComplementSigned > { PROTOX_BASIC(HLAinteger32LE) };
//   +--------------------------------------------+--------------+--------------------+------------------------------+
struct HLAinteger64LE : dtl::basic< long long,      64,            dtl::endian::little, HLA64BitTwosComplementSigned > { PROTOX_BASIC(HLAinteger64LE) };
//   +--------------------------------------------+--------------+--------------------+------------------------------+
struct HLAfloat32LE   : dtl::basic< float,          32,            dtl::endian::little, HLA32BitIEEESinglePrecision  > { PROTOX_BASIC(HLAfloat32LE)   };
//   +--------------------------------------------+--------------+--------------------+------------------------------+
struct HLAfloat64LE   : dtl::basic< double,         64,            dtl::endian::little, HLA64BitIEEEDoublePrecision  > { PROTOX_BASIC(HLAfloat64LE)   };
//   +--------------------------------------------+--------------+--------------------+------------------------------+

/******************************************************************************/

}} // protox::hla_1516

/******************************************************************************/

#endif

/******************************************************************************/
