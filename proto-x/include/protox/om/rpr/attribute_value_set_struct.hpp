/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_ATTRIBUTE_VALUE_SET_STRUCT_HPP
#define PROTOX_OM_RPR_ATTRIBUTE_VALUE_SET_STRUCT_HPP

/**********************************************************************************************************************/

#include <vector>

#include <boost/mpl/vector.hpp>

#include <protox/hla_13/complex_type.hpp>
#include <protox/hla_13/variable_array.hpp>
#include <protox/hla_13/basic_data_representation_table.hpp>

#include <protox/om/rpr/attribute_pair_struct.hpp>

/**********************************************************************************************************************/

using namespace boost;
using namespace protox;
using namespace protox::dtl;
using namespace protox::hla_13;

/**********************************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**********************************************************************************************************************/

//      +-------------------------+---------------------------------------------------------------------------------------------------+----------------------+
//      |                         | Field                                                                                             |                      |
//      | Record Name             +-------------------+-------------------------------------------------------------------------------+ Encoding             |
//      |                         | Name              | Type                                                                          |                      |
//      +-------------------------+-------------------+-------------------------------------------------------------------------------+----------------------+
namespace AttributeValueSetStruct {
                             struct AttributeSetCount : field< HLA13unsigned_long                                                 > {};
                             struct AttributePairs    : field< hla_13::variable_array< std::vector< AttributePairStruct::type > > > {};
                                                                                                                          struct type : hla_13::complex_type < mpl::vector< AttributeSetCount, AttributePairs > > {}; }

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
