/*
    Copyright (c) 2010 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_XDR_FIXED_LENGTH_OPAQUE_CODEC_HPP
#define PROTOX_XDR_FIXED_LENGTH_OPAQUE_CODEC_HPP

/**************************************************************************************************/

#include <cstddef>

#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/not_equal_to.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/multiplies.hpp>

#include <protox/dtl/codec_interface.hpp>

#include <protox/xdr/codec_tags.hpp>
#include <protox/xdr/basic_data_representation_table.hpp>

/**************************************************************************************************/

namespace protox {
namespace dtl {

/**************************************************************************************************/

template<> struct codec_impl< protox::xdr::xdr_fixed_length_opaque >
{
private:
  template< int N >
  struct num_pad_bytes
  {
    static const int value = boost::mpl::int_< ((4 - (N % 4)) % 4) >::value;
  };

public:
  template< typename T >
  struct octet_boundary
  {
    typedef typename boost::mpl::int_< 4 >::type type;
  };

  template< typename T >
  struct static_size_in_bytes
  {
    typedef typename boost::mpl::int_<
      T::static_num_elements + num_pad_bytes< T::static_num_elements >::value
    >::type type;
  };

  template< typename T >
  inline static std::size_t dynamic_size( T const &obj )
  {
    return static_size_in_bytes< T >::type::value;
  };

  template< typename S, typename A >
  inline static void encode( S &s, A const &obj )
  {
    s.start_fixed_array();

    int i = 0;

    for (i = 0; i < A::static_num_elements; ++i)
    {
      codec::encode( s, obj[ i ] );
    }

    static const protox::xdr::Opaque ZERO_BYTE = 0;

    for (i = 0; i < num_pad_bytes< A::static_num_elements >::value; ++i )
    {
      codec::encode( s, ZERO_BYTE );
    }

    s.end_fixed_array();
  }

  template< typename S, typename A >
  inline static void decode( A &obj, S const &s, std::size_t &offset )
  {
    s.start_fixed_array();

    // For each element in the array...
    for( int i = 0; i < A::static_num_elements; ++i )
    {
      codec::decode( obj[ i ], s, offset );
    }

    // Add pad bytes
    offset += num_pad_bytes< A::static_num_elements >::value;

    s.end_fixed_array();
  }
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
