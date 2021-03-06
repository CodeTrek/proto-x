/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#define BOOST_AUTO_TEST_MAIN

#include <boost/test/included/unit_test_framework.hpp>
#include <boost/test/auto_unit_test.hpp>

/**********************************************************************************************************************/

#include <protox/io/char_data_sink.hpp>

#include <protox/om/rpr/acceleration_vector_struct.hpp>
#include <protox/om/rpr/angular_velocity_vector_struct.hpp>
#include <protox/om/rpr/orientation_struct.hpp>
#include <protox/om/rpr/beam_antenna_struct.hpp>
#include <protox/om/rpr/spherical_harmonic_antenna_struct.hpp>
#include <protox/om/rpr/antenna_pattern_struct.hpp>
#include <protox/om/rpr/articulated_parts_struct.hpp>
#include <protox/om/rpr/entity_type_struct.hpp>
#include <protox/om/rpr/attached_parts_struct.hpp>
#include <protox/om/rpr/parameter_value_struct.hpp>
#include <protox/om/rpr/articulated_parameter_struct.hpp>
#include <protox/om/rpr/attribute_pair_struct.hpp>
#include <protox/om/rpr/attribute_value_set_struct.hpp>
#include <protox/om/rpr/clock_time_struct.hpp>
#include <protox/om/rpr/federate_identifier_struct.hpp>
#include <protox/om/rpr/entity_identifier_struct.hpp>
#include <protox/om/rpr/rti_object_id_struct.hpp>
#include <protox/om/rpr/event_identifier_struct.hpp>
#include <protox/om/rpr/fixed_datum_struct.hpp>
#include <protox/om/rpr/marking_struct.hpp>
#include <protox/om/rpr/sincgars_modulation_struct.hpp>
#include <protox/om/rpr/modulation_struct.hpp>
#include <protox/om/rpr/radio_type_struct.hpp>
#include <protox/om/rpr/relative_position_struct.hpp>
#include <protox/om/rpr/rf_modulation_type_struct.hpp>
#include <protox/om/rpr/rti_object_id_array_struct.hpp>
#include <protox/om/rpr/supply_struct.hpp>
#include <protox/om/rpr/variable_datum_struct.hpp>
#include <protox/om/rpr/variable_datum_set_struct.hpp>
#include <protox/om/rpr/velocity_vector_struct.hpp>
#include <protox/om/rpr/world_location_struct.hpp>

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_acceleration_vector_struct_access) {

    using namespace protox::om::rpr;
    using namespace protox::om::rpr::AccelerationVectorStruct;

    AccelerationVectorStruct::type s;

    s.f_< XAcceleration >() =  5;
    s.f_< YAcceleration >() = 10;
    s.f_< ZAcceleration >() = 15;

    BOOST_CHECK(s.f_< XAcceleration >() ==  5);
    BOOST_CHECK(s.f_< YAcceleration >() == 10);
    BOOST_CHECK(s.f_< ZAcceleration >() == 15);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_angular_velocity_vector_struct_access) {

    using namespace protox::om::rpr;
    using namespace protox::om::rpr::AngularVelocityVectorStruct;

    AngularVelocityVectorStruct::type s;

    s.f_< XAngularVelocity >() =  5;
    s.f_< YAngularVelocity >() = 10;
    s.f_< ZAngularVelocity >() = 15;

    BOOST_CHECK(s.f_< XAngularVelocity >() ==  5);
    BOOST_CHECK(s.f_< YAngularVelocity >() == 10);
    BOOST_CHECK(s.f_< ZAngularVelocity >() == 15);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_orientation_struct_access) {

    using namespace protox::om::rpr;
    using namespace protox::om::rpr::OrientationStruct;

    OrientationStruct::type s;

    s.f_< Psi   >() =  5;
    s.f_< Theta >() = 10;
    s.f_< Phi   >() = 15;

    BOOST_CHECK(s.f_< Psi   >() ==  5);
    BOOST_CHECK(s.f_< Theta >() == 10);
    BOOST_CHECK(s.f_< Phi   >() == 15);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_beam_antenna_struct_access) {

    using namespace protox::om::rpr;
    using namespace protox::om::rpr::BeamAntennaStruct;
    using namespace protox::om::rpr::OrientationStruct;
    using namespace protox::om::rpr::ReferenceSystemEnum8;

    BeamAntennaStruct::type s;

    s.f_< BeamOrientation        >().f_< Psi   >() =  5;
    s.f_< BeamOrientation        >().f_< Theta >() = 10;
    s.f_< BeamOrientation        >().f_< Phi   >() = 15;
    s.f_< BeamAzimuthBeamwidth   >()               = 20;
    s.f_< BeamElevationBeamwidth >()               = 25;
    s.f_< ReferenceSystem        >()               = EntityCoordinates::value();
    s.f_< Ez                     >()               = 30;
    s.f_< Ex                     >()               = 35;
    s.f_< BeamPhaseAngle         >()               = 40;

    BOOST_CHECK(s.f_< BeamOrientation        >().f_< Psi   >() ==  5);
    BOOST_CHECK(s.f_< BeamOrientation        >().f_< Theta >() == 10);
    BOOST_CHECK(s.f_< BeamOrientation        >().f_< Phi   >() == 15);
    BOOST_CHECK(s.f_< BeamAzimuthBeamwidth   >()               == 20);
    BOOST_CHECK(s.f_< BeamElevationBeamwidth >()               == 25);
    BOOST_CHECK(s.f_< ReferenceSystem        >()               == EntityCoordinates::value());
    BOOST_CHECK(s.f_< Ez                     >()               == 30);
    BOOST_CHECK(s.f_< Ex                     >()               == 35);
    BOOST_CHECK(s.f_< BeamPhaseAngle         >()               == 40);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_sperical_harmonic_antenna_access) {

    using namespace protox::om::rpr;
    using namespace protox::om::rpr::SphericalHarmonicAntennaStruct;
    using namespace protox::om::rpr::ReferenceSystemEnum8;

    SphericalHarmonicAntennaStruct::type s;

    s.f_< Order           >() = '5';
    s.f_< Coefficients    >().push_back(10);
    s.f_< Coefficients    >().push_back(15);
    s.f_< Coefficients    >().push_back(20);
    s.f_< Coefficients    >().push_back(30);
    s.f_< ReferenceSystem >() = WorldCoordinates::value();

    BOOST_CHECK(s.f_< Order           >()    == '5');
    BOOST_CHECK(s.f_< Coefficients    >()[0] == 10);
    BOOST_CHECK(s.f_< Coefficients    >()[1] == 15);
    BOOST_CHECK(s.f_< Coefficients    >()[2] == 20);
    BOOST_CHECK(s.f_< Coefficients    >()[3] == 30);
    BOOST_CHECK(s.f_< ReferenceSystem >()    == WorldCoordinates::value());
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_antenna_pattern_struct_access) {
    using namespace protox::om::rpr;
    using namespace protox::om::rpr::ReferenceSystemEnum8;
    using namespace protox::om::rpr::AntennaPatternTypeEnum32;
    using namespace protox::om::rpr::AntennaPatternStruct;
    using namespace protox::om::rpr::BeamAntennaStruct;
    using namespace protox::om::rpr::SphericalHarmonicAntennaStruct;
    using namespace protox::om::rpr::OrientationStruct;

    AntennaPatternStruct::type s;

    s.discriminant = Beam::value();
    s.alt_< BeamAntenna >(BeamAntennaStruct::type());

    (*s.alt_< BeamAntenna >()).f_< BeamOrientation                    >().f_< Psi   >() =  5;
    (*s.alt_< BeamAntenna >()).f_< BeamOrientation                    >().f_< Theta >() = 10;
    (*s.alt_< BeamAntenna >()).f_< BeamOrientation                    >().f_< Phi   >() = 15;
    (*s.alt_< BeamAntenna >()).f_< BeamAzimuthBeamwidth               >()               = 20;
    (*s.alt_< BeamAntenna >()).f_< BeamElevationBeamwidth             >()               = 25;
    (*s.alt_< BeamAntenna >()).f_< BeamAntennaStruct::ReferenceSystem >()               = EntityCoordinates::value();
    (*s.alt_< BeamAntenna >()).f_< Ez                                 >()               = 30;
    (*s.alt_< BeamAntenna >()).f_< Ex                                 >()               = 35;
    (*s.alt_< BeamAntenna >()).f_< BeamPhaseAngle                     >()               = 40;

    BOOST_CHECK((*s.alt_< BeamAntenna >()).f_< BeamOrientation                    >().f_< Psi   >() ==  5);
    BOOST_CHECK((*s.alt_< BeamAntenna >()).f_< BeamOrientation                    >().f_< Theta >() == 10);
    BOOST_CHECK((*s.alt_< BeamAntenna >()).f_< BeamOrientation                    >().f_< Phi   >() == 15);
    BOOST_CHECK((*s.alt_< BeamAntenna >()).f_< BeamAzimuthBeamwidth               >()               == 20);
    BOOST_CHECK((*s.alt_< BeamAntenna >()).f_< BeamElevationBeamwidth             >()               == 25);
    BOOST_CHECK((*s.alt_< BeamAntenna >()).f_< BeamAntennaStruct::ReferenceSystem >()               == EntityCoordinates::value());
    BOOST_CHECK((*s.alt_< BeamAntenna >()).f_< Ez                                 >()               == 30);
    BOOST_CHECK((*s.alt_< BeamAntenna >()).f_< Ex                                 >()               == 35);
    BOOST_CHECK((*s.alt_< BeamAntenna >()).f_< BeamPhaseAngle                     >()               == 40);

    protox::io::char_data_sink sink;
    sink.encode(s);
    sink.eol();

    s.discriminant = SphericalHarmonic::value();
    s.alt_< SphericalHarmonicAntenna >(SphericalHarmonicAntennaStruct::type());

    (*s.alt_< SphericalHarmonicAntenna >()).f_< Order                                           >() = 'Z';
    (*s.alt_< SphericalHarmonicAntenna >()).f_< Coefficients                                    >().push_back( 5);
    (*s.alt_< SphericalHarmonicAntenna >()).f_< Coefficients                                    >().push_back(10);
    (*s.alt_< SphericalHarmonicAntenna >()).f_< Coefficients                                    >().push_back(15);
    (*s.alt_< SphericalHarmonicAntenna >()).f_< SphericalHarmonicAntennaStruct::ReferenceSystem >() = WorldCoordinates::value();

    BOOST_CHECK((*s.alt_< SphericalHarmonicAntenna >()).f_< Order                                           >()    == 'Z');
    BOOST_CHECK((*s.alt_< SphericalHarmonicAntenna >()).f_< Coefficients                                    >()[0] ==  5);
    BOOST_CHECK((*s.alt_< SphericalHarmonicAntenna >()).f_< Coefficients                                    >()[1] == 10);
    BOOST_CHECK((*s.alt_< SphericalHarmonicAntenna >()).f_< Coefficients                                    >()[2] == 15);
    BOOST_CHECK((*s.alt_< SphericalHarmonicAntenna >()).f_< SphericalHarmonicAntennaStruct::ReferenceSystem >()    == WorldCoordinates::value());

    sink.clear();
    sink.encode(s);
    sink.eol();

    sink.clear();
    s.discriminant = OmniDirectional::value();
    sink.encode(s);
    sink.eol();
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_articulated_parts_struct_access) {

    using namespace protox::om::rpr;
    using namespace protox::om::rpr::ArticulatedPartsStruct;
    using namespace protox::om::rpr::ArticulatedPartsTypeEnum32;
    using namespace protox::om::rpr::ArticulatedTypeMetricEnum32;

    ArticulatedPartsStruct::type s;

    s.f_< Class      >() = SpeedBrake::value();
    s.f_< TypeMetric >() = X::value();
    s.f_< Value      >() = 15;

    BOOST_CHECK(s.f_< Class      >() == SpeedBrake::value());
    BOOST_CHECK(s.f_< TypeMetric >() == X::value());
    BOOST_CHECK(s.f_< Value      >() == 15);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_entity_type_struct_access) {

    using namespace protox::om::rpr;
    using namespace protox::om::rpr::EntityTypeStruct;

    EntityTypeStruct::type s;

    s.f_< EntityKind  >() =  5;
    s.f_< Domain      >() = 10;
    s.f_< CountryCode >() = 15;
    s.f_< Category    >() = 20;
    s.f_< Subcategory >() = 25;
    s.f_< Specific    >() = 30;
    s.f_< Extra       >() = 35;

    BOOST_CHECK(s.f_< EntityKind  >() ==  5);
    BOOST_CHECK(s.f_< Domain      >() == 10);
    BOOST_CHECK(s.f_< CountryCode >() == 15);
    BOOST_CHECK(s.f_< Category    >() == 20);
    BOOST_CHECK(s.f_< Subcategory >() == 25);
    BOOST_CHECK(s.f_< Specific    >() == 30);
    BOOST_CHECK(s.f_< Extra       >() == 35);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_attached_parts_struct_access) {

    using namespace protox::om::rpr;
    using namespace protox::om::rpr::AttachedPartsStruct;
    using namespace protox::om::rpr::EntityTypeStruct;

    AttachedPartsStruct::type s;

    s.f_< Station   >()                     = StationEnum32::M249_SAW::value();
    s.f_< StoreType >().f_< EntityKind  >() =  5;
    s.f_< StoreType >().f_< Domain      >() = 10;
    s.f_< StoreType >().f_< CountryCode >() = 15;
    s.f_< StoreType >().f_< Category    >() = 20;
    s.f_< StoreType >().f_< Subcategory >() = 25;
    s.f_< StoreType >().f_< Specific    >() = 30;
    s.f_< StoreType >().f_< Extra       >() = 35;

    BOOST_CHECK(s.f_< Station   >()                     == StationEnum32::M249_SAW::value());
    BOOST_CHECK(s.f_< StoreType >().f_< EntityKind  >() ==  5);
    BOOST_CHECK(s.f_< StoreType >().f_< Domain      >() == 10);
    BOOST_CHECK(s.f_< StoreType >().f_< CountryCode >() == 15);
    BOOST_CHECK(s.f_< StoreType >().f_< Category    >() == 20);
    BOOST_CHECK(s.f_< StoreType >().f_< Subcategory >() == 25);
    BOOST_CHECK(s.f_< StoreType >().f_< Specific    >() == 30);
    BOOST_CHECK(s.f_< StoreType >().f_< Extra       >() == 35);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_parameter_value_struct_access) {
    using namespace protox::om::rpr;
    using namespace protox::om::rpr::ParameterTypeEnum32;
    using namespace protox::om::rpr::ArticulatedPartsTypeEnum32;
    using namespace protox::om::rpr::ArticulatedTypeMetricEnum32;
    using namespace protox::om::rpr::ParameterValueStruct;
    using namespace protox::om::rpr::ArticulatedPartsStruct;
    using namespace protox::om::rpr::AttachedPartsStruct;
    using namespace protox::om::rpr::EntityTypeStruct;

    ParameterValueStruct::type s;

    s.discriminant = ArticulatedPart::value();
    s.alt_< ArticulatedParts >(ArticulatedPartsStruct::type());

    (*s.alt_< ArticulatedParts >()).f_< Class      >() = SpeedBrake::value();
    (*s.alt_< ArticulatedParts >()).f_< TypeMetric >() = X::value();
    (*s.alt_< ArticulatedParts >()).f_< Value      >() = 15;

    BOOST_CHECK((*s.alt_< ArticulatedParts >()).f_< Class      >() == SpeedBrake::value());
    BOOST_CHECK((*s.alt_< ArticulatedParts >()).f_< TypeMetric >() == X::value());
    BOOST_CHECK((*s.alt_< ArticulatedParts >()).f_< Value      >() == 15);

    s.discriminant = AttachedPart::value();
    s.alt_< AttachedParts >(AttachedPartsStruct::type());

    (*s.alt_< AttachedParts >()).f_< Station   >()                     = StationEnum32::M249_SAW::value();
    (*s.alt_< AttachedParts >()).f_< StoreType >().f_< EntityKind  >() =  5;
    (*s.alt_< AttachedParts >()).f_< StoreType >().f_< Domain      >() = 10;
    (*s.alt_< AttachedParts >()).f_< StoreType >().f_< CountryCode >() = 15;
    (*s.alt_< AttachedParts >()).f_< StoreType >().f_< Category    >() = 20;
    (*s.alt_< AttachedParts >()).f_< StoreType >().f_< Subcategory >() = 25;
    (*s.alt_< AttachedParts >()).f_< StoreType >().f_< Specific    >() = 30;
    (*s.alt_< AttachedParts >()).f_< StoreType >().f_< Extra       >() = 35;

    BOOST_CHECK((*s.alt_< AttachedParts >()).f_< Station   >()                     == StationEnum32::M249_SAW::value());
    BOOST_CHECK((*s.alt_< AttachedParts >()).f_< StoreType >().f_< EntityKind  >() ==  5);
    BOOST_CHECK((*s.alt_< AttachedParts >()).f_< StoreType >().f_< Domain      >() == 10);
    BOOST_CHECK((*s.alt_< AttachedParts >()).f_< StoreType >().f_< CountryCode >() == 15);
    BOOST_CHECK((*s.alt_< AttachedParts >()).f_< StoreType >().f_< Category    >() == 20);
    BOOST_CHECK((*s.alt_< AttachedParts >()).f_< StoreType >().f_< Subcategory >() == 25);
    BOOST_CHECK((*s.alt_< AttachedParts >()).f_< StoreType >().f_< Specific    >() == 30);
    BOOST_CHECK((*s.alt_< AttachedParts >()).f_< StoreType >().f_< Extra       >() == 35);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_articulated_parameter_struct_access) {
    using namespace protox::om::rpr;
    using namespace protox::om::rpr::ParameterTypeEnum32;
    using namespace protox::om::rpr::ArticulatedPartsTypeEnum32;
    using namespace protox::om::rpr::ArticulatedTypeMetricEnum32;
    using namespace protox::om::rpr::ArticulatedParameterStruct;
    using namespace protox::om::rpr::ParameterValueStruct;
    using namespace protox::om::rpr::ArticulatedPartsStruct;
    using namespace protox::om::rpr::AttachedPartsStruct;
    using namespace protox::om::rpr::EntityTypeStruct;

    ArticulatedParameterStruct::type s;

    s.f_< ArticulatedParameterChange >() = 5;
    s.f_< PartAttachedTo >() = 10;
    s.f_< ParameterValue >().discriminant = ArticulatedPart::value();
    s.f_< ParameterValue >().alt_< ArticulatedParts >(ArticulatedPartsStruct::type());

    (*s.f_< ParameterValue >().alt_< ArticulatedParts >()).f_< Class >() = SpeedBrake::value();
    (*s.f_< ParameterValue >().alt_< ArticulatedParts >()).f_< TypeMetric >() = X::value();
    (*s.f_< ParameterValue >().alt_< ArticulatedParts >()).f_< Value      >() = 15;

    BOOST_CHECK((*s.f_< ParameterValue >().alt_< ArticulatedParts >()).f_< Class      >() == SpeedBrake::value());
    BOOST_CHECK((*s.f_< ParameterValue >().alt_< ArticulatedParts >()).f_< TypeMetric >() == X::value());
    BOOST_CHECK((*s.f_< ParameterValue >().alt_< ArticulatedParts >()).f_< Value      >() == 15);

    s.f_< ParameterValue >().discriminant = AttachedPart::value();
    s.f_< ParameterValue >().alt_< AttachedParts >(AttachedPartsStruct::type());

    (*s.f_< ParameterValue >().alt_< AttachedParts >()).f_< Station   >()                     = StationEnum32::M249_SAW::value();
    (*s.f_< ParameterValue >().alt_< AttachedParts >()).f_< StoreType >().f_< EntityKind  >() =  5;
    (*s.f_< ParameterValue >().alt_< AttachedParts >()).f_< StoreType >().f_< Domain      >() = 10;
    (*s.f_< ParameterValue >().alt_< AttachedParts >()).f_< StoreType >().f_< CountryCode >() = 15;
    (*s.f_< ParameterValue >().alt_< AttachedParts >()).f_< StoreType >().f_< Category    >() = 20;
    (*s.f_< ParameterValue >().alt_< AttachedParts >()).f_< StoreType >().f_< Subcategory >() = 25;
    (*s.f_< ParameterValue >().alt_< AttachedParts >()).f_< StoreType >().f_< Specific    >() = 30;
    (*s.f_< ParameterValue >().alt_< AttachedParts >()).f_< StoreType >().f_< Extra       >() = 35;

    BOOST_CHECK((*s.f_< ParameterValue >().alt_< AttachedParts >()).f_< Station   >()                     == StationEnum32::M249_SAW::value());
    BOOST_CHECK((*s.f_< ParameterValue >().alt_< AttachedParts >()).f_< StoreType >().f_< EntityKind  >() ==  5);
    BOOST_CHECK((*s.f_< ParameterValue >().alt_< AttachedParts >()).f_< StoreType >().f_< Domain      >() == 10);
    BOOST_CHECK((*s.f_< ParameterValue >().alt_< AttachedParts >()).f_< StoreType >().f_< CountryCode >() == 15);
    BOOST_CHECK((*s.f_< ParameterValue >().alt_< AttachedParts >()).f_< StoreType >().f_< Category    >() == 20);
    BOOST_CHECK((*s.f_< ParameterValue >().alt_< AttachedParts >()).f_< StoreType >().f_< Subcategory >() == 25);
    BOOST_CHECK((*s.f_< ParameterValue >().alt_< AttachedParts >()).f_< StoreType >().f_< Specific    >() == 30);
    BOOST_CHECK((*s.f_< ParameterValue >().alt_< AttachedParts >()).f_< StoreType >().f_< Extra       >() == 35);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_attribute_pair_struct_access) {
    using namespace protox::om::rpr;
    using namespace protox::om::rpr::AttributePairStruct;

    AttributePairStruct::type s;

    s.f_< AttributeHandle >() =  5;
    s.f_< ValueLength     >() = 10;

    s.f_< Value           >().push_back( 3);
    s.f_< Value           >().push_back( 6);
    s.f_< Value           >().push_back( 9);
    s.f_< Value           >().push_back(12);

    BOOST_CHECK(s.f_< AttributeHandle >()    ==  5);
    BOOST_CHECK(s.f_< ValueLength     >()    == 10);
    BOOST_CHECK(s.f_< Value           >()[0] ==  3);
    BOOST_CHECK(s.f_< Value           >()[1] ==  6);
    BOOST_CHECK(s.f_< Value           >()[2] ==  9);
    BOOST_CHECK(s.f_< Value           >()[3] == 12);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_attribute_value_set_struct_access) {
    using namespace protox::om::rpr;
    using namespace protox::om::rpr::AttributePairStruct;
    using namespace protox::om::rpr::AttributeValueSetStruct;

    AttributeValueSetStruct::type s;

    s.f_< AttributeSetCount >() = 5;
    s.f_ < AttributePairs >().push_back(AttributePairStruct::type());
    s.f_ < AttributePairs >().push_back(AttributePairStruct::type());
    s.f_ < AttributePairs >().push_back(AttributePairStruct::type());

    s.f_< AttributePairs >()[0].f_< AttributeHandle >() =  5;
    s.f_< AttributePairs >()[0].f_< ValueLength     >() = 10;
    s.f_< AttributePairs >()[0].f_< Value           >().push_back(3);
    s.f_< AttributePairs >()[0].f_< Value           >().push_back(6);
    s.f_< AttributePairs >()[0].f_< Value           >().push_back(9);

    s.f_< AttributePairs >()[1].f_< AttributeHandle >() = 15;
    s.f_< AttributePairs >()[1].f_< ValueLength     >() = 20;
    s.f_< AttributePairs >()[1].f_< Value           >().push_back(12);
    s.f_< AttributePairs >()[1].f_< Value           >().push_back(15);
    s.f_< AttributePairs >()[1].f_< Value           >().push_back(18);

    s.f_< AttributePairs >()[2].f_< AttributeHandle >() = 25;
    s.f_< AttributePairs >()[2].f_< ValueLength     >() = 30;
    s.f_< AttributePairs >()[2].f_< Value           >().push_back(21);
    s.f_< AttributePairs >()[2].f_< Value           >().push_back(24);
    s.f_< AttributePairs >()[2].f_< Value           >().push_back(27);

    BOOST_CHECK(s.f_< AttributeSetCount >()                               ==  5);

    BOOST_CHECK(s.f_< AttributePairs    >()[0].f_< AttributeHandle >()    ==  5);
    BOOST_CHECK(s.f_< AttributePairs    >()[0].f_< ValueLength     >()    == 10);
    BOOST_CHECK(s.f_< AttributePairs    >()[0].f_< Value           >()[0] ==  3);
    BOOST_CHECK(s.f_< AttributePairs    >()[0].f_< Value           >()[1] ==  6);
    BOOST_CHECK(s.f_< AttributePairs    >()[0].f_< Value           >()[2] ==  9);

    BOOST_CHECK(s.f_< AttributePairs    >()[1].f_< AttributeHandle >()    == 15);
    BOOST_CHECK(s.f_< AttributePairs    >()[1].f_< ValueLength     >()    == 20);
    BOOST_CHECK(s.f_< AttributePairs    >()[1].f_< Value           >()[0] == 12);
    BOOST_CHECK(s.f_< AttributePairs    >()[1].f_< Value           >()[1] == 15);
    BOOST_CHECK(s.f_< AttributePairs    >()[1].f_< Value           >()[2] == 18);

    BOOST_CHECK(s.f_< AttributePairs    >()[2].f_< AttributeHandle >()    == 25);
    BOOST_CHECK(s.f_< AttributePairs    >()[2].f_< ValueLength     >()    == 30);
    BOOST_CHECK(s.f_< AttributePairs    >()[2].f_< Value           >()[0] == 21);
    BOOST_CHECK(s.f_< AttributePairs    >()[2].f_< Value           >()[1] == 24);
    BOOST_CHECK(s.f_< AttributePairs    >()[2].f_< Value           >()[2] == 27);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_clock_time_struct_access) {
    using namespace protox::om::rpr;
    using namespace protox::om::rpr::ClockTimeStruct;

    ClockTimeStruct::type s;

    s.f_< Hours           >() =  5;
    s.f_< TimePastTheHour >() = 10;

    BOOST_CHECK(s.f_< Hours           >() ==  5);
    BOOST_CHECK(s.f_< TimePastTheHour >() == 10);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_federation_identifier_struct_access) {
    using namespace protox::om::rpr;
    using namespace protox::om::rpr::FederateIdentifierStruct;

    FederateIdentifierStruct::type s;

    s.f_< SiteID        >() =  5;
    s.f_< ApplicationID >() = 10;

    BOOST_CHECK(s.f_< SiteID        >() ==  5);
    BOOST_CHECK(s.f_< ApplicationID >() == 10);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_entity_identifier_struct_access) {
    using namespace protox::om::rpr;
    using namespace protox::om::rpr::FederateIdentifierStruct;
    using namespace protox::om::rpr::EntityIdentifierStruct;

    EntityIdentifierStruct::type s;

    s.f_< FederateIdentifier >().f_< SiteID        >() =  5;
    s.f_< FederateIdentifier >().f_< ApplicationID >() = 10;
    s.f_< EntityNumber       >()                       = 15;

    BOOST_CHECK(s.f_< FederateIdentifier >().f_< SiteID        >() ==  5);
    BOOST_CHECK(s.f_< FederateIdentifier >().f_< ApplicationID >() == 10);
    BOOST_CHECK(s.f_< EntityNumber       >()                       == 15);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_rti_object_id_struct_access) {
    using namespace protox::om::rpr;
    using namespace protox::om::rpr::RTIObjectIdStruct;

    RTIObjectIdStruct::type s;

    s.f_< ID >().push_back('a');
    s.f_< ID >().push_back('b');
    s.f_< ID >().push_back('c');
    s.f_< ID >().push_back('d');
    s.f_< ID >().push_back('e');

    BOOST_CHECK(s.f_< ID >()[0] == 'a');
    BOOST_CHECK(s.f_< ID >()[1] == 'b');
    BOOST_CHECK(s.f_< ID >()[2] == 'c');
    BOOST_CHECK(s.f_< ID >()[3] == 'd');
    BOOST_CHECK(s.f_< ID >()[4] == 'e');
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_event_identifier_struct_access) {
    using namespace protox::om::rpr;
    using namespace protox::om::rpr::RTIObjectIdStruct;
    using namespace protox::om::rpr::EventIdentifierStruct;

    EventIdentifierStruct::type s;

    s.f_< EventCount              >() = 5;
    s.f_< IssuingObjectIdentifier >().f_< ID >().push_back('a');
    s.f_< IssuingObjectIdentifier >().f_< ID >().push_back('b');
    s.f_< IssuingObjectIdentifier >().f_< ID >().push_back('c');
    s.f_< IssuingObjectIdentifier >().f_< ID >().push_back('d');
    s.f_< IssuingObjectIdentifier >().f_< ID >().push_back('e');

    BOOST_CHECK(s.f_< EventCount              >()               ==   5);
    BOOST_CHECK(s.f_< IssuingObjectIdentifier >().f_< ID >()[0] == 'a');
    BOOST_CHECK(s.f_< IssuingObjectIdentifier >().f_< ID >()[1] == 'b');
    BOOST_CHECK(s.f_< IssuingObjectIdentifier >().f_< ID >()[2] == 'c');
    BOOST_CHECK(s.f_< IssuingObjectIdentifier >().f_< ID >()[3] == 'd');
    BOOST_CHECK(s.f_< IssuingObjectIdentifier >().f_< ID >()[4] == 'e');
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_fixed_datum_struct_access) {
    using namespace protox::om::rpr;
    using namespace protox::om::rpr::FixedDatumStruct;
    using namespace protox::om::rpr::DatumIdentifierEnum32;

    FixedDatumStruct::type s;

    s.f_< FixedDatumIdentifier >() = Body_Part_Damaged_Ratio::value();
    s.f_< FixedDatumValue      >() = 5;

    BOOST_CHECK(s.f_< FixedDatumIdentifier >() == Body_Part_Damaged_Ratio::value());
    BOOST_CHECK(s.f_< FixedDatumValue      >() == 5);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_marking_struct_access) {
    using namespace protox::om::rpr;
    using namespace protox::om::rpr::MarkingStruct;
    using namespace protox::om::rpr::MarkingEncodingEnum8;

    MarkingStruct::type s;

    s.f_< MarkingEncodingType >()     = DigitChevron::value();
    s.f_< MarkingData         >()[ 0] = 'a';
    s.f_< MarkingData         >()[ 5] = 'b';
    s.f_< MarkingData         >()[ 7] = 'c';
    s.f_< MarkingData         >()[10] = 'd';

    BOOST_CHECK(s.f_< MarkingEncodingType >()     == DigitChevron::value());
    BOOST_CHECK(s.f_< MarkingData         >()[ 0] == 'a');
    BOOST_CHECK(s.f_< MarkingData         >()[ 5] == 'b');
    BOOST_CHECK(s.f_< MarkingData         >()[ 7] == 'c');
    BOOST_CHECK(s.f_< MarkingData         >()[10] == 'd');
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_sincgars_modulation_struct_access) {
    using namespace protox::om::rpr;
    using namespace protox::om::rpr::SINCGARSModulationStruct;

    SINCGARSModulationStruct::type s;

    s.f_< FHNetID                     >() =  5;
    s.f_< HopSetID                    >() = 10;
    s.f_< LockoutSetID                >() = 15;
    s.f_< StartOfMessage              >() = StartMessageEnum8::StartOfMessage::value();
    s.f_< FHSynchronizationTimeOffset >() = 20;
    s.f_< TransmissionSecurityKey     >() = 25;
    s.f_< ClearChannel                >() = 'z';

    BOOST_CHECK(s.f_< FHNetID                     >() ==  5);
    BOOST_CHECK(s.f_< HopSetID                    >() == 10);
    BOOST_CHECK(s.f_< LockoutSetID                >() == 15);
    BOOST_CHECK(s.f_< StartOfMessage              >() == StartMessageEnum8::StartOfMessage::value());
    BOOST_CHECK(s.f_< FHSynchronizationTimeOffset >() == 20);
    BOOST_CHECK(s.f_< TransmissionSecurityKey     >() == 25);
    BOOST_CHECK(s.f_< ClearChannel                >() == 'z');
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_modulation_struct_access) {
    using namespace protox::om::rpr;
    using namespace protox::om::rpr::ModulationStruct;
    using namespace protox::om::rpr::SINCGARSModulationStruct;

    ModulationStruct::type s;

    s.f_< SINCGARModulation >().push_back(SINCGARSModulationStruct::type());

    s.f_< SINCGARModulation >()[0].f_< FHNetID                     >() =  5;
    s.f_< SINCGARModulation >()[0].f_< HopSetID                    >() = 10;
    s.f_< SINCGARModulation >()[0].f_< LockoutSetID                >() = 15;
    s.f_< SINCGARModulation >()[0].f_< StartOfMessage              >() = StartMessageEnum8::StartOfMessage::value();
    s.f_< SINCGARModulation >()[0].f_< FHSynchronizationTimeOffset >() = 20;
    s.f_< SINCGARModulation >()[0].f_< TransmissionSecurityKey     >() = 25;
    s.f_< SINCGARModulation >()[0].f_< ClearChannel                >() = 'z';

    BOOST_CHECK(s.f_< SINCGARModulation >()[0].f_< FHNetID                     >() ==  5);
    BOOST_CHECK(s.f_< SINCGARModulation >()[0].f_< HopSetID                    >() == 10);
    BOOST_CHECK(s.f_< SINCGARModulation >()[0].f_< LockoutSetID                >() == 15);
    BOOST_CHECK(s.f_< SINCGARModulation >()[0].f_< StartOfMessage              >() == StartMessageEnum8::StartOfMessage::value());
    BOOST_CHECK(s.f_< SINCGARModulation >()[0].f_< FHSynchronizationTimeOffset >() == 20);
    BOOST_CHECK(s.f_< SINCGARModulation >()[0].f_< TransmissionSecurityKey     >() == 25);
    BOOST_CHECK(s.f_< SINCGARModulation >()[0].f_< ClearChannel                >() == 'z');

}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_radio_type_struct_access) {
    using namespace protox::om::rpr;
    using namespace protox::om::rpr::RadioTypeStruct;

    RadioTypeStruct::type s;

    s.f_< EntityKind          >() =  5;
    s.f_< Domain              >() = 10;
    s.f_< CountryCode         >() = 15;
    s.f_< Category            >() = 20;
    s.f_< NomenclatureVersion >() = NomenclatureVersionEnum8::Other::value();
    s.f_< Nomenclature        >() = NomenclatureEnum16::Other::value();

    BOOST_CHECK(s.f_< EntityKind          >() ==  5);
    BOOST_CHECK(s.f_< Domain              >() == 10);
    BOOST_CHECK(s.f_< CountryCode         >() == 15);
    BOOST_CHECK(s.f_< Category            >() == 20);
    BOOST_CHECK(s.f_< NomenclatureVersion >() == NomenclatureVersionEnum8::Other::value());
    BOOST_CHECK(s.f_< Nomenclature        >() == NomenclatureEnum16::Other::value());
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_relative_positioin_struct_access) {
    using namespace protox::om::rpr;
    using namespace protox::om::rpr::RelativePositionStruct;

    RelativePositionStruct::type s;

    s.f_< BodyXDistance >() =  5;
    s.f_< BodyYDistance >() = 10;
    s.f_< BodyZDistance >() = 15;

    BOOST_CHECK(s.f_< BodyXDistance >() ==  5);
    BOOST_CHECK(s.f_< BodyYDistance >() == 10);
    BOOST_CHECK(s.f_< BodyZDistance >() == 15);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_rf_modulation_type_struct_access) {
    using namespace protox::om::rpr;
    using namespace protox::om::rpr::RFModulationTypeStruct;
    using namespace protox::om::rpr::MajorRFModulationTypeEnum16;
    using namespace protox::om::rpr::AmplitudeModulationTypeEnum16;
    using namespace protox::om::rpr::AmplitudeAngleModulationTypeEnum16;
    using namespace protox::om::rpr::AngleModulationTypeEnum16;
    using namespace protox::om::rpr::CombinationModulationTypeEnum16;
    using namespace protox::om::rpr::PulseModulationTypeEnum16;
    using namespace protox::om::rpr::UnmodulatedTypeEnum16;

    RFModulationTypeStruct::type s;

    s.discriminant = Amplitude::value();
    s.alt_< AmplitudeModulationType >(AmplitudeModulationTypeEnum16::type());
    BOOST_CHECK((*s.alt_< AmplitudeModulationType >()) == AmplitudeModulationTypeEnum16::Other::value());

    (*s.alt_< AmplitudeModulationType >()) = AmplitudeModulationTypeEnum16::SSB_LowerSideband::value();
    BOOST_CHECK((*s.alt_< AmplitudeModulationType >()) == AmplitudeModulationTypeEnum16::SSB_LowerSideband::value());

    s.discriminant = MajorRFModulationTypeEnum16::AmplitudeAndAngle::value();
    s.alt_< AmplitudeAngleModulationType >(AmplitudeAngleModulationTypeEnum16::type());
    BOOST_CHECK((*s.alt_< AmplitudeAngleModulationType >()) == AmplitudeAngleModulationTypeEnum16::Other::value());

    (*s.alt_< AmplitudeAngleModulationType >()) = AmplitudeAngleModulationTypeEnum16::AmplitudeAndAngle::value();
    BOOST_CHECK((*s.alt_< AmplitudeAngleModulationType >()) == AmplitudeAngleModulationTypeEnum16::AmplitudeAndAngle::value());

    s.discriminant = MajorRFModulationTypeEnum16::Angle::value();
    s.alt_< AngleModulationType >(AngleModulationTypeEnum16::type());
    BOOST_CHECK((*s.alt_< AngleModulationType >()) == AngleModulationTypeEnum16::Other::value());

    (*s.alt_< AngleModulationType >()) = FrequencyShiftKeying::value();
    BOOST_CHECK((*s.alt_< AngleModulationType >()) == FrequencyShiftKeying::value());

    s.discriminant = MajorRFModulationTypeEnum16::Combination::value();
    s.alt_< CombinationModulationType >(CombinationModulationTypeEnum16::type());
    BOOST_CHECK((*s.alt_< CombinationModulationType >()) == CombinationModulationTypeEnum16::Other::value());

    (*s.alt_< CombinationModulationType >()) = AmplitudeAnglePulse::value();
    BOOST_CHECK((*s.alt_< CombinationModulationType >()) == AmplitudeAnglePulse::value());

    s.discriminant = MajorRFModulationTypeEnum16::Pulse::value();
    s.alt_< PulseModulationType >(PulseModulationTypeEnum16::type());
    BOOST_CHECK((*s.alt_< PulseModulationType >()) == PulseModulationTypeEnum16::Other::value());

    (*s.alt_< PulseModulationType >()) = PulseModulationTypeEnum16::Pulse::value();
    BOOST_CHECK((*s.alt_< PulseModulationType >()) == PulseModulationTypeEnum16::Pulse::value());

    s.discriminant = MajorRFModulationTypeEnum16::Unmodulated::value();
    s.alt_< UnmodulatedType >(UnmodulatedTypeEnum16::type());
    BOOST_CHECK((*s.alt_< UnmodulatedType >()) == UnmodulatedTypeEnum16::Other::value());

    (*s.alt_< UnmodulatedType >()) = ContinuousWaveEmission::value();
    BOOST_CHECK((*s.alt_< UnmodulatedType >()) == ContinuousWaveEmission::value());
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_rti_object_id_array_struct_access) {
    using namespace protox::om::rpr;
    using namespace protox::om::rpr::RTIObjectIdArrayStruct;

    RTIObjectIdArrayStruct::type s;

    s.f_< Length >() = 5;

    RTIObjectIdStruct::type id1;
    id1.f_< RTIObjectIdStruct::ID >().push_back('a');
    id1.f_< RTIObjectIdStruct::ID >().push_back('b');

    s.f_< ID >().push_back(id1);

    RTIObjectIdStruct::type id2;
    id2.f_< RTIObjectIdStruct::ID >().push_back('c');
    id2.f_< RTIObjectIdStruct::ID >().push_back('d');
    id2.f_< RTIObjectIdStruct::ID >().push_back('e');

    s.f_< ID >().push_back(id2);

    BOOST_CHECK(s.f_< Length >() == 5);
    BOOST_CHECK(s.f_< ID >()[0].f_< RTIObjectIdStruct::ID >()[0] == 'a');
    BOOST_CHECK(s.f_< ID >()[0].f_< RTIObjectIdStruct::ID >()[1] == 'b');
    BOOST_CHECK(s.f_< ID >()[1].f_< RTIObjectIdStruct::ID >()[0] == 'c');
    BOOST_CHECK(s.f_< ID >()[1].f_< RTIObjectIdStruct::ID >()[1] == 'd');
    BOOST_CHECK(s.f_< ID >()[1].f_< RTIObjectIdStruct::ID >()[2] == 'e');
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_supply_struct_access) {
    using namespace protox::om::rpr;
    using namespace protox::om::rpr::SupplyStruct;
    using namespace protox::om::rpr::EntityTypeStruct;

    SupplyStruct::type s;

    s.f_< SupplyType >().f_< EntityKind  >() =  5;
    s.f_< SupplyType >().f_< Domain      >() = 10;
    s.f_< SupplyType >().f_< CountryCode >() = 15;
    s.f_< SupplyType >().f_< Category    >() = 20;
    s.f_< SupplyType >().f_< Subcategory >() = 25;
    s.f_< SupplyType >().f_< Specific    >() = 30;
    s.f_< SupplyType >().f_< Extra       >() = 35;

    s.f_< Quantity >() = 40;

    BOOST_CHECK(s.f_< SupplyType >().f_< EntityKind  >() ==  5);
    BOOST_CHECK(s.f_< SupplyType >().f_< Domain      >() == 10);
    BOOST_CHECK(s.f_< SupplyType >().f_< CountryCode >() == 15);
    BOOST_CHECK(s.f_< SupplyType >().f_< Category    >() == 20);
    BOOST_CHECK(s.f_< SupplyType >().f_< Subcategory >() == 25);
    BOOST_CHECK(s.f_< SupplyType >().f_< Specific    >() == 30);
    BOOST_CHECK(s.f_< SupplyType >().f_< Extra       >() == 35);
    BOOST_CHECK(s.f_< Quantity   >()                     == 40);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_variable_datum_struct_access) {
    using namespace protox::om::rpr;
    using namespace protox::om::rpr::VariableDatumStruct;
    using namespace protox::om::rpr::DatumIdentifierEnum32;

    VariableDatumStruct::type s;

    s.f_< DatumID     >() = Body_Part_Damaged_Ratio::value();
    s.f_< DatumLength >() = 5;
    s.f_< DatumValue  >().push_back(1);
    s.f_< DatumValue  >().push_back(2);
    s.f_< DatumValue  >().push_back(3);
    s.f_< DatumValue  >().push_back(4);

    BOOST_CHECK(s.f_< DatumID     >()    == Body_Part_Damaged_Ratio::value());
    BOOST_CHECK(s.f_< DatumLength >()    == 5);
    BOOST_CHECK(s.f_< DatumValue  >()[0] == 1);
    BOOST_CHECK(s.f_< DatumValue  >()[1] == 2);
    BOOST_CHECK(s.f_< DatumValue  >()[2] == 3);
    BOOST_CHECK(s.f_< DatumValue  >()[3] == 4);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_variable_datum_set_struct_access) {
    using namespace protox::om::rpr;
    using namespace protox::om::rpr::VariableDatumSetStruct;
    using namespace protox::om::rpr::VariableDatumStruct;
    using namespace protox::om::rpr::DatumIdentifierEnum32;

    VariableDatumSetStruct::type s;

    s.f_< NumberOfVariableDatums >() = 5;

    VariableDatumStruct::type d1;

    d1.f_< DatumID     >() = Body_Part_Damaged_Ratio::value();
    d1.f_< DatumLength >() = 5;
    d1.f_< DatumValue  >().push_back(1);
    d1.f_< DatumValue  >().push_back(2);
    d1.f_< DatumValue  >().push_back(3);
    d1.f_< DatumValue  >().push_back(4);

    s.f_< VariableDatums >().push_back(d1);

    VariableDatumStruct::type d2;

    d2.f_< DatumID     >() = Default_Time_For_Radio_Transmission_For_Moving_Transmitters::value();
    d2.f_< DatumLength >() = 10;
    d2.f_< DatumValue  >().push_back(10);
    d2.f_< DatumValue  >().push_back(20);
    d2.f_< DatumValue  >().push_back(30);

    s.f_< VariableDatums >().push_back(d2);

    BOOST_CHECK(s.f_< NumberOfVariableDatums >() == 5);

    BOOST_CHECK(s.f_< VariableDatums >()[0].f_< DatumID     >()    == Body_Part_Damaged_Ratio::value());
    BOOST_CHECK(s.f_< VariableDatums >()[0].f_< DatumLength >()    == 5);
    BOOST_CHECK(s.f_< VariableDatums >()[0].f_< DatumValue  >()[0] == 1);
    BOOST_CHECK(s.f_< VariableDatums >()[0].f_< DatumValue  >()[1] == 2);
    BOOST_CHECK(s.f_< VariableDatums >()[0].f_< DatumValue  >()[2] == 3);
    BOOST_CHECK(s.f_< VariableDatums >()[0].f_< DatumValue  >()[3] == 4);

    BOOST_CHECK(s.f_< VariableDatums >()[1].f_< DatumID     >()    == Default_Time_For_Radio_Transmission_For_Moving_Transmitters::value());
    BOOST_CHECK(s.f_< VariableDatums >()[1].f_< DatumLength >()    == 10);
    BOOST_CHECK(s.f_< VariableDatums >()[1].f_< DatumValue  >()[0] == 10);
    BOOST_CHECK(s.f_< VariableDatums >()[1].f_< DatumValue  >()[1] == 20);
    BOOST_CHECK(s.f_< VariableDatums >()[1].f_< DatumValue  >()[2] == 30);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_velocity_vector_struct_access) {
    using namespace protox::om::rpr;
    using namespace protox::om::rpr::VelocityVectorStruct;

    VelocityVectorStruct::type s;

    s.f_< XVelocity >() =  5;
    s.f_< YVelocity >() = 10;
    s.f_< ZVelocity >() = 15;

    BOOST_CHECK(s.f_< XVelocity >() ==  5);
    BOOST_CHECK(s.f_< YVelocity >() == 10);
    BOOST_CHECK(s.f_< ZVelocity >() == 15);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_world_location_struct_access) {
    using namespace protox::om::rpr;
    using namespace protox::om::rpr::WorldLocationStruct;

    WorldLocationStruct::type s;

    s.f_< X >() =  5;
    s.f_< Y >() = 10;
    s.f_< Z >() = 15;

    BOOST_CHECK(s.f_< X >() ==  5);
    BOOST_CHECK(s.f_< Y >() == 10);
    BOOST_CHECK(s.f_< Z >() == 15);

}
