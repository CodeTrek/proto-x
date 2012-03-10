/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_RPR_CONSTITUENT_PART_POSITION_ENUM16_HPP
#define PROTOX_RPR_CONSTITUENT_PART_POSITION_ENUM16_HPP

/**************************************************************************************************/

#include "protox/dtl/enum_pp.hpp"

#include "protox/hla_13/enumerated.hpp"
#include "protox/hla_13/basic_data_representation_table.hpp"

/**************************************************************************************************/

namespace protox {
namespace rpr_fom {

/**************************************************************************************************/

using namespace protox;
using namespace protox::hla_13;

/**************************************************************************************************/

//      +-------------------------------+------------------------------------------------------------+------------+--------+
//      | Name                          | Representation                                             | Enumerator | Values |
//      +-------------------------------+------------------------------------------------------------+------------+--------+
namespace ConstituentPartPositionEnum16 { PROTOX_ENUM_TYPE( HLA13unsigned_short, hla_13::enumerated );
//      +-------------------------------+------------------------------------------------------------+------------+--------+
                                                                                    PROTOX_ENUM_VALUE( Other,           0 );
//                                                                                                   +------------+--------+
                                                                                    PROTOX_ENUM_VALUE( OnTopOf,         1 );
//                                                                                                   +------------+--------+
                                                                                    PROTOX_ENUM_VALUE( Inside,          2 );
//      +-------------------------------+------------------------------------------------------------+------------+--------+

PROTOX_ENUM_EQUALITY_OPERATOR;
PROTOX_ENUM_DEFAULT( Other );

/**************************************************************************************************/

}

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
