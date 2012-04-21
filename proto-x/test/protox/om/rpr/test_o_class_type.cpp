/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#define BOOST_AUTO_TEST_MAIN

#include <boost/test/included/unit_test_framework.hpp>
#include <boost/test/auto_unit_test.hpp>

#include <boost/type_traits.hpp>

/**********************************************************************************************************************/

#include <protox/hla/som.hpp>
#include <protox/hla/o_class_type.hpp>

#include <protox/om/rpr/obj_class_table.hpp>

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_o_class_static_attributes) {
    using namespace protox::om::rpr;

    typedef protox::hla::som< obj_class_table > som;

    typedef o_class_type< som, q_name< BaseEntity > >::type base_entity_type;
    BOOST_CHECK(base_entity_type::get_name() == "HLAobjectRoot.BaseEntity");
    BOOST_CHECK(base_entity_type::get_num_attrs() == 9);

    typedef o_class_type< som, q_name< BaseEntity, EnvironmentalEntity > >::type environmental_entity_type;
    BOOST_CHECK(environmental_entity_type::get_name() == "HLAobjectRoot.BaseEntity.EnvironmentalEntity");
    BOOST_CHECK(environmental_entity_type::get_num_attrs() == 10);
    BOOST_CHECK((boost::is_base_of< base_entity_type, environmental_entity_type >::value) == true);

    typedef o_class_type< som, q_name< BaseEntity, PhysicalEntity > >::type physical_entity_type;
    BOOST_CHECK(physical_entity_type::get_name() == "HLAobjectRoot.BaseEntity.PhysicalEntity");
    BOOST_CHECK(physical_entity_type::get_num_attrs() == 28);
    BOOST_CHECK((boost::is_base_of< base_entity_type, physical_entity_type >::value) == true);

    typedef o_class_type< som, q_name< BaseEntity, PhysicalEntity, Platform > >::type platform_type;
    BOOST_CHECK(platform_type::get_name() == "HLAobjectRoot.BaseEntity.PhysicalEntity.Platform");
    BOOST_CHECK(platform_type::get_num_attrs() == 44);
    BOOST_CHECK((boost::is_base_of< physical_entity_type, platform_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< base_entity_type, platform_type >::value) == true);

    typedef o_class_type< som, q_name< BaseEntity, PhysicalEntity, Platform, Aircraft > >::type aircraft_type;
    BOOST_CHECK(aircraft_type::get_name() == "HLAobjectRoot.BaseEntity.PhysicalEntity.Platform.Aircraft");
    BOOST_CHECK(aircraft_type::get_num_attrs() == 44);
    BOOST_CHECK((boost::is_base_of< platform_type, aircraft_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< physical_entity_type, aircraft_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< base_entity_type, aircraft_type >::value) == true);

    typedef o_class_type< som, q_name< BaseEntity, PhysicalEntity, Platform, AmphibiousVehicle > >::type amphibious_vehicle_type;
    BOOST_CHECK(amphibious_vehicle_type::get_name() == "HLAobjectRoot.BaseEntity.PhysicalEntity.Platform.AmphibiousVehicle");
    BOOST_CHECK(amphibious_vehicle_type::get_num_attrs() == 44);
    BOOST_CHECK((boost::is_base_of< platform_type, amphibious_vehicle_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< physical_entity_type, amphibious_vehicle_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< base_entity_type, amphibious_vehicle_type >::value) == true);

    typedef o_class_type< som, q_name< BaseEntity, PhysicalEntity, Platform, GroundVehicle > >::type ground_vehicle_type;
    BOOST_CHECK(ground_vehicle_type::get_name() == "HLAobjectRoot.BaseEntity.PhysicalEntity.Platform.GroundVehicle");
    BOOST_CHECK(ground_vehicle_type::get_num_attrs() == 44);
    BOOST_CHECK((boost::is_base_of< platform_type, ground_vehicle_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< physical_entity_type, ground_vehicle_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< base_entity_type, ground_vehicle_type >::value) == true);

    typedef o_class_type< som, q_name< BaseEntity, PhysicalEntity, Platform, MultiDomainPlatform > >::type multi_domain_platform_type;
    BOOST_CHECK(multi_domain_platform_type::get_name() == "HLAobjectRoot.BaseEntity.PhysicalEntity.Platform.MultiDomainPlatform");
    BOOST_CHECK(multi_domain_platform_type::get_num_attrs() == 44);
    BOOST_CHECK((boost::is_base_of< platform_type, multi_domain_platform_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< physical_entity_type, multi_domain_platform_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< base_entity_type, multi_domain_platform_type >::value) == true);

    typedef o_class_type< som, q_name< BaseEntity, PhysicalEntity, Platform, Spacecraft > >::type spacecraft_type;
    BOOST_CHECK(spacecraft_type::get_name() == "HLAobjectRoot.BaseEntity.PhysicalEntity.Platform.Spacecraft");
    BOOST_CHECK(spacecraft_type::get_num_attrs() == 44);
    BOOST_CHECK((boost::is_base_of< platform_type, spacecraft_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< physical_entity_type, spacecraft_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< base_entity_type, spacecraft_type >::value) == true);

    typedef o_class_type< som, q_name< BaseEntity, PhysicalEntity, Platform, SubmersibleVessel > >::type submersible_vessel_type;
    BOOST_CHECK(submersible_vessel_type::get_name() == "HLAobjectRoot.BaseEntity.PhysicalEntity.Platform.SubmersibleVessel");
    BOOST_CHECK(submersible_vessel_type::get_num_attrs() == 44);
    BOOST_CHECK((boost::is_base_of< platform_type, submersible_vessel_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< physical_entity_type, submersible_vessel_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< base_entity_type, submersible_vessel_type >::value) == true);

    typedef o_class_type< som, q_name< BaseEntity, PhysicalEntity, Platform, SurfaceVessel > >::type surface_vessel_type;
    BOOST_CHECK(surface_vessel_type::get_name() == "HLAobjectRoot.BaseEntity.PhysicalEntity.Platform.SurfaceVessel");
    BOOST_CHECK(surface_vessel_type::get_num_attrs() == 44);
    BOOST_CHECK((boost::is_base_of< platform_type, surface_vessel_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< physical_entity_type, surface_vessel_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< base_entity_type, surface_vessel_type >::value) == true);

    typedef o_class_type< som, q_name< BaseEntity, PhysicalEntity, Lifeform > >::type lifeform_type;
    BOOST_CHECK(lifeform_type::get_name() == "HLAobjectRoot.BaseEntity.PhysicalEntity.Lifeform");
    BOOST_CHECK(lifeform_type::get_num_attrs() == 32);
    BOOST_CHECK((boost::is_base_of< physical_entity_type, lifeform_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< base_entity_type, lifeform_type >::value) == true);

    typedef o_class_type< som, q_name< BaseEntity, PhysicalEntity, Lifeform, Human > >::type human_type;
    BOOST_CHECK(human_type::get_name() == "HLAobjectRoot.BaseEntity.PhysicalEntity.Lifeform.Human");
    BOOST_CHECK(human_type::get_num_attrs() == 32);
    BOOST_CHECK((boost::is_base_of< lifeform_type, human_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< physical_entity_type, human_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< base_entity_type, human_type >::value) == true);

    typedef o_class_type< som, q_name< BaseEntity, PhysicalEntity, Lifeform, NonHuman > >::type nonhuman_type;
    BOOST_CHECK(nonhuman_type::get_name() == "HLAobjectRoot.BaseEntity.PhysicalEntity.Lifeform.NonHuman");
    BOOST_CHECK(nonhuman_type::get_num_attrs() == 32);
    BOOST_CHECK((boost::is_base_of< lifeform_type, nonhuman_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< physical_entity_type, nonhuman_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< base_entity_type, nonhuman_type >::value) == true);

    typedef o_class_type< som, q_name< BaseEntity, PhysicalEntity, CulturalFeature > >::type cultural_feature_type;
    BOOST_CHECK(cultural_feature_type::get_name() == "HLAobjectRoot.BaseEntity.PhysicalEntity.CulturalFeature");
    BOOST_CHECK(cultural_feature_type::get_num_attrs() == 31);
    BOOST_CHECK((boost::is_base_of< physical_entity_type, cultural_feature_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< base_entity_type, cultural_feature_type >::value) == true);

    typedef o_class_type< som, q_name< BaseEntity, PhysicalEntity, Expendables > >::type expendables_type;
    BOOST_CHECK(expendables_type::get_name() == "HLAobjectRoot.BaseEntity.PhysicalEntity.Expendables");
    BOOST_CHECK(expendables_type::get_num_attrs() == 28);
    BOOST_CHECK((boost::is_base_of< physical_entity_type, expendables_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< base_entity_type, expendables_type >::value) == true);

    typedef o_class_type< som, q_name< BaseEntity, PhysicalEntity, Munition > >::type munition_type;
    BOOST_CHECK(munition_type::get_name() == "HLAobjectRoot.BaseEntity.PhysicalEntity.Munition");
    BOOST_CHECK(munition_type::get_num_attrs() == 29);
    BOOST_CHECK((boost::is_base_of< physical_entity_type, munition_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< base_entity_type, munition_type >::value) == true);

    typedef o_class_type< som, q_name< BaseEntity, PhysicalEntity, Radio > >::type radio_type;
    BOOST_CHECK(radio_type::get_name() == "HLAobjectRoot.BaseEntity.PhysicalEntity.Radio");
    BOOST_CHECK(radio_type::get_num_attrs() == 28);
    BOOST_CHECK((boost::is_base_of< physical_entity_type, radio_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< base_entity_type, radio_type >::value) == true);

    typedef o_class_type< som, q_name< BaseEntity, PhysicalEntity, Sensor > >::type sensor_type;
    BOOST_CHECK(sensor_type::get_name() == "HLAobjectRoot.BaseEntity.PhysicalEntity.Sensor");
    BOOST_CHECK(sensor_type::get_num_attrs() == 33);
    BOOST_CHECK((boost::is_base_of< physical_entity_type, sensor_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< base_entity_type, sensor_type >::value) == true);

    typedef o_class_type< som, q_name< BaseEntity, PhysicalEntity, Supplies > >::type supplies_type;
    BOOST_CHECK(supplies_type::get_name() == "HLAobjectRoot.BaseEntity.PhysicalEntity.Supplies");
    BOOST_CHECK(supplies_type::get_num_attrs() == 28);
    BOOST_CHECK((boost::is_base_of< physical_entity_type, supplies_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< base_entity_type, supplies_type >::value) == true);

    typedef o_class_type< som, q_name< EmbeddedSystem > >::type embedded_system_type;
    BOOST_CHECK(embedded_system_type::get_name() == "HLAobjectRoot.EmbeddedSystem");
    BOOST_CHECK(embedded_system_type::get_num_attrs() == 3);

    typedef o_class_type< som, q_name< EmbeddedSystem, Designator > >::type designator_type;
    BOOST_CHECK(designator_type::get_name() == "HLAobjectRoot.EmbeddedSystem.Designator");
    BOOST_CHECK(designator_type::get_num_attrs() == 12);
    BOOST_CHECK((boost::is_base_of< embedded_system_type, designator_type >::value) == true);

    typedef o_class_type< som, q_name< EmbeddedSystem, EmitterSystem > >::type emitter_system_type;
    BOOST_CHECK(emitter_system_type::get_name() == "HLAobjectRoot.EmbeddedSystem.EmitterSystem");
    BOOST_CHECK(emitter_system_type::get_num_attrs() == 7);
    BOOST_CHECK((boost::is_base_of< embedded_system_type, emitter_system_type >::value) == true);

    typedef o_class_type< som, q_name< EmbeddedSystem, RadioReceiver > >::type radio_receiver_type;
    BOOST_CHECK(radio_receiver_type::get_name() == "HLAobjectRoot.EmbeddedSystem.RadioReceiver");
    BOOST_CHECK(radio_receiver_type::get_num_attrs() == 6);
    BOOST_CHECK((boost::is_base_of< embedded_system_type, radio_receiver_type >::value) == true);

    typedef o_class_type< som, q_name< EmbeddedSystem, RadioTransmitter > >::type radio_transmitter_type;
    BOOST_CHECK(radio_transmitter_type::get_name() == "HLAobjectRoot.EmbeddedSystem.RadioTransmitter");
    BOOST_CHECK(radio_transmitter_type::get_num_attrs() == 21);
    BOOST_CHECK((boost::is_base_of< embedded_system_type, radio_transmitter_type >::value) == true);

    typedef o_class_type< som, q_name< EmitterBeam > >::type emitter_beam_type;
    BOOST_CHECK(emitter_beam_type::get_name() == "HLAobjectRoot.EmitterBeam");
    BOOST_CHECK(emitter_beam_type::get_num_attrs() == 15);

    typedef o_class_type< som, q_name< EmitterBeam, RadarBeam > >::type radar_beam_type;
    BOOST_CHECK(radar_beam_type::get_name() == "HLAobjectRoot.EmitterBeam.RadarBeam");
    BOOST_CHECK(radar_beam_type::get_num_attrs() == 17);
    BOOST_CHECK((boost::is_base_of< emitter_beam_type, radar_beam_type >::value) == true);

    typedef o_class_type< som, q_name< EmitterBeam, JammerBeam > >::type jammer_beam_type;
    BOOST_CHECK(jammer_beam_type::get_name() == "HLAobjectRoot.EmitterBeam.JammerBeam");
    BOOST_CHECK(jammer_beam_type::get_num_attrs() == 18);
    BOOST_CHECK((boost::is_base_of< emitter_beam_type, jammer_beam_type >::value) == true);
}
