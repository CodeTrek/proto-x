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

#include <protox/om/rpr/acceleration_vector_struct.hpp>

/**********************************************************************************************************************/

using namespace protox::om::rpr;

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_field_access) {

    using namespace protox::om::rpr::AccelerationVectorStruct;

    AccelerationVectorStruct::type s;

    s.f_< XAcceleration >() =  5;
    s.f_< YAcceleration >() = 10;
    s.f_< ZAcceleration >() = 15;

    BOOST_CHECK(s.f_< XAcceleration >() ==  5);
    BOOST_CHECK(s.f_< YAcceleration >() == 10);
    BOOST_CHECK(s.f_< ZAcceleration >() == 15);
}
