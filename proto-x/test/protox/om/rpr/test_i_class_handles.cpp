/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#define BOOST_AUTO_TEST_MAIN

/**********************************************************************************************************************/

#include <iostream>
#include <typeinfo>

/**********************************************************************************************************************/

#include <boost/test/included/unit_test_framework.hpp>
#include <boost/test/auto_unit_test.hpp>

/**********************************************************************************************************************/

#include <RTI.hh>

/**********************************************************************************************************************/

#include <protox/hla/som.hpp>
#include <protox/hla/i_class_type.hpp>
#include <protox/hla/o_class_type.hpp>

#include <protox/om/rpr/obj_class_table.hpp>
#include <protox/om/rpr/inter_class_table.hpp>

/**********************************************************************************************************************/

void init_class_to_handle_map(RTI::RTIambassador &rti_amb) {

    rti_amb.o_class_to_handle_map["HLAobjectRoot"] = 1;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity"] = 2;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.EnvironmentalEntity"] = 3;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity"] = 4;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Platform"] = 5;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Platform.Aircraft"] = 6;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Platform.AmphibiousVehicle"] = 7;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Platform.GroundVehicle"] = 8;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Platform.MultiDomainPlatform"] = 9;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Platform.Spacecraft"] = 10;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Platform.SubmersibleVessel"] = 11;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Platform.SurfaceVessel"] = 12;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Lifeform"] = 13;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Lifeform.Human"] = 14;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Lifeform.NonHuman"] = 15;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.CulturalFeature"] = 16;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Expendables"] = 17;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Munition"] = 18;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Radio"] = 19;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Sensor"] = 20;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Supplies"] = 21;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.EmbeddedSystem"] = 22;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.EmbeddedSystem.Designator"] = 23;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.EmbeddedSystem.EmitterSystem"] = 24;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.EmbeddedSystem.RadioReceiver"] = 25;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.EmbeddedSystem.RadioTransmitter"] = 26;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.EmitterBeam"] = 27;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.EmitterBeam.RadarBeam"] = 28;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.EmitterBeam.JammerBeam"] = 29;

    rti_amb.i_class_to_handle_map["HLAinteractionRoot" ] = 1;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.Acknowledge" ] = 2;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.ActionRequest" ] = 3;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.ActionResponse" ] = 4;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.ActionRequestToObject" ] = 5;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.ActionResponseFromObject" ] = 6;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.AttributeChangeRequest" ] = 7;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.AttributeChangeResult" ] = 8;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.Collision" ] = 9;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.Comment" ] = 10;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.CreateObjectRequest" ] = 11;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.CreateObjectResult" ] = 12;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.CreateEntity" ] = 13;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.Data" ] = 14;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.DataQuery" ] = 15;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.EventReport" ] = 16;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.MunitionDetonation" ] = 17;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.RadioSignal" ] = 18;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.RadioSignal.ApplicationSpecificRadioSignal" ] = 19;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.RadioSignal.DatabaseIndexRadioSignal" ] = 20;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.RadioSignal.EncodedAudioRadioSignal" ] = 21;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.RadioSignal.RawBinaryRadioSignal" ] = 22;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.RemoveObjectRequest" ] = 23;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.RemoveObjectResult" ] = 24;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.RemoveEntity" ] = 25;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.RepairComplete" ] = 26;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.RepairResponse" ] = 27;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.ResupplyCancel" ] = 28;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.ResupplyOffer" ] = 29;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.ResupplyReceived" ] = 30;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.ServiceRequest" ] = 31;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.SetData" ] = 32;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.StartResume" ] = 33;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.StopFreeze" ] = 34;
    rti_amb.i_class_to_handle_map["HLAinteractionRoot.WeaponFire" ] = 35;
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_om_rpr_i_class_handles) {

    using namespace protox::om::rpr;

    RTI::RTIambassador rti_amb;
    init_class_to_handle_map(rti_amb);

    typedef protox::hla::som< obj_class_table, inter_class_table > rpr_som;

    rpr_som::init_handles(rti_amb);

    rpr_som::print_param_handle_map();

    typedef i_class_type< rpr_som, q_name< Acknowledge > >::type acknowledge_type;
    BOOST_CHECK(acknowledge_type::get_handle() == 2);

    acknowledge_type acknowledge;
    BOOST_CHECK(acknowledge.get_param_handle< OriginatingEntity >() == 153);
    BOOST_CHECK(acknowledge.get_param_handle< ReceivingEntity   >() == 152);
    BOOST_CHECK(acknowledge.get_param_handle< RequestIdentifier >() == 151);
    BOOST_CHECK(acknowledge.get_param_handle< AcknowledgeFlag   >() == 150);
    BOOST_CHECK(acknowledge.get_param_handle< ResponseFlag      >() == 149);

    typedef i_class_type< rpr_som, q_name< RadioSignal, ApplicationSpecificRadioSignal > >::type application_specific_radio_signal_type;
    BOOST_CHECK(application_specific_radio_signal_type::get_handle() == 19);

    application_specific_radio_signal_type application_specific_radio_signal;
    BOOST_CHECK(application_specific_radio_signal.get_param_handle< HostRadioIndex >() == 80);
}

/**********************************************************************************************************************/
