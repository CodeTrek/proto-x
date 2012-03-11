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

#include <protox/om/rpr/antenna_pattern_struct.hpp>
#include <protox/om/rpr/acceleration_vector_struct.hpp>
#include <protox/om/rpr/angular_velocity_vector_struct.hpp>
#include <protox/om/rpr/antenna_pattern_struct.hpp>

/**********************************************************************************************************************/

using namespace protox::om::rpr;

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_acceleration_vector_struct_field_access) {

    AccelerationVectorStruct::type s;

    s.f_< XAcceleration >() =  5;
    s.f_< YAcceleration >() = 10;
    s.f_< ZAcceleration >() = 15;

    BOOST_CHECK(s.f_< XAcceleration >() ==  5);
    BOOST_CHECK(s.f_< YAcceleration >() == 10);
    BOOST_CHECK(s.f_< ZAcceleration >() == 15);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_angular_velocity_vector_struct_field_access) {

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

BOOST_AUTO_TEST_CASE(test_antenna_pattern_struct_field_access) {

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
