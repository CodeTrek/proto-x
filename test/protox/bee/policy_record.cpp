/******************************************************************************************************************************************/
// (c) 2009 - 2019 Jay Graham
//
// Distributed under the MIT License
// (see accompanying file LICENSE_1_0_0.txt or http://www.opensource.org/licenses/mit-license.php)
/******************************************************************************************************************************************/

#include <boost/test/unit_test.hpp>

/******************************************************************************************************************************************/

#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/dynamic_bitset.hpp>

#include <protox/dtl/endian_enum.hpp>
#include <protox/dtl/basic.hpp>
#include <protox/codec/codecs.hpp>
#include <protox/bee/codec_tags.hpp>
#include <protox/platform.hpp>
#include <protox/bee/record_type.hpp>

/******************************************************************************************************************************************/

namespace test_bee_policy_record {

/******************************************************************************************************************************************/

using namespace boost;
using namespace protox::dtl;
using namespace protox::bee;

/* @formatter:off */
struct na {};


struct Boolean     : basic<bool,            1, endian::big,    boolean> {PROTOX_BASIC(Boolean  )};
struct UInt03bitBe : basic<unsigned char,   3, endian::big,    number > {PROTOX_BASIC(UInt03bitBe)};
struct UInt13bitBe : basic<unsigned short, 13, endian::big,    number > {PROTOX_BASIC(UInt13bitBe)};
struct UInt19bitBe : basic<unsigned long,  19, endian::big,    number > {PROTOX_BASIC(UInt19bitBe)};
struct UInt03bitLe : basic<unsigned char,   3, endian::little, number > {PROTOX_BASIC(UInt03bitLe)};
struct UInt13bitLe : basic<unsigned short, 13, endian::little, number > {PROTOX_BASIC(UInt13bitLe)};
struct UInt19bitLe : basic<unsigned long,  19, endian::little, number > {PROTOX_BASIC(UInt19bitLe)};

/* @formatter:on */

/******************************************************************************************************************************************/

namespace t01 {
    struct f01 : protox::dtl::field< Boolean > {};
    struct f02 : protox::dtl::field< UInt03bitBe > {};
    struct f03 : protox::dtl::field< UInt13bitBe > {};
    struct f04 : protox::dtl::field< UInt19bitBe > {};

    typedef protox::bee::record_type< mpl::vector < f01, f02, f03, f04 > > R;
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_record_field_assignment) {
    t01::R r;

    r.f_<t01::f01>() = true;
    r.f_<t01::f02>() = 0b110;
    r.f_<t01::f03>() = 0b1100111;

    BOOST_CHECK_EQUAL(true, r.f_<t01::f01>());
    BOOST_CHECK_EQUAL(0b110, r.f_<t01::f02>());
    BOOST_CHECK_EQUAL(0b1100111, r.f_<t01::f03>());
}

/******************************************************************************************************************************************/

}

/******************************************************************************************************************************************/
