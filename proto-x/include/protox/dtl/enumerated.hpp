/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_DTL_ENUMERATED_HPP
#define PROTOX_DTL_ENUMERATED_HPP

/******************************************************************************/

namespace protox { namespace dtl {

/******************************************************************************/

// A base class for representing enumerated types. Concrete enumerated types
// must derive from this class.
//
// Example:
//
//   class MyEnum : public dtl::enumerated< MyEnum, HLAinteger32BE > {...};
//
// E The concrete enumerated type.
// T The basic data type used to represent values of the enumerated type.

template< typename E, typename T, typename CODEC_TAG >
class enumerated
{
public:
  typedef CODEC_TAG codec_tag;
  typedef T value_type;

  // Some helpful operators.
  enumerated &operator = (const enumerated &rhs)
  {
    if (this == &rhs)
      return (*this);

    value = rhs.value;

    return (*this);
  }

  bool operator == (const enumerated &rhs) const
  {
    return E::is_equal(value, rhs.value);
  }

  bool operator != (const enumerated &rhs) const
  {
    return !(E::is_equal( value, rhs.value ));
  }

protected:
  T value;

protected:
  enumerated() {}
  enumerated(const T v) : value(v) {}
  enumerated(const enumerated &v) : value(v.value) {}
};

/******************************************************************************/

}} // protox::dtl

/******************************************************************************/

#endif

/******************************************************************************/
