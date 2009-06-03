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
#include <boost/mpl/vector.hpp>

#include <protox/dtl/simple.hpp>
#include <protox/hla_1516/basic_data_representation_table.hpp>
#include <protox/hla_1516/fixed_record.hpp>

#include <protox/hla/o_class.hpp>
#include <protox/hla/o_class_type.hpp>
#include <protox/hla/keywords.hpp>
#include <protox/hla/attr.hpp>
#include <protox/hla/name.hpp>
#include <protox/hla/som.hpp>

/******************************************************************************/

namespace test_protox_hla_o_class_type {

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

BOOST_AUTO_TEST_CASE( test_o_class_type_definition )
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

  RTI::RTIambassador rti_amb;  
  rti_amb.o_class_to_handle_map[ "Class_A"                 ] =  1;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_B"         ] =  2;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_B.Class_E" ] =  3;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_B.Class_F" ] =  4;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_B.Class_C" ] =  5;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_C"         ] =  6;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_C.Class_A" ] =  7;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_C.Class_C" ] =  8;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_D"         ] =  9;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_D.Class_G" ] = 10;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_D.Class_H" ] = 11;
  som::init_handles( rti_amb );

  typedef o_class_type< som, q_name< Class_C, Class_A, Class_E > >::type
    class_type;

  class_type eObj;

  BOOST_CHECK( eObj.get_attr_handle< A1 >() > 0 );
  BOOST_CHECK( eObj.get_attr_handle< A2 >() > 0 );
  BOOST_CHECK( eObj.get_attr_handle< A3 >() > 0 );
}

BOOST_AUTO_TEST_CASE( test_o_class_type_attr_mutators )
{
  typedef protox::hla::som< o_class_table > som;

  RTI::RTIambassador rti_amb;

  rti_amb.o_class_to_handle_map[ "Class_A"                 ] =  1;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_B"         ] =  2;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_B.Class_E" ] =  3;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_B.Class_F" ] =  4;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_B.Class_C" ] =  5;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_C"         ] =  6;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_C.Class_A" ] =  7;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_C.Class_C" ] =  8;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_D"         ] =  9;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_D.Class_G" ] = 10;
  rti_amb.o_class_to_handle_map[ "Class_A.Class_D.Class_H" ] = 11;

  som::init_handles( rti_amb );

  typedef o_class_type< som, q_name< Class_C, Class_A, Class_E > >::type
    class_type;

  class_type eObj;

  eObj.a_< A1 >() = 5;
  BOOST_CHECK( eObj.a_< A1 >() == 5 );

  eObj.a_< A2 >() = 3.145f;
  BOOST_CHECK( (eObj.a_< A2 >() - 3.145f) < 0.00001f );

  eObj.a_< A3 >().f_< f1 >() = 'a';
  eObj.a_< A3 >().f_< f2 >() = 'm';
  eObj.a_< A3 >().f_< f3 >() = 'z';

  BOOST_CHECK( eObj.a_< A3 >().f_< f1 >() == 'a' );
  BOOST_CHECK( eObj.a_< A3 >().f_< f2 >() == 'm' );
  BOOST_CHECK( eObj.a_< A3 >().f_< f3 >() == 'z' );
}

BOOST_AUTO_TEST_CASE( test_o_class_type_publish_all )
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
  c1::publish( rti_amb );
  
  typedef o_class_type< som, q_name< Class_B > >::type c2;
  c2::publish( rti_amb );
}

BOOST_AUTO_TEST_CASE( test_o_class_type_publish_subset )
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
  c1::publish( rti_amb, "A1.A3" );
  
  typedef o_class_type< som, q_name< Class_B > >::type c2;
  
  BOOST_CHECK_THROW( c2::publish( rti_amb, "A7.A2.A4" ),
                     RTI::AttributeNotDefined );
}

BOOST_AUTO_TEST_CASE( test_o_class_type_unpublish )
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
  c1::publish( rti_amb );

  c1::unpublish( rti_amb );
}

/******************************************************************************/

} // test_protox_hla_o_class_type

/******************************************************************************/

#endif

/******************************************************************************/
