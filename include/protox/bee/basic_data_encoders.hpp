/******************************************************************************************************************************************/
// (c) 2009 - 2019 Jay Graham
//
// Distributed under the MIT License
// (see accompanying file LICENSE_1_0_0.txt or http://www.opensource.org/licenses/mit-license.php)
/******************************************************************************************************************************************/

#ifndef PROTOX_BEE_ENCODERS_HPP
#define PROTOX_BEE_ENCODERS_HPP

/******************************************************************************************************************************************/

#include <assert.h>
#include <boost/static_assert.hpp>

/******************************************************************************************************************************************/

namespace protox {
namespace bee {

/******************************************************************************************************************************************/

/**
 * Encode the bits in the given value from least to most significant bit.
 * The least significant bit is located at bit position 0.
 *
 * @param s the bit-addressable destination buffer.
 * @param value the value to be encoded.
 * @param num_bits the number of bits to encode in the range > 1 and <= 8.
 */
template<typename S>
void encode_value(S &s, const unsigned char value, const unsigned num_bits) {
    assert(num_bits > 0);
    assert(num_bits <= 8);

    static const unsigned char ONE = 1;

    for (unsigned shift_count = 0; shift_count < num_bits; ++shift_count) {
        const bool bit_value = ((value & (ONE << shift_count)) > 0);
        s.push_back(bit_value);
    }
}

/******************************************************************************************************************************************/
/**
 * Generic encode basic template.
 */
template<typename S,               // The destination (bit-addressable) buffer.
        unsigned SIZE_IN_BITS,     // Size of value to be encoded in bits.
        std::size_t SIZE_IN_BYTES, // Size of value to be encoded in bytes.
        bool CONVERT_ENDIAN        // True, if endian conversion is required.
> struct encode_basic;

/******************************************************************************************************************************************/

template<typename S, unsigned SIZE_IN_BITS, bool CONVERT_ENDIAN>
struct encode_basic<S, SIZE_IN_BITS, 1, CONVERT_ENDIAN> {
    static inline void pack(S &s, unsigned char const *value) {
        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 0));
        BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 8));

        encode_value(s, *value, SIZE_IN_BITS);
    }
};

/******************************************************************************************************************************************/

template<typename S, unsigned SIZE_IN_BITS>
struct encode_basic<S, SIZE_IN_BITS, 2, false> {
    static inline void pack(S &s, unsigned char const *value) {
        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 8));
        BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 16));

        // Encode from least to most significant byte
        encode_value(s, value[1], 8);
        encode_value(s, value[0], SIZE_IN_BITS - 8);
    }
};

/******************************************************************************************************************************************/

template<typename S, unsigned SIZE_IN_BITS>
struct encode_basic<S, SIZE_IN_BITS, 3, false> {
    static inline void pack(S &s, unsigned char const *value) {
        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 16));
        BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 24));

        // Encode from least to most significant byte
        encode_value(s, value[2], 8);
        encode_value(s, value[1], 8);
        encode_value(s, value[0], SIZE_IN_BITS - 16);
    }
};

/******************************************************************************************************************************************/

template<typename S, unsigned SIZE_IN_BITS>
struct encode_basic<S, SIZE_IN_BITS, 4, false> {
    static inline void pack(S &s, unsigned char const *value) {
        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 24));
        BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 32));

        // Encode from least to most significant byte
        encode_value(s, value[3], 8);
        encode_value(s, value[2], 8);
        encode_value(s, value[1], 8);
        encode_value(s, value[0], SIZE_IN_BITS - 24);
    }
};

/******************************************************************************************************************************************/

template<typename S, unsigned SIZE_IN_BITS>
struct encode_basic<S, SIZE_IN_BITS, 2, true> {
    static inline void pack(S &s, unsigned char const *value) {
        unsigned char converted_value[2];

        converted_value[0] = value[1];
        converted_value[1] = value[0];

        encode_basic<S, SIZE_IN_BITS, 2, false>::pack(s, converted_value);
    }
};

/******************************************************************************************************************************************/

template<typename S, unsigned SIZE_IN_BITS>
struct encode_basic<S, SIZE_IN_BITS, 3, true> {
    static inline void pack(S &s, unsigned char const *value) {
        unsigned char converted_value[3];

        converted_value[0] = value[2];
        converted_value[1] = value[1];
        converted_value[2] = value[0];

        encode_basic<S, SIZE_IN_BITS, 3, false>::pack(s, converted_value);
    }
};

/******************************************************************************************************************************************/

template<typename S, unsigned SIZE_IN_BITS>
struct encode_basic<S, SIZE_IN_BITS, 4, true> {
    static inline void pack(S &s, unsigned char const *value) {
        unsigned char converted_value[4];

        converted_value[0] = value[3];
        converted_value[1] = value[2];
        converted_value[2] = value[1];
        converted_value[3] = value[0];

        encode_basic<S, SIZE_IN_BITS, 4, false>::pack(s, converted_value);
    }
};

/******************************************************************************************************************************************/

}
}

/******************************************************************************************************************************************/

#endif

/******************************************************************************************************************************************/
