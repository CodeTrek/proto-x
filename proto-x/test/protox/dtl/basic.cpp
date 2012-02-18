/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#define BOOST_AUTO_TEST_MAIN

#include <boost/test/included/unit_test_framework.hpp>
#include <boost/test/auto_unit_test.hpp>

#include <test/protox/dtl/basic_data_table.hpp>

/**********************************************************************************************************************/

using namespace test::protox_dtl;

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_default_constructor) {
    Integer32LE int32LE;
    BOOST_CHECK(int32LE == 0);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_initialization_constructor) {
    Integer32LE int32LE(10);
    BOOST_CHECK(int32LE == 10);
}
/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_copy_constructor) {
    Integer32LE int32LE_1(10);
    BOOST_CHECK(int32LE_1 == 10);

    Integer32LE int32LE_2( int32LE_1);
    BOOST_CHECK(int32LE_2 == 10);
    BOOST_CHECK(int32LE_2 == int32LE_1);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_assignment) {
    Integer16BE int16BE;

    int16BE = 5;
    BOOST_CHECK(int16BE == 5);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_type_casting_1) {
    Integer16BE int16BE(10);
    short short1 = int16BE;
    BOOST_CHECK(short1 == 10);

    int16BE = 3.14; // Generates a compiler warning
    BOOST_CHECK(int16BE == 3);

    double double1 = int16BE;
    BOOST_CHECK(double1 == 3.0);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_type_casting_2) {
    Integer16BE int16BE(10);
    Float32LE float32LE;

    float32LE = int16BE;
    BOOST_CHECK(float32LE == 10.0f);
    BOOST_CHECK(10.0f == float32LE);

    float32LE = 5.678f;

    int16BE = float32LE; // Generates a compiler warning
    BOOST_CHECK(5 == int16BE);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_inequality_operator) {
    Integer16BE int16BE(10);

    BOOST_CHECK(5 != int16BE);
    BOOST_CHECK(int16BE != 20);

    Float32LE float32LE(8.5f);
    BOOST_CHECK(1.2 != float32LE);
    BOOST_CHECK(float32LE != 5.55);

    BOOST_CHECK(float32LE != int16BE);
    BOOST_CHECK(int16BE != float32LE);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_increment_operator) {
    Integer16BE int16BE(10);
    ++int16BE;
    ++int16BE;
    BOOST_CHECK(12 == int16BE);

    int16BE += 5;
    BOOST_CHECK(17 == int16BE);
}
