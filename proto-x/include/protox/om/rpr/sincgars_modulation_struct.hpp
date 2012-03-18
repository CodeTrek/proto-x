/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_SINCGARS_MODULATION_STRUCT_HPP
#define PROTOX_OM_RPR_SINCGARS_MODULATION_STRUCT_HPP

/**********************************************************************************************************************/

#include <boost/mpl/vector.hpp>

#include <protox/hla_13/complex_type.hpp>
#include <protox/hla_13/basic_data_representation_table.hpp>

#include <protox/om/rpr/start_message_enum8.hpp>

/**********************************************************************************************************************/

using namespace boost;
using namespace protox;
using namespace protox::dtl;
using namespace protox::hla_13;

/**********************************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**********************************************************************************************************************/

//      +--------------------------+-----------------------------+------------------------------------+----------------------+
//      |                          | Field                                                            |                      |
//      | Record Name              +-----------------------------+------------------------------------+ Encoding             |
//      |                          | Name                        | Type                               |                      |
//      +--------------------------+-----------------------------+------------------------------------+----------------------+
namespace SINCGARSModulationStruct {
                              struct FHNetID                     : field< HLA13short              > {};
                              struct HopSetID                    : field< HLA13short              > {};
                              struct LockoutSetID                : field< HLA13short              > {};
                              struct StartOfMessage              : field< StartMessageEnum8::type > {};
                              struct Padding                     : field< HLA13octet              > {};
                              struct FHSynchronizationTimeOffset : field< HLA13long               > {};
                              struct TransmissionSecurityKey     : field< HLA13short              > {};
                              struct ClearChannel                : field< HLA13octet              > {};
//      +--------------------------+-----------------------------+------------------------------------+----------------------+
                                                                                          struct type : hla_13::complex_type < mpl::vector< FHNetID, HopSetID, LockoutSetID, StartOfMessage, Padding, FHSynchronizationTimeOffset, TransmissionSecurityKey, ClearChannel > > {}; }
//      +---------------------------------------------------------------------------------------------+----------------------+

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
