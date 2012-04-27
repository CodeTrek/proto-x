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

BOOST_AUTO_TEST_CASE(test_om_rpr_base_entity_attr_access) {

    using namespace protox::om::rpr;

    RTI::RTIambassador rti_amb;
    init_o_class_to_handle_map(rti_amb);

    typedef protox::hla::som< obj_class_table > rpr_som;

    rpr_som::init_handles(rti_amb);

    typedef o_class_type< rpr_som, q_name< BaseEntity > >::type base_entity_type;

    base_entity_type base_entity;

    using namespace protox::om::rpr::AccelerationVectorStruct;

    base_entity.a_< AccelerationVector >().f_< XAcceleration >() =  5;
    base_entity.a_< AccelerationVector >().f_< YAcceleration >() = 10;
    base_entity.a_< AccelerationVector >().f_< ZAcceleration >() = 15;

    BOOST_CHECK(base_entity.a_< AccelerationVector >().f_< XAcceleration >() ==  5);
    BOOST_CHECK(base_entity.a_< AccelerationVector >().f_< YAcceleration >() == 10);
    BOOST_CHECK(base_entity.a_< AccelerationVector >().f_< ZAcceleration >() == 15);

    using namespace protox::om::rpr::AngularVelocityVectorStruct;

    base_entity.a_< AngularVelocityVector >().f_< XAngularVelocity >() =  5;
    base_entity.a_< AngularVelocityVector >().f_< YAngularVelocity >() =  10;
    base_entity.a_< AngularVelocityVector >().f_< ZAngularVelocity >() =  15;

    BOOST_CHECK(base_entity.a_< AngularVelocityVector >().f_< XAngularVelocity >() ==   5);
    BOOST_CHECK(base_entity.a_< AngularVelocityVector >().f_< YAngularVelocity >() ==  10);
    BOOST_CHECK(base_entity.a_< AngularVelocityVector >().f_< ZAngularVelocity >() ==  15);

    using namespace protox::om::rpr::DeadReckoningAlgorithmEnum8;

    base_entity.a_< DeadReckoningAlgorithm >() = DRM_FVW::value();

    BOOST_CHECK(base_entity.a_< DeadReckoningAlgorithm >() ==  DRM_FVW::value());

    using namespace protox::om::rpr::EntityTypeStruct;

    base_entity.a_< EntityType >().f_< EntityKind >()  = 1;
    base_entity.a_< EntityType >().f_< Domain >()      = 2;
    base_entity.a_< EntityType >().f_< CountryCode >() = 3;
    base_entity.a_< EntityType >().f_< Category >()    = 4;
    base_entity.a_< EntityType >().f_< Subcategory >() = 5;
    base_entity.a_< EntityType >().f_< Specific >()    = 6;
    base_entity.a_< EntityType >().f_< Extra >()       = 7;

    BOOST_CHECK(base_entity.a_< EntityType >().f_< EntityKind >()  == 1);
    BOOST_CHECK(base_entity.a_< EntityType >().f_< Domain >()      == 2);
    BOOST_CHECK(base_entity.a_< EntityType >().f_< CountryCode >() == 3);
    BOOST_CHECK(base_entity.a_< EntityType >().f_< Category >()    == 4);
    BOOST_CHECK(base_entity.a_< EntityType >().f_< Subcategory >() == 5);
    BOOST_CHECK(base_entity.a_< EntityType >().f_< Specific >()    == 6);
    BOOST_CHECK(base_entity.a_< EntityType >().f_< Extra >()       == 7);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_om_rpr_environmental_entity_attr_access) {

    using namespace protox::om::rpr;

    RTI::RTIambassador rti_amb;
    init_o_class_to_handle_map(rti_amb);

    typedef protox::hla::som< obj_class_table > rpr_som;

    rpr_som::init_handles(rti_amb);

    typedef o_class_type< rpr_som, q_name< BaseEntity, EnvironmentalEntity > >::type environmental_entity_type;
    environmental_entity_type environmental_entity;

    using namespace protox::om::rpr::AngularVelocityVectorStruct;

    environmental_entity.a_< AngularVelocityVector >().f_< XAngularVelocity >() =  5;
    environmental_entity.a_< AngularVelocityVector >().f_< YAngularVelocity >() =  10;
    environmental_entity.a_< AngularVelocityVector >().f_< ZAngularVelocity >() =  15;

    BOOST_CHECK(environmental_entity.a_< AngularVelocityVector >().f_< XAngularVelocity >() ==   5);
    BOOST_CHECK(environmental_entity.a_< AngularVelocityVector >().f_< YAngularVelocity >() ==  10);
    BOOST_CHECK(environmental_entity.a_< AngularVelocityVector >().f_< ZAngularVelocity >() ==  15);

    using namespace protox::om::rpr::OpacityCodeEnum32;

    environmental_entity.a_< OpacityCode >() =  VeryDense::value();
    BOOST_CHECK(environmental_entity.a_< OpacityCode >() ==  VeryDense::value());
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_om_rpr_physical_entity_attr_access) {

    using namespace protox::om::rpr;

    RTI::RTIambassador rti_amb;
    init_o_class_to_handle_map(rti_amb);

    typedef protox::hla::som< obj_class_table > rpr_som;

    rpr_som::init_handles(rti_amb);

    typedef o_class_type< rpr_som, q_name< BaseEntity, PhysicalEntity > >::type physical_entity_type;
    physical_entity_type physical_entity;

    using namespace protox::om::rpr::AccelerationVectorStruct;

    physical_entity.a_< AccelerationVector >().f_< XAcceleration >() =  5;
    physical_entity.a_< AccelerationVector >().f_< YAcceleration >() = 10;
    physical_entity.a_< AccelerationVector >().f_< ZAcceleration >() = 15;

    BOOST_CHECK(physical_entity.a_< AccelerationVector >().f_< XAcceleration >() ==  5);
    BOOST_CHECK(physical_entity.a_< AccelerationVector >().f_< YAcceleration >() == 10);
    BOOST_CHECK(physical_entity.a_< AccelerationVector >().f_< ZAcceleration >() == 15);

    using namespace protox::om::rpr::DamageStatusEnum32;

    physical_entity.a_< DamageState >() =  ModerateDamage::value();
    BOOST_CHECK(physical_entity.a_< DamageState >() ==  ModerateDamage::value());
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_om_rpr_platform_attr_access) {

    using namespace protox::om::rpr;

    RTI::RTIambassador rti_amb;
    init_o_class_to_handle_map(rti_amb);

    typedef protox::hla::som< obj_class_table > rpr_som;

    rpr_som::init_handles(rti_amb);

    typedef o_class_type< rpr_som, q_name< BaseEntity, PhysicalEntity, Platform > >::type platform_type;
    platform_type platform;

    using namespace protox::om::rpr::AccelerationVectorStruct;

    platform.a_< AccelerationVector >().f_< XAcceleration >() =  5;
    platform.a_< AccelerationVector >().f_< YAcceleration >() = 10;
    platform.a_< AccelerationVector >().f_< ZAcceleration >() = 15;

    BOOST_CHECK(platform.a_< AccelerationVector >().f_< XAcceleration >() ==  5);
    BOOST_CHECK(platform.a_< AccelerationVector >().f_< YAcceleration >() == 10);
    BOOST_CHECK(platform.a_< AccelerationVector >().f_< ZAcceleration >() == 15);

    using namespace protox::om::rpr::DamageStatusEnum32;

    platform.a_< DamageState >() =  ModerateDamage::value();
    BOOST_CHECK(platform.a_< DamageState >() ==  ModerateDamage::value());

    using namespace protox::om::rpr::HatchStateEnum32;

    platform.a_< HatchState >() =  PrimaryHatchIsPoppedAndPersonIsVisibleUnderHatch::value();
    BOOST_CHECK(platform.a_< HatchState >() ==  PrimaryHatchIsPoppedAndPersonIsVisibleUnderHatch::value());
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_om_rpr_platform_types_attr_access) {

    using namespace protox::om::rpr;

    RTI::RTIambassador rti_amb;
    init_o_class_to_handle_map(rti_amb);

    typedef protox::hla::som< obj_class_table > rpr_som;

    rpr_som::init_handles(rti_amb);

    typedef o_class_type< rpr_som, q_name< BaseEntity, PhysicalEntity, Platform, Aircraft > >::type aircraft_type;

    aircraft_type aircraft;

    using namespace protox::om::rpr::AccelerationVectorStruct;

    // aircraft
    aircraft.a_< AccelerationVector >().f_< XAcceleration >() =  5;
    aircraft.a_< AccelerationVector >().f_< YAcceleration >() = 10;
    aircraft.a_< AccelerationVector >().f_< ZAcceleration >() = 15;

    BOOST_CHECK(aircraft.a_< AccelerationVector >().f_< XAcceleration >() ==  5);
    BOOST_CHECK(aircraft.a_< AccelerationVector >().f_< YAcceleration >() == 10);
    BOOST_CHECK(aircraft.a_< AccelerationVector >().f_< ZAcceleration >() == 15);

    using namespace protox::om::rpr::DamageStatusEnum32;

    aircraft.a_< DamageState >() =  ModerateDamage::value();
    BOOST_CHECK(aircraft.a_< DamageState >() ==  ModerateDamage::value());

    using namespace protox::om::rpr::HatchStateEnum32;

    aircraft.a_< HatchState >() =  PrimaryHatchIsPoppedAndPersonIsVisibleUnderHatch::value();
    BOOST_CHECK(aircraft.a_< HatchState >() ==  PrimaryHatchIsPoppedAndPersonIsVisibleUnderHatch::value());

    // multi_domain_platform
    typedef o_class_type< rpr_som, q_name< BaseEntity, PhysicalEntity, Platform, MultiDomainPlatform > >::type multi_domain_platform_type;
    multi_domain_platform_type multi_domain_platform;

    multi_domain_platform.a_< AccelerationVector >().f_< XAcceleration >() =  5;
    multi_domain_platform.a_< AccelerationVector >().f_< YAcceleration >() = 10;
    multi_domain_platform.a_< AccelerationVector >().f_< ZAcceleration >() = 15;

    BOOST_CHECK(multi_domain_platform.a_< AccelerationVector >().f_< XAcceleration >() ==  5);
    BOOST_CHECK(multi_domain_platform.a_< AccelerationVector >().f_< YAcceleration >() == 10);
    BOOST_CHECK(multi_domain_platform.a_< AccelerationVector >().f_< ZAcceleration >() == 15);

    using namespace protox::om::rpr::DamageStatusEnum32;

    multi_domain_platform.a_< DamageState >() =  ModerateDamage::value();
    BOOST_CHECK(multi_domain_platform.a_< DamageState >() ==  ModerateDamage::value());

    using namespace protox::om::rpr::HatchStateEnum32;

    multi_domain_platform.a_< HatchState >() =  PrimaryHatchIsPoppedAndPersonIsVisibleUnderHatch::value();
    BOOST_CHECK(multi_domain_platform.a_< HatchState >() ==  PrimaryHatchIsPoppedAndPersonIsVisibleUnderHatch::value());

    // Spacecraft
    typedef o_class_type< rpr_som, q_name< BaseEntity, PhysicalEntity, Platform, Spacecraft > >::type spacecraft_type;
    spacecraft_type spacecraft;

    spacecraft.a_< AccelerationVector >().f_< XAcceleration >() =  5;
    spacecraft.a_< AccelerationVector >().f_< YAcceleration >() = 10;
    spacecraft.a_< AccelerationVector >().f_< ZAcceleration >() = 15;

    BOOST_CHECK(spacecraft.a_< AccelerationVector >().f_< XAcceleration >() ==  5);
    BOOST_CHECK(spacecraft.a_< AccelerationVector >().f_< YAcceleration >() == 10);
    BOOST_CHECK(spacecraft.a_< AccelerationVector >().f_< ZAcceleration >() == 15);

    using namespace protox::om::rpr::DamageStatusEnum32;

    spacecraft.a_< DamageState >() =  ModerateDamage::value();
    BOOST_CHECK(spacecraft.a_< DamageState >() ==  ModerateDamage::value());

    using namespace protox::om::rpr::HatchStateEnum32;

    spacecraft.a_< HatchState >() =  PrimaryHatchIsPoppedAndPersonIsVisibleUnderHatch::value();
    BOOST_CHECK(spacecraft.a_< HatchState >() ==  PrimaryHatchIsPoppedAndPersonIsVisibleUnderHatch::value());

    using namespace protox::om::rpr::ArticulatedParameterStruct;

    spacecraft.a_< ArticulatedParametersArray >().push_back(ArticulatedParameterStruct::type());
    spacecraft.a_< ArticulatedParametersArray >().push_back(ArticulatedParameterStruct::type());
    spacecraft.a_< ArticulatedParametersArray >().push_back(ArticulatedParameterStruct::type());

    using namespace protox::om::rpr::ParameterValueStruct;
    using namespace protox::om::rpr::ArticulatedPartsStruct;
    using namespace protox::om::rpr::ParameterTypeEnum32;
    using namespace protox::om::rpr::ArticulatedPartsTypeEnum32;
    using namespace protox::om::rpr::ArticulatedTypeMetricEnum32;
    using namespace protox::om::rpr::ArticulatedParameterStruct;
    using namespace protox::om::rpr::AttachedPartsStruct;
    using namespace protox::om::rpr::EntityTypeStruct;

    spacecraft.a_< ArticulatedParametersArray >()[0].f_< ArticulatedParameterChange >() =  5;
    spacecraft.a_< ArticulatedParametersArray >()[0].f_< PartAttachedTo >() =  10;

    spacecraft.a_< ArticulatedParametersArray >()[0].f_< ParameterValue >().discriminant = ArticulatedPart::value();
    spacecraft.a_< ArticulatedParametersArray >()[0].f_< ParameterValue >().alt_< ArticulatedParts >(ArticulatedPartsStruct::type());

    (*spacecraft.a_< ArticulatedParametersArray >()[0].f_< ParameterValue >().alt_< ArticulatedParts >()).f_< Class >() = SpeedBrake::value();
    (*spacecraft.a_< ArticulatedParametersArray >()[0].f_< ParameterValue >().alt_< ArticulatedParts >()).f_< TypeMetric >() = X::value();
    (*spacecraft.a_< ArticulatedParametersArray >()[0].f_< ParameterValue >().alt_< ArticulatedParts >()).f_< Value      >() = 15;

    BOOST_CHECK((*spacecraft.a_< ArticulatedParametersArray >()[0].f_< ParameterValue >().alt_< ArticulatedParts >()).f_< Class >() == SpeedBrake::value());
    BOOST_CHECK((*spacecraft.a_< ArticulatedParametersArray >()[0].f_< ParameterValue >().alt_< ArticulatedParts >()).f_< TypeMetric >() == X::value());
    BOOST_CHECK((*spacecraft.a_< ArticulatedParametersArray >()[0].f_< ParameterValue >().alt_< ArticulatedParts >()).f_< Value >() == 15);
}

/**********************************************************************************************************************/
