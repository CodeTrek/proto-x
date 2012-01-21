/*
    Copyright (c) 2012 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_SDX_POLICY_BASIC_ENCODERS_HPP
#define PROTOX_SDX_POLICY_BASIC_ENCODERS_HPP

/**************************************************************************************************/

#include <protox/sdx/basic_data_representation_table.hpp>

/**************************************************************************************************/

namespace protox {
namespace xdr {

/**************************************************************************************************/

template<
  typename S,                // The destination byte buffer
  std::size_t SIZE_IN_BYTES, // Size of value to be encoded in bytes
  bool CONVERT_ENDIAN        // True, if endian conversion is required
> struct encode_basic;

/**************************************************************************************************/

template< typename S, bool CONVERT_ENDIAN >
struct encode_basic< S, 1, CONVERT_ENDIAN >
{
  static inline void pack( S &s, SDXByte::value_type const *value )
  {
    s.push_back( value[ 0 ] );
  }
};

/**************************************************************************************************/

template< typename S >
struct encode_basic< S, 2, false >
{
  static inline void pack( S &s, SDXByte::value_type const *value )
  {
    s.push_back( value[ 0 ] );
    s.push_back( value[ 1 ] );
  }
};

/**************************************************************************************************/

template< typename S >
struct encode_basic< S, 4, false >
{
  static inline void pack( S &s, SDXByte::value_type const *value )
  {
    s.push_back( value[ 0 ] );
    s.push_back( value[ 1 ] );
    s.push_back( value[ 2 ] );
    s.push_back( value[ 3 ] );
  }
};

/**************************************************************************************************/

template< typename S >
struct encode_basic< S, 2, true >
{
  static inline void pack( S &s, SDXByte::value_type const *value )
  {
    s.push_back( value[ 1 ] );
    s.push_back( value[ 0 ] );
  }
};

/**************************************************************************************************/

template< typename S >
struct encode_basic< S, 4, true >
{
  static inline void pack( S &s, SDXByte::value_type const *value )
  {
    s.push_back( value[ 3 ] );
    s.push_back( value[ 2 ] );
    s.push_back( value[ 1 ] );
    s.push_back( value[ 0 ] );
  }
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
