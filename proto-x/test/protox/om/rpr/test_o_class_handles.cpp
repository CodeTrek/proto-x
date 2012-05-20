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
#include <protox/hla/o_class_type.hpp>

#include <protox/om/rpr/obj_class_table.hpp>

/**********************************************************************************************************************/

void init_o_class_to_handle_map(RTI::RTIambassador &rti_amb) {
    rti_amb.o_class_to_handle_map["HLAobjectRoot" ] = 1;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity" ] = 2;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.EnvironmentalEntity" ] = 3;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity" ] = 4;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Platform" ] = 5;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Platform.Aircraft" ] = 6;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Platform.AmphibiousVehicle" ] = 7;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Platform.GroundVehicle" ] = 8;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Platform.MultiDomainPlatform" ] = 9;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Platform.Spacecraft" ] = 10;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Platform.SubmersibleVessel" ] = 11;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Platform.SurfaceVessel" ] = 12;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Lifeform" ] = 13;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Lifeform.Human" ] = 14;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Lifeform.NonHuman" ] = 15;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.CulturalFeature" ] = 16;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Expendables" ] = 17;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Munition" ] = 18;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Radio" ] = 19;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Sensor" ] = 20;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.BaseEntity.PhysicalEntity.Supplies" ] = 21;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.EmbeddedSystem" ] = 22;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.EmbeddedSystem.Designator" ] = 23;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.EmbeddedSystem.EmitterSystem" ] = 24;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.EmbeddedSystem.RadioReceiver" ] = 25;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.EmbeddedSystem.RadioTransmitter" ] = 26;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.EmitterBeam" ] = 27;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.EmitterBeam.RadarBeam" ] = 28;
    rti_amb.o_class_to_handle_map["HLAobjectRoot.EmitterBeam.JammerBeam" ] = 29;
}

/**********************************************************************************************************************/


BOOST_AUTO_TEST_CASE(test_om_rpr_o_class_handles) {

    using namespace protox::om::rpr;

    RTI::RTIambassador rti_amb;
    init_o_class_to_handle_map(rti_amb);

    typedef protox::hla::som< obj_class_table > rpr_som;

    rpr_som::init_handles(rti_amb);

    //rpr_som::print_attr_handle_map();

    typedef o_class_type< rpr_som, q_name< BaseEntity > >::type base_entity_type;
    BOOST_CHECK(base_entity_type::get_handle() == 2);

    typedef o_class_type< rpr_som, q_name< BaseEntity, EnvironmentalEntity > >::type environmental_entity_type;
    BOOST_CHECK(environmental_entity_type::get_handle() == 3);

    typedef o_class_type< rpr_som, q_name< BaseEntity, PhysicalEntity > >::type physical_entity_type;
    BOOST_CHECK(physical_entity_type::get_handle() == 4);

    typedef o_class_type< rpr_som, q_name< BaseEntity, PhysicalEntity, Platform > >::type platform_type;
    BOOST_CHECK(platform_type::get_handle() == 5);

    typedef o_class_type< rpr_som, q_name< BaseEntity, PhysicalEntity, Platform, Aircraft > >::type aircraft_type;
    BOOST_CHECK(aircraft_type::get_handle() == 6);

    typedef o_class_type< rpr_som, q_name< BaseEntity, PhysicalEntity, Platform, AmphibiousVehicle > >::type amphibious_vehicle_type;
    BOOST_CHECK(amphibious_vehicle_type::get_handle() == 7);

    typedef o_class_type< rpr_som, q_name< BaseEntity, PhysicalEntity, Platform, GroundVehicle > >::type ground_vehicle_type;
    BOOST_CHECK(ground_vehicle_type::get_handle() == 8);

    typedef o_class_type< rpr_som, q_name< BaseEntity, PhysicalEntity, Platform, MultiDomainPlatform > >::type multi_domain_platform_type;
    BOOST_CHECK(multi_domain_platform_type::get_handle() == 9);

    typedef o_class_type< rpr_som, q_name< BaseEntity, PhysicalEntity, Platform, Spacecraft > >::type spacecraft_type;
    BOOST_CHECK(spacecraft_type::get_handle() == 10);

    typedef o_class_type< rpr_som, q_name< BaseEntity, PhysicalEntity, Platform, SubmersibleVessel > >::type submersible_vessel_type;
    BOOST_CHECK(submersible_vessel_type::get_handle() == 11);

    typedef o_class_type< rpr_som, q_name< BaseEntity, PhysicalEntity, Platform, SurfaceVessel > >::type surface_vessel_type;
    BOOST_CHECK(surface_vessel_type::get_handle() == 12);

    typedef o_class_type< rpr_som, q_name< BaseEntity, PhysicalEntity, Lifeform > >::type lifeform_type;
    BOOST_CHECK(lifeform_type::get_handle() == 13);

    typedef o_class_type< rpr_som, q_name< BaseEntity, PhysicalEntity, Lifeform, Human > >::type human_type;
    BOOST_CHECK(human_type::get_handle() == 14);

    typedef o_class_type< rpr_som, q_name< BaseEntity, PhysicalEntity, Lifeform, NonHuman > >::type nonhuman_type;
    BOOST_CHECK(nonhuman_type::get_handle() == 15);

    typedef o_class_type< rpr_som, q_name< BaseEntity, PhysicalEntity, CulturalFeature > >::type cultural_feature_type;
    BOOST_CHECK(cultural_feature_type::get_handle() == 16);

    typedef o_class_type< rpr_som, q_name< BaseEntity, PhysicalEntity, Expendables > >::type expendables_type;
    BOOST_CHECK(expendables_type::get_handle() == 17);

    typedef o_class_type< rpr_som, q_name< BaseEntity, PhysicalEntity, Munition > >::type munition_type;
    BOOST_CHECK(munition_type::get_handle() == 18);

    typedef o_class_type< rpr_som, q_name< BaseEntity, PhysicalEntity, Radio > >::type radio_type;
    BOOST_CHECK(radio_type::get_handle() == 19);

    typedef o_class_type< rpr_som, q_name< BaseEntity, PhysicalEntity, Sensor > >::type sensor_type;
    BOOST_CHECK(sensor_type::get_handle() == 20);

    typedef o_class_type< rpr_som, q_name< BaseEntity, PhysicalEntity, Supplies > >::type supplies_type;
    BOOST_CHECK(supplies_type::get_handle() == 21);

    typedef o_class_type< rpr_som, q_name< EmbeddedSystem > >::type embedded_system_type;
    BOOST_CHECK(embedded_system_type::get_handle() == 22);

    typedef o_class_type< rpr_som, q_name< EmbeddedSystem, Designator > >::type designator_type;
    BOOST_CHECK(designator_type::get_handle() == 23);

    typedef o_class_type< rpr_som, q_name< EmbeddedSystem, EmitterSystem > >::type emitter_system_type;
    BOOST_CHECK(emitter_system_type::get_handle() == 24);

    typedef o_class_type< rpr_som, q_name< EmbeddedSystem, RadioReceiver > >::type radio_receiver_type;
    BOOST_CHECK(radio_receiver_type::get_handle() == 25);

    typedef o_class_type< rpr_som, q_name< EmbeddedSystem, RadioTransmitter > >::type radio_transmitter_type;
    BOOST_CHECK(radio_transmitter_type::get_handle() == 26);

    typedef o_class_type< rpr_som, q_name< EmitterBeam > >::type emitter_beam_type;
    BOOST_CHECK(emitter_beam_type::get_handle() == 27);

    typedef o_class_type< rpr_som, q_name< EmitterBeam, RadarBeam > >::type radar_beam_type;
    BOOST_CHECK(radar_beam_type::get_handle() == 28);

    typedef o_class_type< rpr_som, q_name< EmitterBeam, JammerBeam > >::type jammer_beam_type;
    BOOST_CHECK(jammer_beam_type::get_handle() == 29);
}

/**********************************************************************************************************************/
