/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef TEST_PROTOX_HLA_I_CLASS_TYPE_HPP
#define TEST_PROTOX_HLA_I_CLASS_TYPE_HPP

/******************************************************************************/

#include <RTI.hh>

#include <protox/hla/som.hpp>
#include <protox/hla/o_class.hpp>
#include <protox/hla/i_class_type.hpp>

#include <test/protox/hla/som/s009/inter_class_table.hpp>

/******************************************************************************/

namespace test_protox_hla_i_class_type {

/******************************************************************************/

using namespace boost;
using namespace protox::hla;
using namespace som_s009; 

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_i_class_type_definition )
{
  typedef protox::hla::som< null_o_class, inter_class_table > som;

  RTI::RTIambassador rtiAmb;  
  
  rtiAmb.i_class_to_handle_map["Class_A"] = 1;
  rtiAmb.i_class_to_handle_map["Class_A.Class_B"] = 2;
  rtiAmb.i_class_to_handle_map["Class_A.Class_B.Class_E"] = 3;
  rtiAmb.i_class_to_handle_map["Class_A.Class_B.Class_F"] = 4;
  rtiAmb.i_class_to_handle_map["Class_A.Class_B.Class_C"] = 5;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C"] = 6;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C.Class_A"] = 7;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C.Class_A.Class_E"] = 12;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C.Class_C"] = 8;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C.Class_E"] = 13;
  rtiAmb.i_class_to_handle_map["Class_A.Class_D"] = 9;
  rtiAmb.i_class_to_handle_map["Class_A.Class_D.Class_G"] = 10;
  rtiAmb.i_class_to_handle_map["Class_A.Class_D.Class_H"] = 11;

  som::init_handles( rtiAmb );

  typedef
    i_class_type< som, q_name< Class_C, Class_A, Class_E > >::type class_type;

  BOOST_CHECK( class_type::get_name() == "Class_A.Class_C.Class_A.Class_E" );
  BOOST_CHECK( class_type::get_handle() == 12 );
  BOOST_CHECK( class_type::get_num_parameters() == 3 );
}

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_i_class_type_ctor )
{
  typedef protox::hla::som< null_o_class, inter_class_table > som;

  RTI::RTIambassador rtiAmb;
  
  rtiAmb.i_class_to_handle_map["Class_A"] = 1;
  rtiAmb.i_class_to_handle_map["Class_A.Class_B"] = 2;
  rtiAmb.i_class_to_handle_map["Class_A.Class_B.Class_E"] = 3;
  rtiAmb.i_class_to_handle_map["Class_A.Class_B.Class_F"] = 4;
  rtiAmb.i_class_to_handle_map["Class_A.Class_B.Class_C"] = 5;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C"] = 6;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C.Class_A"] = 7;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C.Class_A.Class_E"] = 12;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C.Class_C"] = 8;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C.Class_E"] = 13;
  rtiAmb.i_class_to_handle_map["Class_A.Class_D"] = 9;
  rtiAmb.i_class_to_handle_map["Class_A.Class_D.Class_G"] = 10;
  rtiAmb.i_class_to_handle_map["Class_A.Class_D.Class_H"] = 11;
  
  som::init_handles(rtiAmb);

  typedef
    i_class_type< som, q_name< Class_C, Class_A, Class_E > >::type class_type;

  class_type obj;

  BOOST_CHECK( obj.get_param_handle<A1>() > 0 );
  BOOST_CHECK( obj.get_param_handle<A2>() > 0 );
  BOOST_CHECK( obj.get_param_handle<A3>() > 0 );
}

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_i_class_type_param_mutators )
{
  typedef protox::hla::som< null_o_class, inter_class_table > som;

  RTI::RTIambassador rtiAmb;
  
  rtiAmb.i_class_to_handle_map["Class_A"] = 1;
  rtiAmb.i_class_to_handle_map["Class_A.Class_B"] = 2;
  rtiAmb.i_class_to_handle_map["Class_A.Class_B.Class_E"] = 3;
  rtiAmb.i_class_to_handle_map["Class_A.Class_B.Class_F"] = 4;
  rtiAmb.i_class_to_handle_map["Class_A.Class_B.Class_C"] = 5;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C"] = 6;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C.Class_A"] = 7;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C.Class_A.Class_E"] = 12;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C.Class_C"] = 8;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C.Class_E"] = 13;
  rtiAmb.i_class_to_handle_map["Class_A.Class_D"] = 9;
  rtiAmb.i_class_to_handle_map["Class_A.Class_D.Class_G"] = 10;
  rtiAmb.i_class_to_handle_map["Class_A.Class_D.Class_H"] = 11;
  
  som::init_handles(rtiAmb);

  typedef
    i_class_type< som, q_name< Class_C, Class_A, Class_E > >::type class_type;

  class_type obj;

  obj.p_<A1>() = 5;
  obj.p_<A2>() = 10;
  obj.p_<A3>() = 3.145f;

  BOOST_CHECK( obj.p_<A1>() == 5 );
  BOOST_CHECK( obj.p_<A2>() == 10 );
  BOOST_CHECK( (obj.p_<A3>() - 3.145f) < 0.00001f );
}

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_i_class_type_publish )
{
  typedef protox::hla::som< null_o_class, inter_class_table > som;

  RTI::RTIambassador rtiAmb;
  
  rtiAmb.i_class_to_handle_map["Class_A"] = 1;
  rtiAmb.i_class_to_handle_map["Class_A.Class_B"] = 2;
  rtiAmb.i_class_to_handle_map["Class_A.Class_B.Class_E"] = 3;
  rtiAmb.i_class_to_handle_map["Class_A.Class_B.Class_F"] = 4;
  rtiAmb.i_class_to_handle_map["Class_A.Class_B.Class_C"] = 5;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C"] = 6;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C.Class_A"] = 7;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C.Class_A.Class_E"] = 12;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C.Class_C"] = 8;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C.Class_E"] = 13;
  rtiAmb.i_class_to_handle_map["Class_A.Class_D"] = 9;
  rtiAmb.i_class_to_handle_map["Class_A.Class_D.Class_G"] = 10;
  rtiAmb.i_class_to_handle_map["Class_A.Class_D.Class_H"] = 11;
  
  som::init_handles(rtiAmb);

  typedef
    i_class_type< som, q_name< Class_C, Class_A, Class_E > >::type class_type;

  class_type::publish(rtiAmb);
}

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_i_class_type_send )
{
  typedef protox::hla::som< null_o_class, inter_class_table > som;

  RTI::RTIambassador rtiAmb;
  
  rtiAmb.i_class_to_handle_map["Class_A"] = 1;
  rtiAmb.i_class_to_handle_map["Class_A.Class_B"] = 2;
  rtiAmb.i_class_to_handle_map["Class_A.Class_B.Class_E"] = 3;
  rtiAmb.i_class_to_handle_map["Class_A.Class_B.Class_F"] = 4;
  rtiAmb.i_class_to_handle_map["Class_A.Class_B.Class_C"] = 5;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C"] = 6;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C.Class_A"] = 7;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C.Class_A.Class_E"] = 12;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C.Class_C"] = 8;
  rtiAmb.i_class_to_handle_map["Class_A.Class_C.Class_E"] = 13;
  rtiAmb.i_class_to_handle_map["Class_A.Class_D"] = 9;
  rtiAmb.i_class_to_handle_map["Class_A.Class_D.Class_G"] = 10;
  rtiAmb.i_class_to_handle_map["Class_A.Class_D.Class_H"] = 11;
  
  som::init_handles(rtiAmb);

  typedef
    i_class_type< som, q_name< Class_C, Class_A, Class_E > >::type class_type;

  class_type::publish(rtiAmb);

  class_type obj(rtiAmb);

  obj.p_<A1>() = 5;
  obj.p_<A2>() = 10;
  obj.p_<A3>() = 3.145f;

  obj.send();
}

/******************************************************************************/

}

/******************************************************************************/

#endif

/******************************************************************************/
