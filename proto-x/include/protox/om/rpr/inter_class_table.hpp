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
       i_class< Acknowledge,                                                              params< OriginatingEntity, ReceivingEntity, RequestIdentifier, AcknowledgeFlag, ResponseFlag > >,
       i_class< ActionRequest,                                                            params< OriginatingEntity, ReceivingEntity, RequestIdentifier, ActionRequestCode, FixedDatums, VariableDatumSet > >,
       i_class< ActionResponse,                                                           params< OriginatingEntity, ReceivingEntity, RequestIdentifier, RequestStatus, FixedDatums, VariableDatumSet > >,
       i_class< ActionRequestToObject,                                                    params< ObjectIdentifiers, ActionRequestCode > >,
       i_class< ActionResponseFromObject,                                                 params< ActionResult > >,
       i_class< AttributeChangeRequest,                                                   params< ObjectIdentifiers, AttributeValueSet > >,
       i_class< AttributeChangeResult,                                                    params< ObjectIdentifier, AttributeChangeResultParam, AttributeValueSet > >,
       i_class< Collision,                                                                params< CollidingObjectIdentifier, IssuingObjectMass, IssuingObjectVelocityVector, CollisionType, CollisionLocation, EventIdentifier, IssuingObjectIdentifier > >,
       i_class< Comment,                                                                  params< OriginatingEntity, ReceivingEntity, VariableDatumSet > >,
       i_class< CreateObjectRequest,                                                      params< ObjectClass, AttributeValueSet, RequestIdentifier > >,
       i_class< CreateObjectResult,                                                       params< CreateObjectResultParam, RequestIdentifier > >,
       i_class< CreateEntity,                                                             params< OriginatingEntity, ReceivingEntity, RequestIdentifier > >,
       i_class< Data                      >,
       i_class< DataQuery                 >,
       i_class< EventReport               >,
       i_class< MunitionDetonation        >,
       i_class< RadioSignal, none,
//   +------------------------------------+-------------------------------------------+
                                     child<  i_class< ApplicationSpecificRadioSignal >,
                                             i_class< DatabaseIndexRadioSignal       >,
                                             i_class< EncodedAudioRadioSignal        >,
                                             i_class< RawBinaryRadioSignal           > > >,
//   +------------------------------------+-------------------------------------------+
       i_class< RemoveObjectRequest       >,
       i_class< RemoveObjectResult        >,
       i_class< RemoveEntity              >,
       i_class< RepairComplete            >,
       i_class< RepairResponse            >,
       i_class< ResupplyCancel            >,
       i_class< ResupplyOffer             >,
       i_class< ResupplyReceived          >,
       i_class< ServiceRequest            >,
       i_class< SetData                   >,
       i_class< StartResume               >,
       i_class< StopFreeze                >,
       i_class< WeaponFire                >
//   +------------------------------------+-------------------------------------------+
> > {};

/**************************************************************************************************/

}}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
