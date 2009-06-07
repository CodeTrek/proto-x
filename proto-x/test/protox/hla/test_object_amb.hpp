/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef TEST_PROTOX_HLA_OBJECT_AMB_HPP
#define TEST_PROTOX_HLA_OBJECT_AMB_HPP

/******************************************************************************/

#include <math.h>

#include <RTI.hh>

#include <boost/mpl/vector.hpp>
#include <boost/shared_ptr.hpp>

#include <protox/dtl/simple.hpp>
#include <protox/hla_1516/basic_data_representation_table.hpp>
#include <protox/hla_1516/fixed_record.hpp>

#include <protox/hla/o_class.hpp>
#include <protox/hla/o_class_type.hpp>
#include <protox/hla/keywords.hpp>
#include <protox/hla/attr.hpp>
#include <protox/hla/name.hpp>
#include <protox/hla/som.hpp>

#include <protox/hla/object_amb.hpp>

/******************************************************************************/

namespace test_protox_hla_object_amb {

/******************************************************************************/

using namespace boost;
using namespace protox;
using namespace protox::hla;
using namespace protox::dtl;
using namespace protox::hla_1516;

/******************************************************************************/

namespace t1 {

  struct SimpleHLAoctet : simple< HLAoctet >
    { PROTOX_SIMPLE( SimpleHLAoctet ) };

  struct f1 : protox::dtl::field< SimpleHLAoctet > {};
  struct f2 : protox::dtl::field< SimpleHLAoctet > {};
  struct f3 : protox::dtl::field< SimpleHLAoctet > {};

  typedef hla_1516::fixed_record< mpl::vector < f1, f2, f3 > > R1;

  struct SimpleHLAinteger32BE : simple<HLAinteger32BE>
    { PROTOX_SIMPLE( SimpleHLAinteger32BE ) }; 

  struct SimpleHLAfloat32BE : simple<HLAfloat32BE>
    { PROTOX_SIMPLE( SimpleHLAfloat32BE ) }; 

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
  struct A1 : protox::hla::attr< SimpleHLAinteger32BE > { HLA_NAME("A1") };
  struct A2 : protox::hla::attr< SimpleHLAfloat32BE   > { HLA_NAME("A2") };
  struct A3 : protox::hla::attr< R1                   > { HLA_NAME("A3") };
  struct A4 : protox::hla::attr< SimpleHLAinteger32BE > { HLA_NAME("A4") };

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

using namespace t1;

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_discover_object )
{
  typedef protox::hla::som< o_class_table > som;

  RTI::RTIambassador rti_amb;
  rti_amb.o_class_to_handle_map[ "Class_A"                         ] =  1;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_B"                 ] =  2;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_B.Class_E"         ] =  3;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_B.Class_F"         ] =  4;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_B.Class_C"         ] =  5;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_C"                 ] =  6;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_C.Class_A"         ] =  7;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_C.Class_A.Class_E" ] = 12;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_C.Class_C"         ] =  8;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_C.Class_E"         ] = 13;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_D"                 ] =  9;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_D.Class_G"         ] = 10;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_D.Class_H"         ] = 11;
  som::init_handles( rti_amb );

  typedef o_class_type< som, q_name< Class_C, Class_A, Class_E > >::type c1;
  typedef o_class_type< som, q_name< Class_D, Class_H > >::type c2;
  typedef o_class_type< som, q_name< Class_B > >::type c3;

  hla::object_amb< mpl::vector< c1, c2, c3 > >::type obj_amb;

  BOOST_CHECK( obj_amb.empty< c1 >() == true );
  BOOST_CHECK( obj_amb.empty< c2 >() == true );
  BOOST_CHECK( obj_amb.empty< c3 >() == true );

  obj_amb.discover_object( 12, 1, "c1_1" );

  BOOST_CHECK( obj_amb.size< c1 >() == 1 );

  //const char a = obj_amb.begin< c1 >()->second.a_< A3 >().f_< f1 >();
  BOOST_CHECK( obj_amb.begin< c1 >()->second.get_obj_name() == "c1_1" );

  obj_amb.discover_object( 2, 1, "c3_1" );
  obj_amb.discover_object( 2, 2, "c3_2" );

  BOOST_CHECK( obj_amb.size< c3 >() == 2 );

  BOOST_CHECK( obj_amb.begin< c3 >() != obj_amb.end< c3 >() );

  BOOST_CHECK( obj_amb.begin< c2 >() == obj_amb.end< c2 >() );

  obj_amb.discover_object( 11, 1, "c2_1" );
  obj_amb.discover_object( 11, 2, "c2_2" );
  obj_amb.discover_object( 11, 3, "c2_3" );

  BOOST_CHECK( obj_amb.begin< c2 >() != obj_amb.end< c2 >() );
  BOOST_CHECK( obj_amb.size< c2 >() == 3 );

  BOOST_CHECK_THROW( obj_amb.discover_object( 9, 1, "cx_1" ),
                     RTI::ObjectClassNotKnown );
}

BOOST_AUTO_TEST_CASE( test_reflect_object )
{
  typedef protox::hla::som< o_class_table > som;

  RTI::RTIambassador rti_amb;
  rti_amb.o_class_to_handle_map[ "Class_A"                         ] =  1;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_B"                 ] =  2;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_B.Class_E"         ] =  3;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_B.Class_F"         ] =  4;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_B.Class_C"         ] =  5;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_C"                 ] =  6;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_C.Class_A"         ] =  7;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_C.Class_A.Class_E" ] = 12;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_C.Class_C"         ] =  8;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_C.Class_E"         ] = 13;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_D"                 ] =  9;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_D.Class_G"         ] = 10;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_D.Class_H"         ] = 11;
  som::init_handles( rti_amb );

  typedef o_class_type< som, q_name< Class_C, Class_A, Class_E > >::type c1_t;
  typedef o_class_type< som, q_name< Class_D, Class_H > >::type c2_t;
  typedef o_class_type< som, q_name< Class_B > >::type c3_t;

  hla::object_amb< mpl::vector< c1_t, c2_t, c3_t > >::type obj_amb;

  BOOST_CHECK( obj_amb.empty< c1_t >() == true );
  BOOST_CHECK( obj_amb.empty< c2_t >() == true );
  BOOST_CHECK( obj_amb.empty< c3_t >() == true );

  obj_amb.discover_object( 12, 1, "c1_1" );

  const int V1 = 2552;
  const float V2 = 3.14156f;
  const float E = 0.000001f;

  BOOST_CHECK( obj_amb.begin< c1_t >()->second.a_< A1 >() != V1 );
  BOOST_CHECK( fabs( obj_amb.begin< c1_t >()->second.a_< A2 >() - V2 ) > E );

  boost::shared_ptr< RTI::AttributeHandleValuePairSet >
    ah_set( RTI::AttributeSetFactory::create( 2 ) );

  // Encode some values and add them to n attribute handle value pair set.
  SimpleHLAinteger32BE v1 = 2552;

  protox::io::byte_data_sink sink;
  sink.encode( v1 );

  ah_set->add( c1_t().get_attr_handle< A1 >(),
               sink.getDataBuffer(),
               (RTI::ULong) sink.getDataBufferSize() );

  sink.clear();
  SimpleHLAfloat32BE v2 = V2;
  sink.encode( v2 );

  ah_set->add( c1_t().get_attr_handle< A2 >(),
               sink.getDataBuffer(),
               (RTI::ULong) sink.getDataBufferSize() );

  obj_amb.reflect_object( 1, *ah_set,  "" );

  BOOST_CHECK( obj_amb.begin< c1_t >()->second.a_< A1 >() == 2552 );
  BOOST_CHECK( fabs( obj_amb.begin< c1_t >()->second.a_< A2 >() - V2 ) <= E );
}

/******************************************************************************/

} // test_protox_hla_o_class_type

/******************************************************************************/

#endif

/******************************************************************************/
