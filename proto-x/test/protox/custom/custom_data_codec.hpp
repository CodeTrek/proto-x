/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef TEST_CUSTOM_DATA_CODEC_HPP
#define TEST_CUSTOM_DATA_CODEC_HPP

/**********************************************************************************************************************/

#include <cstddef>

#include <boost/mpl/int.hpp>
#include <boost/mpl/sizeof.hpp>

#include <boost/static_assert.hpp>

#include <protox/platform.hpp>

#include <protox/hla_1516/basic_data_representation_table.hpp>

#include <protox/dtl/codec_interface.hpp>
#include <protox/dtl/compute_octet_boundary.hpp>

#include <test/protox/custom/codec_tags.hpp>
#include <test/protox/custom/custom_data_encoders.hpp>
#include <test/protox/custom/custom_data_decoders.hpp>

/**********************************************************************************************************************/

namespace test { namespace custom {

/**********************************************************************************************************************/

struct custom_codec_impl {
    template< typename T >
    struct octet_boundary {
        typedef typename protox::dtl::compute_octet_boundary< T::size_in_bits >::type type;
        BOOST_STATIC_ASSERT((type::value != protox::dtl::UNKNOWN_OCTET_BOUNDARY::value));
    };

    // Compute the data type's size in bytes from size in bits. If the size in bits is not a multiple of 8, add a
    // padding byte.
    template< typename T >
    struct static_size_in_bytes {
        typedef typename
        boost::mpl::int_< (T::size_in_bits/8) + (((T::size_in_bits % 8) == 0) ? 0 : 1) >::type type;
    };

    template< typename T >
    inline static std::size_t dynamic_size(T) {
        return static_size_in_bytes< T >::type::value;
    }

    template< typename S, typename T >
    inline static void encode(S &s, const T &obj) {
        BOOST_STATIC_ASSERT((boost::mpl::sizeof_< protox::hla_1516::HLAoctet::value_type >::value == 1));

        const protox::hla_1516::HLAoctet::value_type *bytes
            = (const protox::hla_1516::HLAoctet::value_type *)(&obj.value);

        s.start_value();

        custom::encode_custom<
            S,
            protox::dtl::codec::static_size_in_bytes< T >::value,
            (T::endianess::value != PROTOX_DTL_PLATFORM_ENDIANESS)
        >::pack(s, bytes);

        s.end_value();
    }

    template< typename S, typename T >
    inline static void decode( T &v, const S &s, std::size_t &offset )
    {
        BOOST_STATIC_ASSERT((boost::mpl::sizeof_< protox::hla_1516::HLAoctet::value_type >::value == 1));

        protox::hla_1516::HLAoctet::value_type *v_ptr = (protox::hla_1516::HLAoctet::value_type *)(&v.value);

        s.start_value();

        custom::decode_custom<
            S,
            protox::dtl::codec::static_size_in_bytes<T>::value,
            (T::endianess::value != PROTOX_DTL_PLATFORM_ENDIANESS)
        >::unpack(v_ptr, s, offset);

        s.end_value();
    }
};

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

// Note: All code implementations must be defined in the protox::dtl namespace.

namespace protox { namespace dtl {

/**********************************************************************************************************************/

template<>
struct codec_impl< test::custom::Test16BitTwosComplementUnsigned > : test::custom::custom_codec_impl {};

template<>
struct codec_impl< test::custom::Test32BitTwosComplementUnsigned > : test::custom::custom_codec_impl {};

template<>
struct codec_impl< test::custom::Test64BitTwosComplementUnsigned > : test::custom::custom_codec_impl {};

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
