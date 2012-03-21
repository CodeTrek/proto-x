/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_AMPLITUDE_MODULATION_TYPE_ENUM16_HPP
#define PROTOX_OM_RPR_AMPLITUDE_MODULATION_TYPE_ENUM16_HPP

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

//      +-------------------------------+----------------------------------------------------------+--------------------------+--------+
//      | Name                          | Representation                                           | Enumerator               | Values |
//      +-------------------------------+----------------------------------------------------------+--------------------------+--------+
namespace AmplitudeModulationTypeEnum16 { PROTOX_ENUM_TYPE(HLA13unsigned_short, hla_13::enumerated);
                                                                                  PROTOX_ENUM_VALUE( Other,                         0 );
                                                                                  PROTOX_ENUM_VALUE( AudioFrequencyShiftKeying,     1 );
                                                                                  PROTOX_ENUM_VALUE( AmplitudeModulation,           2 );
                                                                                  PROTOX_ENUM_VALUE( ContinuousWaveModulation,      3 );
                                                                                  PROTOX_ENUM_VALUE( DoubleSideband,                4 );
                                                                                  PROTOX_ENUM_VALUE( IndependentSideband,           5 );
                                                                                  PROTOX_ENUM_VALUE( SSB_LowerSideband,             6 );
                                                                                  PROTOX_ENUM_VALUE( SSB_FullCarrier,               7 );
                                                                                  PROTOX_ENUM_VALUE( SSB_ReducedCarrier,            8 );
                                                                                  PROTOX_ENUM_VALUE( SSB_UpperSideband,             9 );
                                                                                  PROTOX_ENUM_VALUE( VestigialSideband,            10 );
//      +------------------------------------------------------------------------------------------+--------------------------+--------+

PROTOX_ENUM_EQUALITY_OPERATOR;
PROTOX_ENUM_DEFAULT(Other);

/**********************************************************************************************************************/

}

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
