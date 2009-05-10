/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/
 
#ifndef PROTOX_HLA_ELEMENT_COUNTER_HPP
#define PROTOX_HLA_ELEMENT_COUNTER_HPP

/**************************************************************************************************/

#include <boost/mpl/count.hpp>

/**************************************************************************************************/

namespace protox { namespace hla {

/**************************************************************************************************/

using namespace boost;

/**************************************************************************************************/

// Creates a unary operator that counts duplicate set elements.
template< typename SET >
struct element_counter
{
  // Returns the number of times E occurs in SET.
  template< typename E >
  struct op
  {
    typedef typename mpl::count< SET, E >::type type;
  };
};
  
/**************************************************************************************************/

}} // namespace protox.hla

/**************************************************************************************************/

#endif

/**************************************************************************************************/