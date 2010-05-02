/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_XDR_VARIABLE_LENGTH_ARRAY_CODEC_HPP
#define PROTOX_XDR_VARIABLE_LENGTH_ARRAY_CODEC_HPP

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

#include <protox/xdr/codec_tags.hpp>
#include <protox/xdr/basic_data_representation_table.hpp>

/**************************************************************************************************/

namespace protox {
namespace dtl {

/**************************************************************************************************/

namespace xdr_variable_length_array_codec {

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
    std::size_t size = codec::static_size_in_bytes< protox::xdr::UnsignedInteger >::value;

    if (obj.empty())
    {
      return size;
    }

    size += (obj.size() * codec::static_size_in_bytes< typename T::value_type >::value);

    return (size);
  }
};

/**************************************************************************************************/

template<>
struct layout_< false >
{
  template< typename T >
  inline static std::size_t dynamic_size( T const &obj )
  {
    BOOST_STATIC_ASSERT((
      codec::static_size_in_bytes< typename T::value_type >::value ==
      UNKNOWN_STATIC_SIZE::value
    ));

    std::size_t size = codec::static_size_in_bytes< protox::xdr::UnsignedInteger >::value;

    if (obj.empty())
    {
      return size;
    }

    std::size_t const num_elements = obj.size();

    for (unsigned i = 0; i < num_elements; ++i)
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

template<> struct codec_impl< protox::xdr::xdr_variable_length_array  >
{
  template< typename T >
  struct octet_boundary
  {
    typedef typename boost::mpl::max<
      typename codec::octet_boundary< typename T::value_type >::type,
      typename codec::octet_boundary< protox::xdr::UnsignedInteger >::type
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
    return xdr_variable_length_array_codec::impl< T >::type::dynamic_size( obj );
  };

  template< typename S, typename T >
  inline static void encode( S &s, T const &obj )
  {
    protox::xdr::UnsignedInteger const num_elements = obj.size();

    s.start_variable_array();

    codec::encode( s, num_elements );

    if (obj.empty())
    {
      s.end_variable_array();
      return;
    }

    for (unsigned i = 0; i < num_elements; ++i)
    {
      codec::encode( s, obj[ i ] );
    }

    s.end_variable_array();
  }

  template< typename S, typename T >
  inline static void decode( T &obj, S const &s, std::size_t &offset )
  {
    protox::xdr::UnsignedInteger num_elements = 0;

    s.start_variable_array();

    codec::decode( num_elements, s, offset );

    if (num_elements == 0)
    {
      obj.clear();
      s.end_variable_array();
      return;
    }

    obj.resize( num_elements );

    for (int i = 0; i < num_elements; ++i)
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
