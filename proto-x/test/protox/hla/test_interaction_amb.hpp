/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef TEST_PROTOX_HLA_INTERACTION_AMB_HPP
#define TEST_PROTOX_HLA_INTERACTION_AMB_HPP

/******************************************************************************/

#include <math.h>

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

#include <test/protox/hla/som/s009/inter_class_table.hpp>

/******************************************************************************/

namespace test_protox_hla_interaction_amb {

/******************************************************************************/

namespace t1
{
  using namespace som_s009;

  typedef protox::hla::som< null_o_class, inter_class_table > som;

  typedef i_class_type< som, q_name< Class_C, Class_A, Class_E > >::type i1_t;
  typedef i_class_type< som, q_name< Class_D, Class_H > >::type i2_t;
  typedef i_class_type< som, q_name< Class_B > >::type i3_t;
  
  const int V1 = 2552;
  const float V2 = 3.14156f;
  const float V3 = 0.12345f;
  const float E = 0.000001f;
  
  bool i1_handler_called = false;
  bool i2_handler_called = false;
  bool i3_handler_called = false;

  void i1_handler( const i1_t &interaction, const RTI::FedTime *, const char * )
  {
    i1_handler_called = true;
  
    BOOST_CHECK( (interaction.p_< A1 >() - V1) == 0    ); 
    BOOST_CHECK( (interaction.p_< A2 >() - V2) <= E    ); 
    BOOST_CHECK( interaction.p_< A3 >()        == 0.0f ); 
  }

  void i2_handler( const i2_t &interaction, const RTI::FedTime *, const char * )
  {
    i2_handler_called = true;
    
    BOOST_CHECK( (interaction.p_< A1 >() - V1) == 0 ); 
    BOOST_CHECK( (interaction.p_< A2 >() - V2) <= E ); 
  }

  void i3_handler( const i3_t &interaction, const RTI::FedTime *, const char * )
  {
    i3_handler_called = true;
    
    BOOST_CHECK( (interaction.p_< A1 >() - V1) == 0 ); 
    BOOST_CHECK( (interaction.p_< A2 >() - V2) <= E ); 
    BOOST_CHECK( (interaction.p_< A3 >() - V3) <= E ); 
  }

} // t1

/******************************************************************************/

using namespace boost;
using namespace protox;
using namespace t1;

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_interaction_amb_recv )
{
  using namespace som_s009;
  
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
    ph_set1( RTI::ParameterSetFactory::create( 2 ) );

  // Encode some values and add them to n attribute handle value pair set.
  simple_int v1 = 2552;

  protox::io::byte_data_sink sink;
  sink.encode( v1 );

  ph_set1->add( i1_t().get_param_handle< A1 >(),
               sink.getDataBuffer(),
               (RTI::ULong) sink.getDataBufferSize() );

  sink.clear();
  simple_float v2 = V2;
  sink.encode( v2 );

  ph_set1->add( i1_t().get_param_handle< A2 >(),
               sink.getDataBuffer(),
               (RTI::ULong) sink.getDataBufferSize() );
               
  boost::shared_ptr< RTI::ParameterHandleValuePairSet >
    ph_set2( RTI::ParameterSetFactory::create( 2 ) );
    
  sink.clear();
  sink.encode( v1 );
  
  ph_set2->add( i2_t().get_param_handle< A1 >(),
               sink.getDataBuffer(),
               (RTI::ULong) sink.getDataBufferSize() );
               
  sink.clear();
  sink.encode( v2 );
  
  ph_set2->add( i2_t().get_param_handle< A2 >(),
               sink.getDataBuffer(),
               (RTI::ULong) sink.getDataBufferSize() );
               
  boost::shared_ptr< RTI::ParameterHandleValuePairSet >
    ph_set3( RTI::ParameterSetFactory::create( 3 ) );
    
  sink.clear();
  sink.encode( v1 );
  
  ph_set3->add( i3_t().get_param_handle< A1 >(),
               sink.getDataBuffer(),
               (RTI::ULong) sink.getDataBufferSize() );
               
  sink.clear();
  sink.encode( v2 );
  
  ph_set3->add( i3_t().get_param_handle< A2 >(),
               sink.getDataBuffer(),
               (RTI::ULong) sink.getDataBufferSize() );
               
  simple_float v3 = V3;
               
  sink.clear();
  sink.encode( v3 );
  
  ph_set3->add( i3_t().get_param_handle< A3 >(),
               sink.getDataBuffer(),
               (RTI::ULong) sink.getDataBufferSize() );
               
  inter_amb.recv_interaction( 12, *ph_set1, 0, 0 );
  inter_amb.recv_interaction( 11, *ph_set2, 0, 0 );
  inter_amb.recv_interaction(  2, *ph_set3, 0, 0 );
  
  BOOST_CHECK( i1_handler_called );
  BOOST_CHECK( i2_handler_called );
  BOOST_CHECK( i3_handler_called );
}

/******************************************************************************/

}

/******************************************************************************/

#endif

/******************************************************************************/
