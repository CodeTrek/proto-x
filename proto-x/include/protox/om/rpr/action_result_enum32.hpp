/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_ACTION_RESULT_ENUM32_HPP
#define PROTOX_OM_RPR_ACTION_RESULT_ENUM32_HPP

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

//      +--------------------+----------------------------------------------------------+-----------------------+--------+
//      | Name               | Representation                                           | Enumerator            | Values |
//      +--------------------+----------------------------------------------------------+-----------------------+--------+
namespace ActionResultEnum32 { PROTOX_ENUM_TYPE(HLA13unsigned_long, hla_13::enumerated) ;
                                                                       PROTOX_ENUM_VALUE( Other,                      0 );
                                                                       PROTOX_ENUM_VALUE( Pending,                    1 );
                                                                       PROTOX_ENUM_VALUE( Executing,                  2 );
                                                                       PROTOX_ENUM_VALUE( PartiallyComplete,          3 );
                                                                       PROTOX_ENUM_VALUE( Complete,                   4 );
                                                                       PROTOX_ENUM_VALUE( RequestRejected,            5 );
                                                                       PROTOX_ENUM_VALUE( RetransmitRequestNow,       6 );
                                                                       PROTOX_ENUM_VALUE( RetransmitRequestLater,     7 );
                                                                       PROTOX_ENUM_VALUE( InvalidTimeParameters,      8 );
                                                                       PROTOX_ENUM_VALUE( SimulationTimeExceeded,     9 );
                                                                       PROTOX_ENUM_VALUE( RequestDone,               10 );
//      +-------------------------------------------------------------------------------+-----------------------+--------+

PROTOX_ENUM_EQUALITY_OPERATOR;
PROTOX_ENUM_DEFAULT(Other);

}

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
