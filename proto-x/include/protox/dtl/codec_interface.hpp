/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_DTL_CODEC_INTERFACE_HPP
#define PROTOX_DTL_CODEC_INTERFACE_HPP

/**************************************************************************************************/

#include <cstddef>

#include <protox/dtl/codec_impl.hpp>

/**************************************************************************************************/

namespace protox {
namespace dtl {

/**************************************************************************************************/

/**
 * \c codec provides a uniform interface to the \c struct and function templates used to encode and
 * decode a value of type T. T must provide a member type called \c codec_tag, which is used
 * by the templates inside of \c codec to dispatch to concrete implementations that perform the
 * actual encoding and decoding functionality for the type T. Concrete encode/decode
 * functionality is implemented in another \c struct called \c codec_impl.
 */
struct codec
{
  /**
   * Compute T's octet boundary at compile time.
   */
  template< typename T >
  struct octet_boundary
  {
    // Forward to codec_impl...
    typedef typename codec_impl< typename T::codec_tag >::template octet_boundary< T >::type type;

    static typename type::value_type const value = type::value; // The computed value
  };

  // Return T's compile time size in bytes (if known)
  /**
   * Compute T's size in bytes at compile time. If T's size is not static, then
   * <tt>static_size_in_bytes< T >::value</tt> returns <tt>protox::dtl::UNKNOWN_STATIC_SIZE</tt>.
   *
   */
  template< typename T >
  struct static_size_in_bytes
  {
    // Forward to codec_impl...
    typedef typename
      codec_impl< typename T::codec_tag >::template static_size_in_bytes< T >::type type;

    static typename type::value_type const value = type::value; // The computed value
  };

  /**
   * Compute T's size in bytes at run time. If T's size is static, then
   * <tt>dynamic_size<T>(const T &v) == static_size_in_bytes< T >::value<\tt>
   * is true for any value \c v.
   */
  template< typename T >
  inline static std::size_t dynamic_size( const T &obj )
  {
    return codec_impl< typename T::codec_tag >::dynamic_size( obj );
  };

  /**
   * Encodes values of type \c T into a stream of type \S.
   * @param s The value \c obj is encoded into this stream
   * @param obj The type of values to be encoded
   */
  template< typename S, typename T >
  inline static void encode( S &s, const T &obj )
  {
    codec_impl< typename T::codec_tag >::encode( s, obj );
  }

  /**
   * Decodes values of type \c T from a stream of type \S.
   * @param obj Holds the decoded value
   * @param s Contains the value to be decoded
   * @param offset Start decoding \c offset bytes into the stream \c s.
   */
  template<
    typename S,  // The stream type
    typename T > // The type to be encoded
  inline static void decode( T &obj, const S &s, std::size_t &offset )
  {
    codec_impl< typename T::codec_tag >::decode( obj, s, offset );
  }
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
