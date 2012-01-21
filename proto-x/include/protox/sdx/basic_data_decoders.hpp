/*
    Copyright (c) 2012 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_SDX_BASIC_DATA_DECODERS_HPP
#define PROTOX_SDX_BASIC_DATA_DECODERS_HPP

/**************************************************************************************************/

#include <protox/sdx/basic_data_representation_table.hpp>

/**************************************************************************************************/

namespace protox {
namespace sdx {

/**************************************************************************************************/

template<
  typename S,                // Source byte buffer
  std::size_t SIZE_IN_BYTES, // Size of value to be decoded in bytes
  bool CONVERT_ENDIAN        // True, if endian conversion is required during
                             // decoding
> struct decode_basic;

/**************************************************************************************************/

template< typename S, bool CONVERT_ENDIAN >
struct decode_basic< S, 1, CONVERT_ENDIAN >
{
  static inline void unpack( SDXByte::value_type *value, const S &s, std::size_t &offset )
  {
    *value = s[ (unsigned int) (offset) ];
    ++offset;
  }
};

/**************************************************************************************************/

template< typename S >
struct decode_basic< S, 2, false >
{
  static inline void unpack( SDXByte::value_type *value, const S &s, std::size_t &offset )
  {
    value[ 0 ] = s[ (unsigned int) (offset + 0) ];
    value[ 1 ] = s[ (unsigned int) (offset + 1) ];

    offset += 2;
  }
};

/**************************************************************************************************/

template< typename S >
struct decode_basic< S, 4, false >
{
  static inline void unpack( SDXByte::value_type *value, const S &s, std::size_t &offset )
  {
    value[ 0 ] = s[ (unsigned int) (offset + 0) ];
    value[ 1 ] = s[ (unsigned int) (offset + 1) ];
    value[ 2 ] = s[ (unsigned int) (offset + 2) ];
    value[ 3 ] = s[ (unsigned int) (offset + 3) ];

    offset += 4;
  }
};

/**************************************************************************************************/

template< typename S >
struct decode_basic< S, 2, true >
{
  static inline void unpack( SDXByte::value_type *value, const S &s, std::size_t &offset )
  {
    value[ 1 ] = s[ (unsigned int) (offset + 0) ];
    value[ 0 ] = s[ (unsigned int) (offset + 1) ];

    offset += 2;
  }
};

/**************************************************************************************************/

template< typename S >
struct decode_basic< S, 4, true >
{
  static inline void unpack( SDXByte::value_type *value, const S &s, std::size_t &offset )
  {
    value[ 3 ] = s[ (unsigned int) (offset + 0) ];
    value[ 2 ] = s[ (unsigned int) (offset + 1) ];
    value[ 1 ] = s[ (unsigned int) (offset + 2) ];
    value[ 0 ] = s[ (unsigned int) (offset + 3) ];

    offset += 4;
  }
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
