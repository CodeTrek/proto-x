/******************************************************************************************************************************************/
// (c) 2009 - 2019 Jay Graham
//
// Distributed under the MIT License
// (see accompanying file LICENSE_1_0_0.txt or http://www.opensource.org/licenses/mit-license.php)
/******************************************************************************************************************************************/

#include <type_traits>
#include <string>

#include <boost/mpl/vector.hpp>
#include <boost/test/unit_test.hpp>

#include <protox/dtl/fixed_record.hpp>

/******************************************************************************************************************************************/

namespace test_fixed_record {

/******************************************************************************************************************************************/

struct na {
};

/******************************************************************************************************************************************/

/* @formatter:off */
struct X  : protox::dtl::field< short > {};
struct Y  : protox::dtl::field< int   > {};
struct Z  : protox::dtl::field< float > {};

struct record_xyz : protox::dtl::fixed_record< boost::mpl::vector< X, Y, Z > , na > {};
/* @formatter:on */

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_fixed_record_fiel_access) {
    record_xyz value;

    value.f_<X>() = 7;
    value.f_<Y>() = 517;
    value.f_<Z>() = 3.14156f;

    BOOST_CHECK(7 == value.f_<X>());
    BOOST_CHECK(517 == value.f_<Y>());
    BOOST_CHECK(3.14156f == value.f_<Z>());
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_fixed_record_returns_correct_codec_tag) {
    const bool result = std::is_same<na, record_xyz::codec_tag>::value;

    BOOST_CHECK(result == true);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_fixed_record_eqaulity_operator) {
    record_xyz value1;
    record_xyz value2;

    value1.f_<X>() = 7;
    value1.f_<Y>() = 517;
    value1.f_<Z>() = 3.14156f;

    value2.f_<X>() = 7;
    value2.f_<Y>() = 517;
    value2.f_<Z>() = 3.14156f;

    BOOST_CHECK(value1 == value2);
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_fixed_record_ineqaulity_operator) {
    record_xyz value1;
    record_xyz value2;

    value1.f_<X>() = 7;
    value1.f_<Y>() = 517;
    value1.f_<Z>() = 3.14156f;

    value2.f_<X>() = 7;
    value2.f_<Y>() = 516;
    value2.f_<Z>() = 3.14156f;

    BOOST_CHECK(value1 != value2);
}

/******************************************************************************************************************************************/

}

/******************************************************************************************************************************************/
