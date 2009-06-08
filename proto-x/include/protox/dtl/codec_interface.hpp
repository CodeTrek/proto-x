/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_DTL_CODEC_INTERFACE_HPP
#define PROTOX_DTL_CODEC_INTERFACE_HPP

/******************************************************************************/

#include <cstddef>

#include <protox/dtl/codec_impl.hpp>

/******************************************************************************/

namespace protox { namespace dtl {

/******************************************************************************/

// Compile time polymorphic interface to codec_impl
struct codec
{
  // Return T's octet_boundary
  template< typename T >
  struct octet_boundary
  {
    typedef typename codec_impl<
      typename T::codec_tag
    >::template octet_boundary< T >::type type;

    static typename type::value_type const value = type::value;
  };

  // Return T's compile time size in bytes (if known)
  template< typename T >
  struct static_size_in_bytes
  {
    typedef typename codec_impl<
      typename T::codec_tag
    >::template static_size_in_bytes< T >::type type;

    static typename type::value_type const value = type::value;
  };

  // Return T's runtime size in bytes
  template< typename T >
  inline static std::size_t dynamic_size( const T &obj )
  {
    return codec_impl< typename T::codec_tag >::dynamic_size( obj );
  };

  template<
    typename S,  // The stream type
    typename T > // The type to be encoded
  inline static void encode( S &s, const T &obj )
  {
    codec_impl< typename T::codec_tag >::encode( s, obj );
  }

  template<
    typename S,  // The stream type
    typename T > // The type to be encoded
  inline static void decode( T &obj, const S &s, std::size_t &offset )
  {
    codec_impl< typename T::codec_tag >::decode( obj, s, offset );
  }
};

/******************************************************************************/

}} // protox::dtl

/******************************************************************************/

#endif

/******************************************************************************/
