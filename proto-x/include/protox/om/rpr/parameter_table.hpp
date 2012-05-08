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
#include <protox/om/rpr/datum_identifier_enum32_array.hpp>
#include <protox/om/rpr/encoding_type_enum32.hpp>
#include <protox/om/rpr/event_type_enum32.hpp>
#include <protox/om/rpr/articulated_parameter_struct_array.hpp>
#include <protox/om/rpr/world_location_struct.hpp>
#include <protox/om/rpr/detonation_result_code_enum8.hpp>
#include <protox/om/rpr/fuse_type_enum16.hpp>
#include <protox/om/rpr/entity_type_struct.hpp>
#include <protox/om/rpr/relative_position_struct.hpp>
#include <protox/om/rpr/warhead_type_enum16.hpp>
#include <protox/om/rpr/repair_type_enum16.hpp>
#include <protox/om/rpr/repair_result_enum8.hpp>
#include <protox/om/rpr/supply_struct_array.hpp>
#include <protox/om/rpr/service_type_enum8.hpp>
#include <protox/om/rpr/clock_time_struct.hpp>
#include <protox/om/rpr/stop_freeze_reason_enum8.hpp>
#include <protox/om/rpr/bool_enum8.hpp>

/**********************************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**********************************************************************************************************************/

using namespace protox;
using namespace protox::hla;


/**********************************************************************************************************************/

//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
//   | Name                                                                         | Parameter                     | Datatype                                | String Name                                  |
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct HLAinteractionRoot  { HLA_NAME("HLAinteractionRoot")                        };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct Acknowledge { HLA_NAME("Acknowledge")                                       };
                                                                               struct OriginatingEntity             : param< EntityIdentifierStruct::type     > { HLA_NAME("OriginatingEntity")             };
                                                                               struct ReceivingEntity               : param< EntityIdentifierStruct::type     > { HLA_NAME("ReceivingEntity")               };
                                                                               struct RequestIdentifier             : param< hla_13::HLA13unsigned_long       > { HLA_NAME("RequestIdentifier")             };
                                                                               struct AcknowledgeFlag               : param< AcknowledgeFlagEnum16::type      > { HLA_NAME("AcknowledgeFlag")               };
                                                                               struct ResponseFlag                  : param< ResponseFlagEnum16::type         > { HLA_NAME("ResponseFlag")                  };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct ActionRequest { HLA_NAME("ActionRequest")                                   };
                                                                            // struct OriginatingEntity             : param< EntityIdentifierStruct::type     > { HLA_NAME("OriginatingEntity")             };
                                                                            // struct ReceivingEntity               : param< EntityIdentifierStruct::type     > { HLA_NAME("ReceivingEntity")               };
                                                                            // struct RequestIdentifier             : param< hla_13::HLA13unsigned_long       > { HLA_NAME("RequestIdentifier")             };
                                                                               struct ActionRequestCode             : param< ActionEnum32::type               > { HLA_NAME("ActionRequestCode")             };
                                                                               struct FixedDatums                   : param< FixedDatumStructArray            > { HLA_NAME("FixedDatums")                   };
                                                                               struct VariableDatumSet              : param< VariableDatumSetStruct::type     > { HLA_NAME("VariableDatumSet")              };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct ActionRequestToObject { HLA_NAME("ActionRequestToObject")                   };
                                                                               struct ObjectIdentifiers             : param< RTIObjectIdArrayStruct::type     > { HLA_NAME("ObjectIdentifiers")             };
                                                                            // struct ActionRequestCode             : param< ActionEnum32::type               > { HLA_NAME("ActionRequestCode")             };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct ActionResponse { HLA_NAME("ActionResponse")                                 };
                                                                            // struct OriginatingEntity             : param< EntityIdentifierStruct::type     > { HLA_NAME("OriginatingEntity")             };
                                                                            // struct ReceivingEntity               : param< EntityIdentifierStruct::type     > { HLA_NAME("ReceivingEntity")               };
                                                                            // struct RequestIdentifier             : param< hla_13::HLA13unsigned_long       > { HLA_NAME("RequestIdentifier")             };
                                                                               struct RequestStatus                 : param< RequestStatusEnum32::type        > { HLA_NAME("RequestStatus")                 };
                                                                            // struct FixedDatums                   : param< FixedDatumStructArray            > { HLA_NAME("FixedDatums")                   };
                                                                            // struct VariableDatumSet              : param< VariableDatumSetStruct::type     > { HLA_NAME("VariableDatumSet")              };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct ActionResponseFromObject { HLA_NAME("ActionResponseFromObject")             };
                                                                               struct ActionResult                  : param< ActionResultEnum32::type         > { HLA_NAME("ActionResult")                  };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct ApplicationSpecificRadioSignal { HLA_NAME("ApplicationSpecificRadioSignal") };
                                                                               struct HostRadioIndex                : param< RTIObjectIdStruct::type          > { HLA_NAME("HostRadioIndex")                };
                                                                               struct DataRate                      : param< hla_13::HLA13unsigned_long       > { HLA_NAME("HostRadioIndex")                };
                                                                               struct SignalDataLength              : param< hla_13::HLA13unsigned_short      > { HLA_NAME("SignalDataLength")              };
                                                                               struct SignalData                    : param< OctetArray                       > { HLA_NAME("SignalData")                    };
                                                                               struct TacticalDataLinkType          : param< TacticalDataLinkTypeEnum16::type > { HLA_NAME("TacticalDataLinkType")          };
                                                                               struct TDLMessageCount               : param< hla_13::HLA13unsigned_short      > { HLA_NAME("TDLMessageCount")               };
                                                                               struct UserProtocolID                : param< UserProtocolEnum32::type         > { HLA_NAME("UserProtocolID")                };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct AttributeChangeRequest { HLA_NAME("AttributeChangeRequest")                 };
                                                                            // struct ObjectIdentifiers             : param< RTIObjectIdArrayStruct::type     > { HLA_NAME("ObjectIdentifiers")             };
                                                                               struct AttributeValueSet             : param< AttributeValueSetStruct::type    > { HLA_NAME("AttributeValueSet")             };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct AttributeChangeResult { HLA_NAME("AttributeChangeResult")                   };
                                                                               struct ObjectIdentifier              : param< RTIObjectIdStruct::type          > { HLA_NAME("ObjectIdentifier")              };
                                                                               struct AttributeChangeResultParam    : param< ResponseFlagEnum16::type         > { HLA_NAME("AttributeChangeResult")         };
                                                                            // struct AttributeValueSet             : param< AttributeValueSetStruct::type    > { HLA_NAME("AttributeValueSet")             };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct Collision { HLA_NAME("Collision")                                           };
                                                                               struct CollidingObjectIdentifier     : param< RTIObjectIdStruct::type          > { HLA_NAME("CollidingObjectIdentifier")     };
                                                                               struct IssuingObjectMass             : param< hla_13::HLA13float               > { HLA_NAME("IssuingObjectMass")             };
                                                                               struct IssuingObjectVelocityVector   : param< VelocityVectorStruct::type       > { HLA_NAME("IssuingObjectVelocityVector")   };
                                                                               struct CollisionType                 : param< CollisionTypeEnum8::type         > { HLA_NAME("CollisionType")                 };
                                                                               struct CollisionLocation             : param< RelativePositionStruct::type     > { HLA_NAME("CollisionLocation")             };
                                                                               struct EventIdentifierParam          : param< EventIdentifierStruct::type      > { HLA_NAME("EventIdentifier")               };
                                                                               struct IssuingObjectIdentifier       : param< RTIObjectIdStruct::type          > { HLA_NAME("IssuingObjectIdentifier")       };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct Comment { HLA_NAME("Comment")                                               };
                                                                            // struct OriginatingEntity             : param< EntityIdentifierStruct::type     > { HLA_NAME("OriginatingEntity")             };
                                                                            // struct ReceivingEntity               : param< EntityIdentifierStruct::type     > { HLA_NAME("ReceivingEntity")               };
                                                                            // struct VariableDatumSet              : param< VariableDatumSetStruct::type     > { HLA_NAME("VariableDatumSet")              };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct CreateEntity { HLA_NAME("CreateEntity")                                     };
                                                                            // struct OriginatingEntity             : param< EntityIdentifierStruct::type     > { HLA_NAME("OriginatingEntity")             };
                                                                            // struct ReceivingEntity               : param< EntityIdentifierStruct::type     > { HLA_NAME("ReceivingEntity")               };
                                                                            // struct RequestIdentifier             : param< hla_13::HLA13unsigned_long       > { HLA_NAME("RequestIdentifier")             };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct CreateObjectRequest { HLA_NAME("CreateObjectRequest")                       };
                                                                               struct ObjectClass                   : param< hla_13::HLA13unsigned_long       > { HLA_NAME("ObjectClass")                   };
                                                                            // struct AttributeValueSet             : param< AttributeValueSetStruct::type    > { HLA_NAME("AttributeValueSet")             };
                                                                            // struct RequestIdentifier             : param< hla_13::HLA13unsigned_long       > { HLA_NAME("RequestIdentifier")             };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct CreateObjectResult { HLA_NAME("CreateObjectResult")                         };
                                                                               struct CreateObjectResultParam       : param< ResponseFlagEnum16::type         > { HLA_NAME("CreateObjectResult")            };
                                                                            // struct RequestIdentifier             : param< hla_13::HLA13unsigned_long       > { HLA_NAME("RequestIdentifier")             };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct Data { HLA_NAME("Data")                                                     };
                                                                            // struct OriginatingEntity             : param< EntityIdentifierStruct::type     > { HLA_NAME("OriginatingEntity")             };
                                                                            // struct ReceivingEntity               : param< EntityIdentifierStruct::type     > { HLA_NAME("ReceivingEntity")               };
                                                                            // struct RequestIdentifier             : param< hla_13::HLA13unsigned_long       > { HLA_NAME("RequestIdentifier")             };
                                                                            // struct FixedDatums                   : param< FixedDatumStructArray            > { HLA_NAME("FixedDatums")                   };
                                                                            // struct VariableDatumSet              : param< VariableDatumSetStruct::type     > { HLA_NAME("VariableDatumSet")              };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct DatabaseIndexRadioSignal { HLA_NAME("DatabaseIndexRadioSignal")             };
                                                                            // struct HostRadioIndex                : param< RTIObjectIdStruct::type          > { HLA_NAME("HostRadioIndex")                };
                                                                               struct DatabaseIndex                 : param< hla_13::HLA13unsigned_long       > { HLA_NAME("DatabaseIndex")                 };
                                                                               struct Duration                      : param< hla_13::HLA13unsigned_long       > { HLA_NAME("Duration")                      };
                                                                               struct StartOffset                   : param< hla_13::HLA13unsigned_long       > { HLA_NAME("StartOffset")                   };
                                                                            // struct TacticalDataLinkType          : param< TacticalDataLinkTypeEnum16::type > { HLA_NAME("TacticalDataLinkType")          };
                                                                            // struct TDLMessageCount               : param< hla_13::HLA13unsigned_short      > { HLA_NAME("TDLMessageCount")               };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct DataQuery { HLA_NAME("DataQuery")                                           };
                                                                            // struct OriginatingEntity             : param< EntityIdentifierStruct::type     > { HLA_NAME("OriginatingEntity")             };
                                                                            // struct ReceivingEntity               : param< EntityIdentifierStruct::type     > { HLA_NAME("ReceivingEntity")               };
                                                                            // struct RequestIdentifier             : param< hla_13::HLA13unsigned_long       > { HLA_NAME("RequestIdentifier")             };
                                                                               struct TimeInterval                  : param< hla_13::HLA13unsigned_long       > { HLA_NAME("TimeInterval")                  };
                                                                               struct FixedDatumIdentifiers         : param< DatumIdentifierEnum32Array       > { HLA_NAME("FixedDatumIdentifiers")         };
                                                                               struct VariableDatumIdentifiers      : param< DatumIdentifierEnum32Array       > { HLA_NAME("VariableDatumIdentifiers")      };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct EncodedAudioRadioSignal { HLA_NAME("EncodedAudioRadioSignal")                                               };
                                                                            // struct HostRadioIndex                : param< RTIObjectIdStruct::type          > { HLA_NAME("HostRadioIndex")                };
                                                                               struct TransmitterSignalEncodingType : param< EncodingTypeEnum32::type         > { HLA_NAME("TransmitterSignalEncodingType") };
                                                                               struct SignalSampleRate              : param< hla_13::HLA13unsigned_long       > { HLA_NAME("SignalSampleRate")              };
                                                                               struct SampleCount                   : param< hla_13::HLA13unsigned_short      > { HLA_NAME("SampleCount")                   };
                                                                            // struct SignalDataLength              : param< hla_13::HLA13unsigned_short      > { HLA_NAME("SignalDataLength")              };
                                                                            // struct SignalData                    : param< OctetArray                       > { HLA_NAME("SignalData")                    };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct EventReport { HLA_NAME("EventReport")                                       };
                                                                            // struct OriginatingEntity             : param< EntityIdentifierStruct::type     > { HLA_NAME("OriginatingEntity")             };
                                                                            // struct ReceivingEntity               : param< EntityIdentifierStruct::type     > { HLA_NAME("ReceivingEntity")               };
                                                                               struct EventType                     : param< EventTypeEnum32::type            > { HLA_NAME("EventType")                     };
                                                                            // struct FixedDatums                   : param< FixedDatumStructArray            > { HLA_NAME("FixedDatums")                   };
                                                                            // struct VariableDatumSet              : param< VariableDatumSetStruct::type     > { HLA_NAME("VariableDatumSet")              };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct MunitionDetonation { HLA_NAME("MunitionDetonation")                         };
                                                                               struct ArticulatedPartData           : param< ArticulatedParameterStructArray  > { HLA_NAME("ArticulatedPartData")           };
                                                                               struct DetonationLocation            : param< WorldLocationStruct::type        > { HLA_NAME("DetonationLocation")            };
                                                                               struct DetonationResultCode          : param< DetonationResultCodeEnum8::type  > { HLA_NAME("DetonationResultCode")          };
                                                                            // struct EventIdentifierParam          : param< EventIdentifierStruct::type      > { HLA_NAME("EventIdentifier")               };
                                                                               struct FiringObjectIdentifier        : param< RTIObjectIdStruct::type          > { HLA_NAME("FiringObjectIdentifier")        };
                                                                               struct FinalVelocityVector           : param< VelocityVectorStruct::type       > { HLA_NAME("FinalVelocityVector")           };
                                                                               struct FuseType                      : param< FuseTypeEnum16::type             > { HLA_NAME("FuseType")                      };
                                                                               struct MunitionObjectIdentifier      : param< RTIObjectIdStruct::type          > { HLA_NAME("MunitionObjectIdentifier")      };
                                                                               struct MunitionType                  : param< EntityTypeStruct::type           > { HLA_NAME("MunitionType")                  };
                                                                               struct QuantityFired                 : param< hla_13::HLA13unsigned_short      > { HLA_NAME("QuantityFired")                 };
                                                                               struct RateOfFire                    : param< hla_13::HLA13unsigned_short      > { HLA_NAME("RateOfFire")                    };
                                                                               struct RelativeDetonationLocation    : param< RelativePositionStruct::type     > { HLA_NAME("RelativeDetonationLocation")    };
                                                                               struct TargetObjectIdentifier        : param< RTIObjectIdStruct::type          > { HLA_NAME("TargetObjectIdentifier")        };
                                                                               struct WarheadType                   : param< WarheadTypeEnum16::type          > { HLA_NAME("WarheadType")                   };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct RadioSignal { HLA_NAME("RadioSignal")                                       };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct RawBinaryRadioSignal { HLA_NAME("RawBinaryRadioSignal")                     };
                                                                            // struct HostRadioIndex                : param< RTIObjectIdStruct::type          > { HLA_NAME("HostRadioIndex")                };
                                                                            // struct DataRate                      : param< hla_13::HLA13unsigned_long       > { HLA_NAME("HostRadioIndex")                };
                                                                            // struct SignalDataLength              : param< hla_13::HLA13unsigned_short      > { HLA_NAME("SignalDataLength")              };
                                                                            // struct SignalData                    : param< OctetArray                       > { HLA_NAME("SignalData")                    };
                                                                            // struct TacticalDataLinkType          : param< TacticalDataLinkTypeEnum16::type > { HLA_NAME("TacticalDataLinkType")          };
                                                                            // struct TDLMessageCount               : param< hla_13::HLA13unsigned_short      > { HLA_NAME("TDLMessageCount")               };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct RemoveEntity { HLA_NAME("RemoveEntity")                     };
                                                                            // struct OriginatingEntity             : param< EntityIdentifierStruct::type     > { HLA_NAME("OriginatingEntity")             };
                                                                            // struct ReceivingEntity               : param< EntityIdentifierStruct::type     > { HLA_NAME("ReceivingEntity")               };
                                                                            // struct RequestIdentifier             : param< hla_13::HLA13unsigned_long       > { HLA_NAME("RequestIdentifier")             };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct RemoveObjectRequest { HLA_NAME("RemoveObjectRequest")                       };
                                                                            // struct ObjectIdentifiers             : param< RTIObjectIdArrayStruct::type     > { HLA_NAME("ObjectIdentifiers")             };
                                                                            // struct RequestIdentifier             : param< hla_13::HLA13unsigned_long       > { HLA_NAME("RequestIdentifier")             };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct RemoveObjectResult { HLA_NAME("RemoveObjectResult")                         };
                                                                               struct RemoveObjectResultParam       : param< ResponseFlagEnum16::type         > { HLA_NAME("RemoveObjectResult")            };
                                                                            // struct RequestIdentifier             : param< hla_13::HLA13unsigned_long       > { HLA_NAME("RequestIdentifier")             };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct RepairComplete { HLA_NAME("RepairComplete")                                 };
                                                                               struct ReceivingObject               : param< RTIObjectIdStruct::type          > { HLA_NAME("ReceivingObject")               };
                                                                               struct RepairingObject               : param< RTIObjectIdStruct::type          > { HLA_NAME("RepairingObject")               };
                                                                               struct RepairType                    : param< RepairTypeEnum16::type           > { HLA_NAME("RepairType")                    };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct RepairResponse { HLA_NAME("RepairResponse")                                 };
                                                                            // struct ReceivingObject               : param< RTIObjectIdStruct::type          > { HLA_NAME("ReceivingObject")               };
                                                                            // struct RepairingObject               : param< RTIObjectIdStruct::type          > { HLA_NAME("RepairingObject")               };
                                                                               struct RepairResultCode              : param< RepairTypeEnum16::type           > { HLA_NAME("RepairResultCode")              };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct ResupplyCancel { HLA_NAME("ResupplyCancel")                                 };
                                                                            // struct ReceivingObject               : param< RTIObjectIdStruct::type          > { HLA_NAME("ReceivingObject")               };
                                                                               struct SupplyingObject               : param< RTIObjectIdStruct::type          > { HLA_NAME("SupplyingObject")               };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct ResupplyOffer { HLA_NAME("ResupplyOffer")                                   };
                                                                            // struct ReceivingObject               : param< RTIObjectIdStruct::type          > { HLA_NAME("ReceivingObject")               };
                                                                            // struct SupplyingObject               : param< RTIObjectIdStruct::type          > { HLA_NAME("SupplyingObject")               };
                                                                               struct SuppliesData                  : param< SupplyStructArray                > { HLA_NAME("SuppliesData")                  };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct ResupplyReceived { HLA_NAME("ResupplyReceived")                             };
                                                                            // struct ReceivingObject               : param< RTIObjectIdStruct::type          > { HLA_NAME("ReceivingObject")               };
                                                                            // struct SupplyingObject               : param< RTIObjectIdStruct::type          > { HLA_NAME("SupplyingObject")               };
                                                                            // struct SuppliesData                  : param< SupplyStructArray                > { HLA_NAME("SuppliesData")                  };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct ServiceRequest { HLA_NAME("ServiceRequest")                                 };
                                                                               struct RequestingObject              : param< RTIObjectIdStruct::type          > { HLA_NAME("RequestingObject")              };
                                                                               struct ServicingObject               : param< RTIObjectIdStruct::type          > { HLA_NAME("ServicingObject")               };
                                                                               struct ServiceType                   : param< ServiceTypeEnum8::type           > { HLA_NAME("ServiceType")                   };
                                                                            // struct SuppliesData                  : param< SupplyStructArray                > { HLA_NAME("SuppliesData")                  };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct SetData { HLA_NAME("SetData")                                               };
                                                                            // struct OriginatingEntity             : param< EntityIdentifierStruct::type     > { HLA_NAME("OriginatingEntity")             };
                                                                            // struct ReceivingEntity               : param< EntityIdentifierStruct::type     > { HLA_NAME("ReceivingEntity")               };
                                                                            // struct RequestIdentifier             : param< hla_13::HLA13unsigned_long       > { HLA_NAME("RequestIdentifier")             };
                                                                            // struct FixedDatums                   : param< FixedDatumStructArray            > { HLA_NAME("FixedDatums")                   };
                                                                            // struct VariableDatumSet              : param< VariableDatumSetStruct::type     > { HLA_NAME("VariableDatumSet")              };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct StartResume { HLA_NAME("StartResume")                                       };
                                                                            // struct OriginatingEntity             : param< EntityIdentifierStruct::type     > { HLA_NAME("OriginatingEntity")             };
                                                                            // struct ReceivingEntity               : param< EntityIdentifierStruct::type     > { HLA_NAME("ReceivingEntity")               };
                                                                            // struct RequestIdentifier             : param< hla_13::HLA13unsigned_long       > { HLA_NAME("RequestIdentifier")             };
                                                                               struct RealWorldTime                 : param< ClockTimeStruct::type            > { HLA_NAME("RealWorldTime")                 };
                                                                               struct SimulationTime                : param< ClockTimeStruct::type            > { HLA_NAME("SimulationTime")                };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct StopFreeze { HLA_NAME("StopFreeze")                                         };
                                                                            // struct OriginatingEntity             : param< EntityIdentifierStruct::type     > { HLA_NAME("OriginatingEntity")             };
                                                                            // struct ReceivingEntity               : param< EntityIdentifierStruct::type     > { HLA_NAME("ReceivingEntity")               };
                                                                            // struct RequestIdentifier             : param< hla_13::HLA13unsigned_long       > { HLA_NAME("RequestIdentifier")             };
                                                                            // struct RealWorldTime                 : param< ClockTimeStruct::type            > { HLA_NAME("RealWorldTime")                 };
                                                                               struct Reason                        : param< StopFreezeReasonEnum8::type      > { HLA_NAME("Reason")                        };
                                                                               struct ReflectValues                 : param< BoolEnum8::type                  > { HLA_NAME("ReflectValues")                 };
                                                                               struct RunInternalSimulationClock    : param< BoolEnum8::type                  > { HLA_NAME("RunInternalSimulationClock")    };
                                                                               struct UpdateAttributes              : param< BoolEnum8::type                  > { HLA_NAME("UpdateAttributes")              };
//   +------------------------------------------------------------------------------+-------------------------------+-----------------------------------------+----------------------------------------------+
struct WeaponFire { HLA_NAME("WeaponFire")                                         };
                                                                            // struct EventIdentifierParam          : param< EventIdentifierStruct::type      > { HLA_NAME("EventIdentifier")               };
                                                                               struct FireControlSolutionRange      : param< hla_13::HLA13float               > { HLA_NAME("FireControlSolutionRange")      };
                                                                               struct FireMissionIndex              : param< hla_13::HLA13unsigned_long       > { HLA_NAME("FireMissionIndex")              };
                                                                               struct FiringLocation                : param< WorldLocationStruct::type        > { HLA_NAME("FiringLocation")                };
                                                                            // struct FiringObjectIdentifier        : param< RTIObjectIdStruct::type          > { HLA_NAME("FiringObjectIdentifier")        };
                                                                            // struct FuseType                      : param< FuseTypeEnum16::type             > { HLA_NAME("FuseType")                      };
                                                                               struct InitialVelocityVector         : param< VelocityVectorStruct::type       > { HLA_NAME("InitialVelocityVector")         };
                                                                            // struct MunitionObjectIdentifier      : param< RTIObjectIdStruct::type          > { HLA_NAME("MunitionObjectIdentifier")      };
                                                                            // struct MunitionType                  : param< EntityTypeStruct::type           > { HLA_NAME("MunitionType")                  };
                                                                            // struct QuantityFired                 : param< hla_13::HLA13unsigned_short      > { HLA_NAME("QuantityFired")                 };
                                                                            // struct RateOfFire                    : param< hla_13::HLA13unsigned_short      > { HLA_NAME("RateOfFire")                    };
                                                                            // struct RelativeDetonationLocation    : param< RelativePositionStruct::type     > { HLA_NAME("RelativeDetonationLocation")    };
                                                                            // struct TargetObjectIdentifier        : param< RTIObjectIdStruct::type          > { HLA_NAME("TargetObjectIdentifier")        };
                                                                            // struct WarheadType                   : param< WarheadTypeEnum16::type          > { HLA_NAME("WarheadType")                   };
/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
