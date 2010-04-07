/*
    Copyright (c) 2010 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_XDR_VARIABLE_LENGTH_OPAQUE_CODEC_HPP
#define PROTOX_XDR_VARIABLE_LENGTH_OPAQUE_CODEC_HPP

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

template<> struct codec_impl< protox::xdr::xdr_variable_length_opaque >
{
private:
  static unsigned num_pad_bytes( const unsigned N )
  {
    return ((4 -(N % 4)) % 4);
  }

public:
  template< typename T >
  struct octet_boundary
  {
    typedef typename boost::mpl::int_< 4 >::type type;
  };

  template< typename T >
  struct static_size_in_bytes
  {
    typedef UNKNOWN_STATIC_SIZE::type type;
  };

  template< typename T >
  inline static std::size_t dynamic_size( T const &obj )
  {
    assert( obj.size() <= T::UPPER_BOUND );

    return (   codec::static_size_in_bytes< xdr::UnsignedInteger >::value
             + obj.size()
             + num_pad_bytes( obj.size() ));
  };

  template< typename S, typename A >
  inline static void encode( S &s, A const &obj )
  {
    assert( obj.size() <= A::UPPER_BOUND );

    s.start_variable_array();

    codec::encode( s, A::UPPER_BOUND );

    int i = 0;

    for (i = 0; i < obj.size(); ++i)
    {
      codec::encode( s, obj[ i ] );
    }

    static const Opaque ZERO_BYTE = 0;

    for (i = 0; i < num_pad_bytes( obj.size() ); ++i )
    {
      ecode::encode( s, ZERO_BYTE );
    }

    s.end_variable_array();
  }

  template< typename S, typename A >
  inline static void decode( A &obj, S const &s, std::size_t &offset )
  {
    s.start_fixed_array();

    xdr::UnsignedInteger num_elements = 0;

    codec::decode( num_elements, s, offset )

    if (num_elements == 0)
    {
      obj.clear();
      s.end_variable_array();
      return;
    }

    obj.resize( num_elements );

    for( unsigned i = 0; i < num_elements; ++i )
    {
      codec::decode( obj[ i ], s, offset );
    }

    // Add pad bytes
    offset += num_pad_bytes( num_elements );

    s.end_variable_array();
  }
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
