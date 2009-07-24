/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef TEST_PROTOX_HLA_O_CLASS_HPP
#define TEST_PROTOX_HLA_O_CLASS_HPP

/******************************************************************************/

#include <boost/mpl/size.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>

#include <protox/hla/o_class.hpp>
#include <protox/hla/keywords.hpp>
#include <protox/hla/attr.hpp>
#include <protox/hla/name.hpp>

#include <test/protox/hla/som/s000/obj_class_table.hpp>
#include <test/protox/hla/som/s001/obj_class_table.hpp>
#include <test/protox/hla/som/s002/obj_class_table.hpp>
#include <test/protox/hla/som/s003/obj_class_table.hpp>

/******************************************************************************/

namespace test_protox_hla_o_class {

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_o_class_empty )
{
  using namespace som::s001;

  BOOST_CHECK( obj_class_table::name_type::name() == std::string( "Class_A" ) );
  BOOST_CHECK( obj_class_table::name_type::name() != std::string( "Class_B" ) );
}

BOOST_AUTO_TEST_CASE( test_o_class_children )
{
  using namespace boost;
  using namespace som::s000;

  BOOST_CHECK( obj_class_table::name_type::name() == std::string( "Class_A" ) );

  // No attributes?
  BOOST_CHECK( mpl::size< obj_class_table::attr_list_type >::value == 0 );

  // 3 child classes?
  BOOST_CHECK( mpl::size< obj_class_table::child_list_type >::value == 3 );
}

template< typename T >
static void verify_class()
{
  using namespace boost;

  if( T::name_type::name() == std::string( "Class_B" ) )
  {
    BOOST_CHECK( mpl::size< typename T::attr_list_type >::value == 0 );
    BOOST_CHECK( mpl::size< typename T::child_list_type >::value == 3 );
  }
  else if( T::name_type::name() == std::string( "Class_C" ) )
  {
    BOOST_CHECK( mpl::size< typename T::attr_list_type >::value == 0 );
    BOOST_CHECK( mpl::size< typename T::child_list_type >::value == 2 );
  }
  else if( T::name_type::name() == std::string( "Class_D" ) )
  {
    BOOST_CHECK( mpl::size< typename T::attr_list_type >::value == 0 );
    BOOST_CHECK( mpl::size< typename T::child_list_type >::value == 2 );
  }
}

BOOST_AUTO_TEST_CASE( test_o_class_nested_children )
{
  using namespace som::s002;
  using namespace boost;

  BOOST_CHECK( obj_class_table::name_type::name() == std::string( "Class_A" ) );

  // No attributes?
  BOOST_CHECK( mpl::size<obj_class_table::attr_list_type>::value == 0 );

  // Class_A has 3 child classes?
  BOOST_CHECK( mpl::size<obj_class_table::child_list_type>::value == 3 );

  typedef mpl::deref< mpl::begin< obj_class_table::child_list_type >::type >::type class_1_type;
  typedef mpl::deref< mpl::next< mpl::begin< obj_class_table::child_list_type >::type >::type >::type class_2_type;
  typedef mpl::deref< mpl::next< mpl::next< mpl::begin< obj_class_table::child_list_type >::type >::type >::type >::type class_3_type;

  verify_class< class_1_type >();
  verify_class< class_2_type >();
  verify_class< class_3_type >();
}

BOOST_AUTO_TEST_CASE( test_o_class_children_with_attrs )
{
  using namespace boost;
  using namespace som::s003;

  BOOST_CHECK( mpl::size< obj_class_table::attr_list_type >::value == 2 );
}

/******************************************************************************/

}

/******************************************************************************/

#endif

/******************************************************************************/
