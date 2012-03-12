/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_ARTICULATED_TYPE_METRIC_ENUM32_HPP
#define PROTOX_OM_RPR_ARTICULATED_TYPE_METRIC_ENUM32_HPP

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

//      +-----------------------------+----------------------------------------------------------+--------------+--------+
//      | Name                        | Representation                                           | Enumerator   | Values |
//      +-----------------------------+----------------------------------------------------------+--------------+--------+
namespace ArticulatedTypeMetricEnum32 { PROTOX_ENUM_TYPE(HLA13unsigned_long, hla_13::enumerated) ;
                                                                                PROTOX_ENUM_VALUE( Position,          1 );
                                                                                PROTOX_ENUM_VALUE( PositionRate,      2 );
                                                                                PROTOX_ENUM_VALUE( Extension,         3 );
                                                                                PROTOX_ENUM_VALUE( ExtensionRate,     4 );
                                                                                PROTOX_ENUM_VALUE( X,                 5 );
                                                                                PROTOX_ENUM_VALUE( XRate,             6 );
                                                                                PROTOX_ENUM_VALUE( Y,                 7 );
                                                                                PROTOX_ENUM_VALUE( YRate,             8 );
                                                                                PROTOX_ENUM_VALUE( Z,                 9 );
                                                                                PROTOX_ENUM_VALUE( ZRate,            10 );
                                                                                PROTOX_ENUM_VALUE( Azimuth,          11 );
                                                                                PROTOX_ENUM_VALUE( AzimuthRate,      12 );
                                                                                PROTOX_ENUM_VALUE( Elevation,        13 );
                                                                                PROTOX_ENUM_VALUE( ElevationRate,    14 );
                                                                                PROTOX_ENUM_VALUE( Rotation,         15 );
                                                                                PROTOX_ENUM_VALUE( RotationRate,     16 );
PROTOX_ENUM_EQUALITY_OPERATOR;
PROTOX_ENUM_DEFAULT(Position);

/**********************************************************************************************************************/

}

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
