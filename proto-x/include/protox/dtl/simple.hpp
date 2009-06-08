/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_DTL_SIMPLE_HPP
#define PROTOX_DTL_SIMPLE_HPP

/******************************************************************************/

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include <protox/dtl/basic_tag.hpp>

/******************************************************************************/

namespace protox { namespace dtl {

/******************************************************************************/

struct unitless {};

/******************************************************************************/

// This is a type generator for simple data types.
template<
  typename T,             // The basic type used to represent the simple type
                          // being defined.
  typename U = unitless > // The simple type's unit of measure
struct simple : T
{

/******************************************************************************/

  // Test for valid template arguments:

  BOOST_STATIC_ASSERT(( boost::is_base_of<basic_tag, T >::value ));

/******************************************************************************/

  typedef T basic_type;
  typedef U unit_type;

/******************************************************************************/

  simple() {}

  // Implicit conversion from T::value_type to basic type (i.e, T)
  simple( typename T::value_type v ) : T(v) {}

/******************************************************************************/

  // Enable numerical assignment.
  // For example, assignment of float to int, assignment int to float, etc...
  template< typename RHST >
  simple &operator =( const RHST rhs )
  {
    T::value = rhs;
    return( *this );
  }
};

/******************************************************************************/

#define PROTOX_SIMPLE(simple_name)                                 \
  simple_name() {}                                                 \
  typedef protox::dtl::simple<                                     \
    simple_name::basic_type, simple_name::unit_type > simple_type; \
  simple_name(simple_type::value_type v) : simple_type(v) {}

/******************************************************************************/

}} // protox::dtl

/******************************************************************************/

#endif

/******************************************************************************/
