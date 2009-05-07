/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/
 
#ifndef PROTOX_HLA_OBJ_CLASS_TYPE_HPP
#define PROTOX_HLA_OBJ_CLASS_TYPE_HPP

/**************************************************************************************************/

#include <boost/mpl/inherit_linearly.hpp>
#include <boost/mpl/placeholders.hpp>

#include <protox/hla/obj_class_attr_vector.hpp>
#include <protox/hla/attr.hpp>

/**************************************************************************************************/

namespace protox { namespace hla {

/**************************************************************************************************/

using namespace boost::mpl::placeholders;

/**************************************************************************************************/

template<
  typename O_CLASS,
  typename QUALIFIED_NAME_VECTOR
> struct obj_class_type
{
  typedef typename obj_class_attr_vector<
    O_CLASS,
    QUALIFIED_NAME_VECTOR
  >::type attr_vector_type;

  struct type : mpl::inherit_linearly<
    attr_vector_type,
    attr_inherit< attr_base< boost::mpl::placeholders::_2 >, boost::mpl::placeholders::_1 >
  >::type
  {
    type()
    {
    }
  };

#if 0
  typedef typename mpl::inherit_linearly<
    attr_vector_type,
    attr_inherit< attr_base< boost::mpl::placeholders::_2 >, boost::mpl::placeholders::_1 >
  >::type type;
#endif
};
  
/**************************************************************************************************/

}} // namespace protox::hla

/**************************************************************************************************/

#endif

/**************************************************************************************************/