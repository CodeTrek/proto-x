/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_HLA_13_BASIC_DATA_CODEC_HPP
#define PROTOX_HLA_13_BASIC_DATA_CODEC_HPP

/**********************************************************************************************************************/

#include <cstddef>

#include <boost/mpl/int.hpp>
#include <boost/mpl/sizeof.hpp>

#include <boost/static_assert.hpp>

#include <protox/platform.hpp>

#include <protox/dtl/codec_interface.hpp>
#include <protox/dtl/compute_octet_boundary.hpp>

#include <protox/hla_13/basic_data_representation_table.hpp>
#include <protox/hla_13/codec_tags.hpp>
#include <protox/hla_13/basic_data_encoders.hpp>
#include <protox/hla_13/basic_data_decoders.hpp>

/**********************************************************************************************************************/

namespace protox {
namespace dtl {

/**********************************************************************************************************************/

struct basic_codec_impl_13 {
    template< typename T >
    struct octet_boundary {
        typedef typename compute_octet_boundary< T::size_in_bits >::type type;
        BOOST_STATIC_ASSERT((type::value != UNKNOWN_OCTET_BOUNDARY::value));
    };

    // Compute the data type's size in bytes from size in bits. If the size in bits is not a multiple of 8, add a
    // padding byte.
    template< typename T >
    struct static_size_in_bytes {
        typedef typename boost::mpl::int_< (T::size_in_bits/8) + (((T::size_in_bits % 8) == 0) ? 0 : 1) >::type type;
    };

    template< typename T >
    inline static std::size_t dynamic_size(T) {
        return static_size_in_bytes< T >::type::value;
    }

    template< typename S, typename T >
    inline static void encode(S &s, const T &obj) {
        BOOST_STATIC_ASSERT((boost::mpl::sizeof_< hla_13::HLA13octet::value_type >::value == 1));

        const hla_13::HLA13octet::value_type *bytes = (hla_13::HLA13octet::value_type const *)(&obj.value);

        s.start_value();

        hla_13::encode_basic<
            S,
            codec::static_size_in_bytes<T>::value,
            (T::endianess::value != PROTOX_DTL_PLATFORM_ENDIANESS)
        >::pack(s, bytes);

        s.end_value();
    }

    template< typename S, typename T >
    inline static void decode(T &v, const S &s, std::size_t &offset) {
        BOOST_STATIC_ASSERT((boost::mpl::sizeof_< hla_13::HLA13octet::value_type >::value == 1));

        hla_13::HLA13octet::value_type *v_ptr = (hla_13::HLA13octet::value_type *)(&v.value);

        s.start_value();

        hla_13::decode_basic<
            S,
            codec::static_size_in_bytes<T>::value,
            (T::endianess::value != PROTOX_DTL_PLATFORM_ENDIANESS)
        >::unpack(v_ptr, s, offset);

        s.end_value();
    }
};

/**********************************************************************************************************************/

template<> struct codec_impl< hla_13::HLA13portable > : basic_codec_impl_13 {};

/**********************************************************************************************************************/

template<> struct codec_impl< hla_13::HLA13_16BitTwosComplementSigned > : basic_codec_impl_13 {};

/**********************************************************************************************************************/

template<> struct codec_impl< hla_13::HLA13_16BitTwosComplementUnsigned > : basic_codec_impl_13 {};

/**********************************************************************************************************************/

template<> struct codec_impl< hla_13::HLA13_32BitTwosComplementSigned > : basic_codec_impl_13 {};

/**********************************************************************************************************************/

template<> struct codec_impl< hla_13::HLA13_32BitTwosComplementUnsigned > : basic_codec_impl_13 {};

/**********************************************************************************************************************/

template<> struct codec_impl< hla_13::HLA13_32BitIEEESinglePrecision > : basic_codec_impl_13 {};

/**********************************************************************************************************************/

template<> struct codec_impl< hla_13::HLA13_64BitIEEEDoublePrecision > : basic_codec_impl_13 {};

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
