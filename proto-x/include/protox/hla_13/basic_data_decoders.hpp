/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_13_BASIC_DATA_DECODERS_HPP
#define PROTOX_HLA_13_BASIC_DATA_DECODERS_HPP

/**************************************************************************************************/

#include <protox/hla_13/basic_data_representation_table.hpp>
#include <protox/hla_13/size_type.hpp>

/**************************************************************************************************/

namespace protox {
namespace hla_13 {

/**************************************************************************************************/

template< typename S >
inline void decode( char &c, const S &s, std::size_t &offset )
{
  c = s[ (unsigned int) offset ];
  ++offset;
}

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
  static inline void unpack( HLA13octet::value_type *value, const S &s, std::size_t &offset )
  {
    *value = s[ (unsigned int) (offset) ];
    ++offset;
  }
};

/**************************************************************************************************/

template< typename S >
struct decode_basic< S, 2, false >
{
  static inline void unpack( HLA13octet::value_type *value, const S &s, std::size_t &offset )
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
  static inline void unpack( HLA13octet::value_type *value, const S &s, std::size_t &offset )
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
struct decode_basic< S, 8, false >
{
  static inline void unpack( HLA13octet::value_type *value, const S &s, std::size_t &offset )
  {
    value[ 0 ] = s[ (unsigned int) (offset + 0) ];
    value[ 1 ] = s[ (unsigned int) (offset + 1) ];
    value[ 2 ] = s[ (unsigned int) (offset + 2) ];
    value[ 3 ] = s[ (unsigned int) (offset + 3) ];
    value[ 4 ] = s[ (unsigned int) (offset + 4) ];
    value[ 5 ] = s[ (unsigned int) (offset + 5) ];
    value[ 6 ] = s[ (unsigned int) (offset + 6) ];
    value[ 7 ] = s[ (unsigned int) (offset + 7) ];

    offset += 8;
  }
};

/**************************************************************************************************/

template< typename S >
struct decode_basic< S, 2, true >
{
  static inline void unpack( HLA13octet::value_type *value, const S &s, std::size_t &offset )
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
  static inline void unpack( HLA13octet::value_type *value, const S &s, std::size_t &offset )
  {
    value[ 3 ] = s[ (unsigned int) (offset + 0) ];
    value[ 2 ] = s[ (unsigned int) (offset + 1) ];
    value[ 1 ] = s[ (unsigned int) (offset + 2) ];
    value[ 0 ] = s[ (unsigned int) (offset + 3) ];

    offset += 4;
  }
};

/**************************************************************************************************/

template< typename S >
struct decode_basic< S, 8, true >
{
  static inline void unpack( HLA13octet::value_type *value, const S &s, std::size_t &offset )
  {
    value[ 7 ] = s[ (unsigned int) (offset + 0) ];
    value[ 6 ] = s[ (unsigned int) (offset + 1) ];
    value[ 5 ] = s[ (unsigned int) (offset + 2) ];
    value[ 4 ] = s[ (unsigned int) (offset + 3) ];
    value[ 3 ] = s[ (unsigned int) (offset + 4) ];
    value[ 2 ] = s[ (unsigned int) (offset + 5) ];
    value[ 1 ] = s[ (unsigned int) (offset + 6) ];
    value[ 0 ] = s[ (unsigned int) (offset + 7) ];

    offset += 8;
  }
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
