/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_DTL_SIMPLE_HPP
#define PROTOX_DTL_SIMPLE_HPP

/**************************************************************************************************/

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include <protox/dtl/basic_tag.hpp>

/**************************************************************************************************/

namespace protox {
namespace dtl {

/**************************************************************************************************/

/**
 * Used to define a unit-less simple type.
 *
 * \sa protox::dtl::simple
 */
struct unitless {};

/**
 * This is a type generator for simple datatypes, which is a scaler datatype defined by a basic
 * data representation and an optional unit definition.
 *
 * Use simple to associate basic data representation type \a T with a unit definition.
 *
 * <b>Note:</b> Unit definitions are not supported in this release.
 *
 * \tparam T The basic data representation type used to represent the simple datatype being defined.
 *
 * \tparam U The simple datatype's unit of measure e.g., meters, feet, grams, etc...
 *
 * \sa protox::dtl::basic
 *
 * Example:
 *
 * \code
 *      +--------------+-------------------------+----------+
 *      | Name         | Representation          | Units    |
 *      +--------------+-------------------------+----------+
 * struct Distance     : simple< HLAfloat32BE,     unitless > {PROTOX_SIMPLE( Distance  )};
 *      +--------------+-------------------------+----------+
 * struct MassType     : simple< HLAfloat32BE,     unitless > {PROTOX_SIMPLE( MassType  )};
 *      +--------------+-------------------------+----------+
 * struct ASCIIchar    : simple< HLAoctet,         unitless > {PROTOX_SIMPLE( ASCIIchar )};
 *      +--------------+-------------------------+----------+
 * struct Count        : simple< HLAinteger16BE,   unitless > {PROTOX_SIMPLE( Count     )};
 *      +--------------+-------------------------+----------+
 *
 * \endcode
 *
 */

/**************************************************************************************************/

template< typename T, typename U = unitless >
struct simple : T
{

/**************************************************************************************************/

private:

  // Test for valid template arguments:

  BOOST_STATIC_ASSERT(( boost::is_base_of<basic_tag, T >::value ));

/**************************************************************************************************/

public:

  typedef T basic_type;
  typedef U unit_type;

/**************************************************************************************************/

  simple() {}

  /**
   * Implicit conversion from T::value_type to simple type (i.e, T)
   */
  simple( typename T::value_type v ) : T(v) {}

/**************************************************************************************************/

  /**
   * Enable numerical assignment.
   */
  template< typename RHST >
  simple &operator =( const RHST rhs )
  {
    T::value = rhs;
    return( *this );
  }
};

/**************************************************************************************************/

/**
 * \file simple.hpp
 *
 * \def PROTOX_SIMPLE(simple_name)
 * Defines constructor methods for a simple datatype named \a simple_name.
 */

#define PROTOX_SIMPLE(simple_name)                                                            \
  simple_name() {}                                                                            \
  typedef protox::dtl::simple< simple_name::basic_type, simple_name::unit_type > simple_type; \
  simple_name(simple_type::value_type v) : simple_type(v) {}

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
