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
#include <protox/bee/basic_data_encoders.hpp>

#include <protox/platform.hpp>

/**********************************************************************************************************************/

namespace test_bee_encode_bytes {

using namespace boost;
using namespace protox::dtl;
using namespace protox::bee;

BOOST_AUTO_TEST_CASE(test_encode_2_byte_little_endian_value_as_little_endian_bitset) {

    // Arrange.
    boost::dynamic_bitset<> bit_sink;
    // const unsigned char v[2] = {0b00110011, 0b00011101};
    const unsigned short value = 2118;

    // Act.
    protox::bee::encode_bytes<boost::dynamic_bitset<>, 16, 2, true, true>::pack(bit_sink, (const unsigned char *)&value);

    // Assert.
    BOOST_CHECK_EQUAL(16, bit_sink.size());

    BOOST_CHECK_EQUAL(0, bit_sink[15]);

    BOOST_CHECK_EQUAL(1, bit_sink[14]);
    BOOST_CHECK_EQUAL(1, bit_sink[13]);
    BOOST_CHECK_EQUAL(0, bit_sink[12]);
    BOOST_CHECK_EQUAL(0, bit_sink[11]);
    BOOST_CHECK_EQUAL(0, bit_sink[10]);
    BOOST_CHECK_EQUAL(1, bit_sink[ 9]);
    BOOST_CHECK_EQUAL(0, bit_sink[ 8]);

    BOOST_CHECK_EQUAL(0, bit_sink[ 7]);
    BOOST_CHECK_EQUAL(0, bit_sink[ 6]);
    BOOST_CHECK_EQUAL(0, bit_sink[ 5]);
    BOOST_CHECK_EQUAL(1, bit_sink[ 4]);
    BOOST_CHECK_EQUAL(0, bit_sink[ 3]);
    BOOST_CHECK_EQUAL(0, bit_sink[ 2]);
    BOOST_CHECK_EQUAL(0, bit_sink[ 1]);
    BOOST_CHECK_EQUAL(0, bit_sink[ 0]);


}

}
