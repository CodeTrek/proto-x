/******************************************************************************************************************************************/

#include <cmath>

#include <boost/test/unit_test.hpp>
#include <boost/dynamic_bitset.hpp>

#include <protox/binary/sign_bit.hpp>

/******************************************************************************************************************************************/

namespace test_propagate_sign_bit {

/******************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_be_byte_order_signed_3_bit_negative_value) {
    // Arrange.
    //                                  MSB         LSB
    unsigned char encoded_value[] = {0b00000000, 0b00000110}; // -2

	// Act.
	protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_BIG_ENDIAN>::propagate(encoded_value, 3, 2);

	// Assert.
	unsigned char le_encoded_value[] = {encoded_value[1], encoded_value[0]};
	BOOST_CHECK_EQUAL(-2, *((short *) le_encoded_value));
}

BOOST_AUTO_TEST_CASE(test_be_byte_order_signed_3_bit_positive_value) {
    // Arrange.
    //                                  MSB         LSB
    unsigned char encoded_value[] = {0b00000000, 0b00000010}; // 2

	// Act.
	protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_BIG_ENDIAN>::propagate(encoded_value, 3, 2);

	// Assert.
	unsigned char le_encoded_value[] = {encoded_value[1], encoded_value[0]};
	BOOST_CHECK_EQUAL(2, *((short *) le_encoded_value));
}


BOOST_AUTO_TEST_CASE(test_le_byte_order_signed_3_bit_negative_value) {
    // Arrange.
    //                                  LSB         MSB
    unsigned char encoded_value[] = {0b00000110, 0b00000000}; // -2

	// Act.
	protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_LITTLE_ENDIAN>::propagate(encoded_value, 3, 2);

	// Assert.
	BOOST_CHECK_EQUAL(-2, *((short *) encoded_value));
}

BOOST_AUTO_TEST_CASE(test_le_byte_order_signed_3_bit_positive_value) {
    // Arrange.
    //                                  LSB         MSB
    unsigned char encoded_value[] = {0b00000010, 0b00000000}; // 2

	// Act.
	protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_LITTLE_ENDIAN>::propagate(encoded_value, 3, 2);

	// Assert.
	BOOST_CHECK_EQUAL(2, *((short *) encoded_value));
}

BOOST_AUTO_TEST_CASE(test_be_byte_order_signed_9_bit_negative_value) {
    // Arrange.
    //                                  MSB                                 LSB
    unsigned char encoded_value[] = {0b00000000, 0b00000000, 0b00000001, 0b11111010}; // -6

	// Act.
	protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_BIG_ENDIAN>::propagate(encoded_value, 9, 4);

	// Assert.
	unsigned char le_encoded_value[] = {encoded_value[3], encoded_value[2], encoded_value[1], encoded_value[0]};
	BOOST_CHECK_EQUAL(-6, *((int *) le_encoded_value));
}

BOOST_AUTO_TEST_CASE(test_be_byte_order_signed_9_bit_positive_value) {
    // Arrange.
    //                                  MSB                                 LSB
    unsigned char encoded_value[] = {0b00000000, 0b00000000, 0b00000000, 0b00000110}; // 6

	// Act.
	protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_BIG_ENDIAN>::propagate(encoded_value, 9, 4);

	// Assert.
	unsigned char le_encoded_value[] = {encoded_value[3], encoded_value[2], encoded_value[1], encoded_value[0]};
	BOOST_CHECK_EQUAL(6, *((int *) le_encoded_value));
}

BOOST_AUTO_TEST_CASE(test_le_byte_order_signed_9_bit_negative_value) {
    // Arrange.
    //                                  LSB                                 MSB
    unsigned char encoded_value[] = {0b11111010, 0b00000001, 0b00000000, 0b00000000}; // -6

	// Act.
	protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_LITTLE_ENDIAN>::propagate(encoded_value, 9, 4);

	// Assert.
	BOOST_CHECK_EQUAL(-6, *((int *) encoded_value));
}

BOOST_AUTO_TEST_CASE(test_le_byte_order_signed_9_bit_positive_value) {
    // Arrange.
    //                                  LSB                                 MSB
    unsigned char encoded_value[] = {0b00000110, 0b00000000, 0b00000000, 0b00000000}; // -6

	// Act.
	protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_LITTLE_ENDIAN>::propagate(encoded_value, 9, 4);

	// Assert.
	BOOST_CHECK_EQUAL(6, *((int *) encoded_value));
}

BOOST_AUTO_TEST_CASE(test_be_byte_order_signed_24_bit_negative_value) {
    // Arrange.
    //                                  MSB                                 LSB
    unsigned char encoded_value[] = {0b00000000, 0b00001111, 0b11111100, 0b00000001}; // -1023

	// Act.
	protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_BIG_ENDIAN>::propagate(encoded_value, 20, 4);

	// Assert.
	unsigned char le_encoded_value[] = {encoded_value[3], encoded_value[2], encoded_value[1], encoded_value[0]};
	BOOST_CHECK_EQUAL(-1023, *((int *) le_encoded_value));
}

BOOST_AUTO_TEST_CASE(test_be_byte_order_signed_24_bit_positive_value) {
    // Arrange.
    //                                  MSB                                 LSB
    unsigned char encoded_value[] = {0b00000000, 0b00000000, 0b00000011, 0b11111111}; // 1023

	// Act.
	protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_BIG_ENDIAN>::propagate(encoded_value, 20, 4);

	// Assert.
	unsigned char le_encoded_value[] = {encoded_value[3], encoded_value[2], encoded_value[1], encoded_value[0]};
	BOOST_CHECK_EQUAL(1023, *((int *) le_encoded_value));
}

BOOST_AUTO_TEST_CASE(test_le_byte_order_signed_24_bit_negative_value) {
    // Arrange.
    //                                  LSB                                 MSB
    unsigned char encoded_value[] = {0b00000001, 0b11111100, 0b00001111, 0b00000000}; // -1023

	// Act.
	protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_LITTLE_ENDIAN>::propagate(encoded_value, 20, 4);

	// Assert.
	BOOST_CHECK_EQUAL(-1023, *((int *) encoded_value));
}

BOOST_AUTO_TEST_CASE(test_le_byte_order_signed_24_bit_positive_value) {
    // Arrange.
    //                                  LSB                                 MSB
    unsigned char encoded_value[] = {0b11111111, 0b00000011, 0b00000000, 0b00000000}; // 1023

	// Act.
	protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_LITTLE_ENDIAN>::propagate(encoded_value, 20, 4);

	// Assert.
	BOOST_CHECK_EQUAL(1023, *((int *) encoded_value));
}

BOOST_AUTO_TEST_CASE(test_be_signed_3_bit_value_is_negative) {
    // Arrange.
    //                                  MSB
    unsigned char encoded_value[] = {0b00000111}; // -1

	// Act.
	const bool result = protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_BIG_ENDIAN>::is_negative_value(encoded_value, 3, 1);

	// Assert.
	BOOST_CHECK_EQUAL(true, result);
}

BOOST_AUTO_TEST_CASE(test_be_signed_3_bit_value_is_positive) {
    // Arrange.
    //                                  MSB
    unsigned char encoded_value[] = {0b00000011}; // 3

	// Act.
	const bool result = protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_BIG_ENDIAN>::is_negative_value(encoded_value, 3, 1);

	// Assert.
	BOOST_CHECK_EQUAL(false, result);
}

BOOST_AUTO_TEST_CASE(test_be_signed_3_bit_value_is_negative_in_4_byte_value) {
    // Arrange.
    //                                  MSB                                 LSB
    unsigned char encoded_value[] = {0b00000000, 0b00000000, 0b00000000, 0b00000111}; // -1

	// Act.
	const bool result = protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_BIG_ENDIAN>::is_negative_value(encoded_value, 3, 4);

	// Assert.
	BOOST_CHECK_EQUAL(true, result);
}

BOOST_AUTO_TEST_CASE(test_be_signed_3_bit_value_is_positive_in_4_byte_value) {
    // Arrange.
    //                                  MSB                                 LSB
    unsigned char encoded_value[] = {0b00000000, 0b00000000, 0b00000000, 0b00000011}; // 3

	// Act.
	const bool result = protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_BIG_ENDIAN>::is_negative_value(encoded_value, 3, 4);

	// Assert.
	BOOST_CHECK_EQUAL(false, result);
}

BOOST_AUTO_TEST_CASE(test_le_signed_3_bit_value_is_negative) {
    // Arrange.
    //                                  MSB
    unsigned char encoded_value[] = {0b00000111}; // -1

	// Act.
	const bool result = protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_LITTLE_ENDIAN>::is_negative_value(encoded_value, 3, 1);

	// Assert.
	BOOST_CHECK_EQUAL(true, result);
}

BOOST_AUTO_TEST_CASE(test_le_signed_3_bit_value_is_positive) {
    // Arrange.
    //                                  MSB
    unsigned char encoded_value[] = {0b00000011}; // 3

	// Act.
	const bool result = protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_LITTLE_ENDIAN>::is_negative_value(encoded_value, 3, 1);

	// Assert.
	BOOST_CHECK_EQUAL(false, result);
}

BOOST_AUTO_TEST_CASE(test_le_signed_3_bit_value_is_negative_in_4_byte_value) {
    // Arrange.
    //                                  LSB                                 MSB
    unsigned char encoded_value[] = {0b00000111, 0b00000000, 0b00000000, 0b00000000}; // -1

	// Act.
	const bool result = protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_LITTLE_ENDIAN>::is_negative_value(encoded_value, 3, 4);

	// Assert.
	BOOST_CHECK_EQUAL(true, result);
}

BOOST_AUTO_TEST_CASE(test_le_signed_3_bit_value_is_positive_in_4_byte_value) {
    // Arrange.
    //                                  LSB                                 MSB
    unsigned char encoded_value[] = {0b00000011, 0b00000000, 0b00000000, 0b00000000}; // 3

	// Act.
	const bool result = protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_BIG_ENDIAN>::is_negative_value(encoded_value, 3, 4);

	// Assert.
	BOOST_CHECK_EQUAL(false, result);
}

BOOST_AUTO_TEST_CASE(test_be_signed_20_bit_value_is_negative) {
    // Arrange.
    //                                  MSB                                 LSB
    unsigned char encoded_value[] = {0b00000000, 0b00001000, 0b00000000, 0b00000000}; //

	// Act.
	const bool result = protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_BIG_ENDIAN>::is_negative_value(encoded_value, 20, 4);

	// Assert.
	BOOST_CHECK_EQUAL(true, result);
}

BOOST_AUTO_TEST_CASE(test_be_signed_20_bit_value_is_positive) {
    // Arrange.
    //                                  MSB                                 LSB
    unsigned char encoded_value[] = {0b00000000, 0b00000100, 0b00000000, 0b00000000}; //

	// Act.
	const bool result = protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_BIG_ENDIAN>::is_negative_value(encoded_value, 20, 4);

	// Assert.
	BOOST_CHECK_EQUAL(false, result);
}

BOOST_AUTO_TEST_CASE(test_le_signed_20_bit_value_is_negative) {
    // Arrange.
    //                                  LSB                                 MSB
    unsigned char encoded_value[] = {0b00000000, 0b00000000, 0b00001000, 0b00000000}; //

	// Act.
	const bool result = protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_LITTLE_ENDIAN>::is_negative_value(encoded_value, 20, 4);

	// Assert.
	BOOST_CHECK_EQUAL(true, result);
}

BOOST_AUTO_TEST_CASE(test_le_signed_20_bit_value_is_positive) {
    // Arrange.
    //                                  LSB                                 MSB
    unsigned char encoded_value[] = {0b00000000, 0b00000000, 0b00000100, 0b00000000}; //

	// Act.
	const bool result = protox::binary::sign_bit<protox::binary::ByteEndian::BYTE_LITTLE_ENDIAN>::is_negative_value(encoded_value, 20, 4);

	// Assert.
	BOOST_CHECK_EQUAL(false, result);
}


/******************************************************************************************************************************************/

}

/******************************************************************************************************************************************/
