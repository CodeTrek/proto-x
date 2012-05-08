/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_OM_RPR_INTER_CLASS_TABLE_HPP
#define PROTOX_OM_RPR_INTER_CLASS_TABLE_HPP

/**************************************************************************************************/

#include <protox/hla/i_class.hpp>
#include <protox/hla/keywords.hpp>

#include <protox/om/rpr/parameter_table.hpp>

/**************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**************************************************************************************************/

using namespace protox::hla;

/**************************************************************************************************/


//// Interaction Class Table ////////////////////////////////////////////////////////
struct inter_class_table : i_class< HLAinteractionRoot, none, child<
//   +------------------------------------+-------------------------------------------+
//   | Class 1                            | Class 2                                   |
//   +------------------------------------+-------------------------------------------+
       i_class< Acknowledge,                                                                   params< OriginatingEntity, ReceivingEntity, RequestIdentifier, AcknowledgeFlag, ResponseFlag > >,
       i_class< ActionRequest,                                                                 params< OriginatingEntity, ReceivingEntity, RequestIdentifier, ActionRequestCode, FixedDatums, VariableDatumSet > >,
       i_class< ActionResponse,                                                                params< OriginatingEntity, ReceivingEntity, RequestIdentifier, RequestStatus, FixedDatums, VariableDatumSet > >,
       i_class< ActionRequestToObject,                                                         params< ObjectIdentifiers, ActionRequestCode > >,
       i_class< ActionResponseFromObject,                                                      params< ActionResult > >,
       i_class< AttributeChangeRequest,                                                        params< ObjectIdentifiers, AttributeValueSet > >,
       i_class< AttributeChangeResult,                                                         params< ObjectIdentifier, AttributeChangeResultParam, AttributeValueSet > >,
       i_class< Collision,                                                                     params< CollidingObjectIdentifier, IssuingObjectMass, IssuingObjectVelocityVector, CollisionType, CollisionLocation, EventIdentifierParam, IssuingObjectIdentifier > >,
       i_class< Comment,                                                                       params< OriginatingEntity, ReceivingEntity, VariableDatumSet > >,
       i_class< CreateObjectRequest,                                                           params< ObjectClass, AttributeValueSet, RequestIdentifier > >,
       i_class< CreateObjectResult,                                                            params< CreateObjectResultParam, RequestIdentifier > >,
       i_class< CreateEntity,                                                                  params< OriginatingEntity, ReceivingEntity, RequestIdentifier > >,
       i_class< Data,                                                                          params< OriginatingEntity, ReceivingEntity, RequestIdentifier, FixedDatums, VariableDatumSet > >,
       i_class< DataQuery,                                                                     params< OriginatingEntity, ReceivingEntity, RequestIdentifier, TimeInterval, FixedDatumIdentifiers, VariableDatumIdentifiers > >,
       i_class< EventReport,                                                                   params< OriginatingEntity, ReceivingEntity, EventType, FixedDatums, VariableDatumSet > >,
       i_class< MunitionDetonation,                                                            params< ArticulatedPartData, DetonationLocation, DetonationResultCode, EventIdentifierParam, FiringObjectIdentifier, FinalVelocityVector, FuseType, MunitionObjectIdentifier, MunitionType, QuantityFired, RateOfFire, RelativeDetonationLocation, TargetObjectIdentifier, WarheadType > >,
       i_class< RadioSignal, none,
//   +------------------------------------+-------------------------------------------+
                                     child<  i_class< ApplicationSpecificRadioSignal,          params< HostRadioIndex, DataRate, SignalDataLength, SignalData, TacticalDataLinkType, TDLMessageCount, UserProtocolID > >,
                                             i_class< DatabaseIndexRadioSignal,                params< HostRadioIndex, DatabaseIndex, Duration, StartOffset, TacticalDataLinkType, TDLMessageCount > >,
                                             i_class< EncodedAudioRadioSignal,                 params< HostRadioIndex, TransmitterSignalEncodingType, SignalSampleRate, SampleCount, SignalDataLength, SignalData > >,
                                             i_class< RawBinaryRadioSignal,                    params< HostRadioIndex, DataRate, SignalDataLength, SignalData, TacticalDataLinkType, TDLMessageCount > > > >,
//   +------------------------------------+-------------------------------------------+
       i_class< RemoveObjectRequest,                                                           params< ObjectIdentifiers, RequestIdentifier > >,
       i_class< RemoveObjectResult,                                                            params< RemoveObjectResultParam, RequestIdentifier > >,
       i_class< RemoveEntity,                                                                  params< OriginatingEntity, ReceivingEntity, RequestIdentifier > >,
       i_class< RepairComplete,                                                                params< ReceivingObject, RepairingObject, RepairType > >,
       i_class< RepairResponse,                                                                params< ReceivingObject, RepairingObject, RepairResultCode > >,
       i_class< ResupplyCancel,                                                                params< ReceivingObject, SupplyingObject > >,
       i_class< ResupplyOffer,                                                                 params< ReceivingObject, SupplyingObject, SuppliesData > >,
       i_class< ResupplyReceived,                                                              params< ReceivingObject, SupplyingObject, SuppliesData > >,
       i_class< ServiceRequest,                                                                params< RequestingObject, ServicingObject, ServiceType, SuppliesData > >,
       i_class< SetData,                                                                       params< OriginatingEntity, ReceivingEntity, RequestIdentifier, FixedDatums, VariableDatumSet > >,
       i_class< StartResume,                                                                   params< OriginatingEntity, ReceivingEntity, RequestIdentifier, RealWorldTime, SimulationTime > >,
       i_class< StopFreeze,                                                                    params< OriginatingEntity, ReceivingEntity, RequestIdentifier, RealWorldTime, Reason, ReflectValues, RunInternalSimulationClock, UpdateAttributes > >,
       i_class< WeaponFire,                                                                    params< EventIdentifierParam, FireControlSolutionRange, FireMissionIndex, FiringLocation, FiringObjectIdentifier, FuseType, InitialVelocityVector, MunitionObjectIdentifier, MunitionType, QuantityFired, RateOfFire, RelativeDetonationLocation, TargetObjectIdentifier, WarheadType > >
//   +------------------------------------+-------------------------------------------+
> > {};

/**************************************************************************************************/

}}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
