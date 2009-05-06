/*
    Copyright (C) Jay Graham 2008

    Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at 
    http://www.boost.org/LICENSE_1_0.txt)
*/

/**************************************************************************************************/

#ifndef TEST_PROTOX_HLA_OBJ_CLASS_H_
#define TEST_PROTOX_HLA_OBJ_CLASS_H_

/**************************************************************************************************/

#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>

#include <protox/hla/obj_class.hpp>
#include <protox/hla/keywords.hpp>
#include <protox/hla/name.hpp>

/**************************************************************************************************/

namespace test_protox_hla_obj_class {

/**************************************************************************************************/

namespace t1
{
  struct Class_A { HLA_NAME("Class_A") };
  struct c_type : protox::hla::obj_class< Class_A > {};
}

BOOST_AUTO_TEST_CASE( test_obj_class_empty )
{
  using namespace t1;
  
  BOOST_CHECK( c_type::name_type::name() == std::string("Class_A") ); 
  BOOST_CHECK( c_type::name_type::name() != std::string("Class_B") ); 
}

namespace t2
{
  using namespace protox::hla;
 
  // Class names 
  struct Class_A { HLA_NAME("Class_A") };
  struct Class_B { HLA_NAME("Class_B") };
  struct Class_C { HLA_NAME("Class_C") };
  struct Class_D { HLA_NAME("Class_D") };
  
  // Structure
  struct c_type : 
    obj_class< Class_A,
               none,
               child< obj_class< Class_B >,
                      obj_class< Class_C >,
                      obj_class< Class_D > > > {};
  
}

BOOST_AUTO_TEST_CASE( test_obj_class_children )
{
  using namespace t2;

  BOOST_CHECK( c_type::name_type::name() == std::string("Class_A") ); 
  
  // No attributes?  
  BOOST_CHECK( boost::mpl::size<c_type::attr_list_type>::value == 0 );
  
  // 3 child classes?
  BOOST_CHECK( boost::mpl::size<c_type::child_list_type>::value == 3 );
}

namespace t3
{
  using namespace protox::hla;

  // Class names 
  struct Class_A { HLA_NAME("Class_A") };
  struct Class_B { HLA_NAME("Class_B") };
  struct Class_C { HLA_NAME("Class_C") };
  struct Class_D { HLA_NAME("Class_D") };
  struct Class_E { HLA_NAME("Class_E") };
  struct Class_F { HLA_NAME("Class_F") };
  struct Class_G { HLA_NAME("Class_G") };
  struct Class_H { HLA_NAME("Class_H") };
  
  // Structure
  struct c_type : 
    obj_class< Class_A,
               none,
               child< obj_class< Class_B,    // index 0
                                 none,
                                 child< obj_class< Class_E >,
                                        obj_class< Class_F > > >,
                      obj_class< Class_C >,  // index 1
                      obj_class< Class_D,    // index 2
                                 none,
                                 child< obj_class< Class_G >,
                                        obj_class< Class_H > > > > > {};
  
}

BOOST_AUTO_TEST_CASE( test_obj_class_children_nested )
{
  using namespace boost;
  using namespace t3;

  BOOST_CHECK( c_type::name_type::name() == std::string("Class_A") ); 
  
  // No attributes?  
  BOOST_CHECK( boost::mpl::size<c_type::attr_list_type>::value == 0 );
  
  // Class_A has 3 child classes?
  BOOST_CHECK( boost::mpl::size<c_type::child_list_type>::value == 3 );
  
  // Class_B has 2 child classes?
  
  typedef mpl::at< c_type::child_list_type, mpl::int_<0> >::type b_class_type;
  BOOST_CHECK( mpl::size< b_class_type::attr_list_type >::value == 0 );
  BOOST_CHECK( mpl::size< b_class_type::child_list_type >::value == 2 );

}

/**************************************************************************************************/

} // namespace test_protox_hla_obj_class

/**************************************************************************************************/

#endif

/**************************************************************************************************/
