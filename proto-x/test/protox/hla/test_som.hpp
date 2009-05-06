/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef TEST_PROTOX_HLA_SOM_HPP
#define TEST_PROTOX_HLA_SOM_HPP

/**************************************************************************************************/

#include <RTI.hh>

#include <boost/mpl/size.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/int.hpp>

#include <protox/hla/o_class.hpp>
#include <protox/hla/keywords.hpp>
#include <protox/hla/attr.hpp>
#include <protox/hla/name.hpp>

#include <protox/hla/som.hpp>

/**************************************************************************************************/

namespace test_protox_hla_som {

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
  
    // Attribute names
  struct A1 : protox::hla::attr< int > { HLA_NAME("A1") };
  struct A2 : protox::hla::attr< int > { HLA_NAME("A2") };
  struct A3 : protox::hla::attr< double > { HLA_NAME("A3") };
  
  // Structure
  struct c_type : 
    o_class< Class_A,
               attrs< A1 >,
               child< o_class< Class_B,    // index 0
                                 none,
                                 child< o_class< Class_E >,
                                        o_class< Class_F >,
                                        o_class< Class_C > > >,
                      o_class< Class_C,    // index 1
                                 attrs< A2, A3 >,
                                 child< o_class< Class_A >,
                                        o_class< Class_C > > >,
                      o_class< Class_D,    // index 2
                                 none,
                                 child< o_class< Class_G >,
                                        o_class< Class_H > > > > > {};

}

BOOST_AUTO_TEST_CASE( test_som )
{
  using namespace t1;
  using namespace boost;

  typedef protox::hla::som< c_type > som;
  
  RTI::RTIambassador rtiAmb;  
  som::init_handles(rtiAmb);
  
  //som::o_class<name_vector>::type class_a;
  //class_a a;
}

/**************************************************************************************************/

} // namespace test_protox_hla_o_class

/**************************************************************************************************/

#endif

/**************************************************************************************************/
