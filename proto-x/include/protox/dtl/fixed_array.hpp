/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_DTL_FIXED_ARRAY_HPP
#define PROTOX_DTL_FIXED_ARRAY_HPP

/**************************************************************************************************/

#include <boost/static_assert.hpp>

/**************************************************************************************************/

namespace protox {
namespace dtl {

/**************************************************************************************************/

/**
 * Constructs a fixed array of size \a N with elements of type \a T.
 *
 * \tparam T The array's element type.
 * \tparam N The size of the array i.e., the number of elements.
 * \tparam CODEC_TAG The encode/decode policy.
 *
 * Example:
 *
 * \code
 *  // Define a simple type
 *  struct SimpleHLAoctet : simple< HLAoctet > {};
 *
 *  // Define a fixed array using 1516 fixed record encoding
 *  typedef fixed_array< HLAoctet, 10, HLAfixedArray > fixed_array_type;
 *
 * \endcode
 *
 */

template< typename T, int N, typename CODEC_TAG >
struct fixed_array
{
public:
  static const int static_num_elements = N;

/// \cond
  typedef CODEC_TAG codec_tag;
/// \endcond

  typedef T value_type;
  typedef T& reference;             
  typedef const T& const_reference; 

private:
  BOOST_STATIC_ASSERT(( N > 0 ));

  T elems[ N ];

  template< typename A >
  static bool is_equal( const A &lhs, const A &rhs )
  {
    bool result = true;

    // Test each element in the array for equality.
    for( int i = 0; i < A::static_num_elements; ++i )
    {
      if( !(lhs[ i ] == rhs[ i ]) )
      {
        result = false;
        break;
      }
    }
      
    return result;
  }
  
public:
  /**
   * Read/write access to the element at the given zero-based index.
   *
   * \param i The zero-based index.
   *
   * \return A reference to the element at index \a i.
   */
  inline reference operator [] ( int i ) { return elems[i]; }
  
  /**
   * Read-only access to the element at the given zero-based index.
   *
   * \param i The zero-based index.
   *
   * \return A \c const reference to the element at index \a i.
   */
  inline const_reference operator [] ( int i ) const { return elems[i]; }

  /**
   * Performs an element-by-element test of this array with the given array for equality. Two arrays
   * are equal if their elements are equal.
   *
   * \param rhs The right hand side of the equality operator.
   */
  inline bool operator == ( const fixed_array &rhs ) const
  {
    return is_equal( *this, rhs );
  }

  /**
   * Performs an element-by-element test of this array with the given array for inequality. Two
   * arrays are not equal if at least one element is not equal.
   *
   * \param rhs The right hand side of the inequality operator.
   */
  inline bool operator != ( const fixed_array &rhs ) const
  {
    return !( *this == rhs ); 
  }
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
