/******************************************************************************************************************************************/
// (c) 2009 - 2019 Jay Graham
//
// Distributed under the MIT License
// (see accompanying file LICENSE_1_0_0.txt or http://www.opensource.org/licenses/mit-license.php)
/******************************************************************************************************************************************/

#include <boost/test/unit_test.hpp>

/******************************************************************************************************************************************/

#include <boost/mpl/sizeof.hpp>
#include <boost/dynamic_bitset.hpp>

#include <protox/dtl/endian_enum.hpp>
#include <protox/dtl/basic.hpp>
#include <protox/codec/codecs.hpp>
#include <protox/bee/codec_tags.hpp>

#include <protox/platform.hpp>

/******************************************************************************************************************************************/

namespace test_bee_policy_basic_data {

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

BOOST_AUTO_TEST_CASE(test_encode_boolean_true) {

    // Arrang.e
    boost::dynamic_bitset<> bit_sink;
    Boolean value = true;

    // Act.
    protox::dtl::codec::encode(bit_sink, value);

    // Assert.
    BOOST_CHECK_EQUAL(1, bit_sink.size());
    BOOST_CHECK_EQUAL(1, bit_sink[0]);
}

BOOST_AUTO_TEST_CASE(test_encode_boolean_false) {

    // Arrang.e
    boost::dynamic_bitset<> bit_sink;
    Boolean value = false;

    // Act.
    protox::dtl::codec::encode(bit_sink, value);

    // Assert.
    BOOST_CHECK_EQUAL(1, bit_sink.size());
    BOOST_CHECK_EQUAL(0, bit_sink[0]);
}

BOOST_AUTO_TEST_CASE(test_encode_3_bit_value_of_1_as_big_endian_bitset) {

    // Arrang.e
    boost::dynamic_bitset<> bit_sink;
    UInt03bitBe value = 1;

    // Act.
    protox::dtl::codec::encode(bit_sink, value);

    // Assert.
    BOOST_CHECK_EQUAL(3, bit_sink.size());

    BOOST_CHECK_EQUAL(1, bit_sink[0]);
    BOOST_CHECK_EQUAL(0, bit_sink[1]);
    BOOST_CHECK_EQUAL(0, bit_sink[2]);
}

BOOST_AUTO_TEST_CASE(test_encode_3_bit_value_of_1_as_little_endian_bitset) {

    // Arrang.e
    boost::dynamic_bitset<> bit_sink;
    UInt03bitLe value = 1;

    // Act.
    protox::dtl::codec::encode(bit_sink, value);

    // Assert.
    BOOST_CHECK_EQUAL(3, bit_sink.size());

    BOOST_CHECK_EQUAL(0, bit_sink[0]);
    BOOST_CHECK_EQUAL(0, bit_sink[1]);
    BOOST_CHECK_EQUAL(1, bit_sink[2]);
}

BOOST_AUTO_TEST_CASE(test_encode_3_bit_value_of_4_as_big_endian_bitset) {

    // Arrang.e
    boost::dynamic_bitset<> bit_sink;
    UInt03bitBe value = 4;

    // Act.
    protox::dtl::codec::encode(bit_sink, value);

    // Assert.
    BOOST_CHECK_EQUAL(3, bit_sink.size());

    BOOST_CHECK_EQUAL(0, bit_sink[0]);
    BOOST_CHECK_EQUAL(0, bit_sink[1]);
    BOOST_CHECK_EQUAL(1, bit_sink[2]);
}

BOOST_AUTO_TEST_CASE(test_encode_3_bit_value_of_4_as_little_endian_bitset) {

    // Arrang.e
    boost::dynamic_bitset<> bit_sink;
    UInt03bitLe value = 4;

    // Act.
    protox::dtl::codec::encode(bit_sink, value);

    // Assert.
    BOOST_CHECK_EQUAL(3, bit_sink.size());

    BOOST_CHECK_EQUAL(1, bit_sink[0]);
    BOOST_CHECK_EQUAL(0, bit_sink[1]);
    BOOST_CHECK_EQUAL(0, bit_sink[2]);
}

BOOST_AUTO_TEST_CASE(test_encode_13_bit_value_of_1_as_big_endian_bitset) {

    // Arrang.e
    boost::dynamic_bitset<> bit_sink;
    UInt13bitBe value = 1;

    // Act.
    protox::dtl::codec::encode(bit_sink, value);

    // Assert.
    BOOST_CHECK_EQUAL(13, bit_sink.size());

    BOOST_CHECK_EQUAL(1, bit_sink[0]);
    BOOST_CHECK_EQUAL(0, bit_sink[1]);
    BOOST_CHECK_EQUAL(0, bit_sink[2]);
    BOOST_CHECK_EQUAL(0, bit_sink[3]);
    BOOST_CHECK_EQUAL(0, bit_sink[4]);
    BOOST_CHECK_EQUAL(0, bit_sink[5]);
    BOOST_CHECK_EQUAL(0, bit_sink[6]);
    BOOST_CHECK_EQUAL(0, bit_sink[7]);
    BOOST_CHECK_EQUAL(0, bit_sink[8]);
    BOOST_CHECK_EQUAL(0, bit_sink[9]);
    BOOST_CHECK_EQUAL(0, bit_sink[10]);
    BOOST_CHECK_EQUAL(0, bit_sink[11]);
    BOOST_CHECK_EQUAL(0, bit_sink[12]);
}

BOOST_AUTO_TEST_CASE(test_encode_13_bit_value_of_1_as_little_endian_bitset) {

    // Arrang.e
    boost::dynamic_bitset<> bit_sink;
    UInt13bitLe value = 1;

    // Act.
    protox::dtl::codec::encode(bit_sink, value);

    // Assert.
    BOOST_CHECK_EQUAL(13, bit_sink.size());

    BOOST_CHECK_EQUAL(0, bit_sink[0]);
    BOOST_CHECK_EQUAL(0, bit_sink[1]);
    BOOST_CHECK_EQUAL(0, bit_sink[2]);
    BOOST_CHECK_EQUAL(0, bit_sink[3]);
    BOOST_CHECK_EQUAL(0, bit_sink[4]);
    BOOST_CHECK_EQUAL(0, bit_sink[5]);
    BOOST_CHECK_EQUAL(0, bit_sink[6]);
    BOOST_CHECK_EQUAL(0, bit_sink[7]);
    BOOST_CHECK_EQUAL(0, bit_sink[8]);
    BOOST_CHECK_EQUAL(0, bit_sink[9]);
    BOOST_CHECK_EQUAL(0, bit_sink[10]);
    BOOST_CHECK_EQUAL(0, bit_sink[11]);
    BOOST_CHECK_EQUAL(1, bit_sink[12]);
}

BOOST_AUTO_TEST_CASE(test_encode_13_bit_value_of_4096_as_big_endian_bitset) {

    // Arrang.e
    boost::dynamic_bitset<> bit_sink;
    UInt13bitBe value = 4096;

    // Act.
    protox::dtl::codec::encode(bit_sink, value);

    // Assert.
    BOOST_CHECK_EQUAL(13, bit_sink.size());

    BOOST_CHECK_EQUAL(0, bit_sink[0]);
    BOOST_CHECK_EQUAL(0, bit_sink[1]);
    BOOST_CHECK_EQUAL(0, bit_sink[2]);
    BOOST_CHECK_EQUAL(0, bit_sink[3]);
    BOOST_CHECK_EQUAL(0, bit_sink[4]);
    BOOST_CHECK_EQUAL(0, bit_sink[5]);
    BOOST_CHECK_EQUAL(0, bit_sink[6]);
    BOOST_CHECK_EQUAL(0, bit_sink[7]);
    BOOST_CHECK_EQUAL(0, bit_sink[8]);
    BOOST_CHECK_EQUAL(0, bit_sink[9]);
    BOOST_CHECK_EQUAL(0, bit_sink[10]);
    BOOST_CHECK_EQUAL(0, bit_sink[11]);
    BOOST_CHECK_EQUAL(1, bit_sink[12]);
}

BOOST_AUTO_TEST_CASE(test_encode_13_bit_value_of_4096_as_little_endian_bitset) {

    // Arrang.e
    boost::dynamic_bitset<> bit_sink;
    UInt13bitLe value = 4096;

    // Act.
    protox::dtl::codec::encode(bit_sink, value);

    // Assert.
    BOOST_CHECK_EQUAL(13, bit_sink.size());

    BOOST_CHECK_EQUAL(1, bit_sink[0]);
    BOOST_CHECK_EQUAL(0, bit_sink[1]);
    BOOST_CHECK_EQUAL(0, bit_sink[2]);
    BOOST_CHECK_EQUAL(0, bit_sink[3]);
    BOOST_CHECK_EQUAL(0, bit_sink[4]);
    BOOST_CHECK_EQUAL(0, bit_sink[5]);
    BOOST_CHECK_EQUAL(0, bit_sink[6]);
    BOOST_CHECK_EQUAL(0, bit_sink[7]);
    BOOST_CHECK_EQUAL(0, bit_sink[8]);
    BOOST_CHECK_EQUAL(0, bit_sink[9]);
    BOOST_CHECK_EQUAL(0, bit_sink[10]);
    BOOST_CHECK_EQUAL(0, bit_sink[11]);
    BOOST_CHECK_EQUAL(0, bit_sink[12]);
}

BOOST_AUTO_TEST_CASE(test_decode_13_bit_value_of_4096_from_little_endian_bitset) {

    // Arrang.e
    boost::dynamic_bitset<> bit_sink;
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);

    UInt13bitLe value = 0;
    std::size_t offset = 0;

    // Act.
    protox::dtl::codec::decode(value, bit_sink, offset);

    // Assert.
    BOOST_CHECK_EQUAL(13, offset);
    BOOST_CHECK_EQUAL(4096, value);
}

BOOST_AUTO_TEST_CASE(test_decode_13_bit_value_of_4096_from_big_endian_bitset) {

    // Arrang.e
    boost::dynamic_bitset<> bit_sink;
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(1);

    UInt13bitBe value = 0;
    std::size_t offset = 0;

    // Act.
    protox::dtl::codec::decode(value, bit_sink, offset);

    // Assert.
    BOOST_CHECK_EQUAL(13, offset);
    BOOST_CHECK_EQUAL(4096, value);
}

/******************************************************************************************************************************************/

}

/******************************************************************************************************************************************/
