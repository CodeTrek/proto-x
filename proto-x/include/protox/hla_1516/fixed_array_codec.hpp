/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_1516_FIXED_ARRAY_CODEC_HPP
#define PROTOX_HLA_1516_FIXED_ARRAY_CODEC_HPP

/**************************************************************************************************/

#include <cstddef>

#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/not_equal_to.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/multiplies.hpp>

#include <protox/dtl/unknown_static_size.hpp>
#include <protox/dtl/codec_interface.hpp>

#include <protox/hla_1516/codec_tags.hpp>
#include <protox/hla_1516/static_pad.hpp>
#include <protox/hla_1516/dynamic_pad.hpp>

/**************************************************************************************************/

using namespace boost;

/**************************************************************************************************/

namespace protox { namespace dtl {

/**************************************************************************************************/

namespace fixed_array_codec_1516 {

/**************************************************************************************************/

template< bool Has_Static_Size > struct _layout;

// Specilization for arrays with fixed size elements.
template<>
struct _layout< true >
{
  // Compute the pad encoder and decoder functions.
  template< typename S, typename T >
  inline static void encode_pad(S &s, typename T::value_type const &)
  {
    typedef typename protox::hla_1516::static_pad_<
      mpl::int_< 0 >,
      typename protox::dtl::codec::static_size_in_bytes<typename T::value_type>::type,
      typename protox::dtl::codec::octet_boundary< typename T::value_type >::type
    >::type static_pad;

    protox::hla_1516::pad< S, static_pad::value >::encode(s);
  }

  template< typename S, typename T >
  inline static void decode_pad(typename T::value_type &, S const &s, std::size_t &offset)
  {
    typedef typename protox::hla_1516::static_pad_<
      mpl::int_< 0 >,
      typename protox::dtl::codec::static_size_in_bytes<typename T::value_type>::type,
      typename protox::dtl::codec::octet_boundary< typename T::value_type >::type
    >::type static_pad;

    protox::hla_1516::pad< S, static_pad::value >::decode(s, offset);
  }

  // Dynamic size is equal to the static size.
  template< typename T >
  inline static std::size_t dynamic_size(T const &)
  {
    // Ensure elements of T have a fixed size.
    BOOST_STATIC_ASSERT((
      protox::dtl::codec::static_size_in_bytes< typename T::value_type >::value != protox::dtl::UNKNOWN_STATIC_SIZE::value
    ));

    return protox::dtl::codec::static_size_in_bytes<T>::value;
  }
};

// Specilization for arrays with variable size elements.
template<>
struct _layout< false >
{
  // Create the functions used to encode and decode the array's padding.
  template< typename S, typename T >
  static void encode_pad(S &s, typename T::value_type const &obj)
  {
    std::size_t const obj_size = protox::dtl::codec::dynamic_size(obj);
    std::size_t const pad_bytes
      = protox::hla_1516::sizeof_pad(
          obj_size,
          protox::dtl::codec::octet_boundary< typename T::value_type >::value);

    protox::hla_1516::encode_pad(s, pad_bytes);
  }

  template< typename S, typename T >
  static void decode_pad(
    typename T::value_type &obj,
    S const &s,
    std::size_t &offset )
  {
    std::size_t const obj_size = protox::dtl::codec::dynamic_size(obj);

    std::size_t const pad_bytes
      = protox::hla_1516::sizeof_pad(
          obj_size,
          protox::dtl::codec::octet_boundary< typename T::value_type >::value);

    protox::hla_1516::decode_pad(s, pad_bytes, offset);
  }

  template< typename T >
  inline static std::size_t dynamic_size(T const &obj)
  {
    // Ensure elements of T are not fixed size.
    BOOST_STATIC_ASSERT((
      protox::dtl::codec::static_size_in_bytes<typename T::value_type>::value == protox::dtl::UNKNOWN_STATIC_SIZE::value
    ));

    std::size_t size = 0; // Used to accumulate T's size.

    // For each element i in the array, except for the last element ...
    for( std::size_t i = 0; i < (T::static_num_elements - 1); ++i )
    {
      std::size_t const obj_size = protox::dtl::codec::dynamic_size(obj[i]);

      // Sum the size of element i and the size of its padding.
      size += obj_size;
      size += protox::hla_1516::sizeof_pad(
        obj_size, protox::dtl::codec::octet_boundary< typename T::value_type >::value);
    }

    // Add the size of the last element in the array.
    size += T::value_type::impl::layout::dynamic_size(obj[T::static_num_elements - 1]);

    return size;
  }
};

// Create this array's impl compile type interface.
template< typename T >
struct impl
{
  // Is this array's size fixed or dynamic?
  typedef mpl::not_equal_to<
    typename protox::dtl::codec::static_size_in_bytes< T >::type, protox::dtl::UNKNOWN_STATIC_SIZE
  > has_static_size;

  typedef _layout< has_static_size::value > type;
};

/**************************************************************************************************/

} // protox::dtl::fixed_array_codec

/**************************************************************************************************/

template<> struct codec_impl< protox::hla_1516::HLAfixedArray >
{
  template< typename T >
  struct octet_boundary
  {
    typedef typename protox::dtl::codec::octet_boundary< typename T::value_type >::type type;
  };

  template< typename T >
  struct static_size_in_bytes
  {
    // Perform a compile-time operation to compute the size of the padding
    // (in bytes) between each element. Note that if the element type T does
    // not have a fixed size, then the padding is computed at run-time.
    typedef typename mpl::if_<
      // Size of T is not fixed?
      mpl::equal_to< typename protox::dtl::codec::static_size_in_bytes<typename T::value_type>::type, protox::dtl::UNKNOWN_STATIC_SIZE >,

      // true : unknown static pad size.
      mpl::int_< protox::dtl::UNKNOWN_STATIC_SIZE::value >,

      // false : compute the static pad size.
      protox::hla_1516::static_pad_<
        mpl::int_< 0 >,
        typename protox::dtl::codec::static_size_in_bytes<typename T::value_type>::type,
        typename protox::dtl::codec::octet_boundary< typename T::value_type >::type
      >
    >::type static_pad;

    // Perform a compile-time operation to compute the total size of the array
    // (in bytes). Note that if the element type T does not have a fixed
    // size, then the total size of the array is computed at run-time.
    typedef typename mpl::if_<
      // Size of T is not fixed?
      mpl::equal_to< typename protox::dtl::codec::static_size_in_bytes<typename T::value_type>::type, protox::dtl::UNKNOWN_STATIC_SIZE >,

      // true : unknown static size.
      protox::dtl::UNKNOWN_STATIC_SIZE,

      // false : compute the total size of the array in bytes.
      mpl::plus<
        mpl::multiplies< mpl::int_< T::static_num_elements >, typename protox::dtl::codec::static_size_in_bytes<typename T::value_type>::type >,
        mpl::multiplies< mpl::int_< T::static_num_elements - 1 >, typename static_pad::type >
      >
    >::type type;
  };

  template< typename T >
  inline static std::size_t dynamic_size(T const &obj)
  {
    return fixed_array_codec_1516::impl<T>::type::dynamic_size(obj);
  };

  template< typename S, typename A >
  inline static void encode(S &s, A const &obj)
  {
    typedef typename fixed_array_codec_1516::impl<A>::type layout;

    s.start_fixed_array();

    // For each element in the array, except for the last ...
    for( int i = 0; i < (A::static_num_elements - 1); ++i )
    {
      protox::dtl::codec::encode(s, obj[i]);
      layout::template encode_pad<S, A>(s, obj[i]);
    }

    // Encode the last element.
    protox::dtl::codec::encode(s, obj[A::static_num_elements - 1]);

    s.end_fixed_array();
  }

  template< typename S, typename A >
  inline static void decode(A &obj, S const &s, std::size_t &offset)
  {
    typedef typename fixed_array_codec_1516::impl<A>::type layout;

    s.start_fixed_array();

    // For each element in the array, except for the last ...
    for( int i = 0; i < (A::static_num_elements - 1); ++i )
    {
      protox::dtl::codec::decode(obj[i], s, offset);
      layout::template decode_pad<S, A>(obj[i], s, offset);
    }

    // Decode the last element.
    protox::dtl::codec::decode(obj[A::static_num_elements - 1], s, offset);

    s.end_fixed_array();
  }
};

/**************************************************************************************************/

}} // protox::dtl

/**************************************************************************************************/

#endif

/**************************************************************************************************/
