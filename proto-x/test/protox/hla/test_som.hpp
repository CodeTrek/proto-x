/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef TEST_PROTOX_HLA_SOM_HPP
#define TEST_PROTOX_HLA_SOM_HPP

/**************************************************************************************************/

#include <iostream>

#include <RTI.hh>

#include <protox/hla/o_class.hpp>
#include <protox/hla/attr.hpp>
#include <protox/hla/i_class.hpp>
#include <protox/hla/param.hpp>
#include <protox/hla/keywords.hpp>
#include <protox/hla/name.hpp>
#include <protox/hla/som.hpp>

#include <test/protox/hla/som/boccerball/obj_class_table.hpp>
#include <test/protox/hla/som/abc/obj_class_table.hpp>

#include <test/protox/hla/som/abc_populated/obj_class_table.hpp>
#include <test/protox/hla/som/abc_populated/inter_class_table.hpp>

#include <test/protox/hla/som/restaurant/inter_class_table.hpp>
#include <test/protox/hla/som/restaurant/obj_class_table.hpp>

/**************************************************************************************************/

namespace test_protox_hla_som {

/**************************************************************************************************/

BOOST_AUTO_TEST_CASE( test_boccerball_som )
{
  using namespace boost;
  using namespace protox;

  typedef hla::som< som::boccerball::obj_class_table > som;

  RTI::RTIambassador rtiAmb;

  rtiAmb.o_class_to_handle_map[ "HLAobjectRoot"                   ] = 1;
  rtiAmb.o_class_to_handle_map[ "HLAobjectRoot.Table"             ] = 2;
  rtiAmb.o_class_to_handle_map[ "HLAobjectRoot.GameObject"        ] = 3;
  rtiAmb.o_class_to_handle_map[ "HLAobjectRoot.GameObject.Target" ] = 4;
  rtiAmb.o_class_to_handle_map[ "HLAobjectRoot.GameObject.Marble" ] = 5;
  rtiAmb.o_class_to_handle_map[ "HLAobjectRoot.Player"            ] = 6;
  rtiAmb.o_class_to_handle_map[ "HLAobjectRoot.Player.Human"      ] = 7;
  rtiAmb.o_class_to_handle_map[ "HLAobjectRoot.Player.AI"         ] = 8;

  som::init_handles(rtiAmb);

  BOOST_CHECK( som::get_num_object_classes() == 8 );
}

/**************************************************************************************************/
BOOST_AUTO_TEST_CASE( test_som_empty )
{
  typedef protox::hla::som<> som;

  BOOST_CHECK( som::get_num_object_classes() == 0 );
  BOOST_CHECK( som::get_num_interaction_classes() == 0 );
}

/**************************************************************************************************/

BOOST_AUTO_TEST_CASE( test_som_init_class_handles )
{
  using namespace boost;
  using namespace protox;

  typedef hla::som< som::abc::obj_class_table > som;

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

  BOOST_CHECK( som::get_num_object_classes() == 11 );

  BOOST_CHECK( som::get_object_class_handle("Class_A") == 1 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_B") == 2 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_B.Class_E") == 3 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_B.Class_F") == 4 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_B.Class_C") == 5 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_C") == 6 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_C.Class_A") == 7 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_C.Class_C") == 8 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_D") == 9 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_D.Class_G") == 10 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_D.Class_H") == 11 );
}

/**************************************************************************************************/

BOOST_AUTO_TEST_CASE( test_som_init_attr_handles )
{
  using namespace boost;
  using namespace protox;

  typedef hla::som< som::abc_populated::obj_class_table > som;

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

  BOOST_CHECK( som::get_num_object_classes() == 11 );

  BOOST_CHECK( som::get_attr_handle("a1",
                 som::get_object_class_handle("Class_A")) > 0 );

  BOOST_CHECK( som::get_attr_handle("a2",
                 som::get_object_class_handle("Class_A")) > 0 );

  BOOST_CHECK( som::get_attr_handle("Class_A.Class_B", "a2") > 0 );
  BOOST_CHECK( som::get_attr_handle("Class_A.Class_C.Class_A", "a1") > 0 );
}

/**************************************************************************************************/

BOOST_AUTO_TEST_CASE( test_som_init_param_handles )
{
  using namespace boost;
  using namespace protox;

  typedef hla::som< hla::null_o_class, som::abc_populated::inter_class_table > som;

  RTI::RTIambassador rtiAmb;
  rtiAmb.i_class_to_handle_map["IClass_A"] = 1;
  rtiAmb.i_class_to_handle_map["IClass_A.IClass_B"] = 2;
  rtiAmb.i_class_to_handle_map["IClass_A.IClass_B.IClass_E"] = 3;
  rtiAmb.i_class_to_handle_map["IClass_A.IClass_B.IClass_F"] = 4;
  rtiAmb.i_class_to_handle_map["IClass_A.IClass_B.IClass_C"] = 5;
  rtiAmb.i_class_to_handle_map["IClass_A.IClass_C"] = 6;
  rtiAmb.i_class_to_handle_map["IClass_A.IClass_C.IClass_A"] = 7;
  rtiAmb.i_class_to_handle_map["IClass_A.IClass_C.IClass_C"] = 8;
  rtiAmb.i_class_to_handle_map["IClass_A.IClass_D"] = 9;
  rtiAmb.i_class_to_handle_map["IClass_A.IClass_D.IClass_G"] = 10;
  rtiAmb.i_class_to_handle_map["IClass_A.IClass_D.IClass_H"] = 11;
  som::init_handles(rtiAmb);

  BOOST_CHECK( som::get_num_interaction_classes() == 11 );

  BOOST_CHECK( som::get_param_handle("pa1",
                 som::get_interaction_class_handle("IClass_A")) > 0 );

  BOOST_CHECK( som::get_param_handle("pa2",
                 som::get_interaction_class_handle("IClass_A")) > 0 );

  BOOST_CHECK( som::get_param_handle("IClass_A.IClass_B", "pa2") > 0 );
  BOOST_CHECK( som::get_param_handle("IClass_A.IClass_C.IClass_A", "pa1") > 0 );
}

/**************************************************************************************************/

BOOST_AUTO_TEST_CASE( test_som_init_handles )
{
  using namespace boost;
  using namespace protox;

  typedef hla::som< som::restaurant::obj_class_table, som::restaurant::inter_class_table > som;

  RTI::RTIambassador rtiAmb;

  rtiAmb.o_class_to_handle_map["HLAobjectRoot"] = 1;
  rtiAmb.o_class_to_handle_map["HLAobjectRoot.Employee"] = 2;
  rtiAmb.o_class_to_handle_map["HLAobjectRoot.Employee.Waiter"] = 3;
  rtiAmb.o_class_to_handle_map["HLAobjectRoot.Employee.DishWasher"] = 4;
  rtiAmb.o_class_to_handle_map["HLAobjectRoot.Food"] = 5;
  rtiAmb.o_class_to_handle_map["HLAobjectRoot.Food.Entree"] = 6;
  rtiAmb.o_class_to_handle_map["HLAobjectRoot.Food.Entree.Beef"] = 7;
  rtiAmb.o_class_to_handle_map["HLAobjectRoot.Food.Entree.Seafood"] = 8;
  rtiAmb.o_class_to_handle_map["HLAobjectRoot.Food.Dessert"] = 9;

  rtiAmb.i_class_to_handle_map["HLAinteractionRoot"] = 1;
  rtiAmb.i_class_to_handle_map["HLAinteractionRoot.CustomerTransaction"] = 2;
  rtiAmb.i_class_to_handle_map["HLAinteractionRoot.CustomerTransaction.CustomerSeated"] = 3;
  rtiAmb.i_class_to_handle_map["HLAinteractionRoot.CustomerTransaction.FoodServed"] = 4;

  som::init_handles(rtiAmb);

  // Check object and attribute handles
  BOOST_CHECK( som::get_num_object_classes() == 9 );

  BOOST_CHECK( som::get_object_class_handle("HLAobjectRoot") == 1 );
  BOOST_CHECK( som::get_object_class_handle("HLAobjectRoot.Employee") == 2 );
  BOOST_CHECK( som::get_object_class_handle("HLAobjectRoot.Employee.Waiter") == 3 );
  BOOST_CHECK( som::get_object_class_handle("HLAobjectRoot.Employee.DishWasher") == 4 );
  BOOST_CHECK( som::get_object_class_handle("HLAobjectRoot.Food") == 5 );
  BOOST_CHECK( som::get_object_class_handle("HLAobjectRoot.Food.Entree") == 6 );
  BOOST_CHECK( som::get_object_class_handle("HLAobjectRoot.Food.Entree.Beef") == 7 );
  BOOST_CHECK( som::get_object_class_handle("HLAobjectRoot.Food.Entree.Seafood") == 8 );
  BOOST_CHECK( som::get_object_class_handle("HLAobjectRoot.Food.Dessert") == 9 );

  BOOST_CHECK( som::get_attr_handle("HLAobjectRoot.Employee.DishWasher", "HLAprivilegeToDeleteObject") > 0 );
  BOOST_CHECK( som::get_attr_handle("HLAobjectRoot.Employee.DishWasher", "HomeAddress") > 0 );

  // Check interaction and parameter handles
  BOOST_CHECK( som::get_num_interaction_classes() == 4 );

  BOOST_CHECK( som::get_interaction_class_handle("HLAinteractionRoot") == 1 );
  BOOST_CHECK( som::get_interaction_class_handle("HLAinteractionRoot.CustomerTransaction") == 2 );
  BOOST_CHECK( som::get_interaction_class_handle("HLAinteractionRoot.CustomerTransaction.CustomerSeated") == 3 );
  BOOST_CHECK( som::get_interaction_class_handle("HLAinteractionRoot.CustomerTransaction.FoodServed") == 4);

  BOOST_CHECK( som::get_param_handle("HLAinteractionRoot.CustomerTransaction.CustomerSeated", "TimeSeated") > 0 );
  BOOST_CHECK( som::get_param_handle("HLAinteractionRoot.CustomerTransaction.FoodServed", "TimelinessOk") > 0 );
}

/**************************************************************************************************/

} // namespace test_protox_hla_o_class

/**************************************************************************************************/

#endif

/**************************************************************************************************/
