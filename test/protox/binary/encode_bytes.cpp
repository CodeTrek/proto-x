/******************************************************************************************************************************************/
// (c) 2009 - 2019 Jay Graham
//
// Distributed under the MIT License
// (see accompanying file LICENSE_1_0_0.txt or http://www.opensource.org/licenses/mit-license.php)
/******************************************************************************************************************************************/

#include <cmath>

#include <boost/test/unit_test.hpp>
#include <boost/dynamic_bitset.hpp>

#include <protox/binary/bytes.hpp>

/******************************************************************************************************************************************/

namespace test_binary_encode_bytes {

using namespace protox::binary;

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_encode_1_bit_value_of_1) {
    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    const unsigned char value = 0b00000001;

    // Act.
    protox::binary::bytes<1, 1, BYTE_LITTLE_ENDIAN, BIT_LITTLE_ENDIAN>::encode(bit_sink, (const unsigned char *)&value);

    // Assert.
    BOOST_CHECK_EQUAL(1, bit_sink.size());
    BOOST_CHECK_EQUAL(1, bit_sink[0]);
}

BOOST_AUTO_TEST_CASE(test_encode_1_bit_value_of_0) {
    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    const unsigned char value = 0b00000000;

    // Act.
    protox::binary::bytes<1, 1, BYTE_LITTLE_ENDIAN, BIT_LITTLE_ENDIAN>::encode(bit_sink, (const unsigned char *)&value);

    // Assert.
    BOOST_CHECK_EQUAL(1, bit_sink.size());
    BOOST_CHECK_EQUAL(0, bit_sink[0]);
}

BOOST_AUTO_TEST_CASE(test_encode_3_bit_value_as_little_endian_bitset) {
    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    const unsigned char value = 0b00000001;

    // Act.
    protox::binary::bytes<3, 1, BYTE_LITTLE_ENDIAN, BIT_LITTLE_ENDIAN>::encode(bit_sink, (const unsigned char *)&value);

    // Assert.
    BOOST_CHECK_EQUAL(3, bit_sink.size());
    BOOST_CHECK_EQUAL(1, bit_sink[2]);
    BOOST_CHECK_EQUAL(0, bit_sink[1]);
    BOOST_CHECK_EQUAL(0, bit_sink[0]);
}

BOOST_AUTO_TEST_CASE(test_encode_3_bit_value_as_big_endian_bitset) {
    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    const unsigned char value = 0b00000001;

    // Act.
    protox::binary::bytes<3, 1, BYTE_LITTLE_ENDIAN, BIT_BIG_ENDIAN>::encode(bit_sink, (const unsigned char *)&value);

    // Assert.
    BOOST_CHECK_EQUAL(3, bit_sink.size());
    BOOST_CHECK_EQUAL(0, bit_sink[2]);
    BOOST_CHECK_EQUAL(0, bit_sink[1]);
    BOOST_CHECK_EQUAL(1, bit_sink[0]);
}

BOOST_AUTO_TEST_CASE(test_encode_8_bit_value_as_little_endian_bitset) {
    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    const unsigned char value = 0b00110011;

    // Act.
    protox::binary::bytes<8, 1, BYTE_LITTLE_ENDIAN, BIT_LITTLE_ENDIAN>::encode(bit_sink, (const unsigned char *)&value);

    // Assert.
    BOOST_CHECK_EQUAL(8, bit_sink.size());
    BOOST_CHECK_EQUAL(1, bit_sink[7]);
    BOOST_CHECK_EQUAL(1, bit_sink[6]);
    BOOST_CHECK_EQUAL(0, bit_sink[5]);
    BOOST_CHECK_EQUAL(0, bit_sink[4]);
    BOOST_CHECK_EQUAL(1, bit_sink[3]);
    BOOST_CHECK_EQUAL(1, bit_sink[2]);
    BOOST_CHECK_EQUAL(0, bit_sink[1]);
    BOOST_CHECK_EQUAL(0, bit_sink[0]);
}

BOOST_AUTO_TEST_CASE(test_encode_8_bit_value_as_big_endian_bitset) {
    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    const unsigned char value = 0b00110011;

    // Act.
    protox::binary::bytes<8, 1, BYTE_LITTLE_ENDIAN, BIT_BIG_ENDIAN>::encode(bit_sink, (const unsigned char *)&value);

    // Assert.
    BOOST_CHECK_EQUAL(8, bit_sink.size());
    BOOST_CHECK_EQUAL(0, bit_sink[7]);
    BOOST_CHECK_EQUAL(0, bit_sink[6]);
    BOOST_CHECK_EQUAL(1, bit_sink[5]);
    BOOST_CHECK_EQUAL(1, bit_sink[4]);
    BOOST_CHECK_EQUAL(0, bit_sink[3]);
    BOOST_CHECK_EQUAL(0, bit_sink[2]);
    BOOST_CHECK_EQUAL(1, bit_sink[1]);
    BOOST_CHECK_EQUAL(1, bit_sink[0]);
}

BOOST_AUTO_TEST_CASE(test_encode_16_bit_little_endian_value_as_little_endian_bitset) {

    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    //                                 LSB         MSB
    const unsigned char value[2] = {0b00110011, 0b00011101};

    // Act.
    protox::binary::bytes<16, 2, BYTE_LITTLE_ENDIAN, BIT_LITTLE_ENDIAN>::encode(bit_sink, value);

    // Assert.
    BOOST_CHECK_EQUAL(16, bit_sink.size());
    BOOST_CHECK_EQUAL(0b1100110010111000, bit_sink.to_ulong());
}

BOOST_AUTO_TEST_CASE(test_encode_13_bit_little_endian_value_as_little_endian_bitset) {

    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    //                                 LSB          MSB
    const unsigned char value[2] = {0b11111110, 0b00010111};

    // Act.
    protox::binary::bytes<13, 2, BYTE_LITTLE_ENDIAN, BIT_LITTLE_ENDIAN>::encode(bit_sink, value);

    // Assert.
    BOOST_CHECK_EQUAL(13, bit_sink.size());

    BOOST_CHECK_EQUAL(0b0111111111101, bit_sink.to_ulong());
}

BOOST_AUTO_TEST_CASE(test_encode_13_bit_little_endian_value_as_big_endian_bitset) {

    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    //                                 LSB         MSB
    const unsigned char value[2] = {0b11111110, 0b00010111};

    // Act.
    protox::binary::bytes<13, 2, BYTE_LITTLE_ENDIAN, BIT_BIG_ENDIAN>::encode(bit_sink, value);

    // Assert.
    BOOST_CHECK_EQUAL(13, bit_sink.size());

    BOOST_CHECK_EQUAL(0b1011111111110, bit_sink.to_ulong());
}

BOOST_AUTO_TEST_CASE(test_encode_13_bit_big_endian_value_as_little_endian_bitset) {

    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    //                                 MSB         LSB
    const unsigned char value[2] = {0b00010100, 0b00010111};

    // Act.
    protox::binary::bytes<13, 2, BYTE_BIG_ENDIAN, BIT_LITTLE_ENDIAN>::encode(bit_sink, value);

    // Assert.
    BOOST_CHECK_EQUAL(13, bit_sink.size());

    BOOST_CHECK_EQUAL(0b1110100000101, bit_sink.to_ulong());
}

BOOST_AUTO_TEST_CASE(test_encode_13_bit_big_endian_value_as_big_endian_bitset) {

    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    //                                 MSB         LSB
    const unsigned char value[2] = {0b00010100, 0b00010111};

    // Act.
    protox::binary::bytes<13, 2, BYTE_BIG_ENDIAN, BIT_BIG_ENDIAN>::encode(bit_sink, value);

    // Assert.
    BOOST_CHECK_EQUAL(13, bit_sink.size());

    BOOST_CHECK_EQUAL(0b0001010000010111, bit_sink.to_ulong());
}

/******************************************************************************************************************************************/

}

/******************************************************************************************************************************************/
