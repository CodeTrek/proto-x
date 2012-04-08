/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_BEAM_FUNCTION_CODE_ENUM8_HPP
#define PROTOX_OM_RPR_BEAM_FUNCTION_CODE_ENUM8_HPP

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

//      +-----------------------+-------------------------------------------------+----------------------+--------+
//      | Name                  | Representation                                  | Enumerator           | Values |
//      +-----------------------+-------------------------------------------------+----------------------+--------+
namespace BeamFunctionCodeEnum8 { PROTOX_ENUM_TYPE(HLA13octet, hla_13::enumerated);
//      +-----------------------+-------------------------------------------------+----------------------+--------+
                                                                 PROTOX_ENUM_VALUE( Other,                     0 );
                                                                 PROTOX_ENUM_VALUE( Search,                    1 );
                                                                 PROTOX_ENUM_VALUE( HeightFinder,              2 );
                                                                 PROTOX_ENUM_VALUE( Acquisition,               3 );
                                                                 PROTOX_ENUM_VALUE( Tracking,                  4 );
                                                                 PROTOX_ENUM_VALUE( AcquisitionAndTracking,    5 );
                                                                 PROTOX_ENUM_VALUE( CommandGuidance,           6 );
                                                                 PROTOX_ENUM_VALUE( Illumination,              7 );
                                                                 PROTOX_ENUM_VALUE( RangeOnlyRadar,            8 );
                                                                 PROTOX_ENUM_VALUE( MissileBeacon,             9 );
                                                                 PROTOX_ENUM_VALUE( MissileFuze,              10 );
                                                                 PROTOX_ENUM_VALUE( ActiveRadarMissileSeeker, 11 );
                                                                 PROTOX_ENUM_VALUE( Jammer,                   12 );
//      +-----------------------+-------------------------------------------------+----------------------+--------+

PROTOX_ENUM_EQUALITY_OPERATOR;
PROTOX_ENUM_DEFAULT(Other);

/**********************************************************************************************************************/

}

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
