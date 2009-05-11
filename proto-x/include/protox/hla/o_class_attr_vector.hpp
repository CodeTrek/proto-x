/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_HLA_O_CLASS_ATTR_VECTOR_HPP
#define PROTOX_HLA_O_CLASS_ATTR_VECTOR_HPP

/******************************************************************************/

#include <boost/mpl/front.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/back_inserter.hpp>

#include <protox/hla/o_class_vector.hpp>

/******************************************************************************/

namespace protox { namespace hla {

/******************************************************************************/

template<
  bool OBJ_CLASS_VECTOR_IS_EMPTY,
  typename OBJ_CLASS_VECTOR,
  typename ATTR_VECTOR
> struct o_class_attr_vector_impl;

/******************************************************************************/

template<
  typename OBJ_CLASS_VECTOR,
  typename ATTR_VECTOR
> struct o_class_attr_vector_impl< true, OBJ_CLASS_VECTOR, ATTR_VECTOR >
{
  typedef ATTR_VECTOR type;
};

/******************************************************************************/

template<
  typename OBJ_CLASS_VECTOR,
  typename ATTR_VECTOR
> struct o_class_attr_vector_impl< false, OBJ_CLASS_VECTOR, ATTR_VECTOR >
{
  typedef typename boost::mpl::front< OBJ_CLASS_VECTOR >::type front_class;
  
  typedef typename boost::mpl::copy<
    typename front_class::attr_list_type,
    boost::mpl::back_inserter< ATTR_VECTOR >
  >::type attr_vector_type;
  
  typedef typename
    boost::mpl::pop_front< OBJ_CLASS_VECTOR >::type class_vector_tail;
  
  typedef typename o_class_attr_vector_impl<
    (boost::mpl::empty< class_vector_tail >::value),
    class_vector_tail,
    attr_vector_type 
  >::type type;
};

/******************************************************************************/

template<
  typename O_CLASS,
  typename NAME_VECTOR >
struct o_class_attr_vector
{
  typedef typename o_class_vector< O_CLASS, NAME_VECTOR >::type class_vector;

  typedef typename o_class_attr_vector_impl<
    (boost::mpl::empty< class_vector >::value),
    class_vector,
    mpl::vector<>
  >::type type;
};

/******************************************************************************/

}} // protox::hla

/******************************************************************************/

#endif

/******************************************************************************/
