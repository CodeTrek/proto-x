/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_HLA_13_STATIC_PAD_HPP
#define PROTOX_HLA_13_STATIC_PAD_HPP

/**********************************************************************************************************************/

#include <cstddef>

#include <boost/static_assert.hpp>
#include <boost/mpl/modulus.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/minus.hpp>

#include <protox/platform.hpp>
#include <protox/codec/codecs.hpp>

#include <protox/hla_13/size_type.hpp>
#include <protox/hla_13/basic_data_representation_table.hpp>

/**********************************************************************************************************************/

namespace protox { namespace hla_13 {

/**************************************************************************************************/

// Computes padding in bytes according to the following formula: (Offset + Size + Padding) modulus Octet_Boundary = 0
template< typename Offset, typename Size, typename Octet_Boundary >
struct static_pad_ {
    BOOST_STATIC_ASSERT(( (Offset::value >= 0) && (Size::value >= 0) && (Octet_Boundary::value > 0) ));

    typedef typename boost::mpl::modulus< boost::mpl::plus< Offset, Size >, Octet_Boundary > remainder;

    typedef typename
        boost::mpl::if_< boost::mpl::equal_to< remainder, boost::mpl::int_< 0 > >,
            boost::mpl::int_< 0 >,
            boost::mpl::minus< Octet_Boundary, remainder >
        >::type type;
};

/**********************************************************************************************************************/

template< typename S, std::size_t pad_size >
struct pad {
    inline static void encode(S &s) {
        BOOST_STATIC_ASSERT(( pad_size > 0 ));
        s.start_pad(pad_size);

        for (unsigned i = 0; i < pad_size; ++i) {
            protox::dtl::codec::encode(s, HLA13octet(PROTOX_DTL_PAD_CHARACTER));
        }

        s.end_pad(pad_size);
    }

    inline static void decode(S const &s, std::size_t &offset) {
        BOOST_STATIC_ASSERT(( pad_size > 0 ));
        s.start_pad(pad_size);
        offset += pad_size;
        s.end_pad(pad_size);
    }
};

/**********************************************************************************************************************/

template< typename S >
struct pad< S, 0 > {
    inline static void encode(S &s) {}
    inline static void decode(S const &s, std::size_t &offset) {}
};

/**********************************************************************************************************************/

template< typename S >
struct pad< S, 1 > {
    static inline void encode(S &s) {
        s.start_pad(1);
        protox::dtl::codec::encode(s, HLA13octet(PROTOX_DTL_PAD_CHARACTER));
        s.end_pad(1);
    }

    static inline void decode(S const &s, std::size_t &offset) {
        s.start_pad(1);
        offset += 1;
        s.end_pad(1);
    }
};

/**********************************************************************************************************************/

template< typename S >
struct pad< S, 2 > {
    static inline void encode(S &s) {
        s.start_pad(2);
        protox::dtl::codec::encode(s, HLA13octet(PROTOX_DTL_PAD_CHARACTER));
        protox::dtl::codec::encode(s, HLA13octet(PROTOX_DTL_PAD_CHARACTER));
        s.end_pad(2);
    }

    static inline void decode(S const &s, std::size_t &offset) {
        s.start_pad(2);
        offset += 2;
        s.end_pad(2);
    }
};

/**********************************************************************************************************************/

template< typename S >
struct pad< S, 3 > {
    static inline void encode(S &s) {
        s.start_pad(3);
        protox::dtl::codec::encode(s, HLA13octet(PROTOX_DTL_PAD_CHARACTER));
        protox::dtl::codec::encode(s, HLA13octet(PROTOX_DTL_PAD_CHARACTER));
        protox::dtl::codec::encode(s, HLA13octet(PROTOX_DTL_PAD_CHARACTER));
        s.end_pad(3);
    }

    static inline void decode(S const &s, std::size_t &offset) {
        s.start_pad(3);
        offset += 3;
        s.end_pad(3);
    }
};

/**********************************************************************************************************************/

template< typename S >
struct pad< S, 4 > {
    static inline void encode(S &s) {
        s.start_pad(4);
        protox::dtl::codec::encode(s, HLA13octet(PROTOX_DTL_PAD_CHARACTER));
        protox::dtl::codec::encode(s, HLA13octet(PROTOX_DTL_PAD_CHARACTER));
        protox::dtl::codec::encode(s, HLA13octet(PROTOX_DTL_PAD_CHARACTER));
        protox::dtl::codec::encode(s, HLA13octet(PROTOX_DTL_PAD_CHARACTER));
        s.end_pad(4);
    }

    static inline void decode(S const &s, std::size_t &offset) {
        s.start_pad(4);
        offset += 4;
        s.end_pad(4);
    }
};

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
