/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_HLA_ATTR_HPP
#define PROTOX_HLA_ATTR_HPP

/******************************************************************************/

#include <vector>
#include <string>

#include <RTI.hh>

#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/back_inserter.hpp>

/******************************************************************************/

namespace protox { namespace hla {

/******************************************************************************/


template< typename T >
struct attr_base
{
  typedef T attr_type;
  typename T::value_type value;

  RTI::AttributeHandle handle;

  static char const *name() { return T::name(); }

  attr_base() : handle(0) {}

protected:
  template< typename S >
  void init_handle(const std::string &class_name )
  {
    handle = S::get_attr_handle(class_name, name());;
  }
};

/******************************************************************************/

template< typename T >
struct attr
{
  typedef T value_type;
};

/******************************************************************************/

// Forward declaration
template< typename A, typename B > struct attr_inherit;

/******************************************************************************/

template< typename A >
struct attr_inherit< A, boost::mpl::empty_base > : A, boost::mpl::empty_base
{
protected:
  template< typename T >
  void init_handles(const std::string &class_name)
  {
    A::template init_handle< T >(class_name);
  }
};

/******************************************************************************/

/**
 * A is an attribute and B is set of predecessor attributes.
 */
template< typename A, typename B >
struct attr_inherit : A, B
{
protected:
  template< typename T >
  void init_handles(const std::string &class_name)
  {
    A::template init_handle< T >(class_name);
    B::template init_handles< T >(class_name);
  }

public:
  template< typename T >
  inline typename T::value_type const &a_() const
  {
    return (static_cast< attr_base< T > const & >(*this).value);
  }

  template< typename T >
  inline typename T::value_type &a_()
  {
    return (static_cast< attr_base< T > & >(*this).value);
  }
  
  template< typename T >
  inline RTI::AttributeHandle get_attr_handle()
  {
    return (static_cast< attr_base< T > & >(*this).handle);
  }
};

/******************************************************************************/

}} // protox::hla

/******************************************************************************/

#endif

/******************************************************************************/
