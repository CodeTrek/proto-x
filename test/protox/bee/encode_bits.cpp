/*
 Copyright 2009 Jay Graham

 Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
 or http://www.opensource.org/licenses/mit-license.php)
 */

/**********************************************************************************************************************/

#include <boost/test/unit_test.hpp>

/**********************************************************************************************************************/

#include <boost/mpl/sizeof.hpp>
#include <boost/dynamic_bitset.hpp>

#include <protox/dtl/endian_enum.hpp>
#include <protox/dtl/basic.hpp>
#include <protox/codec/codecs.hpp>
#include <protox/bee/codec_tags.hpp>

#include <protox/platform.hpp>

/**********************************************************************************************************************/

namespace test_bee_encode_bits {

using namespace boost;
using namespace protox::dtl;
using namespace protox::bee;

BOOST_AUTO_TEST_CASE(test_encode_8_bits_as_little_endian_bitset) {

    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    const unsigned char byte = 0b00110011;

    // Act.
    protox::bee::encode_bits<boost::dynamic_bitset<>, true>::pack(bit_sink, byte, 8);

    // Assert.
    BOOST_CHECK_EQUAL(8, bit_sink.size());
    BOOST_CHECK_EQUAL(0, bit_sink[0]);
    BOOST_CHECK_EQUAL(0, bit_sink[1]);
    BOOST_CHECK_EQUAL(1, bit_sink[2]);
    BOOST_CHECK_EQUAL(1, bit_sink[3]);
    BOOST_CHECK_EQUAL(0, bit_sink[4]);
    BOOST_CHECK_EQUAL(0, bit_sink[5]);
    BOOST_CHECK_EQUAL(1, bit_sink[6]);
    BOOST_CHECK_EQUAL(1, bit_sink[7]);
}

BOOST_AUTO_TEST_CASE(test_encode_5_bits_as_little_endian_bitset) {

    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    const unsigned char byte = 0b00010011;

    // Act.
    protox::bee::encode_bits<boost::dynamic_bitset<>, true>::pack(bit_sink, byte, 5);

    // Assert.
    BOOST_CHECK_EQUAL(5, bit_sink.size());
    BOOST_CHECK_EQUAL(1, bit_sink[0]);
    BOOST_CHECK_EQUAL(0, bit_sink[1]);
    BOOST_CHECK_EQUAL(0, bit_sink[2]);
    BOOST_CHECK_EQUAL(1, bit_sink[3]);
    BOOST_CHECK_EQUAL(1, bit_sink[4]);
}

BOOST_AUTO_TEST_CASE(test_encode_8_bits_as_big_endian_bitset) {

    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    const unsigned char byte = 0b00110011;

    // Act.
    protox::bee::encode_bits<boost::dynamic_bitset<>, false>::pack(bit_sink, byte, 8);

    // Assert.
    BOOST_CHECK_EQUAL(8, bit_sink.size());
    BOOST_CHECK_EQUAL(1, bit_sink[0]);
    BOOST_CHECK_EQUAL(1, bit_sink[1]);
    BOOST_CHECK_EQUAL(0, bit_sink[2]);
    BOOST_CHECK_EQUAL(0, bit_sink[3]);
    BOOST_CHECK_EQUAL(1, bit_sink[4]);
    BOOST_CHECK_EQUAL(1, bit_sink[5]);
    BOOST_CHECK_EQUAL(0, bit_sink[6]);
    BOOST_CHECK_EQUAL(0, bit_sink[7]);
}

BOOST_AUTO_TEST_CASE(test_encode_5_bits_as_big_endian_bitset) {

    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    const unsigned char byte = 0b00010011;

    // Act.
    protox::bee::encode_bits<boost::dynamic_bitset<>, false>::pack(bit_sink, byte, 5);

    // Assert.
    BOOST_CHECK_EQUAL(5, bit_sink.size());
    BOOST_CHECK_EQUAL(1, bit_sink[0]);
    BOOST_CHECK_EQUAL(1, bit_sink[1]);
    BOOST_CHECK_EQUAL(0, bit_sink[2]);
    BOOST_CHECK_EQUAL(0, bit_sink[3]);
    BOOST_CHECK_EQUAL(1, bit_sink[4]);
}

}
