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
#include <protox/codec/codecs.hpp>

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
  /**
   * Constructs a source initialized with the data from the givne \a sink.
   *
   * \param sink Used to initialize this source's data buffer.
   */
  byte_data_source( const byte_data_sink &sink ) :
    data_buffer(sink.getDataBuffer()),
    data_buffer_size(sink.size())
  {}

  /**
   * Constructs a source that uses the given \a buffer.
   *
   * \param buffer Pointer to an array of bytes of size \a size.
   * \param size The size of the given \a buffer in bytes.
   */
  byte_data_source( const char *buffer, unsigned size ) :
    data_buffer(buffer),
    data_buffer_size(size)
  {}

  /**
   * Decodes a byte array into a value of type \c T and stores the result in \a value.
   *
   * \param value holds the decoded value.
   * \return the number of bytes decoded.
   *
   * Example:
   * \code
   *
   * PositionRecord pos_in;
   *
   * pos_in.f_< X >() = 2;
   * pos_in.f_< Y >() = 3;
   *
   * byte_data_sink sink;
   * sink.encode( pos_in );
   *
   * byte_data_source source( sink );
   *
   * PositionRecord pos_out;
   *
   * sorce.decode( pos_out );
   * assert( pos_out == pos_in ); // true
   *
   * \endcode
   *
   * \sa protox::io::byte_data_sink
   *
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
