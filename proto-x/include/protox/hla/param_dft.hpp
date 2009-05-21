/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_HLA_PARAM_DFT_HPP
#define PROTOX_HLA_PARAM_DFT_HPP

/******************************************************************************/

#include <RTI.hh>

#include <string>
#include <iostream>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/inherit.hpp>
#include <boost/mpl/inherit_linearly.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

#include <protox/hla/name_to_i_class_handle_map.hpp>
#include <protox/hla/class_handle_to_param_handle_map.hpp>
#include <protox/hla/build_full_name.hpp>
#include <protox/hla/print_stack.hpp>

/******************************************************************************/

namespace protox { namespace hla {

/******************************************************************************/

struct init_param_handle
{
  RTI::RTIambassador &rtiAmb;
  RTI::InteractionClassHandle class_handle;
  i_class_handle_to_param_map &map;
  
  init_param_handle(
    RTI::RTIambassador &rtiAmb,
    RTI::InteractionClassHandle ch,
    i_class_handle_to_param_map &m
  ) :
    rtiAmb(rtiAmb),
    class_handle(ch),
    map(m)
  {}

  template< typename N >
  void operator()(N)
  {
    // Find the class handle entry
    i_class_handle_to_param_map::iterator i = map.find(class_handle);

    if (i == map.end())
    {
      map[class_handle] = param_name_to_handle_map();
    }

    // Find the paramibute handle by name
    param_name_to_handle_map::iterator j = map[class_handle].find(N::name());

    // No entry for the paramibute name?
    if (j == map[class_handle].end())
    {
      map[class_handle][N::name()]
        = rtiAmb.getParameterHandle(N::name(), class_handle);
    }
  }
};

/******************************************************************************/

// forward declaration
template< typename T, typename Stack > struct param_dft;

/******************************************************************************/

// forward declaration
template< bool empty, typename Children, typename Stack >
struct param_dft_children;

/******************************************************************************/

template< typename Children, typename Stack >
struct param_dft_children< false, Children, Stack >
{
  // Separate the first child from the rest.
  typedef typename boost::mpl::front< Children >::type first_child;

  // Get the remaining children (i.e, the tail of the child vector)
  typedef typename
    boost::mpl::erase< Children, boost::mpl::front< Children > >::type tail;

  // Traverse the first child of the given Children vector.
  typedef param_dft< first_child, Stack > stack;

  // Traverse the remaining children.
  typedef param_dft_children<
    boost::mpl::empty<tail>::value,
    tail,
    typename stack::type
  > result;

  typedef typename result::type type;

  static void dump_stack()
  {
    stack::dump_stack();
    result::dump_stack();
  };
  
  static void init_i_class_handles(RTI::RTIambassador &rtiAmb,
    name_to_i_class_handle_map &class_map,
    i_class_handle_to_param_map &param_map)
  {
    stack::init_i_class_handles(rtiAmb, class_map, param_map);
    result::init_i_class_handles(rtiAmb, class_map, param_map);
  }
};

/******************************************************************************/

template< typename Children, typename Stack >
struct param_dft_children< true, Children, Stack >
{
  typedef typename boost::mpl::pop_front< Stack >::type type;

  static void dump_stack()
  {
    boost::mpl::for_each< Stack >( print_stack() );
    std::cout << "null\n";
  }
  
  static void init_i_class_handles(
    RTI::RTIambassador &rtiAmb,
    name_to_i_class_handle_map &class_map,
    i_class_handle_to_param_map &param_map)
  {
    std::string full_name;
    boost::mpl::for_each< Stack >(build_full_name(full_name, REVERSED));

    // No interaction classes?
    if (full_name.empty())
    {
      return;
    }
    
    RTI::InteractionClassHandle class_handle =
      rtiAmb.getInteractionClassHandle(full_name.c_str());

    class_map[full_name] = class_handle;
    
    typedef typename boost::mpl::front< Stack >::type child;
    
    boost::mpl::for_each< typename child::param_list_type >
      (init_param_handle(rtiAmb, class_handle, param_map));
  }
};

/******************************************************************************/

/**
 * Perform a depth first traversal of the given tree T.  
 */
template< typename T, typename Stack = boost::mpl::vector<> >
struct param_dft
{
  // Push the root of the tree onto a stack.  
  typedef typename boost::mpl::push_front< Stack, T >::type stack;

  // Continue the traversal by recursively looping over the children of T.
  typedef param_dft_children<
    boost::mpl::empty< typename T::child_list_type >::value,
    typename T::child_list_type,
    stack
  > result;
  
  typedef typename result::type type;

  static void dump_stack()
  {
    result::dump_stack();
  }
  
  static void init_i_class_handles(
    RTI::RTIambassador &rtiAmb,
    name_to_i_class_handle_map &class_map,
    i_class_handle_to_param_map &param_map)
  {
    result::init_i_class_handles(rtiAmb, class_map, param_map);
  }
};
  
/******************************************************************************/

}} // protox::hla

/******************************************************************************/

#endif

/******************************************************************************/
