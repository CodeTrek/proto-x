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

#include <protox/dtl/field.hpp>

/******************************************************************************************************************************************/

namespace test_field {

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_field_returns_correct_type) {
    struct field_type : protox::dtl::field<std::string> {
    };

    const bool result = std::is_same<std::string, field_type::value_type>::value;

    BOOST_CHECK(result == true);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_field_base_returns_correct_value) {
    struct field_type : protox::dtl::field<std::string> {
    };

    struct field_base_type : protox::dtl::field_base<field_type> {
    };

    field_base_type result;
    result.value = "hello, world";

    BOOST_CHECK("hello, world" == result.value);
}

/******************************************************************************************************************************************/

}

/******************************************************************************************************************************************/
