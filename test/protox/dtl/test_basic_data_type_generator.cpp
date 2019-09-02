/******************************************************************************************************************************************/
// (c) 2009 - 2019 Jay Graham
//
// Distributed under the MIT License
// (see accompanying file LICENSE_1_0_0.txt or http://www.opensource.org/licenses/mit-license.php)
/******************************************************************************************************************************************/

#include <boost/test/unit_test.hpp>
#include <protox/dtl/endian_enum.hpp>
#include <protox/dtl/basic.hpp>

/******************************************************************************************************************************************/

namespace test_basic {

/******************************************************************************************************************************************/

using namespace protox::dtl;

/******************************************************************************************************************************************/

struct na {
};

/******************************************************************************************************************************************/

// Generate basic types.
typedef basic<long,  32, endian::little, na> Integer32LE;
typedef basic<short, 16, endian::big,    na> Integer16BE;
typedef basic<float, 32, endian::little, na> Float32LE;

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_default_constructor) {
    Integer32LE int32LE;
    BOOST_CHECK(int32LE == 0);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_initialization_constructor) {
    Integer32LE int32LE(10);
    BOOST_CHECK(int32LE == 10);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_copy_constructor) {
    Integer32LE int32LE_1(10);
    BOOST_CHECK(int32LE_1 == 10);

    Integer32LE int32LE_2(int32LE_1);
    BOOST_CHECK(int32LE_2 == 10);
    BOOST_CHECK(int32LE_2 == int32LE_1);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_assignment) {
    Integer16BE int16BE;

    int16BE = 5;
    BOOST_CHECK(int16BE == 5);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_type_cast_int16BE_to_short) {
    const Integer16BE value { 10 };

    short result = value;

    BOOST_CHECK(result == 10);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_type_cast_double_to_int16BE) {
    Integer16BE result { };

    result = 3.14; // Generates a compiler warning

    BOOST_CHECK(result == 3);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_type_cast_int16be_to_double) {
    const Integer16BE value { 3 };

    double result = value;

    BOOST_CHECK(result == 3.0);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_type_cast_int16BE_to_float32LE) {
    const Integer16BE value(10);
    Float32LE result;

    result = value;

    BOOST_CHECK(result == 10.0f);
    BOOST_CHECK(10.0f == result);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_type_casting_float32LE_to_int16BE) {
    const Float32LE value { 5.678f };
    Integer16BE result { };

    result = value; // Generates a compiler warning

    BOOST_CHECK(5 == result);
}

/******************************************************************************************************************************************/

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

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_increment_operator) {
    Integer16BE int16BE(10);
    ++int16BE;
    ++int16BE;
    BOOST_CHECK(12 == int16BE);

    int16BE += 5;
    BOOST_CHECK(17 == int16BE);
}

/******************************************************************************************************************************************/

}

/******************************************************************************************************************************************/
