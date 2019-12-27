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

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_encode_1_bit_1_byte_value_true) {
    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    const unsigned char value = 0b00000001;

    // Act.
    protox::binary::bytes<boost::dynamic_bitset<>, 1, 1, true, true>::encode(bit_sink, (const unsigned char *)&value);

    // Assert.
    BOOST_CHECK_EQUAL(1, bit_sink.size());
    BOOST_CHECK_EQUAL(1, bit_sink[0]);
}

BOOST_AUTO_TEST_CASE(test_encode_1_bit_1_byte_value_false) {
    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    const unsigned char value = 0b00000000;

    // Act.
    protox::binary::bytes<boost::dynamic_bitset<>, 1, 1, true, true>::encode(bit_sink, (const unsigned char *)&value);

    // Assert.
    BOOST_CHECK_EQUAL(1, bit_sink.size());
    BOOST_CHECK_EQUAL(0, bit_sink[0]);
}

BOOST_AUTO_TEST_CASE(test_encode_3_bits_1_byte_value_le) {
    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    const unsigned char value = 0b00000001;

    // Act.
    protox::binary::bytes<boost::dynamic_bitset<>, 3, 1, true, true>::encode(bit_sink, (const unsigned char *)&value);

    // Assert.
    BOOST_CHECK_EQUAL(3, bit_sink.size());
    BOOST_CHECK_EQUAL(1, bit_sink[2]);
    BOOST_CHECK_EQUAL(0, bit_sink[1]);
    BOOST_CHECK_EQUAL(0, bit_sink[0]);
}

BOOST_AUTO_TEST_CASE(test_encode_3_bits_1_byte_value_be) {
    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    const unsigned char value = 0b00000001;

    // Act.
    protox::binary::bytes<boost::dynamic_bitset<>, 3, 1, true, false>::encode(bit_sink, (const unsigned char *)&value);

    // Assert.
    BOOST_CHECK_EQUAL(3, bit_sink.size());
    BOOST_CHECK_EQUAL(0, bit_sink[2]);
    BOOST_CHECK_EQUAL(0, bit_sink[1]);
    BOOST_CHECK_EQUAL(1, bit_sink[0]);
}

BOOST_AUTO_TEST_CASE(test_encode_8_bit_1_byte_value_le) {
    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    const unsigned char value = 0b00110011;

    // Act.
    protox::binary::bytes<boost::dynamic_bitset<>, 8, 1, true, true>::encode(bit_sink, (const unsigned char *)&value);

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

BOOST_AUTO_TEST_CASE(test_encode_8_bit_1_byte_value_be) {
    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    const unsigned char value = 0b00110011;

    // Act.
    protox::binary::bytes<boost::dynamic_bitset<>, 8, 1, true, false>::encode(bit_sink, (const unsigned char *)&value);

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

/******************************************************************************************************************************************/

}

/******************************************************************************************************************************************/
