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

namespace test_binary_decode_bytes {

using namespace protox::binary;

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_decode_1_bit_value_of_1) {
    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    bit_sink.push_back(1);
    unsigned char value = 0b00000000;
    std::size_t offset = 0;

    // Act.
    protox::binary::bytes<1, 1, BYTE_LITTLE_ENDIAN, BIT_LITTLE_ENDIAN>::decode(bit_sink, &value, offset);

    // Assert.
    BOOST_CHECK_EQUAL(1, offset);
    BOOST_CHECK_EQUAL(0b00000001, value);
}

BOOST_AUTO_TEST_CASE(test_decode_1_bit_value_of_0) {
    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    bit_sink.push_back(0);
    unsigned char value = 0b11111111;
    std::size_t offset = 0;

    // Act.
    protox::binary::bytes<1, 1, BYTE_LITTLE_ENDIAN, BIT_LITTLE_ENDIAN>::decode(bit_sink, &value, offset);

    // Assert.
    BOOST_CHECK_EQUAL(1, offset);
    BOOST_CHECK_EQUAL(0b00000000, value);
}

BOOST_AUTO_TEST_CASE(test_decode_3_bit_value_from_little_endian_bitset) {
    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    unsigned char value = 0b00000000;
    std::size_t offset = 0;

    // Act.
    protox::binary::bytes<3, 1, BYTE_LITTLE_ENDIAN, BIT_LITTLE_ENDIAN>::decode(bit_sink, &value, offset);

    // Assert.
    BOOST_CHECK_EQUAL(3, offset);
    BOOST_CHECK_EQUAL(0b00000001, value);
}

BOOST_AUTO_TEST_CASE(test_decode_3_bit_value_from_big_endian_bitset) {
    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    unsigned char value = 0b00000000;
    std::size_t offset = 0;

    // Act.
    protox::binary::bytes<3, 1, BYTE_LITTLE_ENDIAN, BIT_BIG_ENDIAN>::decode(bit_sink, &value, offset);

    // Assert.
    BOOST_CHECK_EQUAL(3, offset);
    BOOST_CHECK_EQUAL(0b00000100, value);
}

BOOST_AUTO_TEST_CASE(test_decode_8_bit_value_from_little_endian_bitset) {
    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    unsigned char value = 0b00000000;
    std::size_t offset = 0;

    // Act.
    protox::binary::bytes<8, 1, BYTE_LITTLE_ENDIAN, BIT_LITTLE_ENDIAN>::decode(bit_sink, &value, offset);

    // Assert.
    BOOST_CHECK_EQUAL(8, offset);
    BOOST_CHECK_EQUAL(0b10001011, value);
}

BOOST_AUTO_TEST_CASE(test_decode_8_bit_value_from_big_endian_bitset) {
    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    unsigned char value = 0b00000000;
    std::size_t offset = 0;

    // Act.
    protox::binary::bytes<8, 1, BYTE_LITTLE_ENDIAN, BIT_BIG_ENDIAN>::decode(bit_sink, &value, offset);

    // Assert.
    BOOST_CHECK_EQUAL(8, offset);
    BOOST_CHECK_EQUAL(0b11010001, value);
}

BOOST_AUTO_TEST_CASE(test_decode_16_bit_little_endian_value_from_little_endian_bitset) {

    // Arrange.
    boost::dynamic_bitset<> bit_sink;

    // MSB
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(1);

    // LSB
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(0);

    unsigned char value[2] = {0b00000000, 0b00000000};
    std::size_t offset = 0;

    // Act.
    protox::binary::bytes<16, 2, BYTE_LITTLE_ENDIAN, BIT_LITTLE_ENDIAN>::decode(bit_sink, value, offset);

    // Assert.
    BOOST_CHECK_EQUAL(16, offset);
    BOOST_CHECK_EQUAL(0b11001100, value[0]);
    BOOST_CHECK_EQUAL(0b10111001, value[1]);
}

BOOST_AUTO_TEST_CASE(test_decode_13_bit_little_endian_value_from_little_endian_bitset) {

    // Arrange.
    boost::dynamic_bitset<> bit_sink;

    // MSB.
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(1);

    // LSB
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(0);

    unsigned char value[2] = {0b00000000, 0b00000000};
    std::size_t offset = 0;

    // Act.
    protox::binary::bytes<13, 2, BYTE_LITTLE_ENDIAN, BIT_LITTLE_ENDIAN>::decode(bit_sink, value, offset);

    // Assert.
    BOOST_CHECK_EQUAL(13, offset);
    BOOST_CHECK_EQUAL(0b11111110, value[0]);
    BOOST_CHECK_EQUAL(0b00010111, value[1]);
}

BOOST_AUTO_TEST_CASE(test_decode_19_bit_little_endian_value_from_little_endian_bitset) {

    // Arrange.
    boost::dynamic_bitset<> bit_sink;

    // MSB.
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(0);

    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(0);

    // LSB
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(0);

    unsigned char value[3] = {0b00000000, 0b00000000, 0b00000000};
    std::size_t offset = 0;

    // Act.
    protox::binary::bytes<19, 3, BYTE_LITTLE_ENDIAN, BIT_LITTLE_ENDIAN>::decode(bit_sink, value, offset);

    // Assert.
    BOOST_CHECK_EQUAL(19, offset);
    BOOST_CHECK_EQUAL(0b11011110, value[0]);
    BOOST_CHECK_EQUAL(0b10111100, value[1]);
    BOOST_CHECK_EQUAL(0b00000110, value[2]);
}

BOOST_AUTO_TEST_CASE(test_decode_13_bit_little_endian_value_from_big_endian_bitset) {

    // Arrange.
    boost::dynamic_bitset<> bit_sink;

    // LSB.
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);

    // MSB
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(1);

    unsigned char value[2] = {0b00000000, 0b00000000};
    std::size_t offset = 0;

    // Act.
    protox::binary::bytes<13, 2, BYTE_LITTLE_ENDIAN, BIT_BIG_ENDIAN>::decode(bit_sink, value, offset);

    // Assert.
    BOOST_CHECK_EQUAL(13, offset);
    BOOST_CHECK_EQUAL(0b00011101, value[0]);
    BOOST_CHECK_EQUAL(0b00011101, value[1]);
}

BOOST_AUTO_TEST_CASE(test_decode_19_bit_little_endian_value_from_big_endian_bitset) {

    // Arrange.
    boost::dynamic_bitset<> bit_sink;

    // LSB.
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(0);

    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(0);

    // MSB
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(1);

    unsigned char value[3] = {0b00000000, 0b00000000, 0b00000000};
    std::size_t offset = 0;

    // Act.
    protox::binary::bytes<19, 3, BYTE_LITTLE_ENDIAN, BIT_BIG_ENDIAN>::decode(bit_sink, value, offset);

    // Assert.
    BOOST_CHECK_EQUAL(19, offset);
    BOOST_CHECK_EQUAL(0b01011101, value[0]);
    BOOST_CHECK_EQUAL(0b00110101, value[1]);
    BOOST_CHECK_EQUAL(0b00000110, value[2]);
}

BOOST_AUTO_TEST_CASE(test_decode_13_bit_big_endian_value_from_little_endian_bitset) {

    // Arrange.
    boost::dynamic_bitset<> bit_sink;

    // MSB.
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(0);

    // LSB
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(0);

    unsigned char value[2] = {0b00000000, 0b00000000};
    std::size_t offset = 0;

    // Act.
    protox::binary::bytes<13, 2, BYTE_BIG_ENDIAN, BIT_LITTLE_ENDIAN>::decode(bit_sink, value, offset);

    // Assert.
    BOOST_CHECK_EQUAL(13, offset);
    BOOST_CHECK_EQUAL(0b00010100, value[0]);
    BOOST_CHECK_EQUAL(0b10110100, value[1]);
}

BOOST_AUTO_TEST_CASE(test_decode_19_bit_big_endian_value_from_little_endian_bitset) {

    // Arrange.
    boost::dynamic_bitset<> bit_sink;

    // MSB.
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(0);

    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(0);

    // LSB
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(1);

    unsigned char value[3] = {0b00000000, 0b00000000, 0b00000000};
    std::size_t offset = 0;

    // Act.
    protox::binary::bytes<19, 3, BYTE_BIG_ENDIAN, BIT_LITTLE_ENDIAN>::decode(bit_sink, value, offset);

    // Assert.
    BOOST_CHECK_EQUAL(19, offset);
    BOOST_CHECK_EQUAL(0b00000100, value[0]);
    BOOST_CHECK_EQUAL(0b11010010, value[1]);
    BOOST_CHECK_EQUAL(0b11110101, value[2]);
}

BOOST_AUTO_TEST_CASE(test_decode_13_bit_big_endian_value_from_big_endian_bitset) {

    // Arrange.
    boost::dynamic_bitset<> bit_sink;

    // LSB.
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(0);

    // MSB
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(1);

    unsigned char value[2] = {0b00000000, 0b00000000};
    std::size_t offset = 0;

    // Act.
    protox::binary::bytes<13, 2, BYTE_BIG_ENDIAN, BIT_BIG_ENDIAN>::decode(bit_sink, value, offset);

    // Assert.
    BOOST_CHECK_EQUAL(13, offset);
    BOOST_CHECK_EQUAL(0b00010011, value[0]);
    BOOST_CHECK_EQUAL(0b01000101, value[1]);
}

BOOST_AUTO_TEST_CASE(test_decode_19_bit_big_endian_value_from_big_endian_bitset) {

    // Arrange.
    boost::dynamic_bitset<> bit_sink;

    // LSB.
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(0);

    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(1);
    bit_sink.push_back(1);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(1);

    // MSB
    bit_sink.push_back(0);
    bit_sink.push_back(0);
    bit_sink.push_back(1);

    unsigned char value[3] = {0b00000000, 0b00000000, 0b00000000};
    std::size_t offset = 0;

    // Act.
    protox::binary::bytes<19, 3, BYTE_BIG_ENDIAN, BIT_BIG_ENDIAN>::decode(bit_sink, value, offset);

    // Assert.
    BOOST_CHECK_EQUAL(19, offset);
    BOOST_CHECK_EQUAL(0b00000100, value[0]);
    BOOST_CHECK_EQUAL(0b10001101, value[1]);
    BOOST_CHECK_EQUAL(0b01000101, value[2]);
}

/******************************************************************************************************************************************/

}

/******************************************************************************************************************************************/
