/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_13_VARIABLE_ARRAY_CODEC_HPP
#define PROTOX_HLA_13_VARIABLE_ARRAY_CODEC_HPP

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

namespace variable_array_codec_13 {

/**************************************************************************************************/

template< bool Has_Static_Size > struct layout_;

/**************************************************************************************************/

template<>
struct layout_< true >
{
  template< typename T >
  inline static std::size_t dynamic_size( T const &obj )
  {
    BOOST_STATIC_ASSERT((
      codec::static_size_in_bytes< typename T::value_type >::value !=
      UNKNOWN_STATIC_SIZE::value
    ));

    // Compute the size of the header and then add the size of the elements and padding
    std::size_t size = codec::static_size_in_bytes< hla_13::size_type >::value;

    if( obj.empty() )
    {
      return size;
    }

    size += (obj.size() * codec::static_size_in_bytes< typename T::value_type >::value);

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

    std::size_t size = codec::static_size_in_bytes< hla_13::size_type >::value;

    if( obj.empty() )
    {
      return size;
    }

    std::size_t const num_elements = obj.size();

    for( unsigned i = 0; i < num_elements; ++i )
    {
      std::size_t const elem_size = codec::dynamic_size( obj[ i ] );
      size += elem_size;
    }

    return size;
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

template<> struct codec_impl< protox::hla_13::HLA13variableArray >
{
  template< typename T >
  struct octet_boundary
  {
    typedef typename boost::mpl::max<
      typename codec::octet_boundary< typename T::value_type >::type,
      typename codec::octet_boundary< hla_13::size_type >::type
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
    return variable_array_codec_13::impl< T >::type::dynamic_size( obj );
  };

  template< typename S, typename T >
  inline static void encode( S &s, T const &obj )
  {
    hla_13::size_type const num_elements = obj.size();

    s.start_variable_array();

    codec::encode( s, num_elements );

    if( obj.empty() )
    {
      s.end_variable_array();
      return;
    }

    for( int i = 0; i < num_elements; ++i )
    {
      codec::encode( s, obj[ i ] );
    }

    s.end_variable_array();
  }

  template< typename S, typename T >
  inline static void decode( T &obj, S const &s, std::size_t &offset )
  {
    hla_13::size_type num_elements = 0;

    s.start_variable_array();

    codec::decode( num_elements, s, offset );

    if( num_elements == 0 )
    {
      s.end_variable_array();
      return;
    }

    obj.resize( num_elements );

    for( int i = 0; i < num_elements; ++i )
    {
      codec::decode( obj[ i ], s, offset );
    }

    s.end_variable_array();
  }
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
