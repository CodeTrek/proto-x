/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_DTL_FIXED_RECORD_HPP
#define PROTOX_DTL_FIXED_RECORD_HPP

/******************************************************************************/

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

/******************************************************************************/

namespace protox { namespace dtl {

/******************************************************************************/

// The fixed_record template constructs a fixed record definition from the
// given vector of field types.
//
// The structure of a fixed record is built using series of derivations under
// the control of a reverse fold meta-function. The reverse fold builds a
// derivation chain by applying the mpl::inherit binary operation to
// the elements of the given field vector in a pair-wise fashion.
//
// The following pseudo code illustrates how the reverse fold meta-function
// works:
//
// Given the following definitons:
//    struct empty {};                    // Same as mpl::empty_base
//
//    template< typename L, typename H >
//    struct derive : L, H {};            // Same as mpl::inherit
//
//    V = < F1, F2, F3 >;                 // A vector of types
//
// Applying the reverse fold like this:
//
//    reverse_fold< V, empty, derive< _2, _1 > >
//
// results in a type that is structured like this:
//
// Fold 1 (first application of derive):
//   derive< F1, reverse_fold< <F2, F3>, empty, derive<_2, _1> > >
//
// Fold 2 (second application of derive):
//    derive< F1, derive< F2, reverse_fold< <F3>, empty, derive<_2, _1> > >

// Fold 3 (final application of derive):
//    derive< F1, derive< F2, derive< F3, empty > > >
//
// Expanding the defintion of derive yields:
//
//        F3  empty
//         \  /
//      F2 derive
//       \  /
//    F1 derive
//     \  /
//     derive
//       |
//  fixed_record
//
// Note that the data type derived from this application of the
// reverse fold meta-function is a C++ plain old datatype (POD), and is
// essentially equivalent to this POD struct:

//   struct fixed_record
//   {
//     F1 f1;
//     F2 f2;
//     F3 f3;
//   };

// brief Defines an HLA 1516 fixed record datatype.

template< typename FIELD_VECTOR, typename CODEC_TAG >
struct fixed_record : public boost::mpl::reverse_fold<
  FIELD_VECTOR,
  boost::mpl::empty_base,
  boost::mpl::inherit<
    field_base< boost::mpl::placeholders::_2 >, boost::mpl::placeholders::_1 >
>::type
{
  BOOST_STATIC_ASSERT( (boost::mpl::empty< FIELD_VECTOR >::value != true) );

  typedef CODEC_TAG codec_tag;

  typedef FIELD_VECTOR field_vector;

  struct null_field_compare
  {
    template< typename R >
    static bool is_equal(const R &, const R &) { return true; }
  };

  template< typename T, typename Base >
  struct field_compare
  {
    template< typename R >
    static bool is_equal(const R &lhs, const R &rhs)
    {
      typename T::value_type const &lhs_value = lhs.template f_< T >();
      typename T::value_type const &rhs_value = rhs.template f_< T >();

      if (!(lhs_value == rhs_value))
        return false;

      return Base::is_equal(lhs, rhs);
    }
  };

  /**
   * @brief Tests for equality.
   *
   * Performs a field-by-field comparison of two fixed records.
   */
  inline bool operator == (const fixed_record &rhs) const
  {
    typedef typename boost::mpl::fold<
      FIELD_VECTOR,
      null_field_compare,
      field_compare< mpl::placeholders::_2, mpl::placeholders::_1 >
    >::type type;

    return type::is_equal(*this, rhs);
  }

  inline bool operator != (const fixed_record &rhs) const
  {
    return !(*this == rhs);
  }

  // Returns a read-only reference to the field value identified by typename T.
  template< typename T >
  inline typename T::value_type const &f_() const
  {
    return( static_cast< const field_base< T > & >(*this).value );
  }

  // Returns a read/write reference to the field value identified by typename T.
  template< typename T >
  inline typename T::value_type &f_()
  {
    return( static_cast< field_base< T > & >(*this).value );
  }
};

/******************************************************************************/

}} // protox::dtl

/******************************************************************************/

#endif

/******************************************************************************/
