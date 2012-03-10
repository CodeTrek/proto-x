
/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_RPR_SPATIAL_STATIC_STRUCT_VAR_HPP
#define PROTOX_RPR_SPATIAL_STATIC_STRUCT_VAR_HPP

/**************************************************************************************************/

#include <vector>

#include <protox/hla_13/variable_array.hpp>

#include "./spatial_static_struct.hpp"

/**************************************************************************************************/

namespace protox {
namespace rpr_fom {

/**************************************************************************************************/

using namespace protox;
using namespace protox::hla_13;

/**************************************************************************************************/

//      +------------------------+-------------------------------------+---------------------------------+-------------+
//      | Name                   | Encoding                            | Element type                    | Cardinality |
//      +------------------------+-------------------------------------+---------------------------------+-------------+
namespace SpatialStaticStructVar { struct type : hla_13::variable_array< std::vector< SpatialStaticStruct::type > > {}; } // dynamic
//      +------------------------+-------------------------------------+---------------------------------+-------------+

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
