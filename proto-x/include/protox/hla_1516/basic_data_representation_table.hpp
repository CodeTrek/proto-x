/*
    Copyright 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_1516_BASIC_DATA_REPRESENTATION_TABLE_HPP
#define PROTOX_HLA_1516_BASIC_DATA_REPRESENTATION_TABLE_HPP

/**************************************************************************************************/

#include <protox/dtl/endian_enum.hpp>
#include <protox/dtl/basic.hpp>

#include <protox/hla_1516/codec_tags.hpp>

/**************************************************************************************************/

namespace protox { namespace hla_1516 {

/**************************************************************************************************/

using namespace boost;

using namespace protox;
using namespace protox::dtl;

/**************************************************************************************************/

//   +-------------------------------------------------------------------------------------------------------+
//   | Basic data representation table                                                                       |
//   +---------------------------------------+--------------+-----------------+------------------------------+
//   | Name                                  | Size in bits | Endian          | Encoding                     |
//   +---------------------------------------+--------------+-----------------+------------------------------+
struct HLAoctet       : basic< unsigned char,   8,            endian::big,      HLAportable                  > { PROTOX_BASIC(HLAoctet)       };
//   +---------------------------------------+--------------+-----------------+------------------------------+
struct HLAoctetPairBE : basic< unsigned short, 16,            endian::big,      HLAportable                  > { PROTOX_BASIC(HLAoctetPairBE) };
//   +---------------------------------------+--------------+-----------------+------------------------------+
struct HLAinteger16BE : basic< short,          16,            endian::big,      HLA16BitTwosComplementSigned > { PROTOX_BASIC(HLAinteger16BE) };
//   +---------------------------------------+--------------+-----------------+------------------------------+
struct HLAinteger32BE : basic< int,            32,            endian::big,      HLA32BitTwosComplementSigned > { PROTOX_BASIC(HLAinteger32BE) };
//   +---------------------------------------+--------------+-----------------+------------------------------+
struct HLAinteger64BE : basic< long long,      64,            endian::big,      HLA64BitTwosComplementSigned > { PROTOX_BASIC(HLAinteger64BE) };
//   +---------------------------------------+--------------+-----------------+------------------------------+
struct HLAfloat32BE   : basic< float,          32,            endian::big,      HLA32BitIEEESinglePrecision  > { PROTOX_BASIC(HLAfloat32BE)   };
//   +---------------------------------------+--------------+-----------------+------------------------------+
struct HLAfloat64BE   : basic< double,         64,            endian::big,      HLA64BitIEEEDoublePrecision  > { PROTOX_BASIC(HLAfloat64BE)   };
//   +---------------------------------------+--------------+-----------------+------------------------------+
struct HLAoctetPairLE : basic< unsigned short, 16,            endian::little,   HLAportable                  > { PROTOX_BASIC(HLAoctetPairLE) };
//   +---------------------------------------+--------------+-----------------+------------------------------+
struct HLAinteger16LE : basic< short,          16,            endian::little,   HLA16BitTwosComplementSigned > { PROTOX_BASIC(HLAinteger16LE) };
//   +---------------------------------------+--------------+-----------------+------------------------------+
struct HLAinteger32LE : basic< int,            32,            endian::little,   HLA32BitTwosComplementSigned > { PROTOX_BASIC(HLAinteger32LE) };
//   +---------------------------------------+--------------+-----------------+------------------------------+
struct HLAinteger64LE : basic< long long,      64,            endian::little,   HLA64BitTwosComplementSigned > { PROTOX_BASIC(HLAinteger64LE) };
//   +---------------------------------------+--------------+-----------------+------------------------------+
struct HLAfloat32LE   : basic< float,          32,            endian::little,   HLA32BitIEEESinglePrecision  > { PROTOX_BASIC(HLAfloat32LE)   };
//   +---------------------------------------+--------------+-----------------+------------------------------+
struct HLAfloat64LE   : basic< double,         64,            endian::little,   HLA64BitIEEEDoublePrecision  > { PROTOX_BASIC(HLAfloat64LE)   };
//   +---------------------------------------+--------------+-----------------+------------------------------+

/**************************************************************************************************/

}} // protox::hla_1516

/**************************************************************************************************/

#endif

/**************************************************************************************************/

