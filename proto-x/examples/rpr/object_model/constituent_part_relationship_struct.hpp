/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_RPR_CONSTITUENT_PART_RELATIONSHIP_STRUCT_HPP
#define PROTOX_RPR_CONSTITUENT_PART_RELATIONSHIP_STRUCT_HPP

/**************************************************************************************************/

#include <boost/mpl/vector.hpp>

#include <protox/hla_13/complex_type.hpp>
#include <protox/hla_13/basic_data_representation_table.hpp>

#include "./constituent_part_nature_enum16.hpp"
#include "./constituent_part_position_enum16.hpp"

/**************************************************************************************************/

namespace protox {
namespace rpr_fom {

/**************************************************************************************************/

using namespace boost;
using namespace protox;
using namespace protox::dtl;
using namespace protox::hla_13;

/**************************************************************************************************/

//      +-----------------------------------+----------+------------------------------------------------+----------------------+
//      |                                   | Field                                                     |                      |
//      | Record                            +----------+------------------------------------------------+ Encoding             |
//      | name                              | Name     | Type                                           |                      |
//      +-----------------------------------+----------+------------------------------------------------+----------------------+
namespace ConstituentPartRelationshipStruct {
//      +-----------------------------------+----------+------------------------------------------------+
                                       struct Nature   : field< ConstituentPartNatureEnum16::Type   > {};
//                                          +----------+------------------------------------------------+
                                       struct Position : field< ConstituentPartPositionEnum16::Type > {};
//      +-----------------------------------+----------+------------------------------------------------+
                                                                                            struct type : hla_13::complex_type < mpl::vector< Nature, Position > > {}; }
//      +-----------------------------------------------------------------------------------------------+----------------------+

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/

