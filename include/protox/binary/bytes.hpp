/******************************************************************************************************************************************/
// (c) 2009 - 2019 Jay Graham
//
// Distributed under the MIT License
// (see accompanying file LICENSE_1_0_0.txt or http://www.opensource.org/licenses/mit-license.php)
/******************************************************************************************************************************************/

#ifndef PROTOX_BINARY_BYTES_HPP
#define PROTOX_BINARY_BYTES_HPP

#include <protox/binary/bits.hpp>
#include <protox/binary/endian.hpp>

/******************************************************************************************************************************************/

namespace protox {
namespace binary {

/******************************************************************************************************************************************/

template<unsigned SIZE_IN_BITS,       // Size of value to be encoded in bits.
        std::size_t SIZE_IN_BYTES,    // Size of value to be encoded in bytes.
        protox::binary::ByteEndian E, // Byte endieness
        protox::binary::BitEndian BE  // Bit endianess.
> struct bytes;


/******************************************************************************************************************************************/

// 0-8 bits.

template<unsigned SIZE_IN_BITS, ByteEndian E, BitEndian BE>
struct bytes<SIZE_IN_BITS, 1, E, BE> {
    BOOST_STATIC_ASSERT((SIZE_IN_BITS > 0));
    BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 8));

    template<typename S>
    static inline void encode(S &s, unsigned char const *value) {
        bits<BE, SIZE_IN_BITS>::encode(s, value[0]);
    }

    template<typename S>
    static inline void decode(const S &s, unsigned char *value, std::size_t &offset) {
        bits<BE, SIZE_IN_BITS>::decode(s, value[0], offset);
    }
};

// 8-16 bits.

template<unsigned SIZE_IN_BITS> struct bytes<SIZE_IN_BITS, 2, BYTE_LITTLE_ENDIAN, BIT_LITTLE_ENDIAN> {
    BOOST_STATIC_ASSERT((SIZE_IN_BITS > 8));
    BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 16));

    template<typename S>
    static inline void encode(S &s, unsigned char const *value) {
        bits<BIT_LITTLE_ENDIAN, SIZE_IN_BITS - 8>::encode(s, value[1]);
        bits<BIT_LITTLE_ENDIAN,                8>::encode(s, value[0]);
    }

    template<typename S>
    static inline void decode(const S &s, unsigned char *value, std::size_t &offset) {
        bits<BIT_LITTLE_ENDIAN,                8>::decode(s, value[0], offset);
        bits<BIT_LITTLE_ENDIAN, SIZE_IN_BITS - 8>::decode(s, value[1], offset);
    }
};

template<unsigned SIZE_IN_BITS> struct bytes<SIZE_IN_BITS, 2, BYTE_LITTLE_ENDIAN, BIT_BIG_ENDIAN> {
    BOOST_STATIC_ASSERT((SIZE_IN_BITS > 8));
    BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 16));

    template<typename S>
    static inline void encode(S &s, unsigned char const *value) {
        bits<BIT_BIG_ENDIAN,                8>::encode(s, value[0]);
        bits<BIT_BIG_ENDIAN, SIZE_IN_BITS - 8>::encode(s, value[1]);
    }

    template<typename S>
    static inline void decode(const S &s, unsigned char *value, std::size_t &offset) {
        bits<BIT_BIG_ENDIAN, SIZE_IN_BITS - 8>::decode(s, value[1], offset);
        bits<BIT_BIG_ENDIAN,                8>::decode(s, value[0], offset);
    }
};

template<unsigned SIZE_IN_BITS> struct bytes<SIZE_IN_BITS, 2, BYTE_BIG_ENDIAN, BIT_LITTLE_ENDIAN> {
    BOOST_STATIC_ASSERT((SIZE_IN_BITS > 8));
    BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 16));

    template<typename S>
    static inline void encode(S &s, unsigned char const *value) {
        bits<BIT_LITTLE_ENDIAN, SIZE_IN_BITS - 8>::encode(s, value[0]);
        bits<BIT_LITTLE_ENDIAN,                8>::encode(s, value[1]);
    }

    template<typename S>
    static inline void decode(const S &s, unsigned char *value, std::size_t &offset) {
        bits<BIT_LITTLE_ENDIAN,                8>::decode(s, value[1], offset);
        bits<BIT_LITTLE_ENDIAN, SIZE_IN_BITS - 8>::decode(s, value[0], offset);
    }
};

template<unsigned SIZE_IN_BITS> struct bytes<SIZE_IN_BITS, 2, BYTE_BIG_ENDIAN, BIT_BIG_ENDIAN> {
    BOOST_STATIC_ASSERT((SIZE_IN_BITS > 8));
    BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 16));

    template<typename S>
    static inline void encode(S &s, unsigned char const *value) {
        bits<BIT_BIG_ENDIAN,                8>::encode(s, value[1]);
        bits<BIT_BIG_ENDIAN, SIZE_IN_BITS - 8>::encode(s, value[0]);
    }

    template<typename S>
    static inline void decode(const S &s, unsigned char *value, std::size_t &offset) {
        bits<BIT_BIG_ENDIAN, SIZE_IN_BITS - 8>::decode(s, value[0], offset);
        bits<BIT_BIG_ENDIAN,                8>::decode(s, value[1], offset);
    }

};

// 16-24 bits.

//template<typename S, unsigned SIZE_IN_BITS> struct encode_bytes<S, SIZE_IN_BITS, 3, true, true> {
//    static inline void pack(S &s, unsigned char const *value) {
//        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 16));
//        BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 24));
//
//        encode_bits<S, true>::pack(s, value[2], SIZE_IN_BITS - 16);
//        encode_bits<S, true>::pack(s, value[1], 8);
//        encode_bits<S, true>::pack(s, value[0], 8);
//    }
//};

//template<typename S, unsigned SIZE_IN_BITS> struct encode_bytes<S, SIZE_IN_BITS, 3, true, false> {
//    static inline void pack(S &s, unsigned char const *value) {
//        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 16));
//        BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 24));
//
//        encode_bits<S, false>::pack(s, value[0], 8);
//        encode_bits<S, false>::pack(s, value[1], 8);
//        encode_bits<S, false>::pack(s, value[2], SIZE_IN_BITS - 16);
//    }
//};

//template<typename S, unsigned SIZE_IN_BITS> struct encode_bytes<S, SIZE_IN_BITS, 3, false, true> {
//    static inline void pack(S &s, unsigned char const *value) {
//        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 16));
//        BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 24));
//
//        encode_bits<S, true>::pack(s, value[0], SIZE_IN_BITS - 16);
//        encode_bits<S, true>::pack(s, value[1], 8);
//        encode_bits<S, true>::pack(s, value[2], 8);
//    }
//};

//template<typename S, unsigned SIZE_IN_BITS> struct encode_bytes<S, SIZE_IN_BITS, 3, false, false> {
//    static inline void pack(S &s, unsigned char const *value) {
//        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 16));
//        BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 24));
//
//        encode_bits<S, false>::pack(s, value[2], 8);
//        encode_bits<S, false>::pack(s, value[1], 8);
//        encode_bits<S, false>::pack(s, value[0], SIZE_IN_BITS - 16);
//    }
//};

/******************************************************************************************************************************************/

}
}

/******************************************************************************************************************************************/

#endif

/******************************************************************************************************************************************/
