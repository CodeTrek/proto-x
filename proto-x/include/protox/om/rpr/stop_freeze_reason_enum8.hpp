/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_STOP_FREEZE_REASON_ENUM8_HPP
#define PROTOX_OM_RPR_STOP_FREEZE_REASON_ENUM8_HPP

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

//      +-----------------------+-------------------------------------------------+--------------------------+--------+
//      | Name                  | Representation                                  | Enumerator               | Values |
//      +-----------------------+-------------------------------------------------+--------------------------+--------+
namespace StopFreezeReasonEnum8 { PROTOX_ENUM_TYPE(HLA13octet, hla_13::enumerated);
//      +-----------------------+-------------------------------------------------+--------------------------+--------+
                                                                 PROTOX_ENUM_VALUE( Other,                         0 );
                                                                 PROTOX_ENUM_VALUE( Recess,                        1 );
                                                                 PROTOX_ENUM_VALUE( Termination,                   2 );
                                                                 PROTOX_ENUM_VALUE( SystemFailure,                 3 );
                                                                 PROTOX_ENUM_VALUE( SecurityViolation,             4 );
                                                                 PROTOX_ENUM_VALUE( EntityReconstitution,          5 );
                                                                 PROTOX_ENUM_VALUE( StopForReset,                  6 );
                                                                 PROTOX_ENUM_VALUE( StopForRestart,                7 );
                                                                 PROTOX_ENUM_VALUE( AbortTrainingResumeTacOps,     8 );
//      +-----------------------+-------------------------------------------------+--------------------------+--------+

PROTOX_ENUM_EQUALITY_OPERATOR;
PROTOX_ENUM_DEFAULT(Other);

/**********************************************************************************************************************/

}

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
