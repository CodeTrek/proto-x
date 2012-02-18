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

#include <protox/hla/som.hpp>
#include <protox/hla/o_class_type.hpp>

#include <boost/mpl/vector.hpp>

#include <test/protox/hla/som/s004/obj_class_table.hpp>

/******************************************************************************/

namespace test_protox_hla_o_class_type {

/******************************************************************************/

using namespace protox::hla;
using namespace som_s004;

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_o_class_type_definition )
{
  //using namespace som_s004;

  typedef protox::hla::som< obj_class_table > som;

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
  //using namespace som_s004;

  typedef protox::hla::som< obj_class_table > som;

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

#include <boost/type_traits/is_base_of.hpp>

BOOST_AUTO_TEST_CASE( test_o_class_type_attr_mutators )
{
  //using namespace som_s004;
  using namespace som_s004::R1;

  typedef protox::hla::som< obj_class_table > som;

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

  typedef o_class_type<
    som,
    q_name< Class_C,
            Class_A,
            Class_E >
  >::type class_type;

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

BOOST_AUTO_TEST_CASE( test_o_class_type_inheritance )
{
  //using namespace som_s004;
  using namespace som_s004::R1;

  typedef protox::hla::som< obj_class_table > som;

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

  typedef o_class_type<
    som,
    q_name< Class_C >
  >::type c_class_type;

  typedef o_class_type<
    som,
    q_name< Class_C,
            Class_A >
  >::type ca_class_type;

  typedef o_class_type<
    som,
    q_name< Class_C,
            Class_C >
  >::type cc_class_type;

  typedef o_class_type<
    som,
    q_name< Class_C,
            Class_A,
            Class_E >
  >::type cae_class_type;

  BOOST_STATIC_ASSERT(( boost::is_base_of< c_class_type, ca_class_type >::value == true ));
  BOOST_STATIC_ASSERT(( boost::is_base_of< c_class_type, cc_class_type >::value == true ));
  BOOST_STATIC_ASSERT(( boost::is_base_of< c_class_type, cae_class_type >::value == true ));
  BOOST_STATIC_ASSERT(( boost::is_base_of< ca_class_type, cae_class_type >::value == true ));

  cae_class_type cae_obj;
  ca_class_type &ca_obj = cae_obj;
  c_class_type &c_obj = cae_obj;

  cae_obj.a_< A3 >().f_< f1 >() = 'a';

  BOOST_CHECK( ca_obj.a_< A3 >().f_< f1 >() == cae_obj.a_< A3 >().f_< f1 >() );
  BOOST_CHECK( c_obj.a_< A3 >().f_< f1 >() == cae_obj.a_< A3 >().f_< f1 >() );

  cae_obj.a_< A3 >().f_< f2 >() = 'z';

  BOOST_CHECK( ca_obj.a_< A3 >().f_< f2 >() != 'b' );
  BOOST_CHECK( c_obj.a_< A3 >().f_< f2 >() != 'b' );

  BOOST_CHECK( ca_obj.a_< A3 >().f_< f2 >() == 'z' );
  BOOST_CHECK( c_obj.a_< A3 >().f_< f2 >() == 'z' );
}

BOOST_AUTO_TEST_CASE( test_o_class_type_publish_all )
{
  //using namespace som_s004;

  typedef protox::hla::som< obj_class_table > som;

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
  //using namespace som_s004;

  typedef protox::hla::som< obj_class_table > som;

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
  //using namespace som_s004;

  typedef protox::hla::som< obj_class_table > som;

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
