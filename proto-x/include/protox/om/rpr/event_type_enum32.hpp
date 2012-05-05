/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_EVENT_TYPE_ENUM32_HPP
#define PROTOX_OM_RPR_EVENT_TYPE_ENUM32_HPP

/**********************************************************************************************************************/

#include "protox/dtl/enum_pp.hpp"

#include "protox/hla_13/enumerated.hpp"
#include "protox/hla_13/basic_data_representation_table.hpp"

/**********************************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**********************************************************************************************************************/

using namespace protox;
using namespace protox::hla_13;

/**********************************************************************************************************************/

//      +-----------------+----------------------------------------------------------+-----------------------------------+--------+
//      | Name            | Representation                                           | Enumerator                        | Values |
//      +-----------------+----------------------------------------------------------+-----------------------------------+--------+
namespace EventTypeEnum32 { PROTOX_ENUM_TYPE(HLA13unsigned_long, hla_13::enumerated) ;
                                                                    PROTOX_ENUM_VALUE( Other,                                  0 );
                                                                    PROTOX_ENUM_VALUE( Unused,                                 1 );
                                                                    PROTOX_ENUM_VALUE( RanOutOfAmmunition,                     2 );
                                                                    PROTOX_ENUM_VALUE( KilledInAction,                         3 );
                                                                    PROTOX_ENUM_VALUE( Damage,                                 4 );
                                                                    PROTOX_ENUM_VALUE( MobilityDisabled,                       5 );
                                                                    PROTOX_ENUM_VALUE( FireDisabled,                           6 );
                                                                    PROTOX_ENUM_VALUE( RanOutOfFuel,                           7 );
                                                                    PROTOX_ENUM_VALUE( EntityInitialization,                   8 );
                                                                    PROTOX_ENUM_VALUE( RequestForIndirectFireOrCASMission,     9 );
                                                                    PROTOX_ENUM_VALUE( IndirectFireOrCASMission,              10 );
                                                                    PROTOX_ENUM_VALUE( MinefieldEntry,                        11 );
                                                                    PROTOX_ENUM_VALUE( MinefieldDetonation,                   12 );
                                                                    PROTOX_ENUM_VALUE( VehicleMasterPowerOn,                  13 );
                                                                    PROTOX_ENUM_VALUE( VehicleMasterPowerOff,                 14 );
                                                                    PROTOX_ENUM_VALUE( AggregateStateChangeRequested,         15 );
//      +-----------------+----------------------------------------------------------+-----------------------------------+--------+

PROTOX_ENUM_EQUALITY_OPERATOR;
PROTOX_ENUM_DEFAULT(Other);

}

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
