/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_DTL_VARIANT_RECORD_HPP
#define PROTOX_DTL_VARIANT_RECORD_HPP

/**************************************************************************************************/

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/max.hpp>
#include <boost/variant.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/vector.hpp>

#include <protox/dtl/alternative.hpp>
#include <protox/dtl/discriminant.hpp>

/**************************************************************************************************/

namespace protox {
namespace dtl {

/**************************************************************************************************/

template<
  typename D_TYPE,   // Discriminant type
  typename D_VECTOR, // Vector of alternatives
  typename OTHER,    // HLAOTHER case (optional)
  typename CODEC_TAG
>
struct variant_record
{
  variant_record() {}

  typedef CODEC_TAG codec_tag;

  typedef D_VECTOR d_vector;
  typedef OTHER other_type;

  typedef typename boost::mpl::fold<
    D_VECTOR,
    boost::mpl::vector<>,
    boost::mpl::push_back<
      boost::mpl::placeholders::_1,
      get_alternative_type< boost::mpl::placeholders::_2 > >
  >::type alternative_vector;

  typename boost::make_variant_over<
    typename dtl::append_other< alternative_vector, OTHER >::type
  >::type value;

  typedef D_TYPE discriminant_type;

  //Set this value to select an alternative value.
  discriminant_type discriminant;

  template< typename OTHER_T, typename NA > struct compare_other;

  template<typename NA>
  struct compare_other< protox::dtl::discriminant_other_none, NA >
  {
    template< typename R >
    inline static bool is_equal( const R &lhs, const R &rhs )
    {
      return false;
    }
  };

  template< typename OTHER_T, typename NA >
  struct compare_other
  {
    template< typename R >
    inline static bool is_equal( const R &lhs, const R &rhs )
    {
      // This is the "other" case, so testing for discriminant equality is not necessary.
      typename OTHER_T::value_type const *lhs_value = lhs.other_();
      typename OTHER_T::value_type const *rhs_value = rhs.other_();

      if( !lhs_value )
      {
        return false;
      }

      if( !rhs_value )
      {
        return false;
      }

      return( (*lhs_value) == (*rhs_value) );
    }
  };

  template< typename D, typename BASE >
  struct discriminant_compare
  {
    typedef typename protox::dtl::discriminator_test< D >::type discriminator_test;

    template< typename R >
    inline static bool is_equal( const R &lhs, const R &rhs )
    {
      if( discriminator_test::is_equal( lhs.discriminant ) )
      {
        // Same object?
        if( &lhs == &rhs )
        {
          return true;
        }

        if( !(lhs.discriminant == rhs.discriminant) )
        {
          return false;
        }

        typename D::alternative::value_type const *lhs_value = lhs.template alt_< D >();
        typename D::alternative::value_type const *rhs_value = rhs.template alt_< D >();

        // No alternative values?
        if( (!lhs_value) && (!rhs_value) )
        {
          return true;
        }

        if( !lhs_value )
        {
          return false;
        }

        if( !rhs_value )
        {
          return false;
        }

        return( (*lhs_value) == (*rhs_value) );
      }

      return BASE::is_equal( lhs, rhs );
    }
  };

  inline bool operator == ( const variant_record &rhs ) const
  {
    typedef typename boost::mpl::fold<
      D_VECTOR,
      compare_other< OTHER, void >,
      discriminant_compare<
        boost::mpl::placeholders::_2,
        boost::mpl::placeholders::_1 >
    >::type type;

    return type::is_equal( *this, rhs );
  }

  inline bool operator != ( const variant_record &rhs ) const
  {
    return !(*this == rhs);
  }

  // Alternative getters and setters.
  template< typename T >
  inline void alt_( typename get_alternative_type<T>::type::value_type const &v )
  {
    value = static_cast< typename get_alternative_type< T >::type >( v );
  }

  // Gets a read/write pointer to an alternative's value
  template< typename T >
  inline typename get_alternative_type< T >::type::value_type *alt_()
  {
    typedef typename get_alternative_type< T >::type alternative_type;
    alternative_type *alt_ptr = boost::get< alternative_type >( &value );

    if( alt_ptr == 0 )
    {
      return 0;
    }

    return( &(alt_ptr->value) );
  }

  // Gets a read-only pointer to an alternative's value
  template< typename T >
  inline typename get_alternative_type< T >::type::value_type const *alt_() const
  {
    typedef typename get_alternative_type< T >::type alternative_type;
    alternative_type const *alt_ptr = boost::get< alternative_type >( &value );

    if( alt_ptr == 0 )
    {
      return 0;
    }

    return( &(alt_ptr->value) );
  }

  // Compute the HLAOTHER accessor type
  inline void other_( typename OTHER::value_type const &v )
  {
    typedef dtl::other_access< OTHER, variant_record< D_TYPE, D_VECTOR, OTHER, CODEC_TAG > > other;

    other::set_value( *this, v );
  }

  inline typename OTHER::value_type const *other_() const
  {
    typedef dtl::other_access< OTHER, variant_record< D_TYPE, D_VECTOR, OTHER, CODEC_TAG > > other;

    return other::get_value( *this );
  }
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
