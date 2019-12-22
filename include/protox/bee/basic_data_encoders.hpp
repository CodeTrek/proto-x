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

/******************************************************************************************************************************************/
/**
 * Generic encode value template.
 */
template<typename S, // The destination (bit-addressable) buffer.
         bool LE     // If true, encode the bits from least to most significant bit, else encode
                     // from most to least significant bit.
> struct encode_bits;

template<typename S>
struct encode_bits<S, true> {
    static inline void pack(S &s, const unsigned char value, const unsigned num_bits) {
        assert(num_bits > 0);
        assert(num_bits <= 8);

        static const unsigned char ONE = 1;

        for (unsigned bit = 0; bit < num_bits; ++bit) {
            const unsigned shift_count = (num_bits - 1) - bit;
            const bool bit_value = ((value & (ONE << shift_count)) > 0);
            s.push_back(bit_value);
        }
    }
};

template<typename S>
struct encode_bits<S, false> {
    static inline void pack(S &s, const unsigned char value, const unsigned num_bits) {
        assert(num_bits > 0);
        assert(num_bits <= 8);

        static const unsigned char ONE = 1;

        for (unsigned bit = 0; bit < num_bits; ++bit) {
            const unsigned shift_count = bit;
            const bool bit_value = ((value & (ONE << shift_count)) > 0);
            s.push_back(bit_value);
        }
    }
};

/**
 * Generic encode basic template.
 */
template<typename S,               // The destination (bit-addressable) buffer.
        unsigned SIZE_IN_BITS,     // Size of value to be encoded in bits.
        std::size_t SIZE_IN_BYTES, // Size of value to be encoded in bytes.
        bool PLATFORM_LE,          // True, if the platform is little-endian.
        bool ENCODE_LE             // True, if the value should be encoded as little-endian.
> struct encode_bytes;

///////////// 0-8 bits.

template<typename S, unsigned SIZE_IN_BITS, bool PLATFORM_LE, bool ENCODE_LE> struct encode_bytes<S, SIZE_IN_BITS, 1, PLATFORM_LE, ENCODE_LE> {
    static inline void pack(S &s, unsigned char const *value) {
        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 0));
        BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 8));

        encode_bits<S, ENCODE_LE>::pack(s, *value, SIZE_IN_BITS);
    }
};

///////////// 8-16 bits.

template<typename S, unsigned SIZE_IN_BITS> struct encode_bytes<S, SIZE_IN_BITS, 2, true, true> {
    static inline void pack(S &s, unsigned char const *value) {
        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 8));
        BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 16));

        encode_bits<S, true>::pack(s, value[1], SIZE_IN_BITS - 8);
        encode_bits<S, true>::pack(s, value[0], 8);
    }
};

template<typename S, unsigned SIZE_IN_BITS> struct encode_bytes<S, SIZE_IN_BITS, 2, true, false> {
    static inline void pack(S &s, unsigned char const *value) {
        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 8));
        BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 16));

        encode_bits<S, false>::pack(s, value[0], 8);
        encode_bits<S, false>::pack(s, value[1], SIZE_IN_BITS - 8);
    }
};

template<typename S, unsigned SIZE_IN_BITS> struct encode_bytes<S, SIZE_IN_BITS, 2, false, true> {
    static inline void pack(S &s, unsigned char const *value) {
        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 8));
        BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 16));

        encode_bits<S, true>::pack(s, value[0], SIZE_IN_BITS - 8);
        encode_bits<S, true>::pack(s, value[1], 8);
    }
};

template<typename S, unsigned SIZE_IN_BITS> struct encode_bytes<S, SIZE_IN_BITS, 2, false, false> {
    static inline void pack(S &s, unsigned char const *value) {
        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 8));
        BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 16));

        encode_bits<S, false>::pack(s, value[1], 8);
        encode_bits<S, false>::pack(s, value[0], SIZE_IN_BITS - 8);
    }
};

///////////// 16-24 bits.

template<typename S, unsigned SIZE_IN_BITS> struct encode_bytes<S, SIZE_IN_BITS, 3, true, true> {
    static inline void pack(S &s, unsigned char const *value) {
        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 16));
        BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 24));

        encode_bits<S, true>::pack(s, value[2], SIZE_IN_BITS - 16);
        encode_bits<S, true>::pack(s, value[1], 8);
        encode_bits<S, true>::pack(s, value[0], 8);
    }
};

template<typename S, unsigned SIZE_IN_BITS> struct encode_bytes<S, SIZE_IN_BITS, 3, true, false> {
    static inline void pack(S &s, unsigned char const *value) {
        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 16));
        BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 24));

        encode_bits<S, false>::pack(s, value[0], 8);
        encode_bits<S, false>::pack(s, value[1], 8);
        encode_bits<S, false>::pack(s, value[2], SIZE_IN_BITS - 16);
    }
};

template<typename S, unsigned SIZE_IN_BITS> struct encode_bytes<S, SIZE_IN_BITS, 3, false, true> {
    static inline void pack(S &s, unsigned char const *value) {
        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 16));
        BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 24));

        encode_bits<S, true>::pack(s, value[0], SIZE_IN_BITS - 16);
        encode_bits<S, true>::pack(s, value[1], 8);
        encode_bits<S, true>::pack(s, value[2], 8);
    }
};

template<typename S, unsigned SIZE_IN_BITS> struct encode_bytes<S, SIZE_IN_BITS, 3, false, false> {
    static inline void pack(S &s, unsigned char const *value) {
        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 16));
        BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 24));

        encode_bits<S, false>::pack(s, value[2], 8);
        encode_bits<S, false>::pack(s, value[1], 8);
        encode_bits<S, false>::pack(s, value[0], SIZE_IN_BITS - 16);
    }
};

/**
 * Encode the bits in the given value from least to most significant bit.
 * The least significant bit is located at bit position 0.
 *
 * @param s the bit-addressable destination buffer.
 * @param value the value to be encoded.
 * @param num_bits the number of bits to encode in the range > 1 and <= 8.
 * @param little_endian if true, encode the bits from least to most significant bit, else encode
 *                      from most to least significant bit.
 */
template<typename S>
void encode_value(S &s, const unsigned char value, const unsigned num_bits, const bool little_endian = false) {
    assert(num_bits > 0);
    assert(num_bits <= 8);

    static const unsigned char ONE = 1;

    for (unsigned bit = 0; bit < num_bits; ++bit) {
        const unsigned shift_count = (little_endian ? ((num_bits - 1) - bit) : bit);
        const bool bit_value = ((value & (ONE << shift_count)) > 0);
        s.push_back(bit_value);
    }
}

template<typename S, unsigned SIZE_IN_BITS, bool DATA_LE>
struct encode_bytes<S, SIZE_IN_BITS, DATA_LE, 2, false> {
    static inline void pack(S &s, unsigned char const *value) {
        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 0));
        BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 16));

        // Encode from least to most significant byte.
        encode_bits<S, DATA_LE>::pack(s, value[1], 8);
        encode_bits<S, DATA_LE>::PACK(s, value[0], SIZE_IN_BITS - 8);
    }
};

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
