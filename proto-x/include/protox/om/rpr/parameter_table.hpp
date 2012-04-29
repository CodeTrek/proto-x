/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_PARAMETER_TABLE_HPP
#define PROTOX_OM_RPR_PARAMETER_TABLE_HPP

/**********************************************************************************************************************/

#include <protox/hla/param.hpp>
#include <protox/hla/keywords.hpp>
#include <protox/hla/name.hpp>

#include <protox/hla_13/basic_data_representation_table.hpp>

#include <protox/om/rpr/entity_identifier_struct.hpp>
#include <protox/om/rpr/acknowledge_flag_enum16.hpp>
#include <protox/om/rpr/response_flag_enum16.hpp>
#include <protox/om/rpr/action_enum32.hpp>

/**********************************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**********************************************************************************************************************/

using namespace protox;
using namespace protox::hla;


/**********************************************************************************************************************/

//   +--------------------------------------------+-------------------+---------------------------------------+--------------------------------++
//   | Name                                       | Parameter         | Datatype                              | String Name                    |
//   +--------------------------------------------+-------------------+---------------------------------------+--------------------------------+
struct Acknowledge { HLA_NAME("Acknowledge")     };
                                             struct OriginatingEntity : param< EntityIdentifierStruct::type > { HLA_NAME("OriginatingEntity") };
                                             struct ReceivingEntity   : param< EntityIdentifierStruct::type > { HLA_NAME("ReceivingEntity")   };
                                             struct RequestIdentifier : param< hla_13::HLA13unsigned_long   > { HLA_NAME("RequestIdentifier") };
                                             struct AcknowledgeFlag   : param< AcknowledgeFlagEnum16::type  > { HLA_NAME("AcknowledgeFlag")   };
                                             struct ResponseFlag      : param< ResponseFlagEnum16::type     > { HLA_NAME("ResponseFlag")      };
//   +--------------------------------------------+-------------------+---------------------------------------+--------------------------------+
struct ActionRequest { HLA_NAME("ActionRequest") };
                                          // struct OriginatingEntity : param< EntityIdentifierStruct::type > { HLA_NAME("OriginatingEntity") };
                                          // struct ReceivingEntity   : param< EntityIdentifierStruct::type > { HLA_NAME("ReceivingEntity")   };
                                          // struct RequestIdentifier : param< hla_13::HLA13unsigned_long   > { HLA_NAME("RequestIdentifier") };
                                             struct ActionRequestCode : param< ActionEnum32::type           > { HLA_NAME("ActionRequestCode") };
//   +--------------------------------------------+-------------------+---------------------------------------+--------------------------------+
/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
