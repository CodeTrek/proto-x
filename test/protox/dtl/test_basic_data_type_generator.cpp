/******************************************************************************************************************************************/
// (c) 2009 - 2019 Jay Graham
//
// Distributed under the MIT License
// (see accompanying file LICENSE_1_0_0.txt or http://www.opensource.org/licenses/mit-license.php)
/******************************************************************************************************************************************/

#include <type_traits>

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

/* @formatter:off */
// Generate basic types.
struct Integer32LE : basic<long,  32, endian::little, na> {PROTOX_BASIC(Integer32LE)};
struct Integer16BE : basic<short, 16, endian::big,    na> {PROTOX_BASIC(Integer16BE)};
struct Float32LE   : basic<float, 32, endian::little, na> {PROTOX_BASIC(Float32LE  )};
/* @formatter:on */

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
    Integer32LE value1(10);
    Integer32LE value2(value1);

    BOOST_CHECK(value2 == 10);
    BOOST_CHECK(value2 == value1);
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

    result.value = value.value;

    BOOST_CHECK(result == 10.0f);
    BOOST_CHECK(10.0f == result);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_type_casting_float32LE_to_int16BE) {
    const Float32LE value { 5.678f };
    Integer16BE result { };

    result.value = value.value; // Generates a compiler warning

    BOOST_CHECK(5 == result);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_int16BE_inequality_operator) {
    Integer16BE int16BE(10);

    BOOST_CHECK(5 != int16BE);
    BOOST_CHECK(int16BE != 20);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_float32LE_inequality_operator) {
    Float32LE float32LE(8.5f);
    BOOST_CHECK(1.2 != float32LE);
    BOOST_CHECK(float32LE != 5.55);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_int16BE_float32LE_inequality_operator) {
    Integer16BE int16BE(10);
    Float32LE float32LE(8.5f);

    BOOST_CHECK(float32LE != int16BE);
    BOOST_CHECK(int16BE != float32LE);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_int16BE_increment_operator) {
    Integer16BE int16BE(10);
    ++int16BE;
    ++int16BE;
    BOOST_CHECK(12 == int16BE);

    int16BE += 5;
    BOOST_CHECK(17 == int16BE);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_basic_returns_correct_codec_tag) {

    const bool result = std::is_same<na, Integer16BE::codec_tag>::value;

    BOOST_CHECK(result == true);
}

/******************************************************************************************************************************************/

}

/******************************************************************************************************************************************/
