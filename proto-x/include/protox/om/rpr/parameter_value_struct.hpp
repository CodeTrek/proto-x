/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_PARAMETER_VALUE_STRUCT_HPP
#define PROTOX_OM_RPR_PARAMETER_VALUE_STRUCT_HPP

/**********************************************************************************************************************/

#include <boost/mpl/vector.hpp>

#include <protox/dtl/pnull.hpp>

#include <protox/hla_13/variant_record.hpp>
#include <protox/hla_13/basic_data_representation_table.hpp>

#include <protox/om/rpr/parameter_type_enum32.hpp>
#include <protox/om/rpr/articulated_parts_struct.hpp>
#include <protox/om/rpr/attached_parts_struct.hpp>

/**********************************************************************************************************************/

using namespace boost;
using namespace protox;
using namespace protox::dtl;
using namespace protox::hla_13;

/**********************************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**********************************************************************************************************************/

namespace pte32 = protox::om::rpr::ParameterTypeEnum32;

/**********************************************************************************************************************/

// +---------------------------+------------------+--------------------------------------------------------------------------------------------+--------------------------------------------------+
// |                           | Alternative      |                                                                                            |                                                  |
// | Record Name               +------------------+ Disciminant Enumerator(s)                                                                  | Encoding                                         |
// |                           | Name             | Type                                                                                       |                                                  |
// +---------------------------+------------------+--------------------------------------------------------------------------------------------+--------------------------------------------------+
namespace ParameterValueStruct {
                          struct ArticulatedParts : dtl::discriminant< ArticulatedPartsStruct::type, mpl::vector< pte32::ArticulatedPart > > {};
                          struct AttachedParts    : dtl::discriminant< AttachedPartsStruct::type,    mpl::vector< pte32::AttachedPart    > > {};
//                                                +--------------------------------------------------------------------------------------------+--------------------------------------------------+
                                                                                                                                   struct type : hla_13::variant_record< ParameterTypeEnum32::type, mpl::vector< ArticulatedParts, AttachedParts > > {};
//                                                +--------------------------------------------------------------------------------------------+--------------------------------------------------+

}

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
