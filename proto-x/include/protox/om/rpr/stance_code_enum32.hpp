/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_STANCE_CODE_ENUM32_HPP
#define PROTOX_OM_RPR_STANCE_CODE_ENUM32_HPP

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

//      +------------------+----------------------------------------------------------+---------------------+--------+
//      | Name             | Representation                                           | Enumerator          | Values |
//      +------------------+----------------------------------------------------------+---------------------+--------+
namespace StanceCodeEnum32 { PROTOX_ENUM_TYPE(HLA13unsigned_long, hla_13::enumerated) ;
                                                                     PROTOX_ENUM_VALUE( NotApplicable,            0 );
                                                                     PROTOX_ENUM_VALUE( UprightStandingStill,     1 );
                                                                     PROTOX_ENUM_VALUE( UprightWalking,           2 );
                                                                     PROTOX_ENUM_VALUE( UprightRunning,           3 );
                                                                     PROTOX_ENUM_VALUE( Kneeling,                 4 );
                                                                     PROTOX_ENUM_VALUE( Prone,                    5 );
                                                                     PROTOX_ENUM_VALUE( Crawling,                 6 );
                                                                     PROTOX_ENUM_VALUE( Swimming,                 7 );
                                                                     PROTOX_ENUM_VALUE( Parachuting,              8 );
                                                                     PROTOX_ENUM_VALUE( Jumping,                  9 );
                                                                     PROTOX_ENUM_VALUE( Sitting,                 10 );
                                                                     PROTOX_ENUM_VALUE( Squatting,               11 );
                                                                     PROTOX_ENUM_VALUE( Crouching,               12 );
                                                                     PROTOX_ENUM_VALUE( Wading,                  13 );
//      +------------------+----------------------------------------------------------+---------------------+--------+

PROTOX_ENUM_EQUALITY_OPERATOR;
PROTOX_ENUM_DEFAULT(NotApplicable);

}

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
