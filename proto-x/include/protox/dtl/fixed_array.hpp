/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_DTL_FIXED_ARRAY_HPP
#define PROTOX_DTL_FIXED_ARRAY_HPP

/******************************************************************************/

#include <boost/static_assert.hpp>

/******************************************************************************/

namespace protox { namespace dtl {

/******************************************************************************/

template< typename T, int N, typename CODEC_TAG >
struct fixed_array
{
public:
  typedef CODEC_TAG codec_tag;

  BOOST_STATIC_ASSERT((N > 0));

  static const int static_num_elements = N;

  typedef T value_type;
  typedef T& reference;             
  typedef const T& const_reference; 

private:
  T elems[N];

  template< typename A >
  static bool is_equal(const A &lhs, const A &rhs)
  {
    bool result = true;

    // Test each element in the array for equality.
    for (int i = 0; i < A::static_num_elements; ++i)
    {
      if (!(lhs[i] == rhs[i]))
      {
        result = false;
        break;
      }
    }
      
    return result;
  }
  
public:
  inline reference operator [] (int i) { return elems[i]; }
  
  inline const_reference operator [] (int i) const { return elems[i]; }
    
  inline bool operator == (const fixed_array &rhs) const
  {
    return is_equal(*this, rhs);
  }

  inline bool operator != (const fixed_array &rhs) const
  {
    return !(*this == rhs); 
  }
};

/******************************************************************************/

}} // protox::dtl

/******************************************************************************/

#endif

/******************************************************************************/
