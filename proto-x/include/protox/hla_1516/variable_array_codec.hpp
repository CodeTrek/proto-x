/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_1516_VARIABLE_ARRAY_CODEC_HPP
#define PROTOX_HLA_1516_VARIABLE_ARRAY_CODEC_HPP

/**************************************************************************************************/

#include <cstddef>

#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/not_equal_to.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/multiplies.hpp>
#include <boost/mpl/max_element.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/call_traits.hpp>
#include <boost/static_assert.hpp>

#include <protox/dtl/codec_interface.hpp>
#include <protox/dtl/unknown_static_size.hpp>

#include <protox/hla_1516/codec_tags.hpp>
#include <protox/hla_1516/static_pad.hpp>
#include <protox/hla_1516/dynamic_pad.hpp>
#include <protox/hla_1516/size_type.hpp>

/**************************************************************************************************/

namespace protox {
namespace dtl {

/**************************************************************************************************/

namespace variable_array_codec_1516 {

/**************************************************************************************************/

template< typename T >
struct sizeof_header_pad
{
  typedef typename hla_1516::static_pad_<
    boost::mpl::int_< 0 >,
    typename codec::static_size_in_bytes<hla_1516::size_type>::type,
    typename codec::octet_boundary< typename T::value_type >::type
  >::type type;
};

/**************************************************************************************************/

template< typename T >
struct compute_static_pad
{
  typedef typename hla_1516::static_pad_<
    boost::mpl::int_< 0 >,
    typename codec::static_size_in_bytes<typename T::value_type>::type,
    typename codec::octet_boundary< typename T::value_type >::type
  >::type type;
};

/**************************************************************************************************/

template< bool Has_Static_Size > struct layout_;

/**************************************************************************************************/

template<>
struct layout_< true >
{
  template< typename S, typename T >
  inline static void encode_pad( S &s, typename T::value_type const & )
  {
    typedef typename compute_static_pad< T >::type static_pad;
    hla_1516::pad< S, static_pad::value >::encode(s);
  }

  template< typename S, typename T >
  inline static void decode_pad( typename boost::call_traits< typename T::value_type >::param_type,
                                 S const &s,
                                 std::size_t &offset )
  {
    typedef typename compute_static_pad< T >::type static_pad;
    hla_1516::pad< S, static_pad::value >::decode( s, offset );
  }

  template< typename T >
  inline static std::size_t dynamic_size( T const &obj )
  {
    BOOST_STATIC_ASSERT((
      codec::static_size_in_bytes< typename T::value_type >::value !=
      UNKNOWN_STATIC_SIZE::value
    ));

    // Compute the size of the header and then add the size of the elements and padding
    std::size_t size = codec::static_size_in_bytes< hla_1516::size_type >::value;

    if( obj.empty() )
    {
      return size;
    }

    typedef typename compute_static_pad< T >::type static_pad;

    size += sizeof_header_pad<T>::type::value;
    size += (obj.size() * codec::static_size_in_bytes< typename T::value_type >::value);
    size += ((obj.size() - 1) * static_pad::value);

    return( size );
  }
};

/**************************************************************************************************/

template<>
struct layout_< false >
{
  template< typename T >
  inline static std::size_t dynamic_size(T const &obj)
  {
    BOOST_STATIC_ASSERT((
      codec::static_size_in_bytes< typename T::value_type >::value ==
      UNKNOWN_STATIC_SIZE::value
    ));

    std::size_t size = codec::static_size_in_bytes< hla_1516::size_type >::value;

    if( obj.empty() )
    {
      return size;
    }

    size += sizeof_header_pad<T>::type::value;

    std::size_t const num_elements = obj.size();

    for( unsigned i = 0; i < (num_elements - 1); ++i )
    {
      std::size_t const elem_size = codec::dynamic_size( obj[ i ] );

      size += elem_size;

      size +=
        hla_1516::sizeof_pad( elem_size, codec::octet_boundary< typename T::value_type >::value );
    }

    size += codec::dynamic_size( obj[ num_elements - 1 ] );

    return size;
  }

  template< typename S, typename T >
  inline static void encode_pad( S &s, typename T::value_type const &obj )
  {
    std::size_t const obj_size = codec::dynamic_size( obj );

    std::size_t const pad_bytes
      = hla_1516::sizeof_pad( obj_size, codec::octet_boundary< typename T::value_type >::value );

    hla_1516::encode_pad( s, pad_bytes );
  }

  template< typename S, typename T >
  inline static void decode_pad( typename T::value_type &obj, S const &s, std::size_t &offset )
  {
    std::size_t const obj_size = codec::dynamic_size( obj );

    std::size_t const pad_bytes
      = hla_1516::sizeof_pad( obj_size, codec::octet_boundary< typename T::value_type >::value );

    hla_1516::decode_pad( s, pad_bytes, offset );
  }
};

/**************************************************************************************************/

template< typename T >
struct impl
{
  // Are the array elements fixed or dynamic in size?
  typedef boost::mpl::not_equal_to<
    typename codec::static_size_in_bytes< typename T::value_type >::type, UNKNOWN_STATIC_SIZE
  > has_static_size;

  typedef layout_< has_static_size::value > type;
};

/**************************************************************************************************/

}

/**************************************************************************************************/

template<> struct codec_impl< protox::hla_1516::HLAvariableArray >
{
  template< typename T >
  struct octet_boundary
  {
    typedef typename boost::mpl::max<
      typename codec::octet_boundary< typename T::value_type >::type,
      typename codec::octet_boundary< hla_1516::size_type >::type
    >::type type;
  };

  template< typename T >
  struct static_size_in_bytes
  {
    typedef UNKNOWN_STATIC_SIZE::type type;
  };

  template< typename T >
  inline static std::size_t dynamic_size( T const &obj )
  {
    return variable_array_codec_1516::impl< T >::type::dynamic_size( obj );
  };

  template< typename S, typename T >
  inline static void encode( S &s, T const &obj )
  {
    typedef typename variable_array_codec_1516::impl< T >::type layout;

    hla_1516::size_type const num_elements = obj.size();

    s.start_variable_array();

    codec::encode( s, num_elements );

    if( obj.empty() )
    {
      s.end_variable_array();
      return;
    }

    protox::hla_1516::encode_pad( s,
                                  variable_array_codec_1516::sizeof_header_pad< T >::type::value );

    for( int i = 0; i < (num_elements - 1); ++i )
    {
      codec::encode( s, obj[ i ] );
      layout::template encode_pad< S, T >( s, obj[ i ] );
    }

    codec::encode( s, obj[ num_elements - 1 ] );

    s.end_variable_array();
  }

  template< typename S, typename T >
  inline static void decode( T &obj, S const &s, std::size_t &offset )
  {
    typedef typename variable_array_codec_1516::impl< T >::type layout;

    hla_1516::size_type num_elements = 0;

    s.start_variable_array();

    codec::decode( num_elements, s, offset );

    if( num_elements == 0 )
    {
      s.end_variable_array();
      return;
    }

    hla_1516::decode_pad
      ( s, variable_array_codec_1516::sizeof_header_pad< T >::type::value, offset );

    obj.resize( num_elements );

    for( int i = 0; i < (num_elements - 1); ++i )
    {
      codec::decode( obj[ i ], s, offset );
      layout::template decode_pad< S, T >( obj[ i ], s, offset );
    }

    codec::decode( obj[ num_elements - 1 ], s, offset );

    s.end_variable_array();
  }
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
