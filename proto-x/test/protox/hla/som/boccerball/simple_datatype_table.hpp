/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef SOM_BOCCERBALL_SIMPLE_DATATYPE_TABLE_HPP
#define SOM_BOCCERBALL_SIMPLE_DATATYPE_TABLE_HPP

/**********************************************************************************************************************/

#include <protox/dtl/simple.hpp>
#include <protox/hla_1516/basic_data_representation_table.hpp>

/**********************************************************************************************************************/

namespace som { namespace boccerball {

/**********************************************************************************************************************/

using namespace protox::dtl;
using namespace protox::hla_1516;

/**********************************************************************************************************************/

//   +------------+-------------------------+---------------------------+
//   | Name       | Representation          | Units                     |
//   +------------+-------------------------+---------------------------+
struct Distance   : simple< HLAfloat32BE,     unitless /* cm         */ > { PROTOX_SIMPLE(Distance  ) };
struct Direction  : simple< HLAfloat32BE,     unitless /* degrees    */ > { PROTOX_SIMPLE(Direction ) };
struct Speed      : simple< HLAfloat32BE,     unitless /* cm/sec     */ > { PROTOX_SIMPLE(Speed     ) };
struct DeltaSpeed : simple< HLAfloat32BE,     unitless /* cm/sec/sec */ > { PROTOX_SIMPLE(DeltaSpeed) };
struct MassType   : simple< HLAfloat32BE,     unitless /* grams      */ > { PROTOX_SIMPLE(MassType  ) };
struct ASCIIchar  : simple< HLAoctet,         unitless                  > { PROTOX_SIMPLE(ASCIIchar ) };
struct Count      : simple< HLAinteger16BE,   unitless                  > { PROTOX_SIMPLE(Count     ) };
//   +------------+-------------------------+---------------------------+

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
