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
    struct f01 : protox::dtl::field< Boolean > {};      // 1 byte
    struct f02 : protox::dtl::field< UInt03bitBe > {};  // 1 byte
    struct f03 : protox::dtl::field< UInt13bitBe > {};  // 2 bytes
    struct f04 : protox::dtl::field< UInt19bitBe > {};  // 3 bytes

    typedef protox::bee::record_type< mpl::vector <
            f01, // low memory, most significant bit.
            f02,
            f03,
            f04  // high memory, least significant bit.
    > > R;
}

namespace t02 {
    struct f01 : protox::dtl::field< Boolean > {};
    struct f02 : protox::dtl::field< UInt03bitLe > {};
    struct f03 : protox::dtl::field< UInt13bitLe > {};
    struct f04 : protox::dtl::field< UInt19bitLe > {};

    typedef protox::bee::record_type< mpl::vector <
            f01, // low memory, most significant bit.
            f02,
            f03,
            f04 // high memory, least significant bit.
    > > R;
}

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_record_field_assignment) {
    // Arrange.
    t01::R r;

    // Act.
    r.f_<t01::f01>() = true;
    r.f_<t01::f02>() = 0b110;
    r.f_<t01::f03>() = 0b1100111;

    boost::dynamic_bitset<> bit_sink;

    // Assert.
    BOOST_CHECK_EQUAL(true, r.f_<t01::f01>());
    BOOST_CHECK_EQUAL(0b110, r.f_<t01::f02>());
    BOOST_CHECK_EQUAL(0b1100111, r.f_<t01::f03>());
}

BOOST_AUTO_TEST_CASE(test_record_size_in_bytes) {
    // Act.
    const unsigned value = codec::static_size_in_bytes<t01::R>::value;

    // Assert.
    BOOST_CHECK_EQUAL(7, value);
}

BOOST_AUTO_TEST_CASE(test_record_encode_big_endian_fields) {
    // Arrange.
    t01::R r;
    boost::dynamic_bitset<> bit_sink;
    r.f_<t01::f01>() = true;
    r.f_<t01::f02>() = 0b110;
    r.f_<t01::f03>() = 0b0000001100111;
    r.f_<t01::f04>() = 0b1100000001100000000;

    // Act.
    protox::dtl::codec::encode(bit_sink, r);

    // Assert.
    BOOST_CHECK_EQUAL(36, bit_sink.size());
    BOOST_CHECK_EQUAL(0b111000000011001111100000001100000000, bit_sink.to_ulong());
}

BOOST_AUTO_TEST_CASE(test_record_decode_big_endian_fields) {
    // Arrange.
    t01::R r;
    boost::dynamic_bitset<> bit_sink(36, 0b111000000011001111100000001100000000);
    std::size_t offset = 0;

    // Act.
    protox::dtl::codec::decode(r, bit_sink, offset);

    // Assert.
    BOOST_CHECK_EQUAL(36, offset);
    BOOST_CHECK_EQUAL(true, r.f_<t01::f01>());
    BOOST_CHECK_EQUAL(0b110, r.f_<t01::f02>());
    BOOST_CHECK_EQUAL(0b1100111, r.f_<t01::f03>());
    BOOST_CHECK_EQUAL(0b1100000001100000000, r.f_<t01::f04>());
}

BOOST_AUTO_TEST_CASE(test_record_encode_little_endian_fields) {
    // Arrange.
    t02::R r;
    boost::dynamic_bitset<> bit_sink;
    r.f_<t02::f01>() = true;
    r.f_<t02::f02>() = 0b110;
    r.f_<t02::f03>() = 0b0000001100111;
    r.f_<t02::f04>() = 0b1100000001100000000;

    // Act.
    protox::dtl::codec::encode(bit_sink, r);

    // Assert.
    BOOST_CHECK_EQUAL(36, bit_sink.size());
    BOOST_CHECK_EQUAL(0b101111100110000000000000011000000011, bit_sink.to_ulong());
}

BOOST_AUTO_TEST_CASE(test_record_decode_little_endian_fields) {
    // Arrange.
    t02::R r;
    boost::dynamic_bitset<> bit_sink(36, 0b101111100110000000000000011000000011);
    std::size_t offset = 0;

    // Act.
    protox::dtl::codec::decode(r, bit_sink, offset);

    // Assert.
    BOOST_CHECK_EQUAL(36, offset);
    BOOST_CHECK_EQUAL(true, r.f_<t02::f01>());
    BOOST_CHECK_EQUAL(0b110, r.f_<t02::f02>());
    BOOST_CHECK_EQUAL(0b1100111, r.f_<t02::f03>());
    BOOST_CHECK_EQUAL(0b1100000001100000000, r.f_<t02::f04>());
}

/******************************************************************************************************************************************/

}

/******************************************************************************************************************************************/
