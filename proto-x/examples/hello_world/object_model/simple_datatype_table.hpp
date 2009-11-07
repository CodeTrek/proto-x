/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_EXAMPLES_HW_SIMPLE_DATATYPE_TABLE_HPP
#define PROTOX_EXAMPLES_HW_SIMPLE_DATATYPE_TABLE_HPP

/**************************************************************************************************/

#include <protox/dtl/simple.hpp>
#include <protox/hla_1516/basic_data_representation_table.hpp>

/**************************************************************************************************/

using namespace protox::dtl;
using namespace protox::hla_1516;

/**************************************************************************************************/

//   +-----------+-------------------+---------------------------+
//   | Name      | Representation    | Units                     |
//   +-----------+-------------------+---------------------------+
struct ASCIIchar : simple< HLAoctet,   unitless                  > {PROTOX_SIMPLE( ASCIIchar  )};
//   +-----------+-------------------+---------------------------+

/**************************************************************************************************/

#endif

/**************************************************************************************************/
