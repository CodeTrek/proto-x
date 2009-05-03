/*
    Copyright 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_DTL_COMPUTE_OCTET_BOUNDARY_HPP
#define PROTOX_DTL_COMPUTE_OCTET_BOUNDARY_HPP

/**************************************************************************************************/

#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/greater_equal.hpp>
#include <boost/mpl/shift_left.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/multiplies.hpp>
#include <boost/static_assert.hpp>

#include <protox/platform.hpp>

/**************************************************************************************************/

using namespace boost;

/**************************************************************************************************/

namespace protox { namespace dtl {

/**************************************************************************************************/

typedef mpl::shift_left<
  mpl::int_< 1 >, mpl::int_< PROTOX_DTL_POW_2_MAX_BIT_SIZE - 3 >
>::type MAX_ITERATIONS;

typedef mpl::int_< -1 > UNKNOWN_OCTET_BOUNDARY;

/**************************************************************************************************/

// Compile time computation of an octect boundary value. The octet
// boundary value for a data type is the smallest value 2^n, where
// n is a non-negative integer, for which (8 * 2^n) >= size of the
// data type in bits.
//
// S Size in bits, where 0 < S <= 2^PROTOX_DTL_POW_2_MAX_BIT_SIZE
// N Used to compute 2^N.
//
//  _ALWAYS_ invoke this meta-function with just the size in bits
//  argument and let N default to 0.
//
//  For example, comput_octet_boundary< 19 > computes the octet
//  boundary of a 19 bit data type.
//
template< int S, int N = 0 >
struct compute_octet_boundary
{
  BOOST_STATIC_ASSERT(( S > 0 ));
  BOOST_STATIC_ASSERT(( S <= (1L << PROTOX_DTL_POW_2_MAX_BIT_SIZE) ));

  // Compute the Nth power of two (i.e., 1 << N ) :
  typedef typename mpl::shift_left<
    mpl::int_< 1 >, mpl::int_< N >
  >::type nth_power_of_two;

  // Compute the product 8 * 2^N :
  typedef typename mpl::multiplies< mpl::int_< 8 >, nth_power_of_two >::type product;

  typedef typename mpl::if_< mpl::greater_equal< product, mpl::int_< S > >,
    nth_power_of_two,                                 // answer found
    typename compute_octet_boundary< S, (N+1) >::type // keep iterating
  >::type type;
};

/**************************************************************************************************/

// This specialization is reached if the octect boundary value is greater than
// or equal to PROTOX_DTL_MAX_OCTET_ITERATIONS.
template< int S >
struct compute_octet_boundary< S, MAX_ITERATIONS::value >
{
  typedef UNKNOWN_OCTET_BOUNDARY type;
};

/**************************************************************************************************/

}} // protox::dtl

/**************************************************************************************************/

#endif

/**************************************************************************************************/
