/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_IO_BYTE_DATA_SINK_HPP
#define PROTOX_IO_BYTE_DATA_SINK_HPP

/**************************************************************************************************/

#include <cstddef>
#include <vector>

#include <protox/codec/codecs.hpp>

/**************************************************************************************************/

/**
 * \namespace protox::io
 *
 * Byte buffer oriented I/O.
 */

/**************************************************************************************************/

namespace protox {
namespace io {

/**************************************************************************************************/

/**
 * A container that stores bytes in contiguous memory.
 */
class byte_data_sink
{
public:
  byte_data_sink() {};

  /**
   * Encode the given value as an array of bytes.
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
   *
   * assert( pos_out == pos_in ); // true
   *
   * \endcode
   *
   * \sa protox::io::byte_data_source
   *
   */
  template< typename T >
  inline void encode( const T &value )
  {
    protox::dtl::codec::encode( *this, value );
  }

  /**
   * Deletes all encoded data.
   */
  void clear()
  {
    data.clear();
  }

  /**
   * \return a reference to the encoded data buffer.
   */
  const std::vector< char > &getData() const
  {
    return data;
  }

  inline void push_back( char d )
  {
    data.push_back( d );
  }

  /**
   * \return The size in bytes of the buffer.
   */
  std::size_t size() const
  {
    return data.size();
  }

  /**
   * \return a pointer to the encoded data buffer.
   */
  inline const char *getDataBuffer() const
  {
    if( data.empty() )
    {
      return 0;
    }

    return( (const char *) &(data[ 0 ]) );
  }

  inline std::size_t getDataBufferSize() const
  {
    return( data.size() * sizeof( char ) );
  }

  void start_value() {}

  void end_value() {}

  void start_variant_record() {}

  void end_variant_record() {}

  void start_fixed_record() {}

  void end_fixed_record() {}

  void start_field() {}

  void end_field() {}

  void start_fixed_array() {}

  void end_fixed_array() {}

  void start_variable_array() {}

  void end_variable_array() {}

  void start_pad( std::size_t num_pad_bytes ) {}

  void end_pad( std::size_t num_pad_bytes ) {}

  void start_enum() {}

  void end_enum() {}

private:
  byte_data_sink( const byte_data_sink & );
  byte_data_sink &operator = ( const byte_data_sink & );

  std::vector< char > data;
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
