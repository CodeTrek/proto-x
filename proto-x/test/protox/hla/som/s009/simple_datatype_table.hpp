/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef SOM_S009_SIMPLE_DATATYPE_TABLE_HPP
#define SOM_S009_SIMPLE_DATATYPE_TABLE_HPP

/******************************************************************************/

#include <protox/dtl/simple.hpp>
#include <protox/hla_1516/basic_data_representation_table.hpp>

/******************************************************************************/

namespace som_s009 {

/******************************************************************************/

using namespace protox::dtl;
using namespace protox::hla_1516;

/******************************************************************************/

//   +----------------------+--------------------------+
//   | Name                 | Representation           |
//   +----------------------+--------------------------+
struct simple_int           : simple< HLAinteger16BE > {PROTOX_SIMPLE( simple_int )};
//   +----------------------+--------------------------+
struct simple_float         : simple< HLAfloat32BE >   {PROTOX_SIMPLE( simple_float )};
//   +----------------------+--------------------------+

/******************************************************************************/

}

/******************************************************************************/

#endif

/******************************************************************************/
