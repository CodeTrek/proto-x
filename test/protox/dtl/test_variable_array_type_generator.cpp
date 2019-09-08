/******************************************************************************************************************************************/
// (c) 2009 - 2019 Jay Graham
//
// Distributed under the MIT License
// (see accompanying file LICENSE_1_0_0.txt or http://www.opensource.org/licenses/mit-license.php)
/******************************************************************************************************************************************/

#include <type_traits>
#include <vector>
#include <string>

#include <boost/test/unit_test.hpp>

#include <protox/dtl/endian_enum.hpp>
#include <protox/dtl/variable_array.hpp>

/******************************************************************************************************************************************/

namespace test_variable_array {

/******************************************************************************************************************************************/

struct na {
};

/******************************************************************************************************************************************/

/* @formatter:off */
struct int_array : protox::dtl::variable_array<std::vector<int>, na> {PROTOX_VARIABLE_ARRAY(int_array)};
/* @formatter:on */

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_fixed_array_returns_correct_value_type) {
    struct variable_array_type : protox::dtl::variable_array<std::vector<std::string>, na> {
    };

    const bool result = std::is_same<std::string, variable_array_type::value_type>::value;

    BOOST_CHECK(result == true);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_variable_array_returns_correct_array_type) {
    struct variable_array_type : protox::dtl::variable_array<std::vector<std::string>, na> {
    };

    const bool result = std::is_same<std::vector<std::string>, variable_array_type::array_type>::value;

    BOOST_CHECK(result == true);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_variable_array_returns_correct_codec_tag) {
    struct variable_array_type : protox::dtl::variable_array<std::vector<std::string>, na> {
    };

    const bool result = std::is_same<na, variable_array_type::codec_tag>::value;

    BOOST_CHECK(result == true);
}

///******************************************************************************************************************************************/
//
BOOST_AUTO_TEST_CASE(test_variable_array_initializer_list) {
    int_array value = { 9, 8, 7, 6, 5 };

    BOOST_CHECK(9 == value[0]);
    BOOST_CHECK(8 == value[1]);
    BOOST_CHECK(7 == value[2]);
    BOOST_CHECK(6 == value[3]);
    BOOST_CHECK(5 == value[4]);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_variable_array_eqaulity_operator) {
    int_array value1 = { 9, 8, 7 };
    int_array value2 = { 9, 8, 7 };

    BOOST_CHECK(value1 == value2);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_variable_array_ineqaulity_operator) {
    int_array value1 = { 9, 8, 7 };
    int_array value2 = { 9, 3, 7 };

    BOOST_CHECK(value1 != value2);
}

/******************************************************************************************************************************************/

}

/******************************************************************************************************************************************/
