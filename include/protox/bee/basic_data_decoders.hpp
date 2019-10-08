/******************************************************************************************************************************************/
// (c) 2009 - 2019 Jay Graham
//
// Distributed under the MIT License
// (see accompanying file LICENSE_1_0_0.txt or http://www.opensource.org/licenses/mit-license.php)
/******************************************************************************************************************************************/

#ifndef PROTOX_BEE_DECODERS_HPP
#define PROTOX_BEE_DECODERS_HPP

/******************************************************************************************************************************************/

#include <assert.h>
#include <boost/static_assert.hpp>

/******************************************************************************************************************************************/

namespace protox {
namespace bee {

/******************************************************************************************************************************************/

template<typename S>
inline void decode_value(unsigned char &value, const S &s, const unsigned num_bits, std::size_t &offset) {
    assert(num_bits > 0);
    assert(num_bits <= 8);

    value = 0;

    // Decode bits from least to most significant bit.
    for (unsigned bit_num = 0; bit_num < num_bits; ++bit_num) {
        const unsigned char bit_value = s[offset + bit_num] ? 1 : 0;
        value = value | (bit_value << bit_num);
    }

    offset += num_bits;
}

/******************************************************************************************************************************************/

template<typename S,               // The source (bit-addressable) buffer
        unsigned SIZE_IN_BITS,     // Size of value to be decoded in bits
        std::size_t SIZE_IN_BYTES, // Size of value to be decoded in bytes
        bool CONVERT_ENDIAN        // True, if endian conversion is required
> struct decode_basic;

/******************************************************************************************************************************************/

template<typename S, unsigned SIZE_IN_BITS, bool CONVERT_ENDIAN>
struct decode_basic<S, SIZE_IN_BITS, 1, CONVERT_ENDIAN> {
    static inline void unpack(unsigned char *value, const S &s, std::size_t &offset) {
        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 0));
        BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 8));

        decode_value(*value, s, SIZE_IN_BITS, offset);
    }
};

/******************************************************************************************************************************************/

template<typename S, unsigned SIZE_IN_BITS>
struct decode_basic<S, SIZE_IN_BITS, 2, false> {
    static inline void unpack(unsigned char *value, const S &s, std::size_t &offset) {
        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 8));
        BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 16));

        // Decode from least to most significant byte
        decode_value(value[1], s, 8, offset);
        decode_value(value[0], s, SIZE_IN_BITS - 8, offset);
    }
};

/******************************************************************************************************************************************/

template<typename S, unsigned SIZE_IN_BITS>
struct decode_basic<S, SIZE_IN_BITS, 3, false> {
    static inline void unpack(unsigned char *value, const S &s, std::size_t &offset) {
        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 16));
        BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 24));

        // Decode from least to most significant byte
        decode_value(value[2], s, 8, offset);
        decode_value(value[1], s, 8, offset);
        decode_value(value[0], s, SIZE_IN_BITS - 16, offset);
    }
};

/******************************************************************************************************************************************/

template<typename S, unsigned SIZE_IN_BITS>
struct decode_basic<S, SIZE_IN_BITS, 4, false> {
    static inline void unpack(unsigned char *value, const S &s, std::size_t &offset) {
        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 24));
        BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 32));

        // Decode from least to most significant byte
        decode_value(value[3], s, 8, offset);
        decode_value(value[2], s, 8, offset);
        decode_value(value[1], s, 8, offset);
        decode_value(value[0], s, SIZE_IN_BITS - 24, offset);
    }
};

/******************************************************************************************************************************************/

template<typename S, unsigned SIZE_IN_BITS>
struct decode_basic<S, SIZE_IN_BITS, 2, true> {
    static inline void unpack(unsigned char *value, const S &s, std::size_t &offset) {
        unsigned char converted_value[2];
        converted_value[0] = 0;
        converted_value[1] = 0;

        decode_basic<S, SIZE_IN_BITS, 2, false>::unpack(converted_value, s, offset);

        value[0] = converted_value[1];
        value[1] = converted_value[0];
    }
};

/******************************************************************************************************************************************/

template<typename S, unsigned SIZE_IN_BITS>
struct decode_basic<S, SIZE_IN_BITS, 3, true> {
    static inline void unpack(unsigned char *value, const S &s, std::size_t &offset) {
        unsigned char converted_value[3];
        converted_value[0] = 0;
        converted_value[1] = 0;
        converted_value[2] = 0;

        decode_basic<S, SIZE_IN_BITS, 3, false>::unpack(converted_value, s, offset);

        value[0] = converted_value[2];
        value[1] = converted_value[1];
        value[2] = converted_value[0];
    }
};

/******************************************************************************************************************************************/

template<typename S, unsigned SIZE_IN_BITS>
struct decode_basic<S, SIZE_IN_BITS, 4, true> {
    static inline void unpack(unsigned char *value, const S &s, std::size_t &offset) {
        unsigned char converted_value[4];

        decode_basic<S, SIZE_IN_BITS, 4, false>::unpack(converted_value, s, offset);

        value[0] = converted_value[3];
        value[1] = converted_value[2];
        value[2] = converted_value[1];
        value[3] = converted_value[0];
    }
};

/******************************************************************************************************************************************/

}
}

/******************************************************************************************************************************************/

#endif

/******************************************************************************************************************************************/
