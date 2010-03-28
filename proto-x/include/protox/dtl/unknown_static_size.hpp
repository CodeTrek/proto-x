/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_DTL_UNKNOWN_STATIC_SIZE_HPP
#define PROTOX_DTL_UNKNOWN_STATIC_SIZE_HPP

/**************************************************************************************************/

#include <boost/mpl/int.hpp>

/**************************************************************************************************/

namespace protox {
namespace dtl {

/**************************************************************************************************/

/**
 * \file unknown_static_size.hpp
 *
 * \typedef UNKNOWN_STATIC_SIZE
 *
 * Denotes a size that can not be computed at compile time.
 */

typedef boost::mpl::int_< -1 > UNKNOWN_STATIC_SIZE;

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
