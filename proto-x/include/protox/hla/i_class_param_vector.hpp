/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_HLA_I_CLASS_PARAM_VECTOR_HPP
#define PROTOX_HLA_I_CLASS_PARAM_VECTOR_HPP

/******************************************************************************/

#include <boost/mpl/front.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/back_inserter.hpp>

#include <protox/hla/x_class_vector.hpp>

/******************************************************************************/

namespace protox { namespace hla {

/******************************************************************************/

template< bool INTER_CLASS_VECTOR_IS_EMPTY,
          typename INTER_CLASS_VECTOR,
          typename PARAM_VECTOR > struct i_class_param_vector_impl;

/******************************************************************************/

template< typename INTER_CLASS_VECTOR,
          typename PARAM_VECTOR >
struct i_class_param_vector_impl< true, INTER_CLASS_VECTOR, PARAM_VECTOR >
{
  typedef PARAM_VECTOR type;
};

/******************************************************************************/

template< typename INTER_CLASS_VECTOR,
          typename PARAM_VECTOR >
struct i_class_param_vector_impl< false, INTER_CLASS_VECTOR, PARAM_VECTOR >
{
  typedef typename boost::mpl::front< INTER_CLASS_VECTOR >::type front_class;
  
  typedef typename boost::mpl::copy<
    typename front_class::param_list_type,
    boost::mpl::back_inserter< PARAM_VECTOR >
  >::type param_vector_type;
  
  typedef typename
    boost::mpl::pop_front< INTER_CLASS_VECTOR >::type class_vector_tail;
  
  typedef typename i_class_param_vector_impl<
    (boost::mpl::empty< class_vector_tail >::value),
    class_vector_tail,
    param_vector_type 
  >::type type;
};

/******************************************************************************/

template< typename i_class,
          typename NAME_VECTOR >
struct i_class_param_vector
{
  typedef typename x_class_vector< i_class, NAME_VECTOR >::type class_vector;

  typedef typename i_class_param_vector_impl<
    (boost::mpl::empty< class_vector >::value),
    class_vector,
    boost::mpl::vector<>
  >::type type;
};

/******************************************************************************/

}} // protox::hla

/******************************************************************************/

#endif

/******************************************************************************/
