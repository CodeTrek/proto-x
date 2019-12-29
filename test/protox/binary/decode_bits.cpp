/******************************************************************************************************************************************/
// (c) 2009 - 2019 Jay Graham
//
// Distributed under the MIT License
// (see accompanying file LICENSE_1_0_0.txt or http://www.opensource.org/licenses/mit-license.php)
/******************************************************************************************************************************************/

#include <cmath>

#include <boost/test/unit_test.hpp>
#include <boost/dynamic_bitset.hpp>

#include <protox/binary/bits.hpp>
#include <protox/binary/util.hpp>
#include <protox/binary/endian.hpp>

/******************************************************************************************************************************************/

namespace test_binary_decode_bits {

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_decode_1_bit_value_little_endian) {
	// Arrange.
	//  7 6 5 4 3 2 1 0
	// +-+-+-+-+-+-+-+-+
	// |              1|
	// +-+-+-+-+-+-+-+-+
	boost::dynamic_bitset<> encoded_value;
	encoded_value.push_back(1);

	unsigned char value = 0;
	std::size_t offset = 0;

	// Act.
	protox::binary::bits<protox::binary::BIT_LITTLE_ENDIAN, 1>::decode(encoded_value, value, offset);

	// Assert.
	BOOST_CHECK_EQUAL(1, value);
	BOOST_CHECK_EQUAL(1, offset);
}

BOOST_AUTO_TEST_CASE(test_decode_1_bit_value_big_endian) {
	// Arrange.
	//  7 6 5 4 3 2 1 0
	// +-+-+-+-+-+-+-+-+
	// |              1|
	// +-+-+-+-+-+-+-+-+
	boost::dynamic_bitset<> encoded_value;
	encoded_value.push_back(1);

	unsigned char value = 0;
	std::size_t offset = 0;

	// Act.
	protox::binary::bits<protox::binary::BIT_BIG_ENDIAN, 1>::decode(encoded_value, value, offset);

	// Assert.
	BOOST_CHECK_EQUAL(1, value);
	BOOST_CHECK_EQUAL(1, offset);
}

BOOST_AUTO_TEST_CASE(test_decode_2_bit_value_little_endian) {
	// Arrange.
	//  7 6 5 4 3 2 1 0
	// +-+-+-+-+-+-+-+-+
	// |            0 1|
	// +-+-+-+-+-+-+-+-+
	boost::dynamic_bitset<> encoded_value;
	encoded_value.push_back(1);
	encoded_value.push_back(0); // decimal 2.

	unsigned char value = 0;
	std::size_t offset = 0;

	// Act.
	protox::binary::bits<protox::binary::BIT_LITTLE_ENDIAN, 2>::decode(encoded_value, value, offset);

	// Assert.
	BOOST_CHECK_EQUAL(2, value);
	BOOST_CHECK_EQUAL(2, offset);
}

BOOST_AUTO_TEST_CASE(test_decode_2_bit_value_big_endian) {
	// Arrange.
	//  7 6 5 4 3 2 1 0
	// +-+-+-+-+-+-+-+-+
	// |            1 0|
	// +-+-+-+-+-+-+-+-+
	boost::dynamic_bitset<> encoded_value;
	encoded_value.push_back(0);
	encoded_value.push_back(1); // decimal 2.

	unsigned char value = 0;
	std::size_t offset = 0;

	// Act.
	protox::binary::bits<protox::binary::BIT_BIG_ENDIAN, 2>::decode(encoded_value, value, offset);

	// Assert.
	BOOST_CHECK_EQUAL(2, value);
	BOOST_CHECK_EQUAL(2, offset);
}

BOOST_AUTO_TEST_CASE(test_decode_3_bit_value_little_endian) {
	// Arrange.
	//  7 6 5 4 3 2 1 0
	// +-+-+-+-+-+-+-+-+
	// |          0 0 1|
	// +-+-+-+-+-+-+-+-+
	boost::dynamic_bitset<> encoded_value;
	encoded_value.push_back(1);
	encoded_value.push_back(0);
	encoded_value.push_back(0); // decimal 4.

	unsigned char value = 0;
	std::size_t offset = 0;

	// Act.
	protox::binary::bits<protox::binary::BIT_LITTLE_ENDIAN, 3>::decode(encoded_value, value, offset);

	// Assert.
	BOOST_CHECK_EQUAL(4, value);
	BOOST_CHECK_EQUAL(3, offset);
}

BOOST_AUTO_TEST_CASE(test_decode_3_bit_value_big_endian) {
	// Arrange.
	//  7 6 5 4 3 2 1 0
	// +-+-+-+-+-+-+-+-+
	// |          1 0 0|
	// +-+-+-+-+-+-+-+-+
	boost::dynamic_bitset<> encoded_value;
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(1); // decimal 4.

	unsigned char value = 0;
	std::size_t offset = 0;

	// Act.
	protox::binary::bits<protox::binary::BIT_BIG_ENDIAN, 3>::decode(encoded_value, value, offset);

	// Assert.
	BOOST_CHECK_EQUAL(4, value);
	BOOST_CHECK_EQUAL(3, offset);
}

BOOST_AUTO_TEST_CASE(test_decode_4_bit_value_little_endian) {
	// Arrange.
	//  7 6 5 4 3 2 1 0
	// +-+-+-+-+-+-+-+-+
	// |        0 0 0 1|
	// +-+-+-+-+-+-+-+-+
	boost::dynamic_bitset<> encoded_value;
	encoded_value.push_back(1);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0); // decimal 8.

	unsigned char value = 0;
	std::size_t offset = 0;

	// Act.
	protox::binary::bits<protox::binary::BIT_LITTLE_ENDIAN, 4>::decode(encoded_value, value, offset);

	// Assert.
	BOOST_CHECK_EQUAL(8, value);
	BOOST_CHECK_EQUAL(4, offset);
}

BOOST_AUTO_TEST_CASE(test_decode_4_bit_value_big_endian) {
	// Arrange.
	//  7 6 5 4 3 2 1 0
	// +-+-+-+-+-+-+-+-+
	// |        1 0 0 0|
	// +-+-+-+-+-+-+-+-+
	boost::dynamic_bitset<> encoded_value;
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(1); // decimal 8.

	unsigned char value = 0;
	std::size_t offset = 0;

	// Act.
	protox::binary::bits<protox::binary::BIT_BIG_ENDIAN, 4>::decode(encoded_value, value, offset);

	// Assert.
	BOOST_CHECK_EQUAL(8, value);
	BOOST_CHECK_EQUAL(4, offset);
}

BOOST_AUTO_TEST_CASE(test_decode_5_bit_value_little_endian) {
	// Arrange.
	//  7 6 5 4 3 2 1 0
	// +-+-+-+-+-+-+-+-+
	// |      0 0 0 0 1|
	// +-+-+-+-+-+-+-+-+
	boost::dynamic_bitset<> encoded_value;
	encoded_value.push_back(1);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0); // decimal 16.

	unsigned char value = 0;
	std::size_t offset = 0;

	// Act.
	protox::binary::bits<protox::binary::BIT_LITTLE_ENDIAN, 5>::decode(encoded_value, value, offset);

	// Assert.
	BOOST_CHECK_EQUAL(16, value);
	BOOST_CHECK_EQUAL(5, offset);
}

BOOST_AUTO_TEST_CASE(test_decode_5_bit_value_big_endian) {
	// Arrange.
	//  7 6 5 4 3 2 1 0
	// +-+-+-+-+-+-+-+-+
	// |      1 0 0 0 0|
	// +-+-+-+-+-+-+-+-+
	boost::dynamic_bitset<> encoded_value;
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(1); // decimal 16.

	unsigned char value = 0;
	std::size_t offset = 0;

	// Act.
	protox::binary::bits<protox::binary::BIT_BIG_ENDIAN, 5>::decode(encoded_value, value, offset);

	// Assert.
	BOOST_CHECK_EQUAL(16, value);
	BOOST_CHECK_EQUAL(5, offset);
}

BOOST_AUTO_TEST_CASE(test_decode_6_bit_value_little_endian) {
	// Arrange.
	//  7 6 5 4 3 2 1 0
	// +-+-+-+-+-+-+-+-+
	// |    0 0 0 0 0 1|
	// +-+-+-+-+-+-+-+-+
	boost::dynamic_bitset<> encoded_value;
	encoded_value.push_back(1);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0); // decimal 32.

	unsigned char value = 0;
	std::size_t offset = 0;

	// Act.
	protox::binary::bits<protox::binary::BIT_LITTLE_ENDIAN, 6>::decode(encoded_value, value, offset);

	// Assert.
	BOOST_CHECK_EQUAL(32, value);
	BOOST_CHECK_EQUAL(6, offset);
}

BOOST_AUTO_TEST_CASE(test_decode_6_bit_value_big_endian) {
	// Arrange.
	//  7 6 5 4 3 2 1 0
	// +-+-+-+-+-+-+-+-+
	// |    1 0 0 0 0 0|
	// +-+-+-+-+-+-+-+-+
	boost::dynamic_bitset<> encoded_value;
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(1); // decimal 32.

	unsigned char value = 0;
	std::size_t offset = 0;

	// Act.
	protox::binary::bits<protox::binary::BIT_BIG_ENDIAN, 6>::decode(encoded_value, value, offset);

	// Assert.
	BOOST_CHECK_EQUAL(32, value);
	BOOST_CHECK_EQUAL(6, offset);
}

BOOST_AUTO_TEST_CASE(test_decode_7_bit_value_little_endian) {
	// Arrange.
	//  7 6 5 4 3 2 1 0
	// +-+-+-+-+-+-+-+-+
	// |  0 0 0 0 0 0 1|
	// +-+-+-+-+-+-+-+-+
	boost::dynamic_bitset<> encoded_value;
	encoded_value.push_back(1);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0); // decimal 64.

	unsigned char value = 0;
	std::size_t offset = 0;

	// Act.
	protox::binary::bits<protox::binary::BIT_LITTLE_ENDIAN, 7>::decode(encoded_value, value, offset);

	// Assert.
	BOOST_CHECK_EQUAL(64, value);
	BOOST_CHECK_EQUAL(7, offset);
}

BOOST_AUTO_TEST_CASE(test_decode_7_bit_value_big_endian) {
	// Arrange.
	//  7 6 5 4 3 2 1 0
	// +-+-+-+-+-+-+-+-+
	// |  1 0 0 0 0 0 0|
	// +-+-+-+-+-+-+-+-+
	boost::dynamic_bitset<> encoded_value;
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(1); // decimal 64.

	unsigned char value = 0;
	std::size_t offset = 0;

	// Act.
	protox::binary::bits<protox::binary::BIT_BIG_ENDIAN, 7>::decode(encoded_value, value, offset);

	// Assert.
	BOOST_CHECK_EQUAL(64, value);
	BOOST_CHECK_EQUAL(7, offset);
}

BOOST_AUTO_TEST_CASE(test_decode_8_bit_value_little_endian) {
	// Arrange.
	//  7 6 5 4 3 2 1 0
	// +-+-+-+-+-+-+-+-+
	// |0 0 0 0 0 0 0 1|
	// +-+-+-+-+-+-+-+-+
	boost::dynamic_bitset<> encoded_value;
	encoded_value.push_back(1);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0); // decimal 128.

	unsigned char value = 0;
	std::size_t offset = 0;

	// Act.
	protox::binary::bits<protox::binary::BIT_LITTLE_ENDIAN, 8>::decode(encoded_value, value, offset);

	// Assert.
	BOOST_CHECK_EQUAL(128, value);
	BOOST_CHECK_EQUAL(8, offset);
}

BOOST_AUTO_TEST_CASE(test_decode_8_bit_value_big_endian) {
	// Arrange.
	//  7 6 5 4 3 2 1 0
	// +-+-+-+-+-+-+-+-+
	// |1 0 0 0 0 0 0 0|
	// +-+-+-+-+-+-+-+-+
	boost::dynamic_bitset<> encoded_value;
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(0);
	encoded_value.push_back(1); // decimal 128.

	unsigned char value = 0;
	std::size_t offset = 0;

	// Act.
	protox::binary::bits<protox::binary::BIT_BIG_ENDIAN, 8>::decode(encoded_value, value, offset);

	// Assert.
	BOOST_CHECK_EQUAL(128, value);
	BOOST_CHECK_EQUAL(8, offset);
}

/******************************************************************************************************************************************/

}

/******************************************************************************************************************************************/
