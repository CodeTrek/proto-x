/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/
 
#ifndef PROTOX_HLA_PARAM_HPP
#define PROTOX_HLA_PARAM_HPP

/******************************************************************************/

#include <boost/mpl/empty_base.hpp>

/******************************************************************************/

namespace protox { namespace hla {

/******************************************************************************/

template< typename T >
struct param_base
{
  typedef T param_type;
  //int handle;
  typename T::value_type value;
  static char const *name() { return T::name(); }
};
  
/******************************************************************************/

template< typename T >
struct param
{
  typedef T value_type;
};

/******************************************************************************/
  
template< typename A, typename B >
struct param_inherit : A, B
{
  template< typename T >
  inline typename T::value_type const &a_() const
  {
    return (static_cast< param_base< T > const & >(*this).value);
  }
  
  template< typename T >
  inline typename T::value_type &a_()
  {
    return (static_cast< param_base< T > & >(*this).value );
  }
};

/******************************************************************************/
 
template< typename A >
struct param_inherit<
  A,
  boost::mpl::empty_base
> : A, boost::mpl::empty_base {};

/******************************************************************************/
  
}} // protox::hla

/******************************************************************************/

#endif

/******************************************************************************/
