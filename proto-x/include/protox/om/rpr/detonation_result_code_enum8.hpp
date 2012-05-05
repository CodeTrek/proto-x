/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_DETONATION_RESULT_CODE_ENUM8_HPP
#define PROTOX_OM_RPR_DETONATION_RESULT_CODE_ENUM8_HPP

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
//      +---------------------------+-------------------------------------------------+-------------------------------------+--------+
//      | Name                      | Representation                                  | Enumerator                          | Values |
//      +---------------------------+-------------------------------------------------+-------------------------------------+--------+
namespace DetonationResultCodeEnum8 { PROTOX_ENUM_TYPE(HLA13octet, hla_13::enumerated);
                                                                     PROTOX_ENUM_VALUE( Other,                                    0 );
                                                                     PROTOX_ENUM_VALUE( EntityImpact,                             1 );
                                                                     PROTOX_ENUM_VALUE( EntityProximateDetonation,                2 );
                                                                     PROTOX_ENUM_VALUE( GroundImpact,                             3 );
                                                                     PROTOX_ENUM_VALUE( GroundProximateDetonation,                4 );
                                                                     PROTOX_ENUM_VALUE( Detonation,                               5 );
                                                                     PROTOX_ENUM_VALUE( None,                                     6 );
                                                                     PROTOX_ENUM_VALUE( HE_hit_Small,                             7 );
                                                                     PROTOX_ENUM_VALUE( HE_hit_Medium,                            8 );
                                                                     PROTOX_ENUM_VALUE( HE_hit_Large,                             9 );
                                                                     PROTOX_ENUM_VALUE( ArmorPiercingHit,                        10 );
                                                                     PROTOX_ENUM_VALUE( DirtBlast_Small,                         11 );
                                                                     PROTOX_ENUM_VALUE( DirtBlast_Medium,                        12 );
                                                                     PROTOX_ENUM_VALUE( DirtBlast_Large,                         13 );
                                                                     PROTOX_ENUM_VALUE( WaterBlast_Small,                        14 );
                                                                     PROTOX_ENUM_VALUE( WaterBlast_Medium,                       15 );
                                                                     PROTOX_ENUM_VALUE( WaterBlast_Large,                        16 );
                                                                     PROTOX_ENUM_VALUE( AirHit,                                  17 );
                                                                     PROTOX_ENUM_VALUE( BuildingHit_Small,                       18 );
                                                                     PROTOX_ENUM_VALUE( BuildingHit_Medium,                      19 );
                                                                     PROTOX_ENUM_VALUE( BuildingHit_Large,                       20 );
                                                                     PROTOX_ENUM_VALUE( MineClearingLineCharge,                  21 );
                                                                     PROTOX_ENUM_VALUE( EnvironmentObjectImpact,                 22 );
                                                                     PROTOX_ENUM_VALUE( EnvironmentObjectProximateDetonation,    23 );
                                                                     PROTOX_ENUM_VALUE( WaterImpact,                             24 );
                                                                     PROTOX_ENUM_VALUE( AirBurst,                                25 );
//      +---------------------------+-------------------------------------------------+-------------------------------------+--------+

PROTOX_ENUM_EQUALITY_OPERATOR;
PROTOX_ENUM_DEFAULT(Other);

/**********************************************************************************************************************/

}

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
