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
#include <protox/om/rpr/fixed_datum_struct_array.hpp>
#include <protox/om/rpr/variable_datum_set_struct.hpp>
#include <protox/om/rpr/rti_object_id_array_struct.hpp>
#include <protox/om/rpr/request_status_enum32.hpp>
#include <protox/om/rpr/action_result_enum32.hpp>
#include <protox/om/rpr/rti_object_id_struct.hpp>
#include <protox/om/rpr/octet_array.hpp>
#include <protox/om/rpr/tactical_data_link_type_enum16.hpp>
#include <protox/om/rpr/user_protocol_enum32.hpp>
#include <protox/om/rpr/attribute_value_set_struct.hpp>
#include <protox/om/rpr/response_flag_enum16.hpp>
#include <protox/om/rpr/velocity_vector_struct.hpp>
#include <protox/om/rpr/collision_type_enum8.hpp>
#include <protox/om/rpr/relative_position_struct.hpp>
#include <protox/om/rpr/event_identifier_struct.hpp>

/**********************************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**********************************************************************************************************************/

using namespace protox;
using namespace protox::hla;


/**********************************************************************************************************************/

//   +------------------------------------------------------------------------------+-----------------------------+-------------------------------------------+--------------------------------------------+
//   | Name                                                                         | Parameter                   | Datatype                                  | String Name                                |
//   +------------------------------------------------------------------------------+-----------------------------+-------------------------------------------+--------------------------------------------+
struct Acknowledge { HLA_NAME("Acknowledge")                                       };
                                                                               struct OriginatingEntity           : param< EntityIdentifierStruct::type     > { HLA_NAME("OriginatingEntity")             };
                                                                               struct ReceivingEntity             : param< EntityIdentifierStruct::type     > { HLA_NAME("ReceivingEntity")               };
                                                                               struct RequestIdentifier           : param< hla_13::HLA13unsigned_long       > { HLA_NAME("RequestIdentifier")             };
                                                                               struct AcknowledgeFlag             : param< AcknowledgeFlagEnum16::type      > { HLA_NAME("AcknowledgeFlag")               };
                                                                               struct ResponseFlag                : param< ResponseFlagEnum16::type         > { HLA_NAME("ResponseFlag")                  };
//   +------------------------------------------------------------------------------+-----------------------------+-------------------------------------------+--------------------------------------------+
struct ActionRequest { HLA_NAME("ActionRequest")                                   };
                                                                            // struct OriginatingEntity           : param< EntityIdentifierStruct::type     > { HLA_NAME("OriginatingEntity")             };
                                                                            // struct ReceivingEntity             : param< EntityIdentifierStruct::type     > { HLA_NAME("ReceivingEntity")               };
                                                                            // struct RequestIdentifier           : param< hla_13::HLA13unsigned_long       > { HLA_NAME("RequestIdentifier")             };
                                                                               struct ActionRequestCode           : param< ActionEnum32::type               > { HLA_NAME("ActionRequestCode")             };
                                                                               struct FixedDatums                 : param< FixedDatumStructArray            > { HLA_NAME("FixedDatums")                   };
                                                                               struct VariableDatumSet            : param< VariableDatumSetStruct::type     > { HLA_NAME("VariableDatumSet")              };
//   +------------------------------------------------------------------------------+-----------------------------+-------------------------------------------+--------------------------------------------+
struct ActionRequestToObject { HLA_NAME("ActionRequestToObject")                   };
                                                                               struct ObjectIdentifiers           : param< RTIObjectIdArrayStruct::type     > { HLA_NAME("ObjectIdentifiers")             };
                                                                            // struct ActionRequestCode           : param< ActionEnum32::type               > { HLA_NAME("ActionRequestCode")             };
//   +------------------------------------------------------------------------------+-----------------------------+-------------------------------------------+--------------------------------------------+
struct ActionResponse { HLA_NAME("ActionResponse")                                 };
                                                                            // struct OriginatingEntity           : param< EntityIdentifierStruct::type     > { HLA_NAME("OriginatingEntity")             };
                                                                            // struct ReceivingEntity             : param< EntityIdentifierStruct::type     > { HLA_NAME("ReceivingEntity")               };
                                                                            // struct RequestIdentifier           : param< hla_13::HLA13unsigned_long       > { HLA_NAME("RequestIdentifier")             };
                                                                               struct RequestStatus               : param< RequestStatusEnum32::type        > { HLA_NAME("RequestStatus")                 };
                                                                            // struct FixedDatums                 : param< FixedDatumStructArray            > { HLA_NAME("FixedDatums")                   };
                                                                            // struct VariableDatumSet            : param< VariableDatumSetStruct::type     > { HLA_NAME("VariableDatumSet")              };
//   +------------------------------------------------------------------------------+-----------------------------+-------------------------------------------+--------------------------------------------+
struct ActionResponseFromObject { HLA_NAME("ActionResponseFromObject")             };
                                                                               struct ActionResult                : param< ActionResultEnum32::type         > { HLA_NAME("ActionResult")                  };
//   +------------------------------------------------------------------------------+-----------------------------+-------------------------------------------+--------------------------------------------+
struct ApplicationSpecificRadioSignal { HLA_NAME("ApplicationSpecificRadioSignal") };
                                                                               struct HostRadioIndex              : param< RTIObjectIdStruct::type          > { HLA_NAME("HostRadioIndex")                };
                                                                               struct DataRate                    : param< hla_13::HLA13unsigned_long       > { HLA_NAME("HostRadioIndex")                };
                                                                               struct SignalDataLength            : param< hla_13::HLA13unsigned_short      > { HLA_NAME("SignalDataLength")              };
                                                                               struct SignalData                  : param< OctetArray                       > { HLA_NAME("SignalData")                    };
                                                                               struct TacticalDataLinkType        : param< TacticalDataLinkTypeEnum16::type > { HLA_NAME("TacticalDataLinkType")          };
                                                                               struct TDLMessageCount             : param< hla_13::HLA13unsigned_short      > { HLA_NAME("TDLMessageCount")               };
                                                                               struct UserProtocolID              : param< UserProtocolEnum32::type         > { HLA_NAME("UserProtocolID")                };
//   +------------------------------------------------------------------------------+-----------------------------+-------------------------------------------+--------------------------------------------+
struct AttributeChangeRequest { HLA_NAME("AttributeChangeRequest")                 };
                                                                            // struct ObjectIdentifiers           : param< RTIObjectIdArrayStruct::type       > { HLA_NAME("ObjectIdentifiers")           };
                                                                               struct AttributeValueSet           : param< AttributeValueSetStruct::type      > { HLA_NAME("AttributeValueSet")           };
//   +------------------------------------------------------------------------------+-----------------------------+-------------------------------------------+--------------------------------------------+
struct AttributeChangeResult { HLA_NAME("AttributeChangeResult")                   };
                                                                               struct ObjectIdentifier            : param< RTIObjectIdStruct::type            > { HLA_NAME("ObjectIdentifier")            };
                                                                               struct AttributeChangeResultParam  : param< ResponseFlagEnum16::type           > { HLA_NAME("AttributeChangeResult")       };
                                                                            // struct AttributeValueSet           : param< AttributeValueSetStruct::type      > { HLA_NAME("AttributeValueSet")           };
//   +------------------------------------------------------------------------------+-----------------------------+-------------------------------------------+--------------------------------------------+
struct Collision { HLA_NAME("Collision")                                           };
                                                                               struct CollidingObjectIdentifier   : param< RTIObjectIdStruct::type            > { HLA_NAME("CollidingObjectIdentifier")   };
                                                                               struct IssuingObjectMass           : param< hla_13::HLA13float                 > { HLA_NAME("IssuingObjectMass")           };
                                                                               struct IssuingObjectVelocityVector : param< VelocityVectorStruct::type         > { HLA_NAME("IssuingObjectVelocityVector") };
                                                                               struct CollisionType               : param< CollisionTypeEnum8::type           > { HLA_NAME("CollisionType")               };
                                                                               struct CollisionLocation           : param< RelativePositionStruct::type       > { HLA_NAME("CollisionLocation")           };
                                                                               struct EventIdentifier             : param< EventIdentifierStruct::type        > { HLA_NAME("EventIdentifier")             };
                                                                               struct IssuingObjectIdentifier     : param< RTIObjectIdStruct::type            > { HLA_NAME("IssuingObjectIdentifier")     };
//   +------------------------------------------------------------------------------+-----------------------------+-------------------------------------------+--------------------------------------------+
/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
