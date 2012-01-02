/*
    Copyright 2012 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_SDX_BASIC_DATA_REPRESENTATION_TABLE_HPP
#define PROTOX_SDX_BASIC_DATA_REPRESENTATION_TABLE_HPP

/**************************************************************************************************/

#include <protox/dtl/endian_enum.hpp>
#include <protox/dtl/basic.hpp>

#include <protox/sdx/codec_tags.hpp>

/**************************************************************************************************/

namespace protox {
namespace sdx {

/**************************************************************************************************/

/**************************************************************************************************/

//   +-----------------------------------------------------------------------------------------------------+
//   | SDX Basic data representation table                                                                 |
//   +----------------------------------------------+--------------+------------------+--------------------+
//   | Name                                         | Size in bits | Endian           | Encoding           |
//   +----------------------------------------------+--------------+------------------+--------------------+
struct SDXByte          : dtl::basic< unsigned char,       8,        dtl::endian::na,   sdx_portable       > {PROTOX_BASIC( SDXByte          )};
struct SDXUnsignedShort : dtl::basic< unsigned short,     16,        dtl::endian::big,  sdx_unsigned_short > {PROTOX_BASIC( SDXUnsignedShort )};
struct SDXUnsignedLong  : dtl::basic< unsigned long,      32,        dtl::endian::big,  sdx_unsigned_long  > {PROTOX_BASIC( SDXUnsignedLong  )};
//   +----------------------------------------------+--------------+------------------+--------------------+

/**************************************************************************************************/

}} // protox::sdx

/**************************************************************************************************/

#endif

/**************************************************************************************************/
