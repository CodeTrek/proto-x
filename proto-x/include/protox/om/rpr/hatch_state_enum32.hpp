/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_HATCH_STATE_ENUM32_HPP
#define PROTOX_OM_RPR_HATCH_STATE_ENUM32_HPP

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

//      +------------------+----------------------------------------------------------+-------------------------------------------------+--------+
//      | Name             | Representation                                           | Enumerator                                      | Values |
//      +------------------+----------------------------------------------------------+-------------------------------------------------+--------+
namespace HatchStateEnum32 { PROTOX_ENUM_TYPE(HLA13unsigned_long, hla_13::enumerated) ;
                                                                     PROTOX_ENUM_VALUE( NotApplicable,                                        0 );
                                                                     PROTOX_ENUM_VALUE( PrimaryHatchIsClosed,                                 1 );
                                                                     PROTOX_ENUM_VALUE( PrimaryHatchIsPopped,                                 2 );
                                                                     PROTOX_ENUM_VALUE( PrimaryHatchIsPoppedAndPersonIsVisibleUnderHatch,     3 );
                                                                     PROTOX_ENUM_VALUE( PrimaryHatchIsOpen,                                   4 );
                                                                     PROTOX_ENUM_VALUE( PrimaryHatchIsOpenAndPersonIsVisible,                 5 );
//      +------------------+----------------------------------------------------------+-------------------------------------------------+--------+


PROTOX_ENUM_EQUALITY_OPERATOR;
PROTOX_ENUM_DEFAULT(NotApplicable);

}

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
