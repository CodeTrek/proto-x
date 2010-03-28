/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_DTL_ENDIAN_ENUM_HPP
#define PROTOX_DTL_ENDIAN_ENUM_HPP

/**************************************************************************************************/

#include <boost/mpl/int.hpp>

#include <protox/platform.hpp>

/**************************************************************************************************/

namespace protox {
namespace dtl {

/**************************************************************************************************/

/**
 * Use these values to define a type's byte-orientation.
 */
struct endian
{
  /**
   * Not applicable.
   */
  typedef boost::mpl::int_< PROTOX_DTL_NA_ENDIAN     > na;

  /**
   * Little endian i.e., least significant byte first.
   */
  typedef boost::mpl::int_< PROTOX_DTL_LITTLE_ENDIAN > little;

  /**
   * Big endian i.e., most significant byte first.
   */
  typedef boost::mpl::int_< PROTOX_DTL_BIG_ENDIAN    > big;
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
