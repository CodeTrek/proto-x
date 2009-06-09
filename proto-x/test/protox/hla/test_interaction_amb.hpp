/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef TEST_PROTOX_HLA_INTERACTION_AMB_HPP
#define TEST_PROTOX_HLA_INTERACTION_AMB_HPP

/******************************************************************************/

#include <RTI.hh>

#include <boost/mpl/vector.hpp>
#include <boost/shared_ptr.hpp>

#include <protox/hla/o_class.hpp>
#include <protox/hla/i_class.hpp>
#include <protox/hla/i_class_type.hpp>
#include <protox/hla/keywords.hpp>
#include <protox/hla/param.hpp>
#include <protox/hla/name.hpp>
#include <protox/hla/som.hpp>
#include <protox/hla/interaction_amb.hpp>

#include <protox/dtl/simple.hpp>
#include <protox/hla_1516/basic_data_representation_table.hpp>

/******************************************************************************/

namespace test_protox_hla_interaction_amb {

/******************************************************************************/

using namespace protox::hla;
using namespace protox::dtl;
using namespace protox::hla_1516;

/******************************************************************************/

namespace t1
{
  struct simple_int : simple<HLAinteger16BE> {PROTOX_SIMPLE(simple_int)}; 
  struct simple_float : simple<HLAfloat32BE> {PROTOX_SIMPLE(simple_float)}; 

  // Class names 
  struct Class_A { HLA_NAME("Class_A") };
  struct Class_B { HLA_NAME("Class_B") };
  struct Class_C { HLA_NAME("Class_C") };
  struct Class_D { HLA_NAME("Class_D") };
  struct Class_E { HLA_NAME("Class_E") };
  struct Class_F { HLA_NAME("Class_F") };
  struct Class_G { HLA_NAME("Class_G") };
  struct Class_H { HLA_NAME("Class_H") };

  // Parameter names
  struct A1 : protox::hla::param< simple_int > { HLA_NAME("A1") };
  struct A2 : protox::hla::param< simple_int > { HLA_NAME("A2") };
  struct A3 : protox::hla::param< simple_float > { HLA_NAME("A3") };

  // Structure
  struct i_class_table : 
// +------------------+
    i_class< Class_A,
      params< A3 >,
//                    +-------------------------+
                        child< i_class< Class_B,
                          params< A1, A2 >,
//                                              +--------------------------+
                                                  child< i_class< Class_E >,
//                                              +--------------------------+
                                                         i_class< Class_F >,
//                                              +--------------------------+
                                                         i_class< Class_C > > >,
//                                              +--------------------------+
//                    +-------------------------+
                        i_class< Class_C,
                          params< A1, A2 >,
//                                              +--------------------------+
                                                  child< i_class< Class_A,
                                                    none,
//                                                                         +-------------------------+
                                                                             child< i_class< Class_E > > >,
//                                                                         +-------------------------+
//                                              +--------------------------+
                                                         i_class< Class_C >,
//                                              +--------------------------+
                                                         i_class< Class_E > > >,
//                                              +--------------------------+
//                    +-------------------------+
                        i_class< Class_D,
                          params< A1, A2 >,
//                                              +--------------------------+
                                                  child< i_class< Class_G >,
//                                              +--------------------------+
                                                         i_class< Class_H > > > > > {};
//                                              +--------------------------+
//                    +-------------------------+
// +------------------+

  typedef protox::hla::som< null_o_class, i_class_table > som;

  typedef i_class_type< som, q_name< Class_C, Class_A, Class_E > >::type i1_t;
  typedef i_class_type< som, q_name< Class_D, Class_H > >::type i2_t;
  typedef i_class_type< som, q_name< Class_B > >::type i3_t;

  void i1_handler( const i1_t &interaction, const RTI::FedTime *, const char * )
  {
    std::cout << "i1_handler " << interaction.p_< A3 >() << "\n";;
  }

  void i2_handler( const i2_t &interaction, const RTI::FedTime *, const char * )
  {
    std::cout << "i2_handler " << interaction.p_< A1 >() << "\n";;
  }

  void i3_handler( const i3_t &interaction, const RTI::FedTime *, const char * )
  {
    std::cout << "i3_handler " << interaction.p_< A2 >() << "\n";;
  }

} // t1

/******************************************************************************/

using namespace boost;
using namespace t1;
using namespace protox;

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_interaction_amb_recv )
{
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

  hla::interaction_amb< mpl::vector< i1_t, i2_t, i3_t > >::type inter_amb;

  inter_amb.set_handler< i1_t >( i1_handler );
  inter_amb.set_handler< i2_t >( i2_handler );
  inter_amb.set_handler< i3_t >( i3_handler );

  boost::shared_ptr< RTI::ParameterHandleValuePairSet >
     param_set( RTI::ParameterSetFactory::create( 2 ) );

  inter_amb.recv_interaction( 12, *param_set, 0, 0 );
  inter_amb.recv_interaction( 11, *param_set, 0, 0 );
  inter_amb.recv_interaction(  2, *param_set, 0, 0 );
}

/******************************************************************************/

} // test_protox_hla_i_class_type

/******************************************************************************/

#endif

/******************************************************************************/
