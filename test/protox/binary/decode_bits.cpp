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

/******************************************************************************************************************************************/

namespace test_binary_decode_bits {

/******************************************************************************************************************************************/

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
	protox::binary::bits<boost::dynamic_bitset<>, true, 2>::decode(encoded_value, value, offset);

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
	protox::binary::bits<boost::dynamic_bitset<>, false, 2>::decode(encoded_value, value, offset);

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
	protox::binary::bits<boost::dynamic_bitset<>, true, 3>::decode(encoded_value, value, offset);

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
	protox::binary::bits<boost::dynamic_bitset<>, false, 3>::decode(encoded_value, value, offset);

	// Assert.
	BOOST_CHECK_EQUAL(4, value);
	BOOST_CHECK_EQUAL(3, offset);
}

/******************************************************************************************************************************************/

}

/******************************************************************************************************************************************/
