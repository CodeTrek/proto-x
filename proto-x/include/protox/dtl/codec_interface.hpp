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
 * decode a value of type \a T. \a T must provide a member type called \c codec_tag, which is used
 * by the templates inside of \c codec to dispatch to concrete implementations that perform the
 * actual encoding and decoding functionality for the type \a T. Concrete encode/decode
 * functionality is implemented in another \c struct called \c codec_impl.
 */
struct codec
{
  /**
   * Computes the octet boundary of \a T at compile time.
   */
  template< typename T >
  struct octet_boundary
  {
    // Forward to codec_impl...
    typedef typename codec_impl< typename T::codec_tag >::template octet_boundary< T >::type type;

    /**
     * The computed value.
     */
    static typename type::value_type const value = type::value;
  };

  /**
   * Compute \a T's size in bytes at compile time. If \a T's size is not static, then
   * <tt>static_size_in_bytes< T >::value</tt> returns <tt>protox::dtl::UNKNOWN_STATIC_SIZE</tt>.
   *
   */
  template< typename T >
  struct static_size_in_bytes
  {
    // Forward to codec_impl...
    typedef typename
      codec_impl< typename T::codec_tag >::template static_size_in_bytes< T >::type type;

    /**
     * The computed value.
     */
    static typename type::value_type const value = type::value;
  };

  /**
   * Compute \a T's size in bytes at run time. If \a T's size is static, then
   * <tt>dynamic_size<T>(const T &v) == static_size_in_bytes< T >::value<\tt>
   * is true for any value \a v.
   *
   * \tparam T The type whose size is to be computed.
   */
  template< typename T >
  inline static std::size_t dynamic_size( const T &obj )
  {
    return codec_impl< typename T::codec_tag >::dynamic_size( obj );
  };

  /**
   * Encodes values of type \a T into a stream of type \a S.
   *
   * \param s The value \a obj is encoded into this stream.
   * \param obj The type of values to be encoded.
   *
   * \tparam S the stream type.
   * \tparam T the type to be encoded.
   */
  template< typename S, typename T >
  inline static void encode( S &s, const T &obj )
  {
    codec_impl< typename T::codec_tag >::encode( s, obj );
  }

  /**
   * Decodes values of type \a T from a stream of type \a S.
   *
   * \param obj Holds the decoded value
   * \param s Contains the value to be decoded
   * \param offset Start decoding \c offset bytes into the stream \c s.
   *
   * \tparam S the stream type.
   * \tparam T the type to be encoded.
   */
  template< typename S, typename T >
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
