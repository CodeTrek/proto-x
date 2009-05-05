/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_DTL_BASIC_HPP
#define PROTOX_DTL_BASIC_HPP

/**************************************************************************************************/

#include <cstddef>

#include <boost/static_assert.hpp>
#include <boost/type_traits/has_trivial_constructor.hpp>

#include <protox/platform.hpp>
#include <protox/dtl/endian_enum.hpp>
#include <protox/dtl/basic_tag.hpp>

/**************************************************************************************************/

namespace protox { namespace dtl {

/**************************************************************************************************/

using namespace boost;

/**************************************************************************************************/

// This is a type generator for basic data representations. Basic data representations
// form the foundation of the protox::dtl type sytem. All simple, enumerated, and
// constructed types are built using basic data representations.

// basic associates C++ type T with the given size in bits and endian representation code.

template<
  typename T,          // T            The native type used to represent the basic data
                       //              representation being defined.

  int SIZE_IN_BITS,    // SIZE_IN_BITS The size of the data representation in bits. This value
                       //              does not have to equal size of T in bits.

  typename ENDIAN,     // ENDIAN       Specifies either big, little, or na endianess.

  typename CODEC_TAG > // CODEC_TAG    The tag used to determine how values of this type are
                       //              encoded and decoded.
struct basic : basic_tag
{

/**************************************************************************************************/

  // Test for valid template arguments:

  // T is default constructable?
  BOOST_STATIC_ASSERT( (has_trivial_constructor< T >::value) );

  // Valid size?
  BOOST_STATIC_ASSERT( (SIZE_IN_BITS > 0) );

  // Valid endian-ness?
  BOOST_STATIC_ASSERT(
    ( ENDIAN::value == endian::little::value ) ||
    ( ENDIAN::value == endian::big::value    ) ||
    ( ENDIAN::value == endian::na::value     )
  );

/**************************************************************************************************/

  typedef CODEC_TAG codec_tag;
  typedef ENDIAN endian;
  typedef T value_type;

/**************************************************************************************************/

  enum{ size_in_bits = SIZE_IN_BITS };

/**************************************************************************************************/

  T value;

/**************************************************************************************************/

  basic() : value(T()) {}

  // Implicit conversion from T to basic
  basic(const T v) : value(v) {}

/**************************************************************************************************/

  // Implicit conversion from basic to T
  inline operator T() const
  {
    return value;
  }

  inline basic &operator ++()
  {
    ++value;
    return (*this);
  }

  inline basic &operator +=(const basic &v)
  {
    value += v;
    return (*this);
  }

  // Enable numerical assignment.
  // For example, assignment of float to int, assignment int to float, etc...
  template< typename RHST >
  basic &operator =(const RHST rhs)
  {
    value = rhs;
    return (*this);
  }
};

#ifdef WIN32
#define PROTOX_BASIC(basic_name)                \
  basic_name() {}                               \
  basic_name(basic::value_type v) : basic(v) {}
#else
#define PROTOX_BASIC(basic_name)                                                                                        \
  basic_name() {}                                                                                                       \
  typedef basic<basic_name::value_type, basic_name::size_in_bits, basic_name::endian, basic_name::codec_tag> base_type; \
  basic_name(base_type::value_type v) : base_type(v) {}
#endif


/**************************************************************************************************/

}} // protox::dtl

/**************************************************************************************************/

#endif

/**************************************************************************************************/
