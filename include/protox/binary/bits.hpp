/******************************************************************************************************************************************/
// (c) 2009 - 2019 Jay Graham
//
// Distributed under the MIT License
// (see accompanying file LICENSE_1_0_0.txt or http://www.opensource.org/licenses/mit-license.php)
/******************************************************************************************************************************************/

#ifndef PROTOX_BINARY_BIT_HPP
#define PROTOX_BINARY_BIT_HPP

#include <protox/binary/endian.hpp>

/******************************************************************************************************************************************/

namespace protox {
namespace binary {

/******************************************************************************************************************************************/

constexpr unsigned char ONE = 0b00000001;

/******************************************************************************************************************************************/

template<protox::binary::BitEndian BE, // Bit endianess.
         const unsigned char NUM_BITS> // Value size in bits.
struct bits;

/******************************************************************************************************************************************/

template<protox::binary::BitEndian BE> struct bits<BE, 1> {
    template<typename S>
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & ONE) > 0);
    }

    template<typename S>
    static inline void decode(const S &s, unsigned char &value, std::size_t &offset) {
        value = 0;

        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 0);
        ++offset;
    }
};

/******************************************************************************************************************************************/

template<> struct bits<BIT_LITTLE_ENDIAN, 2> {
    template<typename S>
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 0)) > 0);
    }

    template<typename S>
    static inline void decode(const S &s, unsigned char &value, std::size_t &offset) {
        value = 0;

        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 0);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 1);
        ++offset;
    }
};

/******************************************************************************************************************************************/

template<> struct bits<BIT_BIG_ENDIAN, 2> {
    template<typename S>
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 0)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
    }

    template<typename S>
    static inline void decode(const S &s, unsigned char &value, std::size_t &offset) {
        value = 0;

        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 1);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 0);
        ++offset;
    }
};

/******************************************************************************************************************************************/

template<> struct bits<BIT_LITTLE_ENDIAN, 3> {
    template<typename S>
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 2)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 0)) > 0);
    }

    template<typename S>
    static inline void decode(const S &s, unsigned char &value, std::size_t &offset) {
        value = 0;

        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 0);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 1);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 2);
        ++offset;
    }
};

/******************************************************************************************************************************************/

template<> struct bits<BIT_BIG_ENDIAN, 3> {
    template<typename S>
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 0)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 2)) > 0);
    }

    template<typename S>
    static inline void decode(const S &s, unsigned char &value, std::size_t &offset) {
        value = 0;

        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 2);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 1);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 0);
        ++offset;
    }
};

/******************************************************************************************************************************************/

template<> struct bits<BIT_LITTLE_ENDIAN, 4> {
    template<typename S>
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 3)) > 0);
        s.push_back((value & (ONE << 2)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 0)) > 0);
    }

    template<typename S>
    static inline void decode(const S &s, unsigned char &value, std::size_t &offset) {
        value = 0;

        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 0);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 1);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 2);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 3);
        ++offset;
    }
};

/******************************************************************************************************************************************/

template<> struct bits<BIT_BIG_ENDIAN, 4> {
    template<typename S>
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 0)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 2)) > 0);
        s.push_back((value & (ONE << 3)) > 0);
    }

    template<typename S>
    static inline void decode(const S &s, unsigned char &value, std::size_t &offset) {
        value = 0;

        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 3);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 2);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 1);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 0);
        ++offset;
    }
};

/******************************************************************************************************************************************/

template<> struct bits<BIT_LITTLE_ENDIAN, 5> {
    template<typename S>
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 4)) > 0);
        s.push_back((value & (ONE << 3)) > 0);
        s.push_back((value & (ONE << 2)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 0)) > 0);
    }

    template<typename S>
    static inline void decode(const S &s, unsigned char &value, std::size_t &offset) {
        value = 0;

        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 0);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 1);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 2);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 3);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 4);
        ++offset;
    }
};

/******************************************************************************************************************************************/

template<> struct bits<BIT_BIG_ENDIAN, 5> {
    template<typename S>
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 0)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 2)) > 0);
        s.push_back((value & (ONE << 3)) > 0);
        s.push_back((value & (ONE << 4)) > 0);
    }

    template<typename S>
    static inline void decode(const S &s, unsigned char &value, std::size_t &offset) {
        value = 0;

        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 4);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 3);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 2);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 1);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 0);
        ++offset;
    }
};

/******************************************************************************************************************************************/

template<> struct bits<BIT_LITTLE_ENDIAN, 6> {
    template<typename S>
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 5)) > 0);
        s.push_back((value & (ONE << 4)) > 0);
        s.push_back((value & (ONE << 3)) > 0);
        s.push_back((value & (ONE << 2)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 0)) > 0);
    }

    template<typename S>
    static inline void decode(const S &s, unsigned char &value, std::size_t &offset) {
        value = 0;

        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 0);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 1);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 2);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 3);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 4);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 5);
        ++offset;
    }
};

/******************************************************************************************************************************************/

template<> struct bits<BIT_BIG_ENDIAN, 6> {
    template<typename S>
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 0)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 2)) > 0);
        s.push_back((value & (ONE << 3)) > 0);
        s.push_back((value & (ONE << 4)) > 0);
        s.push_back((value & (ONE << 5)) > 0);
    }

    template<typename S>
    static inline void decode(const S &s, unsigned char &value, std::size_t &offset) {
        value = 0;

        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 5);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 4);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 3);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 2);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 1);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 0);
        ++offset;
    }
};

/******************************************************************************************************************************************/

template<> struct bits<BIT_LITTLE_ENDIAN, 7> {
    template<typename S>
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 6)) > 0);
        s.push_back((value & (ONE << 5)) > 0);
        s.push_back((value & (ONE << 4)) > 0);
        s.push_back((value & (ONE << 3)) > 0);
        s.push_back((value & (ONE << 2)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 0)) > 0);
    }

    template<typename S>
    static inline void decode(const S &s, unsigned char &value, std::size_t &offset) {
        value = 0;

        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 0);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 1);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 2);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 3);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 4);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 5);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 6);
        ++offset;
    }
};

/******************************************************************************************************************************************/

template<> struct bits<BIT_BIG_ENDIAN, 7> {
    template<typename S>
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 0)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 2)) > 0);
        s.push_back((value & (ONE << 3)) > 0);
        s.push_back((value & (ONE << 4)) > 0);
        s.push_back((value & (ONE << 5)) > 0);
        s.push_back((value & (ONE << 6)) > 0);
    }

    template<typename S>
    static inline void decode(const S &s, unsigned char &value, std::size_t &offset) {
        value = 0;

        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 6);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 5);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 4);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 3);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 2);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 1);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 0);
        ++offset;
    }
};

/******************************************************************************************************************************************/

template<> struct bits<BIT_LITTLE_ENDIAN, 8> {
    template<typename S>
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 7)) > 0);
        s.push_back((value & (ONE << 6)) > 0);
        s.push_back((value & (ONE << 5)) > 0);
        s.push_back((value & (ONE << 4)) > 0);
        s.push_back((value & (ONE << 3)) > 0);
        s.push_back((value & (ONE << 2)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 0)) > 0);
    }

    template<typename S>
    static inline void decode(const S &s, unsigned char &value, std::size_t &offset) {
        value = 0;

        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 0);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 1);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 2);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 3);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 4);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 5);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 6);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 7);
        ++offset;
    }
};

/******************************************************************************************************************************************/

template<> struct bits<BIT_BIG_ENDIAN, 8> {
    template<typename S>
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 0)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 2)) > 0);
        s.push_back((value & (ONE << 3)) > 0);
        s.push_back((value & (ONE << 4)) > 0);
        s.push_back((value & (ONE << 5)) > 0);
        s.push_back((value & (ONE << 6)) > 0);
        s.push_back((value & (ONE << 7)) > 0);
    }

    template<typename S>
    static inline void decode(const S &s, unsigned char &value, std::size_t &offset) {
        value = 0;

        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 7);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 6);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 5);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 4);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 3);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 2);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 1);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 0);
        ++offset;
    }
};

/******************************************************************************************************************************************/

}
}

/******************************************************************************************************************************************/

#endif

/******************************************************************************************************************************************/
