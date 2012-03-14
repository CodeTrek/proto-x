/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_ARTICULATED_PARAMETER_STRUCT_HPP
#define PROTOX_OM_RPR_ARTICULATED_PARAMETER_STRUCT_HPP

/**********************************************************************************************************************/

#include <boost/mpl/vector.hpp>

#include <protox/hla_13/complex_type.hpp>
#include <protox/hla_13/basic_data_representation_table.hpp>

#include <protox/om/rpr/parameter_value_struct.hpp>

/**********************************************************************************************************************/

using namespace boost;
using namespace protox;
using namespace protox::dtl;
using namespace protox::hla_13;

/**********************************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**********************************************************************************************************************/

//      +----------------------------+--------------------------------------------------------------------+----------------------+
//      |                            | Field                                                              |                      |
//      | Record Name                +----------------------------+---------------------------------------+ Encoding             |
//      |                            | Name                       | Type                                  |                      |
//      +----------------------------+----------------------------+---------------------------------------+----------------------+
namespace ArticulatedParameterStruct {
                                struct ArticulatedParameterChange : field< HLA13octet                 > {};
                                struct Padding                    : field< HLA13octet                 > {};
                                struct PartAttachedTo             : field< HLA13unsigned_short        > {};
                                struct ParameterValue             : field< ParameterValueStruct::type > {};
//      +----------------------------+----------------------------+---------------------------------------+----------------------+
                                                                                              struct type : hla_13::complex_type < mpl::vector< ArticulatedParameterChange, Padding, PartAttachedTo, ParameterValue > > {}; }
//      +----------------------------+----------------------------+---------------------------------------+----------------------+

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/

