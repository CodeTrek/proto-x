/*
    Copyright 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef TEST_CUSTOM_DATA_REPRESENTATION_TABLE_HPP
#define TEST_CUSTOM_DATA_REPRESENTATION_TABLE_HPP

/**********************************************************************************************************************/

#include <protox/dtl/endian_enum.hpp>
#include <protox/dtl/basic.hpp>

#include <test/protox/custom/codec_tags.hpp>

/**********************************************************************************************************************/

namespace test { namespace custom {

/**********************************************************************************************************************/

//   +---------------------------------------------------------------------------------------------------------------------------------------+
//   | Basic data representation table                                                                                                       |
//   +---------------------------------------------------------+--------------+----------------------------+---------------------------------+
//   | Name                                                    | Size in bits | Endian                     | Encoding                        |
//   +---------------------------------------------------------+--------------+----------------------------+---------------------------------+
struct UnsignedInt16BE : protox::dtl::basic< unsigned short,     16,            protox::dtl::endian::big,    Test16BitTwosComplementUnsigned > { PROTOX_BASIC( UnsignedInt16BE ) };
struct UnsignedInt32BE : protox::dtl::basic< unsigned int,       32,            protox::dtl::endian::big,    Test32BitTwosComplementUnsigned > { PROTOX_BASIC( UnsignedInt32BE ) };
struct UnsignedInt64BE : protox::dtl::basic< unsigned long long, 64,            protox::dtl::endian::big,    Test64BitTwosComplementUnsigned > { PROTOX_BASIC( UnsignedInt64BE ) };
struct UnsignedInt16LE : protox::dtl::basic< unsigned short,     16,            protox::dtl::endian::little, Test16BitTwosComplementUnsigned > { PROTOX_BASIC( UnsignedInt16LE ) };
struct UnsignedInt64LE : protox::dtl::basic< unsigned long long, 64,            protox::dtl::endian::little, Test64BitTwosComplementUnsigned > { PROTOX_BASIC( UnsignedInt64LE ) };
//   +---------------------------------------------------------+--------------+----------------------------+---------------------------------+

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
