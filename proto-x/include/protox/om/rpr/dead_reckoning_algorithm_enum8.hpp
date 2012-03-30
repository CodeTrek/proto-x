/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_DEAD_RECKONING_ALGORITHM_ENUM8_HPP
#define PROTOX_OM_RPR_DEAD_RECKONING_ALGORITHM_ENUM8_HPP

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

//      +-----------------------------+-------------------------------------------------+------------+--------+
//      | Name                        | Representation                                  | Enumerator | Values |
//      +-----------------------------+-------------------------------------------------+------------+--------+
namespace DeadReckoningAlgorithmEnum8 { PROTOX_ENUM_TYPE(HLA13octet, hla_13::enumerated);
//      +-----------------------------+-------------------------------------------------+------------+--------+
                                                                       PROTOX_ENUM_VALUE( OTHER,           0 );
                                                                       PROTOX_ENUM_VALUE( STATIC,          1 );
                                                                       PROTOX_ENUM_VALUE( DRM_FPW,         2 );
                                                                       PROTOX_ENUM_VALUE( DRM_RPW,         3 );
                                                                       PROTOX_ENUM_VALUE( DRM_RVW,         4 );
                                                                       PROTOX_ENUM_VALUE( DRM_FVW,         5 );
                                                                       PROTOX_ENUM_VALUE( DRM_FPB,         6 );
                                                                       PROTOX_ENUM_VALUE( DRM_RPB,         7 );
                                                                       PROTOX_ENUM_VALUE( DRM_RVB,         8 );
                                                                       PROTOX_ENUM_VALUE( DRM_FVB,         9 );
//      +-------------------------------------------------------------------------------+------------+--------+

PROTOX_ENUM_EQUALITY_OPERATOR;
PROTOX_ENUM_DEFAULT(STATIC);

/**********************************************************************************************************************/

}

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
