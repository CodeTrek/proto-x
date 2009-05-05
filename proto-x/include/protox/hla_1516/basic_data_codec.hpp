/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_1516_BASIC_DATA_CODEC_HPP
#define PROTOX_HLA_1516_BASIC_DATA_CODEC_HPP

/**************************************************************************************************/

#include <cstddef>

#include <boost/mpl/int.hpp>
#include <boost/mpl/sizeof.hpp>

#include <boost/static_assert.hpp>

#include <protox/platform.hpp>

#include <protox/dtl/codec_interface.hpp>
#include <protox/dtl/compute_octet_boundary.hpp>

#include <protox/hla_1516/basic_data_representation_table.hpp>
#include <protox/hla_1516/codec_tags.hpp>
#include <protox/hla_1516/basic_data_encoders.hpp>
#include <protox/hla_1516/basic_data_decoders.hpp>

/**************************************************************************************************/

using namespace boost;
using namespace protox::hla_1516;

/**************************************************************************************************/

namespace protox { namespace dtl {

/**************************************************************************************************/

struct basic_codec_impl_1516
{
  template< typename T >
  struct octet_boundary
  {
    typedef typename protox::dtl::compute_octet_boundary< T::size_in_bits >::type type;
    BOOST_STATIC_ASSERT(( type::value != protox::dtl::UNKNOWN_OCTET_BOUNDARY::value ));
  };

  // Compute the data type's size in bytes from size in bits. If the size
  // in bits is not a multiple of 8, add a padding byte.
  template< typename T >
  struct static_size_in_bytes
  {
    typedef typename mpl::int_< (T::size_in_bits/8) + ( ((T::size_in_bits % 8) == 0) ? 0 : 1 ) >::type type;
  };

  template< typename T >
  inline static std::size_t dynamic_size(T) { return static_size_in_bytes<T>::type::value; }

  template< typename S, typename T >
  inline static void encode(S &s, const T &obj)
  {
    BOOST_STATIC_ASSERT((mpl::sizeof_< HLAoctet::value_type >::value == 1));

    const protox::hla_1516::HLAoctet::value_type *bytes = (HLAoctet::value_type const *)(&obj.value);
    s.start_value();

    encode_basic<
      S,
      codec::static_size_in_bytes<T>::value,
      (T::endian::value != PROTOX_DTL_PLATFORM_ENDIANESS)
    >::pack(s, bytes);

    s.end_value();
  }

  template< typename S, typename T >
  inline static void decode(T &v, const S &s, std::size_t &offset)
  {
    BOOST_STATIC_ASSERT( (mpl::sizeof_< HLAoctet::value_type >::value == 1) );
    HLAoctet::value_type *v_ptr = (HLAoctet::value_type *)(&v.value);

    s.start_value();

    decode_basic<
      S,
      codec::static_size_in_bytes<T>::value,
      (T::endian::value != PROTOX_DTL_PLATFORM_ENDIANESS)
    >::unpack(v_ptr, s, offset);

    s.end_value();
  }
};

template<> struct codec_impl< protox::hla_1516::HLAportable > : basic_codec_impl_1516 {};

template<> struct codec_impl< protox::hla_1516::HLA16BitTwosComplementSigned > : basic_codec_impl_1516 {};

template<> struct codec_impl< protox::hla_1516::HLA32BitTwosComplementSigned > : basic_codec_impl_1516 {};

template<> struct codec_impl< protox::hla_1516::HLA64BitTwosComplementSigned > : basic_codec_impl_1516 {};

template<> struct codec_impl< protox::hla_1516::HLA32BitIEEESinglePrecision > : basic_codec_impl_1516 {};

template<> struct codec_impl< protox::hla_1516::HLA64BitIEEEDoublePrecision > : basic_codec_impl_1516 {};

/**************************************************************************************************/

}} // protox::dtl

/**************************************************************************************************/

#endif

/**************************************************************************************************/
