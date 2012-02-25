/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef SOM_S004_SIMPLE_DATATYPE_TABLE_HPP
#define SOM_S004_SIMPLE_DATATYPE_TABLE_HPP

/**********************************************************************************************************************/

#include <protox/dtl/simple.hpp>
#include <protox/hla_1516/basic_data_representation_table.hpp>

/**********************************************************************************************************************/

namespace som_s004 {

/**********************************************************************************************************************/

using namespace protox::dtl;
using namespace protox::hla_1516;

/**********************************************************************************************************************/

//   +----------------------+--------------------------+
//   | Name                 | Representation           |
//   +----------------------+--------------------------+
struct SimpleHLAoctet       : simple< HLAoctet       > { PROTOX_SIMPLE(SimpleHLAoctet) };
struct SimpleHLAinteger32BE : simple< HLAinteger32BE > { PROTOX_SIMPLE(SimpleHLAinteger32BE) };
struct SimpleHLAfloat32BE   : simple< HLAfloat32BE   > { PROTOX_SIMPLE(SimpleHLAfloat32BE) };
//   +----------------------+--------------------------+

/**********************************************************************************************************************/

}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
