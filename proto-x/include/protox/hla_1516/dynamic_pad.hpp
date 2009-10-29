/*
    Copyright 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_1516_DYNAMIC_PAD_HPP
#define PROTOX_HLA_1516_DYNAMIC_PAD_HPP

/**************************************************************************************************/

#include <cstddef>

#include <protox/platform.hpp>
#include <protox/dtl/codec.hpp>

#include <protox/hla_1516/basic_data_representation_table.hpp>
#include <protox/hla_1516/size_type.hpp>

/**************************************************************************************************/

namespace protox {
namespace hla_1516 {

/**************************************************************************************************/

// Compute pad size in bytes based on the given data type size and octet boundary.
//
// size          The size of a data type in bytes.
// octet_boundary The octet boundary of a data type in bytes.
inline std::size_t sizeof_pad( std::size_t size, std::size_t octet_boundary )
{
  std::size_t const remainder = size % octet_boundary;

  if ( remainder == 0 )
  {
    return 0;
  }

  return( octet_boundary - remainder );
}

/**************************************************************************************************/

// Encoded pad bytes.
//
// s        The data sink stream.
// numBytes The number of pad bytes to encode.
template< typename S >
inline void encode_pad( S &s, std::size_t numBytes )
{
  s.start_pad( numBytes );

  for( std::size_t i = 0; i < numBytes; ++i )
  {
    protox::dtl::codec::encode( s, HLAoctet( PROTOX_DTL_PAD_CHARACTER ) );
  }

  s.end_pad( numBytes );
}

/**************************************************************************************************/

template< typename S >
inline void decode_pad( const S &s, std::size_t numBytes, std::size_t &offset )
{
  s.start_pad( numBytes );
  offset += numBytes;
  s.end_pad( numBytes );
}

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
