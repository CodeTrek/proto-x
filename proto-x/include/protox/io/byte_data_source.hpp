/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_IO_BYTE_DATA_SOURCE_HPP
#define PROTOX_IO_BYTE_DATA_SOURCE_HPP

/**************************************************************************************************/

#include <cstddef>
#include <assert.h>

#include <protox/io/byte_data_sink.hpp>
#include <protox/dtl/codec.hpp>

/**************************************************************************************************/

namespace protox {
namespace io {

/**************************************************************************************************/

/**
 * A wrapper class for an array of bytes.
 */
class byte_data_source
{
public:
  byte_data_source( const byte_data_sink &sink ) :
    data_buffer(sink.getDataBuffer()),
    data_buffer_size(sink.size())
  {}

  byte_data_source( const char *buffer, unsigned size ) :
    data_buffer(buffer),
    data_buffer_size(size)
  {}

  /**
   * Decodes this byte array into a value of type T and stores the result in value.
   *
   * @param value holds the decoded value.
   * @return the number of bytes decoded.
   */
  template< typename T >
  inline unsigned decode( T &value ) const
  {
    std::size_t offset = 0;
    protox::dtl::codec::decode( value, *this, offset );

    return (unsigned) offset;
  }

  inline char operator[]( unsigned i ) const
  {
    assert( i < data_buffer_size );
    return data_buffer[ i ];
  }

  void start_value() const {}

  void end_value() const {}

  void start_variant_record() const {}

  void end_variant_record() const {}

  void start_fixed_record() const {}

  void end_fixed_record() const {}

  void start_field() const {}

  void end_field() const {}

  void start_fixed_array() const {}

  void end_fixed_array() const {}

  void start_variable_array() const {}

  void end_variable_array() const {}

  void start_pad( std::size_t num_pad_bytes ) const {}

  void end_pad( std::size_t num_pad_bytes ) const {}

  void start_enum() const {}

  void end_enum() const {}

private:
  byte_data_source( const byte_data_source & );
  byte_data_source &operator = ( const byte_data_source & );

  const char *data_buffer;
  const std::size_t data_buffer_size;
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
