/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_DTL_COMPUTE_OCTET_BOUNDARY_HPP
#define PROTOX_DTL_COMPUTE_OCTET_BOUNDARY_HPP

/**********************************************************************************************************************/

#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/greater_equal.hpp>
#include <boost/mpl/shift_left.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/multiplies.hpp>
#include <boost/static_assert.hpp>

#include <protox/platform.hpp>

/**********************************************************************************************************************/

namespace protox {
namespace dtl {

/**********************************************************************************************************************/

/// \cond
typedef boost::mpl::shift_left<
      boost::mpl::int_< 1 >,
      boost::mpl::int_< PROTOX_DTL_POW_2_MAX_BIT_SIZE - 3 >
>::type MAX_ITERATIONS;
/// \endcond

typedef boost::mpl::int_< -1 > UNKNOWN_OCTET_BOUNDARY;

/**********************************************************************************************************************/

/**
 * Compile time computation of an octet boundary value. The octet boundary value for a data type is the smallest value
 * <tt>2^n</tt>, where \c n is a non-negative integer, for which <tt>(8 * 2^n) >= the size of the data type in
 * bits.</tt> \b ALWAYS invoke this meta-function with just the size in bits argument and let \c N default to \c 0.
 *
 * \tparam S Size in bits, where <tt>0 < S <= 2^PROTOX_DTL_POW_2_MAX_BIT_SIZE</tt>
 * \tparam N Used to compute <tt>2^N</tt>.
 *
 * Example:
 *
 * \code
 *  comput_octet_boundary< 19 >
 * \endcode
 *
 *  Computes the octet boundary of a 19 bit data type.
 */

template< int S, int N = 0 >
struct compute_octet_boundary {

    private:
        BOOST_STATIC_ASSERT((S > 0));
        BOOST_STATIC_ASSERT((S <= (1L << PROTOX_DTL_POW_2_MAX_BIT_SIZE)));

        // Compute the Nth power of two (i.e., 1 << N ) :
        typedef typename boost::mpl::shift_left< boost::mpl::int_< 1 >, boost::mpl::int_< N > >::type nth_power_of_two;

        // Compute the product 8 * 2^N :
        typedef typename boost::mpl::multiplies< boost::mpl::int_< 8 >, nth_power_of_two >::type product;

    public:
        typedef typename boost::mpl::if_<
            boost::mpl::greater_equal< product, boost::mpl::int_< S > >,
            nth_power_of_two,                                 // true  : answer found
            typename compute_octet_boundary< S, (N+1) >::type // false : keep iterating
        >::type type;
};

/**********************************************************************************************************************/

/// \cond

// This specialization is reached if the octect boundary value is greater than or equal to
// PROTOX_DTL_MAX_OCTET_ITERATIONS.
template< int S >
struct compute_octet_boundary< S, MAX_ITERATIONS::value > {
    typedef UNKNOWN_OCTET_BOUNDARY type;
};

/// \endcond

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
