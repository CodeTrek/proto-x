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

/**************************************************************************************************/

namespace test_protox_hla_som {

/**************************************************************************************************/
BOOST_AUTO_TEST_CASE( test_som_empty )
{
  typedef protox::hla::som<> som;
  
  //RTI::RTIambassador rtiAmb;  
  //som::init_handles(rtiAmb);

  BOOST_CHECK( som::get_num_object_classes() == 0 ); 
  BOOST_CHECK( som::get_num_interaction_classes() == 0 ); 
}

/**************************************************************************************************/

namespace t1
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
  
 
  struct obj_class_table : 
// +-------------------+
     o_class< Class_A,
              none,
//                     +-------------------------+
                         child< o_class< Class_B,
                                         none,
//                                               +--------------------------------+
                                                   child< o_class< Class_E >,
//                                               +--------------------------------+
                                                          o_class< Class_F >,
//                                               +--------------------------------+
                                                          o_class< Class_C > > >,
//                                               +--------------------------------+
//                     +-------------------------+
                               o_class< Class_C,
                                        none,
//                                               +--------------------------------+
                                                   child< o_class< Class_A >,
//                                               +--------------------------------+
                                                          o_class< Class_C > > >,
//                                               +--------------------------------+
//                     +-------------------------+
                               o_class< Class_D,
                                        none,
//                                               +--------------------------------+
                                                   child< o_class< Class_G >,
//                                               +--------------------------------+
                                                          o_class< Class_H > > > > > {};
//                                               +--------------------------------+
//                     +-------------------------+
// +-------------------+
}

/**************************************************************************************************/

BOOST_AUTO_TEST_CASE( test_som_init_class_handles )
{
  using namespace t1;
  using namespace boost;
  using namespace protox;

  typedef hla::som< obj_class_table > som;
  
  RTI::RTIambassador rtiAmb;  
  som::init_handles(rtiAmb);

  BOOST_CHECK( som::get_num_object_classes() == 11 ); 

  BOOST_CHECK( som::get_object_class_handle("Class_A") > 0 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_B") > 0 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_B.Class_E") > 0 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_B.Class_F") > 0 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_B.Class_C") > 0 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_C") > 0 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_C.Class_A") > 0 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_C.Class_C") > 0 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_D") > 0 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_D.Class_G") > 0 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_D.Class_H") > 0 );

  //som::print_object_class_handle_map();
  //som::print_attr_handle_map();
}

/**************************************************************************************************/

namespace t2
{
  using namespace protox::hla;

//     +------------------------------+-----------+-----------------+-----------------+
//     | Name                         | Attribute | Datatype        | String Name     |
//     +------------------------------+-----------+-----------------+-----------------+
  struct Class_A {HLA_NAME("Class_A")};
                                 struct a1        : attr< int >     { HLA_NAME("a1") };
                                 struct a2        : attr< int >     { HLA_NAME("a2") };
//     +------------------------------+-----------+-----------------+-----------------+
  struct Class_B { HLA_NAME("Class_B") };
                                 struct b1        : attr< int >     { HLA_NAME("b1") };
//     +------------------------------+-----------+-----------------+-----------------+
  struct Class_C { HLA_NAME("Class_C") };
//     +------------------------------+-----------+-----------------+-----------------+
  struct Class_D { HLA_NAME("Class_D") };
//     +------------------------------+-----------+-----------------+-----------------+
  struct Class_E { HLA_NAME("Class_E") };
//     +------------------------------+-----------+-----------------+-----------------+
  struct Class_F { HLA_NAME("Class_F") };
//     +------------------------------+-----------+-----------------+-----------------+
  struct Class_G { HLA_NAME("Class_G") };
                                 struct g1        : attr< int >     { HLA_NAME("g1") };
                                 struct g2        : attr< int >     { HLA_NAME("g2") };
//     +------------------------------+-----------+-----------------+-----------------+
  struct Class_H { HLA_NAME("Class_H") };
//     +------------------------------+-----------+-----------------+-----------------+
  
 
  struct obj_class_table : 
// +-------------------+
     o_class< Class_A,
     attrs< a1, a2 >,
//                     +-------------------------+
                         child< o_class< Class_B,
                         attrs< b1 >,
//                                               +--------------------------------+
                                                   child< o_class< Class_E >,
//                                               +--------------------------------+
                                                          o_class< Class_F >,
//                                               +--------------------------------+
                                                          o_class< Class_C > > >,
//                                               +--------------------------------+
//                     +-------------------------+
                               o_class< Class_C,
                                        none,
//                                               +--------------------------------+
                                                   child< o_class< Class_A >,
//                                               +--------------------------------+
                                                          o_class< Class_C > > >,
//                                               +--------------------------------+
//                     +-------------------------+
                               o_class< Class_D,
                                        none,
//                                               +--------------------------------+
                                                   child< o_class< Class_G, attrs< g1, g2 > >,
//                                               +--------------------------------+
                                                          o_class< Class_H > > > > > {};
//                                               +--------------------------------+
//                     +-------------------------+
// +-------------------+
}

/**************************************************************************************************/

BOOST_AUTO_TEST_CASE( test_som_init_attr_handles )
{
  using namespace t2;
  using namespace boost;
  using namespace protox;

   typedef hla::som< obj_class_table > som;
  
  RTI::RTIambassador rtiAmb;  
  som::init_handles(rtiAmb);

  BOOST_CHECK( som::get_num_object_classes() == 11 ); 

  BOOST_CHECK( som::get_object_class_handle("Class_A") > 0 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_B") > 0 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_B.Class_E") > 0 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_B.Class_F") > 0 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_B.Class_C") > 0 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_C") > 0 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_C.Class_A") > 0 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_C.Class_C") > 0 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_D") > 0 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_D.Class_G") > 0 );
  BOOST_CHECK( som::get_object_class_handle("Class_A.Class_D.Class_H") > 0 );

  BOOST_CHECK( som::get_attr_handle("a1",
                 som::get_object_class_handle("Class_A")) > 0 );

  BOOST_CHECK( som::get_attr_handle("a2",
                 som::get_object_class_handle("Class_A")) > 0 );

  BOOST_CHECK( som::get_attr_handle("Class_A.Class_B", "a2") > 0 );
  BOOST_CHECK( som::get_attr_handle("Class_A.Class_C.Class_A", "a1") > 0 );

  //som::print_object_class_handle_map();
  //som::print_attr_handle_map();
}

/**************************************************************************************************/

namespace t3
{
  using namespace protox::hla;

//     +------------------------------+-----------+-----------------+-----------------+
//     | Name                         | Parameter | Datatype        | String Name     |
//     +------------------------------+-----------+-----------------+-----------------+
  struct Class_A {HLA_NAME("Class_A")};
//                                    +-----------+-----------------+-----------------+
                                 struct a1        : param< int >    { HLA_NAME("a1") };
//                                    +-----------+-----------------+-----------------+
                                 struct a2        : param< int >    { HLA_NAME("a2") };
//     +------------------------------+-----------+-----------------+-----------------+
  struct Class_B {HLA_NAME("Class_B")};
//                                    +-----------+-----------------+-----------------+
                                 struct b1        : param< int >    { HLA_NAME("b1") };
//     +------------------------------+-----------+-----------------+-----------------+
  struct Class_C {HLA_NAME("Class_C")};
//     +------------------------------+-----------+-----------------+-----------------+
  struct Class_D {HLA_NAME("Class_D")};
//     +-----------------------------+-----------+-----------------+-----------------+
  struct Class_E {HLA_NAME("Class_E")};
//     +-----------------------------+-----------+-----------------+-----------------+
  struct Class_F {HLA_NAME("Class_F")};
//     +------------------------------+-----------+-----------------+-----------------+
  struct Class_G {HLA_NAME("Class_G")};
//                                    +-----------+-----------------+-----------------+
                                 struct g1        : param< int >    { HLA_NAME("g1") };
//                                    +-----------+-----------------+-----------------+
                                 struct g2        : param< int >    { HLA_NAME("g2") };
//     +------------------------------+-----------+-----------------+-----------------+
  struct Class_H {HLA_NAME("Class_H")};
//     +------------------------------+-----------+-----------------+-----------------+
  
 
  struct inter_class_table : 
// +-------------------+
     i_class< Class_A,
     params< a1, a2 >,
//                     +-------------------------+
                         child< i_class< Class_B,
                         params< b1 >,
//                                               +--------------------------------+
                                                   child< i_class< Class_E >,
//                                               +--------------------------------+
                                                          i_class< Class_F >,
//                                               +--------------------------------+
                                                          i_class< Class_C > > >,
//                                               +--------------------------------+
//                     +-------------------------+
                               i_class< Class_C,
                                        none,
//                                               +--------------------------------+
                                                   child< i_class< Class_A >,
//                                               +--------------------------------+
                                                          i_class< Class_C > > >,
//                                               +--------------------------------+
//                     +-------------------------+
                               i_class< Class_D,
                                        none,
//                                               +--------------------------------+
                                                   child< i_class< Class_G, params< g1, g2 > >,
//                                               +--------------------------------+
                                                          i_class< Class_H > > > > > {};
//                                               +--------------------------------+
//                     +-------------------------+
// +-------------------+
}

/**************************************************************************************************/

BOOST_AUTO_TEST_CASE( test_som_init_param_handles )
{
  using namespace t3;
  using namespace boost;
  using namespace protox;

  typedef hla::som< null_o_class, inter_class_table > som;
  
  RTI::RTIambassador rtiAmb;  
  som::init_handles(rtiAmb);

  BOOST_CHECK( som::get_num_interaction_classes() == 11 ); 

  BOOST_CHECK( som::get_interaction_class_handle("Class_A") > 0 );
  BOOST_CHECK( som::get_interaction_class_handle("Class_A.Class_B") > 0 );
  BOOST_CHECK( som::get_interaction_class_handle("Class_A.Class_B.Class_E") > 0 );
  BOOST_CHECK( som::get_interaction_class_handle("Class_A.Class_B.Class_F") > 0 );
  BOOST_CHECK( som::get_interaction_class_handle("Class_A.Class_B.Class_C") > 0 );
  BOOST_CHECK( som::get_interaction_class_handle("Class_A.Class_C") > 0 );
  BOOST_CHECK( som::get_interaction_class_handle("Class_A.Class_C.Class_A") > 0 );
  BOOST_CHECK( som::get_interaction_class_handle("Class_A.Class_C.Class_C") > 0 );
  BOOST_CHECK( som::get_interaction_class_handle("Class_A.Class_D") > 0 );
  BOOST_CHECK( som::get_interaction_class_handle("Class_A.Class_D.Class_G") > 0 );
  BOOST_CHECK( som::get_interaction_class_handle("Class_A.Class_D.Class_H") > 0 );

  BOOST_CHECK( som::get_param_handle("a1",
                 som::get_interaction_class_handle("Class_A")) > 0 );

  BOOST_CHECK( som::get_param_handle("a2",
                 som::get_interaction_class_handle("Class_A")) > 0 );

  BOOST_CHECK( som::get_param_handle("Class_A.Class_B", "a2") > 0 );
  BOOST_CHECK( som::get_param_handle("Class_A.Class_C.Class_A", "a1") > 0 );
}

/**************************************************************************************************/

namespace t4
{
  using namespace protox::hla;
////// Attribute Table ////////////////////////////
//     +------------------------------------------+----------------------------+--------------+----------------------------------------+
//     | Name                                     | Attribute                  | Datatype     | String Name                            |
//     +------------------------------------------+----------------------------+--------------+----------------------------------------+
  struct HLAobjectRoot {HLA_NAME("HLAobjectRoot")};
                                             struct HLAprivilegeToDeleteObject : attr< int >  { HLA_NAME("HLAprivilegeToDeleteObject")};
//     +------------------------------------------+----------------------------+--------------+----------------------------------------+
  struct Employee      {HLA_NAME("Employee")};
                                             struct PayRate                    : attr< int >  { HLA_NAME("PayRate")};
                                             struct YearsOfService             : attr< int >  { HLA_NAME("YearsOfService")};
                                             struct HomeNumber                 : attr< int >  { HLA_NAME("HomeNumber")};
                                             struct HomeAddress                : attr< int >  { HLA_NAME("HomeAddress")};
//     +------------------------------------------+----------------------------+--------------+----------------------------------------+
  struct Waiter        {HLA_NAME("Waiter")};
                                             struct Efficiency                 : attr< int >  { HLA_NAME("Efficiency")};
                                             struct Cheerfulness               : attr< int >  { HLA_NAME("Cheerfulness")};
                                             struct State                      : attr< int >  { HLA_NAME("State")};
//     +------------------------------------------+----------------------------+--------------+----------------------------------------+
  struct DishWasher    {HLA_NAME("DishWasher")};
                                             struct CleaningRate               : attr< int >  { HLA_NAME("CleaningRate")};
//     +------------------------------------------+----------------------------+--------------+----------------------------------------+
  struct Food          {HLA_NAME("Food")};
                                             struct Price                      : attr< int >  { HLA_NAME("Price")};
//     +------------------------------------------+----------------------------+--------------+----------------------------------------+
  struct Entree        {HLA_NAME("Entree")};
                                             struct MenuItem                   : attr< int >  { HLA_NAME("MenuItem")};
//     +------------------------------------------+----------------------------+--------------+----------------------------------------+
  struct Beef          {HLA_NAME("Beef")};
                                             struct TypeOfCut                  : attr< int >  { HLA_NAME("TypeOfCut")};
//     +------------------------------------------+----------------------------+--------------+----------------------------------------+
  struct Seafood       {HLA_NAME("Seafood")};
//     +------------------------------------------+----------------------------+--------------+----------------------------------------+
  struct Dessert       {HLA_NAME("Dessert")};
//     +------------------------------------------+----------------------------+--------------+----------------------------------------+


//// Object Class Table ////////////////////////////////////////////////////////////////////////
   struct obj_class_table : o_class< HLAobjectRoot, attrs< HLAprivilegeToDeleteObject >, child< 
// +--------------------+--------------------------+-------------------------+
// | Class 1            | Class 2                  | Class 3                 |
// +--------------------+--------------------------+-------------------------+
     o_class< Employee,                                                         attrs< PayRate, YearsOfService, HomeNumber, HomeAddress >,
//                      +--------------------------+
                          child< o_class< Waiter,                               attrs< Efficiency, Cheerfulness, State > >,
//                      +--------------------------+
                                 o_class< DishWasher,                           attrs< CleaningRate > > > >,
//                      +--------------------------+
// +--------------------+
     o_class< Food,                                                             attrs< Price >,
//                      +--------------------------+
                          child< o_class< Entree,                               attrs< MenuItem >,
//                                                 +-------------------------+
                                                     child< o_class< Beef,      attrs< TypeOfCut > >,
//                                                 +-------------------------+
                                                            o_class< Seafood > > >,
//                                                 +-------------------------+
//                      +--------------------------+
                                 o_class< Dessert > > > > > {};
//                      +--------------------------+
// +--------------------+

//////// Parameter Table //////////////////////////////////////
//     +------------------------------------------------------+---------------+---------------+--------------------------+
//     | Name                                                 | Parameter     | Datatype      | String Name              |
//     +------------------------------------------------------+---------------+---------------+--------------------------+
  struct HLAinteractionRoot  {HLA_NAME("HLAinteractionRoot")};
//     +------------------------------------------------------+---------------+---------------+--------------------------+
  struct CustomerTransaction {HLA_NAME("CustomerTransaction")};
//     +------------------------------------------------------+---------------+---------------+--------------------------+
  struct CustomerSeated      {HLA_NAME("CustomerSeated")};
                                                         struct TimeSeated    : param < int > { HLA_NAME("TimeSeated")};
//     +------------------------------------------------------+---------------+---------------+--------------------------+
  struct FoodServed          {HLA_NAME("FoodServed")};
                                                         struct TemperatureOk : param < int > { HLA_NAME("TemperatureOk")};
                                                         struct AccuracyOk    : param < int > { HLA_NAME("AccuracyOk")};
                                                         struct TimelinessOk  : param < int > { HLA_NAME("TimelinessOk")};
//     +------------------------------------------------------+---------------+---------------+--------------------------+

//// Interaction Class Table /////////////////////////////////////////////////
   struct inter_class_table : i_class< HLAinteractionRoot, none, child< 
// +-------------------------------+-------------------------------+
// | Class 1                       | Class 2                       |
// +-------------------------------+-------------------------------+
     i_class< CustomerTransaction,
     none,
//                                 +-------------------------------+
                                     child< i_class< CustomerSeated,  params< TimeSeated > >,
//                                 +-------------------------------+
                                            i_class< FoodServed,      params< TemperatureOk, AccuracyOk, TimelinessOk > > > > > > {};
// +-------------------------------+-------------------------------+
}

/**************************************************************************************************/

BOOST_AUTO_TEST_CASE( test_som_init_handles )
{
  using namespace t4;
  using namespace boost;
  using namespace protox;

  typedef hla::som< obj_class_table, inter_class_table > som;
  
  RTI::RTIambassador rtiAmb;  
  som::init_handles(rtiAmb);

  BOOST_CHECK( som::get_num_object_classes() == 9 ); 
  BOOST_CHECK( som::get_num_interaction_classes() == 4 ); 

  BOOST_CHECK( som::get_object_class_handle("HLAobjectRoot") > 0 );
  BOOST_CHECK( som::get_object_class_handle("HLAobjectRoot.Employee") > 0 );
  BOOST_CHECK( som::get_object_class_handle("HLAobjectRoot.Employee.Waiter") > 0 );
  BOOST_CHECK( som::get_object_class_handle("HLAobjectRoot.Employee.DishWasher") > 0 );
  BOOST_CHECK( som::get_object_class_handle("HLAobjectRoot.Food") > 0 );
  BOOST_CHECK( som::get_object_class_handle("HLAobjectRoot.Food.Entree") > 0 );
  BOOST_CHECK( som::get_object_class_handle("HLAobjectRoot.Food.Entree.Beef") > 0 );
  BOOST_CHECK( som::get_object_class_handle("HLAobjectRoot.Food.Entree.Seafood") > 0 );
  BOOST_CHECK( som::get_object_class_handle("HLAobjectRoot.Food.Dessert") > 0 );

  BOOST_CHECK( som::get_attr_handle("HLAobjectRoot.Employee.DishWasher", "HLAprivilegeToDeleteObject") > 0 );
  BOOST_CHECK( som::get_attr_handle("HLAobjectRoot.Employee.DishWasher", "HomeAddress") > 0 );
}

/**************************************************************************************************/

} // namespace test_protox_hla_o_class

/**************************************************************************************************/

#endif

/**************************************************************************************************/
