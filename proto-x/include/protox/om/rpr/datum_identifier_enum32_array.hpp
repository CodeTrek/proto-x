
/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_DATUM_IDENTIFIER_ENUM32_ARRAY_HPP
#define PROTOX_OM_RPR_DATUM_IDENTIFIER_ENUM32_ARRAY_HPP

/**********************************************************************************************************************/

#include <vector>

#include <protox/hla_13/variable_array.hpp>

#include <protox/om/rpr/datum_identifier_enum32.hpp>

/**********************************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**********************************************************************************************************************/

//   +----------------------------+------------------------------------+-----------------------------+-------------+
//   | Name                       | Encoding                           | Element type                | Cardinality |
//   +----------------------------+------------------------------------+-----------------------------+-------------+
struct DatumIdentifierEnum32Array : hla_13::variable_array< std::vector< DatumIdentifierEnum32::type > > {}; // 0+ |
//   +----------------------------+------------------------------------+-----------------------------+-------------+

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
