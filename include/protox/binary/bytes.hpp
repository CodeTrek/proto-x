/******************************************************************************************************************************************/
// (c) 2009 - 2019 Jay Graham
//
// Distributed under the MIT License
// (see accompanying file LICENSE_1_0_0.txt or http://www.opensource.org/licenses/mit-license.php)
/******************************************************************************************************************************************/

#ifndef PROTOX_BINARY_BYTES_HPP
#define PROTOX_BINARY_BYTES_HPP

#include <protox/binary/bits.hpp>

/******************************************************************************************************************************************/

namespace protox {
namespace binary {

/******************************************************************************************************************************************/

template<typename S,               // The destination (bit-addressable) buffer.
        unsigned SIZE_IN_BITS,     // Size of value to be encoded in bits.
        std::size_t SIZE_IN_BYTES, // Size of value to be encoded in bytes.
        bool PLATFORM_LE,          // True, if the platform is little-endian.
        bool LE                    // True, if the value should be encoded as little-endian.
> struct bytes;


/******************************************************************************************************************************************/

///////////// 0-8 bits.

template<typename S, unsigned SIZE_IN_BITS, bool PLATFORM_LE, bool LE> struct bytes<S, SIZE_IN_BITS, 1, PLATFORM_LE, LE> {
    static inline void encode(S &s, unsigned char const *value) {
        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 0));
        BOOST_STATIC_ASSERT((SIZE_IN_BITS <= 8));

        protox::binary::bits<S, LE, SIZE_IN_BITS>::encode(s, *value);
    }
};

/******************************************************************************************************************************************/

}
}

/******************************************************************************************************************************************/

#endif

/******************************************************************************************************************************************/
