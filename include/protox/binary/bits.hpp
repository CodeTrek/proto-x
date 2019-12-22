/******************************************************************************************************************************************/
// (c) 2009 - 2019 Jay Graham
//
// Distributed under the MIT License
// (see accompanying file LICENSE_1_0_0.txt or http://www.opensource.org/licenses/mit-license.php)
/******************************************************************************************************************************************/

#ifndef PROTOX_BINARY_BIT_HPP
#define PROTOX_BINARY_BIT_HPP

/******************************************************************************************************************************************/

namespace protox {
namespace binary {

/******************************************************************************************************************************************/

constexpr unsigned char ONE = 0b00000001;

/******************************************************************************************************************************************/

template<typename S, // The destination (bit-addressable) buffer.
    bool LE, // If true, encode/decode the bits from least to most significant bit, else encode/decode from most to least significant bit.
    const unsigned char NUM_BITS> struct bits;

/******************************************************************************************************************************************/

template<typename S, bool LE> struct bits<S, LE, 1> {
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & ONE) > 0);
    }

    static inline void decode(const S &s, unsigned char &value, std::size_t &offset) {
        value = 0;
        value = value | ((s[offset + 0] ? 1 : 0) << 0);
        ++offset;
    }
};

/******************************************************************************************************************************************/

template<typename S> struct bits<S, true, 2> {
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 0)) > 0);
    }

    static inline void decode(const S &s, unsigned char &value, std::size_t &offset) {
        value = 0;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 0);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 1);
        ++offset;
    }
};

/******************************************************************************************************************************************/

template<typename S> struct bits<S, false, 2> {
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 0)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
    }

    static inline void decode(const S &s, unsigned char &value, std::size_t &offset) {
        value = 0;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 1);
        ++offset;
        value = value | ((s[((s.size() - 1) - offset)] ? 1 : 0) << 0);
        ++offset;
    }
};

/******************************************************************************************************************************************/

template<typename S> struct bits<S, true, 3> {
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 2)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 0)) > 0);
    }

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

template<typename S> struct bits<S, false, 3> {
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 0)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 2)) > 0);
    }

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

template<typename S> struct bits<S, true, 4> {
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 3)) > 0);
        s.push_back((value & (ONE << 2)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 0)) > 0);
    }

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

template<typename S> struct bits<S, false, 4> {
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 0)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 2)) > 0);
        s.push_back((value & (ONE << 3)) > 0);
    }

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

template<typename S> struct bits<S, true, 5> {
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 4)) > 0);
        s.push_back((value & (ONE << 3)) > 0);
        s.push_back((value & (ONE << 2)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 0)) > 0);
    }
};

/******************************************************************************************************************************************/

template<typename S> struct bits<S, false, 5> {
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 0)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 2)) > 0);
        s.push_back((value & (ONE << 3)) > 0);
        s.push_back((value & (ONE << 4)) > 0);
    }
};

/******************************************************************************************************************************************/

template<typename S> struct bits<S, true, 6> {
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 5)) > 0);
        s.push_back((value & (ONE << 4)) > 0);
        s.push_back((value & (ONE << 3)) > 0);
        s.push_back((value & (ONE << 2)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 0)) > 0);
    }
};

/******************************************************************************************************************************************/

template<typename S> struct bits<S, false, 6> {
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 0)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 2)) > 0);
        s.push_back((value & (ONE << 3)) > 0);
        s.push_back((value & (ONE << 4)) > 0);
        s.push_back((value & (ONE << 5)) > 0);
    }
};

/******************************************************************************************************************************************/

template<typename S> struct bits<S, true, 7> {
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 6)) > 0);
        s.push_back((value & (ONE << 5)) > 0);
        s.push_back((value & (ONE << 4)) > 0);
        s.push_back((value & (ONE << 3)) > 0);
        s.push_back((value & (ONE << 2)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 0)) > 0);
    }
};

/******************************************************************************************************************************************/

template<typename S> struct bits<S, false, 7> {
    static inline void encode(S &s, const unsigned char value) {
        s.push_back((value & (ONE << 0)) > 0);
        s.push_back((value & (ONE << 1)) > 0);
        s.push_back((value & (ONE << 2)) > 0);
        s.push_back((value & (ONE << 3)) > 0);
        s.push_back((value & (ONE << 4)) > 0);
        s.push_back((value & (ONE << 5)) > 0);
        s.push_back((value & (ONE << 6)) > 0);
    }
};

/******************************************************************************************************************************************/

template<typename S> struct bits<S, true, 8> {
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
};

/******************************************************************************************************************************************/

template<typename S> struct bits<S, false, 8> {
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
};

/******************************************************************************************************************************************/

}
}

/******************************************************************************************************************************************/

#endif

/******************************************************************************************************************************************/
