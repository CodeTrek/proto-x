/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_OBJ_CLASS_VECTOR_HPP
#define PROTOX_HLA_OBJ_CLASS_VECTOR_HPP

/**************************************************************************************************/

#include <boost/mpl/vector.hpp>
#include <boost/mpl/size.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/type_traits/is_same.hpp>

/**************************************************************************************************/

using namespace boost;
using namespace boost::mpl::placeholders;

/**************************************************************************************************/

namespace protox { namespace hla {

/**************************************************************************************************/

// Get T's name type
template< typename T >
struct get_name_type
{
  typedef typename T::name_type type;
};

// Use the given qualified name vector NAME_VECTOR to construct another vector
// of object classes (CLASS_VECTOR) from the given root class O_CLASS.
template<
  bool NAME_VECTOR_IS_EMPTY,
  typename O_CLASS,
  typename NAME_VECTOR, // Qualified name
  typename CLASS_VECTOR
> struct obj_class_vector_impl;

// Empty class_vector case.
template<
  typename O_CLASS,
  typename NAME_VECTOR,
  typename CLASS_VECTOR
> struct obj_class_vector_impl< true, O_CLASS, NAME_VECTOR, CLASS_VECTOR >
{
  BOOST_STATIC_ASSERT(( mpl::size< NAME_VECTOR >::value == 0 ));
  typedef CLASS_VECTOR type;
};

// Non-empty class_vector case.
template<
  typename O_CLASS,
  typename NAME_VECTOR,
  typename CLASS_VECTOR
> struct obj_class_vector_impl< false, O_CLASS, NAME_VECTOR, CLASS_VECTOR >
{
  BOOST_STATIC_ASSERT(( mpl::size< NAME_VECTOR >::value > 0 ));
    
  typedef typename mpl::front< NAME_VECTOR >::type front_name; 
  
  typedef typename mpl::find_if<
    typename O_CLASS::child_list_type,
    boost::is_same< front_name, mpl::lambda< get_name_type< _ > > >
  >::type it;
  
  typedef typename mpl::deref< it >::type obj_class_type;
  typedef typename mpl::push_back< CLASS_VECTOR, obj_class_type >::type class_vector_type;
  typedef typename mpl::pop_front< NAME_VECTOR >::type name_vector_tail;

  typedef typename obj_class_vector_impl<
    (mpl::empty<name_vector_tail>::value),
    obj_class_type,
    name_vector_tail,
    class_vector_type
  >::type type;
};
  
template< typename O_CLASS, typename NAME_VECTOR >
struct obj_class_vector
{
  typedef typename obj_class_vector_impl<
    (mpl::empty< NAME_VECTOR >::value),
    O_CLASS,
    NAME_VECTOR,
    mpl::vector< O_CLASS >
  >::type type;
};
  
/**************************************************************************************************/

}} // namespace protox.hla

/**************************************************************************************************/

#endif

/**************************************************************************************************/