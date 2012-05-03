/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_USER_PROTOCOL_ENUM32_HPP
#define PROTOX_OM_RPR_USER_PROTOCOL_ENUM32_HPP

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

//      +--------------------+----------------------------------------------------------+----------------------------------+--------+
//      | Name               | Representation                                           | Enumerator                       | Values |
//      +--------------------+----------------------------------------------------------+----------------------------------+--------+
namespace UserProtocolEnum32 { PROTOX_ENUM_TYPE(HLA13unsigned_long, hla_13::enumerated) ;
                                                                       PROTOX_ENUM_VALUE( CCSIL,                                 1 );
                                                                       PROTOX_ENUM_VALUE( A2ATD_SINCGARS_ERF,                    5 );
                                                                       PROTOX_ENUM_VALUE( A2ATD_CAC2,                            6 );
                                                                       PROTOX_ENUM_VALUE( Battle_Command,                       20 );
                                                                       PROTOX_ENUM_VALUE( ModSAF_Text_Radio,                   177 );
                                                                       PROTOX_ENUM_VALUE( CCTT_SINCGARS_ERF_LOCKOUT,           200 );
                                                                       PROTOX_ENUM_VALUE( CCTT_SINCGARS_ERF_HOPSET,            201 );
                                                                       PROTOX_ENUM_VALUE( CCTT_SINCGARS_OTAR,                  202 );
                                                                       PROTOX_ENUM_VALUE( CCTT_SINCGARS_DATA,                  203 );
                                                                       PROTOX_ENUM_VALUE( ModSAF_FWA_Forward_Air_Controller,   546 );
                                                                       PROTOX_ENUM_VALUE( ModSAF_Threat_ADA_C3,                832 );
                                                                       PROTOX_ENUM_VALUE( ModSAF_Artillery_Fire_Control,      4570 );
                                                                       PROTOX_ENUM_VALUE( AGTS,                               5361 );
                                                                       PROTOX_ENUM_VALUE( GC3,                                6000 );
                                                                       PROTOX_ENUM_VALUE( WNCP_data,                          6010 );
//      +--------------------+----------------------------------------------------------+----------------------------------+--------+

PROTOX_ENUM_EQUALITY_OPERATOR;
PROTOX_ENUM_DEFAULT(CCSIL);

}

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
