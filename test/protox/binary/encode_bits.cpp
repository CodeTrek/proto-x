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

namespace test_binary_encode_bits {

/******************************************************************************************************************************************/

template<const unsigned int NUM_BITS, protox::binary::BitEndian VE> struct bit_value {
	static void test() {
		const unsigned short MAX_VALUE = std::pow(2, NUM_BITS) - 1;

		for (unsigned short value = 0; value <= MAX_VALUE; ++value) {
			boost::dynamic_bitset<> result;
			protox::binary::bits<boost::dynamic_bitset<>, VE, NUM_BITS>::encode(result, (const unsigned char) value);

			BOOST_CHECK_EQUAL(NUM_BITS, result.size());

			if (VE == protox::binary::BIT_LITTLE_ENDIAN) {
				BOOST_CHECK_EQUAL(
						protox::binary::util::reverse(NUM_BITS, value).to_ulong(),
						result.to_ulong());
			} else {
				BOOST_CHECK_EQUAL(value, result.to_ulong());
			}
		}
	}
};

BOOST_AUTO_TEST_CASE(test_encode_1_bit_values_little_endian) {
	bit_value<1, protox::binary::BIT_LITTLE_ENDIAN>::test();
}

BOOST_AUTO_TEST_CASE(test_encode_2_bit_values_little_endian) {
	bit_value<2, protox::binary::BIT_LITTLE_ENDIAN>::test();
}

BOOST_AUTO_TEST_CASE(test_encode_3_bit_values_little_endian) {
	bit_value<3, protox::binary::BIT_LITTLE_ENDIAN>::test();
}

BOOST_AUTO_TEST_CASE(test_encode_4_bit_values_little_endian) {
	bit_value<4, protox::binary::BIT_LITTLE_ENDIAN>::test();
}

BOOST_AUTO_TEST_CASE(test_encode_5_bit_values_little_endian) {
	bit_value<5, protox::binary::BIT_LITTLE_ENDIAN>::test();
}

BOOST_AUTO_TEST_CASE(test_encode_6_bit_values_little_endian) {
	bit_value<6, protox::binary::BIT_LITTLE_ENDIAN>::test();
}

BOOST_AUTO_TEST_CASE(test_encode_7_bit_values_little_endian) {
	bit_value<7, protox::binary::BIT_LITTLE_ENDIAN>::test();
}

BOOST_AUTO_TEST_CASE(test_encode_8_bit_values_little_endian) {
	bit_value<8, protox::binary::BIT_LITTLE_ENDIAN>::test();
}

BOOST_AUTO_TEST_CASE(test_encode_1_bit_values_big_endian) {
	bit_value<1, protox::binary::BIT_BIG_ENDIAN>::test();
}

BOOST_AUTO_TEST_CASE(test_encode_2_bit_values_big_endian) {
	bit_value<2, protox::binary::BIT_BIG_ENDIAN>::test();
}

BOOST_AUTO_TEST_CASE(test_encode_3_bit_values_big_endian) {
	bit_value<3, protox::binary::BIT_BIG_ENDIAN>::test();
}

BOOST_AUTO_TEST_CASE(test_encode_4_bit_values_big_endian) {
	bit_value<4, protox::binary::BIT_BIG_ENDIAN>::test();
}

BOOST_AUTO_TEST_CASE(test_encode_5_bit_values_big_endian) {
	bit_value<5, protox::binary::BIT_BIG_ENDIAN>::test();
}

BOOST_AUTO_TEST_CASE(test_encode_6_bit_values_big_endian) {
	bit_value<6, protox::binary::BIT_BIG_ENDIAN>::test();
}

BOOST_AUTO_TEST_CASE(test_encode_7_bit_values_big_endian) {
	bit_value<7, protox::binary::BIT_BIG_ENDIAN>::test();
}

BOOST_AUTO_TEST_CASE(test_encode_8_bit_values_big_endian) {
	bit_value<8, protox::binary::BIT_BIG_ENDIAN>::test();
}

/******************************************************************************************************************************************/

}

/******************************************************************************************************************************************/
