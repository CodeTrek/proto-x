/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_DTL_FIXED_RECORD_HPP
#define PROTOX_DTL_FIXED_RECORD_HPP

/**************************************************************************************************/

#include <boost/mpl/inherit.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/empty_base.hpp>

#include <boost/mpl/lambda.hpp>

#include <protox/dtl/field.hpp>

/**************************************************************************************************/

namespace protox {
namespace dtl {

/**************************************************************************************************/

/**
 * The <tt>fixed_record template struct</tt> constructs a fixed record definition from a given
 * vector of field types.
 *
 * The structure of a fixed record is built using series of derivations under the control of a
 * reverse fold meta-function. The reverse fold builds a derivation chain by applying the
 * <tt>boost::mpl::inherit</tt> binary operation to the elements of the given field vector in a
 * pair-wise fashion.
 *
 * The following pseudo code illustrates how the reverse fold meta-function works:
 *
 * Given the following definitions:
 \verbatim
      struct empty {};                    // Same as boost::mpl::empty_base

      template< typename L, typename H >
      struct derive : L, H {};            // Same as boost::mpl::inherit

      V = < F1, F2, F3 >;                 // A vector of types
\endverbatim
 *
 * Applying the reverse fold like this:\n
 *
 *<tt>reverse_fold< V, empty, derive< _2, _1 > ></tt>\n
 *
 * results in a type that is structured like this:\n
 *
 * Fold 1 (first application of derive):\n
 *   <tt>derive< F1, reverse_fold< <F2, F3>, empty, derive<_2, _1> > ></tt>
 *
 * Fold 2 (second application of derive):\n
 *    <tt>derive< F1, derive< F2, reverse_fold< <F3>, empty, derive<_2, _1> > ></tt>
 *
 * Fold 3 (final application of derive):\n
 *    <tt>derive< F1, derive< F2, derive< F3, empty > > ></tt>
 *
 * Expanding the definition of derive yields:
 \verbatim
          F3  empty
           \  /
        F2 derive
         \  /
      F1 derive
       \  /
       derive
         |
    fixed_record
 \endverbatim

 * Note that the data type derived from this application of the reverse fold meta-function is a
 * is essentially equivalent to this POD \c struct:

 \code
    struct fixed_record
    {
      F1 f1;
      F2 f2;
      F3 f3;
    };
 \endcode
 */

template< typename FIELD_VECTOR, typename CODEC_TAG >
struct fixed_record : public boost::mpl::reverse_fold<
  FIELD_VECTOR,
  boost::mpl::empty_base,
  boost::mpl::inherit<
    field_base< boost::mpl::placeholders::_2 >, boost::mpl::placeholders::_1 >
>::type
{
  BOOST_STATIC_ASSERT(( boost::mpl::empty< FIELD_VECTOR >::value != true ));

  typedef CODEC_TAG codec_tag;

  typedef FIELD_VECTOR field_vector;

  struct null_field_compare
  {
    template< typename R >
    static bool is_equal( const R &, const R & ) { return true; }
  };

  template<
    typename T,     // The type of the field of record R to be compared
    typename Base > // The partial record formed by T's predecessor fields.
  struct field_compare
  {
    /**
     * Compare two fixed records of type R for equality.
     *
     * @param lhs Left hand side of the equality operator
     * @param rhs Right hand side of the equality operator
     */
    template< typename R >
    static bool is_equal( const R &lhs, const R &rhs )
    {
      typename T::value_type const &lhs_value = lhs.template f_< T >();
      typename T::value_type const &rhs_value = rhs.template f_< T >();

      if( !(lhs_value == rhs_value) )
      {
        return false;
      }

      return Base::is_equal( lhs, rhs );
    }
  };

  /**
   * Equality operator.
   * @param rhs The right hand side of the equality operator.
   */
  inline bool operator == ( const fixed_record &rhs ) const
  {
    // Construct a function that performs field-wise comparisons of the fields defined by
    // \c FIELD_VECTOR.
    typedef typename boost::mpl::fold<
      FIELD_VECTOR,
      null_field_compare,
      field_compare< boost::mpl::placeholders::_2, boost::mpl::placeholders::_1 >
    >::type type;

    return type::is_equal( *this, rhs );
  }

  /**
   * Inequality operator.
   * @param rhs The right hand side of the inequality operator.
   */
  inline bool operator != ( const fixed_record &rhs ) const
  {
    return !(*this == rhs);
  }

  /**
   * @returns a \c const reference to the field value identified by \c typename T.
   */
  template< typename T >
  inline typename T::value_type const &f_() const
  {
    return( static_cast< const field_base< T > & >( *this ).value );
  }

  /**
   * Returns a read/write reference to the field value identified by \c typename T.
   */
  template< typename T >
  inline typename T::value_type &f_()
  {
    return( static_cast< field_base< T > & >( *this ).value );
  }
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
