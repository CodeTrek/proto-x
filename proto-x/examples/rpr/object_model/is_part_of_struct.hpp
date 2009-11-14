/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_RPR_IS_PART_OF_STRUCT_HPP
#define PROTOX_RPR_IS_PART_OF_STRUCT_HPP

/**************************************************************************************************/

#include <boost/mpl/vector.hpp>

#include <protox/hla_13/complex_type.hpp>

#include "entity_identifier_struct.hpp"
#include "rti_object_id_struct.hpp"
#include "constituent_part_relationship_struct.hpp"
#include "named_location_struct.hpp"

/**************************************************************************************************/

namespace protox {
namespace rpr_fom {

/**************************************************************************************************/

using namespace boost;
using namespace protox;
using namespace protox::dtl;

/**************************************************************************************************/

//      +----------------+------------------------------------------------------------------------------+----------------------+
//      |                | Field                                                                        |                      |
//      | Record         +-------------------------+----------------------------------------------------+ Encoding             |
//      | name           | Name                    | Type                                               |                      |
//      +----------------+-------------------------+----------------------------------------------------+----------------------+
namespace IsPartOfStruct {
//      +----------------+-------------------------+----------------------------------------------------+
                    struct HostEntityIdentifier    : field< EntityIdentifierStruct::type            > {};
//                       +-------------------------+----------------------------------------------------+
                    struct HostRTIObjectIdentifier : field< RtiObjectIdStruct::type                 > {};
//                       +-------------------------+----------------------------------------------------+
                    struct Relationship            : field< ConstituentPartRelationshipStruct::type > {};
//                       +-------------------------+----------------------------------------------------+
                    struct NamedLocation           : field< NamedLocationStruct::type               > {};
//      +----------------+-------------------------+----------------------------------------------------+
                                                                                            struct type : hla_13::complex_type < mpl::vector< HostEntityIdentifier, HostRTIObjectIdentifier, Relationship, NamedLocation > > {}; }
//      +-----------------------------------------------------------------------------------------------+----------------------+

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/

