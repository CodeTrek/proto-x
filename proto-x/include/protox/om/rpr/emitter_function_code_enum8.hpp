/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_EMITTER_FUNCTION_CODE_ENUM8_HPP
#define PROTOX_OM_RPR_EMITTER_FUNCTION_CODE_ENUM8_HPP

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

//      +----------------------+-------------------------------------------------+-------------------------------+--------+
//      | Name                 | Representation                                  | Enumerator                    | Values |
//      +----------------------+-------------------------------------------------+-------------------------------+--------+
namespace EmitterFunctionEnum8 { PROTOX_ENUM_TYPE(HLA13octet, hla_13::enumerated);
//      +----------------------+-------------------------------------------------+-------------------------------+--------+
                                                                PROTOX_ENUM_VALUE( Other,                              0 );
                                                                PROTOX_ENUM_VALUE( MultiFunction,                      1 );
                                                                PROTOX_ENUM_VALUE( EarlyWarningSurveillance,           2 );
                                                                PROTOX_ENUM_VALUE( HeightFinding,                      3 );
                                                                PROTOX_ENUM_VALUE( FireControl,                        4 );
                                                                PROTOX_ENUM_VALUE( AcquisitionDetection,               5 );
                                                                PROTOX_ENUM_VALUE( Tracking,                           6 );
                                                                PROTOX_ENUM_VALUE( GuidanceIllumination,               7 );
                                                                PROTOX_ENUM_VALUE( FiringPointLaunchPointLocation,     8 );
                                                                PROTOX_ENUM_VALUE( Ranging,                            9 );
                                                                PROTOX_ENUM_VALUE( RadarAltimeter,                    10 );
                                                                PROTOX_ENUM_VALUE( Imaging,                           11 );
                                                                PROTOX_ENUM_VALUE( MotionDetection,                   12 );
                                                                PROTOX_ENUM_VALUE( Navigation,                        13 );
                                                                PROTOX_ENUM_VALUE( Weather,                           14 );
                                                                PROTOX_ENUM_VALUE( Instrumentation,                   15 );
                                                                PROTOX_ENUM_VALUE( IdentificationClassification,      16 );
                                                                PROTOX_ENUM_VALUE( JammingNoise,                      64 );
                                                                PROTOX_ENUM_VALUE( JammingDeception,                  65 );
                                                                PROTOX_ENUM_VALUE( Decoy,                             66 );
                                                                PROTOX_ENUM_VALUE( WeaponNonLethal,                   96 );
                                                                PROTOX_ENUM_VALUE( WeaponLethal,                      97 );
//      +----------------------+-------------------------------------------------+-------------------------------+--------+

PROTOX_ENUM_EQUALITY_OPERATOR;
PROTOX_ENUM_DEFAULT(Other);

/**********************************************************************************************************************/

}

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
