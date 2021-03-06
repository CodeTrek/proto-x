
/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_ANY_ARRAY_HPP
#define PROTOX_OM_RPR_ANY_ARRAY_HPP

/**********************************************************************************************************************/

#include <vector>

#include <protox/hla_13/variable_array.hpp>
#include <protox/hla_13/basic_data_representation_table.hpp>

/**********************************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**********************************************************************************************************************/

using namespace protox;

/**********************************************************************************************************************/

//   +-------------+------------------------------------+--------------------------+-------------+
//   | Name        | Encoding                           | Element type             | Cardinality |
//   +-------------+------------------------------------+--------------------------+-------------+
struct any         : hla_13::variable_array< std::vector< hla_13::HLA13octet > > {}; // Dynamic  |
//   +-------------+------------------------------------+--------------------------+-------------+

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
