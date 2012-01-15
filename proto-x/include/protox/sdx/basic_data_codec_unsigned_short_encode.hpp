/**************************************************************************************************/

#ifndef PROTOX_SDX_BASIC_DATA_CODEC_HPP
#define PROTOX_SDX_BASIC_DATA_CODEC_HPP

/**************************************************************************************************/

#include <boost/mpl/int.hpp>

#include <protox/dtl/codec_interface.hpp>
#include <protox/dtl/compute_octet_boundary.hpp>

#include <protox/sdx/codec_tags.hpp>

/**************************************************************************************************/

namespace protox {
namespace dtl {

/**************************************************************************************************/

template<
  typename S,         // The destination byte buffer
  bool CONVERT_ENDIAN // true, if endian conversion is required
> struct encode_basic;

// Byte reordering is required
template< typename S >
struct encode_basic< S, true >
{
  static inline void pack( S &s, SDXByte::value_type const *value )
  {
    s.push_back( value[1] );
    s.push_back( value[0] );
  }
};

// Byte reordering is _not_ required
template< typename S >
struct encode_basic< S, false >
{
  static inline void pack( S &s, SDXByte::value_type const *value )
  {
    s.push_back( value[0] );
    s.push_back( value[1] );
  }
};

template<> struct codec_impl< sdx::sdx_unsigned_short >
{
  // ...

  template< typename S, typename T >
  inline static void encode( S &s, const T &obj )
  {
    const sdx::SDXByte::value_type *bytes = (xdr::SDXByte::value_type const *)( &obj.value );

    encode_basic< S, (T::endianess::value != PROTOX_DTL_PLATFORM_ENDIANESS) >::pack( s, bytes );
  }

  // ...
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
