/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_WARHEAD_TYPE_ENUM16_HPP
#define PROTOX_OM_RPR_WARHEAD_TYPE_ENUM16_HPP

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

//      +------------------------------------------------------------------------------+--------------------------+--------+
//      | Name              | Representation                                           | Enumerator               | Values |
//      +------------------------------------------------------------------------------+--------------------------+--------+
namespace WarheadTypeEnum16 { PROTOX_ENUM_TYPE(HLA13unsigned_short, hla_13::enumerated);
                                                                      PROTOX_ENUM_VALUE( Other,                         0 );
                                                                      PROTOX_ENUM_VALUE( CargoVariableSubmunitions,    10 );
                                                                      PROTOX_ENUM_VALUE( FuelAirExplosive,             20 );
                                                                      PROTOX_ENUM_VALUE( GlassBeads,                   30 );
                                                                      PROTOX_ENUM_VALUE( Warhead_1um,                  31 );
                                                                      PROTOX_ENUM_VALUE( Warhead_5um,                  32 );
                                                                      PROTOX_ENUM_VALUE( Warhead_10um,                 33 );
                                                                      PROTOX_ENUM_VALUE( HighExplosive,              1000 );
                                                                      PROTOX_ENUM_VALUE( HE_Plastic,                 1100 );
                                                                      PROTOX_ENUM_VALUE( HE_Incendiary,              1200 );
                                                                      // add more as needed...
//      +------------------------------------------------------------------------------+--------------------------+--------+

PROTOX_ENUM_EQUALITY_OPERATOR;
PROTOX_ENUM_DEFAULT(Other);

/**********************************************************************************************************************/

}

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
