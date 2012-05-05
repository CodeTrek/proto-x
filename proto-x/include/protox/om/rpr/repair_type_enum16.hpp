/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_REPAIR_TYPE_ENUM16_HPP
#define PROTOX_OM_RPR_REPAIR_TYPE_ENUM16_HPP

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

//      +------------------+----------------------------------------------------------+-----------------------------+--------+
//      | Name             | Representation                                           | Enumerator                  | Values |
//      +------------------+----------------------------------------------------------+-----------------------------+--------+
namespace RepairTypeEnum16 { PROTOX_ENUM_TYPE(HLA13unsigned_short, hla_13::enumerated);
                                                                     PROTOX_ENUM_VALUE( NoRepairsPerformed,               0 );
                                                                     PROTOX_ENUM_VALUE( AllRequestedRepairsPerformed,     1 );
                                                                     PROTOX_ENUM_VALUE( MotorOrEngine,                   10 );
                                                                     PROTOX_ENUM_VALUE( Starter,                         20 );
                                                                     PROTOX_ENUM_VALUE( Alternator,                      30 );
                                                                     PROTOX_ENUM_VALUE( Generator,                       40 );
                                                                     PROTOX_ENUM_VALUE( Battery,                         50 );
                                                                     PROTOX_ENUM_VALUE( EngineCoolantLeak,               60 );
                                                                     PROTOX_ENUM_VALUE( FuelFilter,                      70 );
                                                                     PROTOX_ENUM_VALUE( TransmissionOilLeak,             80 );
                                                                     PROTOX_ENUM_VALUE( EngineOilLeak,                   90 );
                                                                     PROTOX_ENUM_VALUE( Pumps,                          100 );
                                                                     PROTOX_ENUM_VALUE( Filters,                        110 );
                                                                     PROTOX_ENUM_VALUE( Transmission,                   120 );
                                                                     PROTOX_ENUM_VALUE( Brakes,                         130 );
                                                                     PROTOX_ENUM_VALUE( SuspensionSystem,               140 );
                                                                     PROTOX_ENUM_VALUE( OilFilter,                      150 );
                                                                     PROTOX_ENUM_VALUE( Hull,                          1000 );
                                                                      // add more as needed...
//      +------------------+----------------------------------------------------------+-----------------------------+--------+

PROTOX_ENUM_EQUALITY_OPERATOR;
PROTOX_ENUM_DEFAULT(NoRepairsPerformed);

/**********************************************************************************************************************/

}

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
