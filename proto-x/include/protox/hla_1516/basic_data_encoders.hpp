/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_1516_POLICY_BASIC_ENCODERS_HPP
#define PROTOX_HLA_1516_POLICY_BASIC_ENCODERS_HPP

/**************************************************************************************************/

#include <protox/hla_1516/basic_data_representation_table.hpp>

/**************************************************************************************************/

namespace protox { namespace hla_1516 {

/**************************************************************************************************/

// Basic type encoders
template< typename S >
inline void encode(S &s, char const c)
{
  s.push_back(c);
}

template<
  typename S,                // The destination byte buffer
  std::size_t SIZE_IN_BYTES, // Size of value to be encoded in bytes
  bool CONVERT_ENDIAN        // True, if endian conversion is required
> struct encode_basic;

template< typename S, bool CONVERT_ENDIAN >
struct encode_basic< S, 1, CONVERT_ENDIAN >
{
  static inline void pack(S &s, HLAoctet::value_type const *value)
  {
    s.push_back(value[0]);
  }
};

template< typename S >
struct encode_basic< S, 2, false >
{
  static inline void pack(S &s, HLAoctet::value_type const *value)
  {
    s.push_back(value[0]);
    s.push_back(value[1]);
  }
};

template< typename S >
struct encode_basic< S, 4, false >
{
  static inline void pack(S &s, HLAoctet::value_type const *value)
  {
    s.push_back(value[0]);
    s.push_back(value[1]);
    s.push_back(value[2]);
    s.push_back(value[3]);
  }
};

template< typename S >
struct encode_basic< S, 8, false >
{
  static inline void pack(S &s, HLAoctet::value_type const *value)
  {
    s.push_back(value[0]);
    s.push_back(value[1]);
    s.push_back(value[2]);
    s.push_back(value[3]);
    s.push_back(value[4]);
    s.push_back(value[5]);
    s.push_back(value[6]);
    s.push_back(value[7]);
  }
};

template< typename S >
struct encode_basic< S, 2, true >
{
  static inline void pack(S &s, HLAoctet::value_type const *value)
  {
    s.push_back(value[1]);
    s.push_back(value[0]);
  }
};

template< typename S >
struct encode_basic< S, 4, true >
{
  static inline void pack(S &s, HLAoctet::value_type const *value)
  {
    s.push_back(value[3]);
    s.push_back(value[2]);
    s.push_back(value[1]);
    s.push_back(value[0]);
  }
};

template< typename S >
struct encode_basic< S, 8, true >
{
  static inline void pack(S &s, HLAoctet::value_type const *value)
  {
    s.push_back(value[7]);
    s.push_back(value[6]);
    s.push_back(value[5]);
    s.push_back(value[4]);
    s.push_back(value[3]);
    s.push_back(value[2]);
    s.push_back(value[1]);
    s.push_back(value[0]);
  }
};

/**************************************************************************************************/

}} // protox::hla_1516

/**************************************************************************************************/

#endif

/**************************************************************************************************/
