/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_FUSE_TYPE_ENUM16_HPP
#define PROTOX_OM_RPR_FUSE_TYPE_ENUM16_HPP

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

//      +----------------+----------------------------------------------------------+---------------------+--------+
//      | Name           | Representation                                           | Enumerator          | Values |
//      +---------------------------------------------------------------------------+---------------------+--------+
namespace FuseTypeEnum16 { PROTOX_ENUM_TYPE(HLA13unsigned_short, hla_13::enumerated);
//      +---------------------------------------------------------------------------+---------------------+--------+
                                                                   PROTOX_ENUM_VALUE( Other,                    0 );
                                                                   PROTOX_ENUM_VALUE( IntelligentInfluence,    10 );
                                                                   PROTOX_ENUM_VALUE( Sensor,                  20 );
                                                                   PROTOX_ENUM_VALUE( SelfDestruct,            30 );
                                                                   PROTOX_ENUM_VALUE( UltraQuick,              40 );
                                                                   PROTOX_ENUM_VALUE( Body,                    50 );
                                                                   PROTOX_ENUM_VALUE( DeepIntrusion,           60 );
                                                                   PROTOX_ENUM_VALUE( Multifunction,          100 );
                                                                   PROTOX_ENUM_VALUE( PointDetonation_PD,     200 );
                                                                   PROTOX_ENUM_VALUE( BaseDetonation_BD,      300 );
                                                                   PROTOX_ENUM_VALUE( Contact,               1000 );
                                                                   PROTOX_ENUM_VALUE( ContactInstantImpact,  1100 );
                                                                   PROTOX_ENUM_VALUE( ContactDelayed,        1200 );
                                                                   // add more as needed...
//      +---------------------------------------------------------------------------+---------------------+--------+

PROTOX_ENUM_EQUALITY_OPERATOR;
PROTOX_ENUM_DEFAULT(Other);

/**********************************************************************************************************************/

}

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
