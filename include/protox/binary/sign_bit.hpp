/******************************************************************************************************************************************/

#ifndef PROTOX_BINARY_SIGN_BIT_HPP
#define PROTOX_BINARY_SIGN_BIT_HPP

#include <protox/binary/endian.hpp>

/******************************************************************************************************************************************/

namespace protox {
namespace binary {

// Index the bytes of a value from the MSB (index 0) to the LSB (index N), where N = (size_in_bytes - 1).
template<ByteEndian E>
struct BYTE_ARRAY;

template<> struct BYTE_ARRAY<ByteEndian::BYTE_LITTLE_ENDIAN> {
    static inline unsigned char &get(unsigned char *value, const unsigned char size_in_bytes, const unsigned index) {
        return value[size_in_bytes - (1 + index)];
    }
};

template<> struct BYTE_ARRAY<ByteEndian::BYTE_BIG_ENDIAN> {
    static inline unsigned char &get(unsigned char *value, const unsigned char size_in_bytes, const unsigned index) {
        return value[index];
    }
};

// Note: bit endianess is assumed to be big;

template<ByteEndian E>
struct sign_bit {

    static inline bool is_negative_value(unsigned char *value, const unsigned char size_in_bits, const unsigned char size_in_bytes) {
        // Calculate the index of the byte that contains the sign bit.
        const unsigned remainder_bits = size_in_bits - ((size_in_bits/8) * 8);
        const unsigned sign_byte_index = size_in_bytes - ((size_in_bits/8) + (remainder_bits > 0 ? 1 : 0));

        // Get the byte that contains the sign bit.
        const unsigned char sign_byte = BYTE_ARRAY<E>::get(value, size_in_bytes, sign_byte_index);

        // Is the sign bit set to 1?
        bool is_negative = sign_byte & 1;
        if (remainder_bits > 0) {
            is_negative = sign_byte & (1 << (remainder_bits - 1));
        }

        return is_negative;
    }

    static inline void propagate(unsigned char *value, const unsigned char size_in_bits, const unsigned char size_in_bytes) {

        if (!is_negative_value(value, size_in_bits, size_in_bytes)) {
            return;
        }

        // Number of sign bits in the value.
        const unsigned num_sign_bits = (size_in_bytes * 8) - size_in_bits;

        // Whole number of sign bytes.
        const unsigned num_sign_bytes = num_sign_bits/8;

        // Set all sign bytes to 0xFF.
        for (int i = 0; i < num_sign_bytes; ++i) {
            unsigned char &byte = BYTE_ARRAY<E>::get(value, size_in_bytes, i);
            byte = byte | 0xFF;
        }

        const unsigned remainder_sign_bits = num_sign_bits - (num_sign_bytes * 8);

        // Need to set remainder sign bits to 1?
        if (remainder_sign_bits > 0) {
            unsigned char shift = 8 - remainder_sign_bits;
            unsigned char mask = (0xFF << shift);
            unsigned char &byte = BYTE_ARRAY<E>::get(value, size_in_bytes, num_sign_bytes);
            byte = byte | mask;
        }
    }
};

/******************************************************************************************************************************************/

}
}

/******************************************************************************************************************************************/

#endif

/******************************************************************************************************************************************/
