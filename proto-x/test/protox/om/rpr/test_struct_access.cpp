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
