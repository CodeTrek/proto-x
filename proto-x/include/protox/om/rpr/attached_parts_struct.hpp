/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_ATTACHED_PARTS_STRUCT_HPP
#define PROTOX_OM_RPR_ATTACHED_PARTS_STRUCT_HPP

/**********************************************************************************************************************/

#include <boost/mpl/vector.hpp>

#include <protox/hla_13/complex_type.hpp>
#include <protox/hla_13/basic_data_representation_table.hpp>

#include <protox/om/rpr/station_enum32.hpp>
#include <protox/om/rpr/entity_type_struct.hpp>

/**********************************************************************************************************************/

using namespace boost;
using namespace protox;
using namespace protox::dtl;
using namespace protox::hla_13;

/**********************************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**********************************************************************************************************************/

//      +---------------------+-----------------------------------------------+----------------------+
//      |                     | Field                                         |                      |
//      | Record Name         +-----------+-----------------------------------+ Encoding             |
//      |                     | Name      | Type                              |                      |
//      +---------------------+-----------+-----------------------------------+----------------------+
namespace AttachedPartsStruct {
                         struct Station   : field< StationEnum32::type    > {};
                         struct StoreType : field< EntityTypeStruct::type > {};
//      +---------------------+-----------+-----------------------------------+----------------------+
                                                                  struct type : hla_13::complex_type < mpl::vector< Station, StoreType > > {}; }
//      +---------------------+-----------+-----------------------------------+----------------------+

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/

