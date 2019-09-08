/******************************************************************************************************************************************/
// (c) 2009 - 2019 Jay Graham
//
// Distributed under the MIT License
// (see accompanying file LICENSE_1_0_0.txt or http://www.opensource.org/licenses/mit-license.php)
/******************************************************************************************************************************************/

#include <type_traits>
#include <string>

#include <boost/test/unit_test.hpp>

#include <protox/dtl/endian_enum.hpp>
#include <protox/dtl/fixed_array.hpp>

/******************************************************************************************************************************************/

namespace test_fixed_array {

/******************************************************************************************************************************************/

struct na {
};

/******************************************************************************************************************************************/

/* @formatter:off */
struct int_array_3 : protox::dtl::fixed_array<int, 3, na> {PROTOX_FIXED_ARRAY(int_array_3)};
/* @formatter:on */

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_fixed_array_returns_correct_value_type) {
    struct fixed_array_type : protox::dtl::fixed_array<std::string, 3, na> {
    };

    const bool result = std::is_same<std::string, fixed_array_type::value_type>::value;

    BOOST_CHECK(result == true);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_fixed_array_returns_correct_reference_type) {
    struct fixed_array_type : protox::dtl::fixed_array<std::string, 3, na> {
    };

    const bool result = std::is_same<std::string&, fixed_array_type::reference>::value;

    BOOST_CHECK(result == true);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_fixed_array_returns_correct_const_reference_type) {
    struct fixed_array_type : protox::dtl::fixed_array<std::string, 3, na> {
    };

    const bool result = std::is_same<const std::string&, fixed_array_type::const_reference>::value;

    BOOST_CHECK(result == true);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_fixed_array_returns_correct_codec_tag) {
    struct fixed_array_type : protox::dtl::fixed_array<std::string, 3, na> {
    };

    const bool result = std::is_same<na, fixed_array_type::codec_tag>::value;

    BOOST_CHECK(result == true);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_fixed_array_returns_correct_dimension_value) {
    struct fixed_array_type : protox::dtl::fixed_array<std::string, 7, na> {
    };

    BOOST_CHECK(7 == fixed_array_type::static_num_elements);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_fixed_array_index_operator) {
    int_array_3 value;

    value[0] = 9;
    value[1] = 8;
    value[2] = 7;

    BOOST_CHECK(9 == value[0]);
    BOOST_CHECK(8 == value[1]);
    BOOST_CHECK(7 == value[2]);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_fixed_array_initializer_list) {
    int_array_3 value = { 9, 8, 7 };

    BOOST_CHECK(9 == value[0]);
    BOOST_CHECK(8 == value[1]);
    BOOST_CHECK(7 == value[2]);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_fixed_array_eqaulity_operator) {
    int_array_3 value1 = { 9, 8, 7 };
    int_array_3 value2 = { 9, 8, 7 };

    BOOST_CHECK(value1 == value2);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_fixed_array_ineqaulity_operator) {
    int_array_3 value1 = { 9, 8, 7 };
    int_array_3 value2 = { 9, 3, 7 };

    BOOST_CHECK(value1 != value2);
}

/******************************************************************************************************************************************/

}

/******************************************************************************************************************************************/
