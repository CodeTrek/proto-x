/******************************************************************************************************************************************/
// (c) 2009 - 2019 Jay Graham
//
// Distributed under the MIT License
// (see accompanying file LICENSE_1_0_0.txt or http://www.opensource.org/licenses/mit-license.php)
/******************************************************************************************************************************************/

#include <boost/test/unit_test.hpp>
#include <protox/dtl/simple.hpp>
#include <protox/dtl/endian_enum.hpp>
#include <protox/dtl/basic.hpp>

/******************************************************************************************************************************************/

namespace test_simple {

using namespace protox::dtl;

struct na {
};

/******************************************************************************************************************************************/

/* @formatter:off */

// Generate the basic types used to define the simple types below.
typedef basic<long,  32, endian::little, na> Integer32LE;
typedef basic<short, 16, endian::big,    na> Integer16BE;
typedef basic<float, 32, endian::little, na> Float32LE;

/******************************************************************************************************************************************/

// Generate simple types.
typedef simple<Integer32LE> Simple32LE;
typedef simple<Integer16BE> Simple16BE;
typedef simple<Float32LE>   SimpleFloat32LE;

/* @formatter:on */

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_default_constructor) {
    Simple32LE result;

    BOOST_CHECK(result == 0);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_initialization_constructor) {
    Simple32LE result(10);

    BOOST_CHECK(result == 10);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_copy_constructor) {
    Simple32LE value(10);

    Simple32LE result(value);

    BOOST_CHECK(result == 10);
    BOOST_CHECK(result == value);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_assignment) {
    Simple16BE result;

    result = 5;

    BOOST_CHECK(result == 5);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_type_cast_int16BE_to_short) {
    Simple16BE value(10);

    short result = value;

    BOOST_CHECK(result == 10);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_type_cast_double_to_int16BE) {
    Simple16BE result(10);

    result = 3.14; // Generates a compiler warning

    BOOST_CHECK(result == 3);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_type_cast_int16BE_to_double) {
    Simple16BE value(10);

    double result = value;

    BOOST_CHECK(result == 10.0);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_type_cast_int16BE_to_float32LE) {
    Simple16BE value(10);
    SimpleFloat32LE result;

    result = value;

    BOOST_CHECK(result == 10.0f);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_type_cast_float32LE_to_int16BE) {
    SimpleFloat32LE value;
    Simple16BE result;

    value = 5.678f;

    result = value; // Generates a compiler warning

    BOOST_CHECK(5 == result);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_inequality_operator_for_int16BE) {
    Simple16BE result(10);

    BOOST_CHECK(5 != result);
    BOOST_CHECK(result != 20);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_inequality_operator_for_float32LE) {
    SimpleFloat32LE result(8.5f);
    BOOST_CHECK(1.2 != result);
    BOOST_CHECK(result != 5.55);

}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_inequality_operator_for_float32LE_and_int16BE) {
    Simple16BE int16BE(10);
    SimpleFloat32LE float32LE(8.5f);

    BOOST_CHECK(float32LE != int16BE);
    BOOST_CHECK(int16BE != float32LE);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_increment_operator_for_int16BE) {
    Simple16BE int16BE(10);

    ++int16BE;
    ++int16BE;

    BOOST_CHECK(12 == int16BE);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_increment_assignment_operator_for_int16BE) {
    Simple16BE result(10);

    result += 5;

    BOOST_CHECK(15 == result);
}

/******************************************************************************************************************************************/

}

/******************************************************************************************************************************************/
