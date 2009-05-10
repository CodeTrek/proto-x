/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef TEST_PROTOX_HLA_O_CLASS_TYPE_HPP
#define TEST_PROTOX_HLA_O_CLASS_TYPE_HPP

/**************************************************************************************************/

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

/**************************************************************************************************/

namespace test_protox_hla_o_class_type {

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
  struct o_class_table : 
    o_class< Class_A,
             attrs< A3 >,
             child< o_class< Class_B,
                             attrs< A1, A2 >,
                             child< o_class< Class_E >,
                                    o_class< Class_F >,
                                    o_class< Class_C > > >,
                    o_class< Class_C,
                             attrs< A1, A2 >,
                             child< o_class< Class_A,
                                             none,
                                             child< o_class< Class_E > > >,
                                    o_class< Class_C >,
                                    o_class< Class_E > > >,
                    o_class< Class_D,
                             attrs< A1, A2 >,
                             child< o_class< Class_G >,
                                    o_class< Class_H > > > > > {};


}

BOOST_AUTO_TEST_CASE( test_o_class_type )
{
  using namespace boost;
  using namespace t1;

  typedef hla::som< o_class_table > som;

  RTI::RTIambassador rtiAmb;  
  som::init_handles(rtiAmb);

  som::print_object_class_handle_map();
  som::print_attr_handle_map();

  typedef o_class_type< som, qualified_name< Class_C, Class_A, Class_E > > class_type;

  std::cout << mpl::size< class_type::attr_vector_type >::value << "\n";
  class_type::type bObj;

  bObj.a_<A1>() = 5;
  bObj.a_<A2>() = 10;
  bObj.a_<A3>() = 3.145;

  std::cout << "class name = " << class_type::type::get_name() << "\n";
  std::cout << "class handle = " << class_type::type::get_handle() << "\n";

  std::cout << "bObj.a_<A1> = " << bObj.a_<A1>() << "\n";
  std::cout << "bObj.a_<A2> = " << bObj.a_<A2>() << "\n";
  std::cout << "bObj.a_<A3> = " << bObj.a_<A3>() << "\n";
}

/**************************************************************************************************/

} // namespace test_protox_hla_o_class_type

/**************************************************************************************************/

#endif

/**************************************************************************************************/
