/**************************************************************************************************/

#ifndef PROTOX_SDX_BASIC_DATA_CODEC_HPP
#define PROTOX_SDX_BASIC_DATA_CODEC_HPP

/**************************************************************************************************/

#include <protox/dtl/codec_interface.hpp>

#include <protox/sdx/codec_tags.hpp>

/**************************************************************************************************/

namespace protox {
namespace dtl {

/**************************************************************************************************/

template<> struct codec_impl< sdx::sdx_portable >
{
  template< typename T >
  struct octet_boundary {};

  template< typename T >
  struct static_size_in_bytes {};

  template< typename T >
  inline static std::size_t dynamic_size( T ) {}

  template< typename S, typename T >
  inline static void encode( S &s, const T &obj ) {}

  template< typename S, typename T >
  inline static void decode( T &v, const S &s, std::size_t &offset ) {}

};

/**************************************************************************************************/

template<> struct codec_impl< sdx::sdx_unsigned_long >
{
  template< typename T >
  struct octet_boundary {};

  template< typename T >
  struct static_size_in_bytes {};

  template< typename T >
  inline static std::size_t dynamic_size( T ) {}

  template< typename S, typename T >
  inline static void encode( S &s, const T &obj ) {}

  template< typename S, typename T >
  inline static void decode( T &v, const S &s, std::size_t &offset ) {}

};

/**************************************************************************************************/

template<> struct codec_impl< sdx::sdx_unsigned_short >
{
  template< typename T >
  struct octet_boundary {};

  template< typename T >
  struct static_size_in_bytes {};

  template< typename T >
  inline static std::size_t dynamic_size( T ) {}

  template< typename S, typename T >
  inline static void encode( S &s, const T &obj ) {}

  template< typename S, typename T >
  inline static void decode( T &v, const S &s, std::size_t &offset ) {}

};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
