/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_EMITTER_TYPE_ENUM16_HPP
#define PROTOX_OM_RPR_EMITTER_TYPE_ENUM16_HPP

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

//      +-------------------+----------------------------------------------------------+-----------------------+--------+
//      | Name              | Representation                                           | Enumerator            | Values |
//      +-------------------+----------------------------------------------------------+-----------------------+--------+
namespace EmitterTypeEnum16 { PROTOX_ENUM_TYPE(HLA13unsigned_short, hla_13::enumerated);
                                                                      PROTOX_ENUM_VALUE( Emitter_1226_DECCA_MIL,     45);
                                                                      PROTOX_ENUM_VALUE( Emitter_9GR600,             90);
                                                                      PROTOX_ENUM_VALUE( Emitter_9LV_200_TA,        135);
                                                                      PROTOX_ENUM_VALUE( Emitter_9LV_200_TV,        180);
                                                                      PROTOX_ENUM_VALUE( A310Z,                     225);
                                                                      PROTOX_ENUM_VALUE( A325A,                     270);
                                                                      PROTOX_ENUM_VALUE( A346Z,                     315);
                                                                      PROTOX_ENUM_VALUE( A353B,                     360);
                                                                      PROTOX_ENUM_VALUE( A372A,                     405);
                                                                      PROTOX_ENUM_VALUE( A372B,                     450);
                                                                      PROTOX_ENUM_VALUE( A372C,                     495);
                                                                      PROTOX_ENUM_VALUE( A377A,                     540);
                                                                      PROTOX_ENUM_VALUE( A377B,                     585);
                                                                      // add more as needed...
//      +-------------------------------------------------------------------------------------+------------+--------+

PROTOX_ENUM_EQUALITY_OPERATOR;
PROTOX_ENUM_DEFAULT(Emitter_1226_DECCA_MIL);

/**********************************************************************************************************************/

}

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
