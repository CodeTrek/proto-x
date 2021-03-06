/*
    Copyright 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_XDR_BASIC_DATA_REPRESENTATION_TABLE_HPP
#define PROTOX_XDR_BASIC_DATA_REPRESENTATION_TABLE_HPP

/**************************************************************************************************/

#include <protox/dtl/endian_enum.hpp>
#include <protox/dtl/basic.hpp>

#include <protox/xdr/codec_tags.hpp>

/**************************************************************************************************/

namespace protox {
namespace xdr {

/**************************************************************************************************/

/**************************************************************************************************/

//   +-------------------------------------------------------------------------------------------------------------+
//   | Basic data representation table                                                                             |
//   +----------------------------------------------+--------------+-------------------+---------------------------+
//   | Name                                         | Size in bits | Endian            | Encoding                  |
//   +----------------------------------------------+--------------+-------------------+---------------------------+
struct Opaque          : dtl::basic< unsigned char,    8,            dtl::endian::big,   xdr_opaque                > {PROTOX_BASIC( Opaque          )};
struct Integer         : dtl::basic< long,            32,            dtl::endian::big,   xdr_signed_integer        > {PROTOX_BASIC( Integer         )};
struct UnsignedInteger : dtl::basic< unsigned long,   32,            dtl::endian::big,   xdr_unsigned_integer      > {PROTOX_BASIC( UnsignedInteger )};
struct Float           : dtl::basic< float,           32,            dtl::endian::big,   xdr_ieee_floating_point   > {PROTOX_BASIC( Float           )};
struct Double          : dtl::basic< double,          64,            dtl::endian::big,   xdr_ieee_double_precision > {PROTOX_BASIC( Double          )};
//   +----------------------------------------------+--------------+-------------------+---------------------------+

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
