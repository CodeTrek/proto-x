/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_HLA_I_CLASS_HPP
#define PROTOX_HLA_I_CLASS_HPP

/******************************************************************************/

#include <boost/static_assert.hpp>

#include <protox/hla/keywords.hpp>
#include <protox/hla/has_duplicate_class_names.hpp>
#include <protox/hla/has_duplicate_param_names.hpp>
#include <protox/hla/name.hpp>

/******************************************************************************/

namespace protox { namespace hla {

/******************************************************************************/

template<
  typename NAME,
  typename PARAM_SET = protox::hla::none,
  typename CHILD_SET = protox::hla::none >
struct i_class
{
  // Check for duplicate child classes.
  BOOST_STATIC_ASSERT(
    (has_duplicate_class_names<CHILD_SET>::type::value == false) );
  
  // Check for duplicate attributes.
  BOOST_STATIC_ASSERT(
    (has_duplicate_param_names<PARAM_SET>::type::value == false) );

  typedef NAME name_type;
 
  typedef PARAM_SET param_list_type;
  typedef CHILD_SET child_list_type;
};

/******************************************************************************/

struct null_i_class : i_class< null_name > {};  

/******************************************************************************/

}} // protox.hla

/******************************************************************************/

#endif

/******************************************************************************/