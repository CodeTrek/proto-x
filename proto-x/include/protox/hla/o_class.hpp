/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/
 
#ifndef PROTOX_HLA_O_CLASS_HPP
#define PROTOX_HLA_O_CLASS_HPP

/**************************************************************************************************/

#include <iostream>

#include <assert.h>
#include <string>
#include <protox/rti/RTI.hh>
#include <boost/static_assert.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <protox/hla/keywords.hpp>
#include <protox/hla/name_to_o_class_handle_map.hpp>
#include <protox/hla/init_class_handle.hpp>
#include <protox/hla/has_duplicate_class_names.hpp>
#include <protox/hla/has_duplicate_attr_names.hpp>

/**************************************************************************************************/

namespace protox { namespace hla {

/**************************************************************************************************/

using namespace boost;

/**************************************************************************************************/

template<
  typename NAME,
  typename ATTR_SET = protox::hla::none,
  typename CHILD_SET = protox::hla::none >
struct o_class
{
  // Check for duplicate child classes.
  BOOST_STATIC_ASSERT( (has_duplicate_class_names<CHILD_SET>::type::value == false) );
  
  // Check for duplicate attributes.
  BOOST_STATIC_ASSERT( (has_duplicate_attr_names<ATTR_SET>::type::value == false) );

  typedef NAME name_type;
 
  // Convert the sets to vectors
  //typedef typename mpl::copy< ATTR_SET, mpl::back_inserter< mpl::vector<> > >::type attr_list_type;
  ////typedef typename mpl::copy< CHILD_SET, mpl::back_inserter< mpl::vector<> > >::type child_list_type;

  typedef ATTR_SET attr_list_type;
  typedef CHILD_SET child_list_type;
 
  // Map fully qualified names to RTI assigned class handles. 
  // 
  // Note: 
  //  An o_class based type may appear in more than one place in an object model (OM)
  //  specification and therefore be associated with more than one class handle.
  //  For example -
  // 
  //    o_class< Class_A,
  //             none,
  //             child< o_class< Class_B,
  //                             none,
  //                             child< o_class< Class_C > > >,
  //                    o_class< Class_C >,
  //                    o_class< Class_D > > > {};
  // 
  // here Class_C is a child of both Class_A and Class_B. Consquently, Class_C
  // will have two handles associated with it, one for Class_A.Class_C and the other
  // for Class_A.Class_B.Class_C. In this example, Class_C's name to handle map
  // would have two entries.
  //
  //static name_to_o_class_handle_map name_to_handle_map;
  static name_to_o_class_handle_map &get_name_to_handle_map()
  {
    static name_to_o_class_handle_map name_to_handle_map;
    return name_to_handle_map;
  }
  
  static void init_handles(RTI::RTIambassador &rtiAmb, const char *parent_name = 0)
  {
    std::string full_name;
    
    if (parent_name != 0)
      full_name = std::string(parent_name) + "." + NAME::name(); 
    else
      full_name = NAME::name(); 
   
    // Check for name duplication.  
    assert( get_name_to_handle_map().find(full_name) == get_name_to_handle_map().end() );
      
    get_name_to_handle_map()[full_name] = rtiAmb.getObjectClassHandle(full_name.c_str());
    
    std::cout << full_name.c_str() << " = " << get_name_to_handle_map()[full_name] << "\n";
  
    // Assign handles to the child classes.
    mpl::for_each< CHILD_SET >(init_class_handle(rtiAmb, full_name.c_str()));
    //mpl::for_each< AttrList >( init_attr_handle( rtiAmb, handle ) );
  }
  
};

/**************************************************************************************************/

#if 0
template<
  typename NAME,
  typename ATTR_SET,
  typename CHILD_SET
> name_to_o_class_handle_map o_class< NAME, ATTR_SET, CHILD_SET >::name_to_handle_map;
#endif

/**************************************************************************************************/

}} // namespace protox.hla

/**************************************************************************************************/

#endif

/**************************************************************************************************/
