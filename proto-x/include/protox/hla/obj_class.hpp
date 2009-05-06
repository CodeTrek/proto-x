/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/
 
#ifndef PROTOX_HLA_OBJ_CLASS_HPP
#define PROTOX_HLA_OBJ_CLASS_HPP

/**************************************************************************************************/

#include <protox/hla/keywords.hpp>

/**************************************************************************************************/

namespace protox { namespace hla {

/**************************************************************************************************/

template<
  typename NAME,
  typename ATTR_LIST = protox::hla::none,
  typename CHILD_LIST = protox::hla::none >
struct obj_class
{
  typedef NAME name_type;
  typedef ATTR_LIST attr_list_type;
  typedef CHILD_LIST child_list_type;
};

/**************************************************************************************************/

}} // namespace protox.hla

/**************************************************************************************************/

#endif

/**************************************************************************************************/