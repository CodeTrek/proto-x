/*
    Copyright (C) Jay Graham 2008

    Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at 
    http://www.boost.org/LICENSE_1_0.txt)
*/

/**************************************************************************************************/

#ifndef PROTOX_DTL_FIXED_ARRAY_H_
#define PROTOX_DTL_FIXED_ARRAY_H_

/**************************************************************************************************/

#include <boost/static_assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/multiplies.hpp>

/**************************************************************************************************/

using namespace boost;

/**************************************************************************************************/

namespace protox { namespace dtl {

/**************************************************************************************************/

/**
 * @brief Defines a fixed array of size N of elements of type T.
 *
 * Example:
 * @code
 *   #include <dfi/dtel/basic_data_representation_table.hpp>
 *   #include <dfi/dtel/fixed_array.hpp>
 *
 *   using namespace dfi::dtel;
 *
 *   // Define a fixed array of 10 HLAinteger16BE elements.
 *   typedef fixed_array< HLAinteger16BE, 10 > MyFixedArray; 
 * @endcode
 */
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
    for( int i = 0; i < A::static_num_elements; ++i )
    {
      if  (!( lhs[i] == rhs[i] ))
      {
        result = false;
        break;
      }
    }
      
    return result;
  }
  
public:
  /**
   * @brief Read/write array element access.
   *
   * @param i index of the element to be accessed.
   * @return a reference to the element at the given index.
   *
   * Example:
   * @code
   *   #include <dfi/dtel/basic_data_representation_table.hpp>
   *   #include <dfi/dtel/fixed_array.hpp>
   *
   *   using namespace dfi::dtel;
   *
   *   fixed_array< HLAinteger16BE, 10 > myArray;
   *
   *   // Access the 5th element.
   *   HLAinteger16BE v = myArray[4];
   * @endcode
   */
  inline reference operator [] (int i) { return elems[i]; }
  
  /**
   * @brief Read-only array element access.
   *
   * @param i index of the element to be accessed.
   * @return a reference to the element at the given index.
   *
   * Example:
   * @code
   *   #include <dfi/dtel/basic_data_representation_table.hpp>
   *   #include <dfi/dtel/fixed_array.hpp>
   *
   *   using namespace dfi::dtel;
   *
   *   fixed_array< HLAinteger16BE, 10 > myArray;
   *
   *   // Access the 5th element.
   *   HLAinteger16BE v = myArray[4];
   * @endcode
   */
  inline const_reference operator [] (int i) const { return elems[i]; }

    
  /**
   * @brief Test for equality.
   *
   * Performs an element by element comparison of two arrays.
   * @param rhs the array this array is compared to.
   * @return true, if the rhs array is equal to this array.
   */
  inline bool operator == (const fixed_array &rhs) const
  {
    return is_equal(*this, rhs);
  }

  inline bool operator != (const fixed_array &rhs) const
  {
    return !(*this == rhs); 
  }
};

/**************************************************************************************************/

}} // namespace protox::dtl

/**************************************************************************************************/

#endif

/**************************************************************************************************/