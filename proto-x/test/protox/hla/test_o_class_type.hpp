/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef TEST_PROTOX_HLA_O_CLASS_TYPE_HPP
#define TEST_PROTOX_HLA_O_CLASS_TYPE_HPP

/******************************************************************************/

#include <RTI.hh>

#include <boost/mpl/size.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/int.hpp>

#include <protox/hla/o_class.hpp>
#include <protox/hla/o_class_type.hpp>
#include <protox/hla/keywords.hpp>
#include <protox/hla/attr.hpp>
#include <protox/hla/name.hpp>
#include <protox/hla/som.hpp>

/******************************************************************************/

namespace test_protox_hla_o_class_type {

/******************************************************************************/

using namespace protox::hla;

/******************************************************************************/

namespace t1
{
  // Class names 
  struct Class_A { HLA_NAME("Class_A") };
  struct Class_B { HLA_NAME("Class_B") };
  struct Class_C { HLA_NAME("Class_C") };
  struct Class_D { HLA_NAME("Class_D") };
  struct Class_E { HLA_NAME("Class_E") };
  struct Class_F { HLA_NAME("Class_F") };
  struct Class_G { HLA_NAME("Class_G") };
  struct Class_H { HLA_NAME("Class_H") };

  // Attribute names
  struct A1 : protox::hla::attr< int >    { HLA_NAME("A1") };
  struct A2 : protox::hla::attr< int >    { HLA_NAME("A2") };
  struct A3 : protox::hla::attr< double > { HLA_NAME("A3") };
  struct A4 : protox::hla::attr< double > { HLA_NAME("A4") };

  // Structure
  struct o_class_table : 
// +------------------+
    o_class< Class_A,
      attrs< A3 >,
//                    +-------------------------+
                        child< o_class< Class_B,
                          attrs< A1, A2, A4 >,
//                                              +--------------------------+
                                                  child< o_class< Class_E >,
//                                              +--------------------------+
                                                         o_class< Class_F >,
//                                              +--------------------------+
                                                         o_class< Class_C > > >,
//                                              +--------------------------+
//                    +-------------------------+
                               o_class< Class_C,
                                 attrs< A1, A2 >,
//                                              +--------------------------+
                                                  child< o_class< Class_A,
                                                    none,
//                                                                         +-------------------------+
                                                                             child< o_class< Class_E > > >,
//                                                                         +-------------------------+
//                                              +--------------------------+
                                                         o_class< Class_C >,
//                                              +--------------------------+
                                                         o_class< Class_E > > >,
//                                              +--------------------------+
//                    +-------------------------+
                               o_class< Class_D,
                                 attrs< A1, A2 >,
//                                              +--------------------------+
                                                  child< o_class< Class_G >,
//                                              +--------------------------+
                                                         o_class< Class_H > > > > > {};
//                                              +--------------------------+
//                    +-------------------------+
// +------------------+

} // t1

/******************************************************************************/

using namespace boost;
using namespace t1;

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_o_class_type_definition )
{
  typedef protox::hla::som< o_class_table > som;

  RTI::RTIambassador rtiAmb;
  rtiAmb.o_class_to_handle_map["Class_A"] = 1;
  rtiAmb.o_class_to_handle_map["Class_A.Class_B"] = 2;
  rtiAmb.o_class_to_handle_map["Class_A.Class_B.Class_E"] = 3;
  rtiAmb.o_class_to_handle_map["Class_A.Class_B.Class_F"] = 4;
  rtiAmb.o_class_to_handle_map["Class_A.Class_B.Class_C"] = 5;
  rtiAmb.o_class_to_handle_map["Class_A.Class_C"] = 6;
  rtiAmb.o_class_to_handle_map["Class_A.Class_C.Class_A"] = 7;
  rtiAmb.o_class_to_handle_map["Class_A.Class_C.Class_A.Class_E"] = 12;
  rtiAmb.o_class_to_handle_map["Class_A.Class_C.Class_C"] = 8;
  rtiAmb.o_class_to_handle_map["Class_A.Class_C.Class_E"] = 13;
  rtiAmb.o_class_to_handle_map["Class_A.Class_D"] = 9;
  rtiAmb.o_class_to_handle_map["Class_A.Class_D.Class_G"] = 10;
  rtiAmb.o_class_to_handle_map["Class_A.Class_D.Class_H"] = 11;
  som::init_handles(rtiAmb);

  typedef o_class_type< som, q_name< Class_C, Class_A, Class_E > >::type c1;

  BOOST_CHECK( c1::get_name() == "Class_A.Class_C.Class_A.Class_E" );
  BOOST_CHECK( c1::get_handle() == 12 );
  BOOST_CHECK( c1::get_num_attrs() == 3 );
  
  typedef o_class_type< som, q_name< Class_B > >::type c2;
  BOOST_CHECK( c2::get_name() == "Class_A.Class_B" );
  BOOST_CHECK( c2::get_handle() == 2 );
  BOOST_CHECK( c2::get_num_attrs() == 4 );
}

BOOST_AUTO_TEST_CASE( test_o_class_type_ctor )
{
  typedef protox::hla::som< o_class_table > som;

  RTI::RTIambassador rtiAmb;  
  rtiAmb.o_class_to_handle_map["Class_A"] = 1;
  rtiAmb.o_class_to_handle_map["Class_A.Class_B"] = 2;
  rtiAmb.o_class_to_handle_map["Class_A.Class_B.Class_E"] = 3;
  rtiAmb.o_class_to_handle_map["Class_A.Class_B.Class_F"] = 4;
  rtiAmb.o_class_to_handle_map["Class_A.Class_B.Class_C"] = 5;
  rtiAmb.o_class_to_handle_map["Class_A.Class_C"] = 6;
  rtiAmb.o_class_to_handle_map["Class_A.Class_C.Class_A"] = 7;
  rtiAmb.o_class_to_handle_map["Class_A.Class_C.Class_C"] = 8;
  rtiAmb.o_class_to_handle_map["Class_A.Class_D"] = 9;
  rtiAmb.o_class_to_handle_map["Class_A.Class_D.Class_G"] = 10;
  rtiAmb.o_class_to_handle_map["Class_A.Class_D.Class_H"] = 11;
  som::init_handles(rtiAmb);

  typedef o_class_type< som, q_name< Class_C, Class_A, Class_E > > class_type;

  class_type::type bObj;

  BOOST_CHECK( bObj.get_attr_handle<A1>() > 0 );
  BOOST_CHECK( bObj.get_attr_handle<A2>() > 0 );
  BOOST_CHECK( bObj.get_attr_handle<A3>() > 0 );
}

BOOST_AUTO_TEST_CASE( test_o_class_type_attr_mutators )
{
  typedef protox::hla::som< o_class_table > som;

  RTI::RTIambassador rtiAmb;  
  rtiAmb.o_class_to_handle_map["Class_A"] = 1;
  rtiAmb.o_class_to_handle_map["Class_A.Class_B"] = 2;
  rtiAmb.o_class_to_handle_map["Class_A.Class_B.Class_E"] = 3;
  rtiAmb.o_class_to_handle_map["Class_A.Class_B.Class_F"] = 4;
  rtiAmb.o_class_to_handle_map["Class_A.Class_B.Class_C"] = 5;
  rtiAmb.o_class_to_handle_map["Class_A.Class_C"] = 6;
  rtiAmb.o_class_to_handle_map["Class_A.Class_C.Class_A"] = 7;
  rtiAmb.o_class_to_handle_map["Class_A.Class_C.Class_C"] = 8;
  rtiAmb.o_class_to_handle_map["Class_A.Class_D"] = 9;
  rtiAmb.o_class_to_handle_map["Class_A.Class_D.Class_G"] = 10;
  rtiAmb.o_class_to_handle_map["Class_A.Class_D.Class_H"] = 11;
  som::init_handles(rtiAmb);

  typedef o_class_type< som, q_name< Class_C, Class_A, Class_E > > class_type;

  class_type::type bObj;

  bObj.a_<A1>() = 5;
  bObj.a_<A2>() = 10;
  bObj.a_<A3>() = 3.145;

  BOOST_CHECK( bObj.a_<A1>() == 5 );
  BOOST_CHECK( bObj.a_<A2>() == 10 );
  BOOST_CHECK( (bObj.a_<A3>() - 3.145) < 0.00001 );
}

/******************************************************************************/

} // test_protox_hla_o_class_type

/******************************************************************************/

#endif

/******************************************************************************/
