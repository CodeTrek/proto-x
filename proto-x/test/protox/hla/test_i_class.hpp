/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef TEST_PROTOX_HLA_I_CLASS_HPP
#define TEST_PROTOX_HLA_I_CLASS_HPP

/******************************************************************************/

#include <RTI.hh>

#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/int.hpp>

#include <protox/hla/i_class.hpp>
#include <protox/hla/keywords.hpp>
#include <protox/hla/param.hpp>
#include <protox/hla/name.hpp>

#include <test/protox/hla/som/s005/inter_class_table.hpp>
#include <test/protox/hla/som/s006/inter_class_table.hpp>
#include <test/protox/hla/som/s007/inter_class_table.hpp>

/******************************************************************************/

namespace test_protox_hla_i_class {

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_i_class_empty )
{
  using namespace som_s005;

  BOOST_CHECK( inter_class_table::name_type::name() == std::string( "Class_A" ) );
  BOOST_CHECK( inter_class_table::name_type::name() != std::string( "Class_B" ) );
}

BOOST_AUTO_TEST_CASE( test_i_class_children )
{
  using namespace som_s006;
  using namespace boost;

  BOOST_CHECK( inter_class_table::name_type::name() == std::string("Class_A") );

  // No parameters?
  BOOST_CHECK( mpl::size<inter_class_table::param_list_type>::value == 0 );

  // 3 child classes?
  BOOST_CHECK( mpl::size<inter_class_table::child_list_type>::value == 3 );
}

BOOST_AUTO_TEST_CASE( test_i_class_nested_children )
{
  using namespace boost;
  using namespace som_s007;

  BOOST_CHECK( inter_class_table::name_type::name() == std::string("Class_A") );

  // No parameters?
  BOOST_CHECK( mpl::size<inter_class_table::param_list_type>::value == 0 );

  // Class_A has 3 child classes?
  BOOST_CHECK( mpl::size<inter_class_table::child_list_type>::value == 3 );

#if 0
  // Class_B has 3 child classes?
  typedef mpl::front< c_type::child_list_type >::type b_class_type;

  BOOST_CHECK( mpl::size< b_class_type::param_list_type >::value == 0 );
  BOOST_CHECK( mpl::size< b_class_type::child_list_type >::value == 3 );

  // Class_C has 2 child classes?
  typedef mpl::at< c_type::child_list_type, mpl::int_<1> >::type c_class_type;
  BOOST_CHECK( mpl::size< c_class_type::param_list_type >::value == 0 );
  BOOST_CHECK( mpl::size< c_class_type::child_list_type >::value == 2 );

  // Class_D has 2 child classes?
  typedef mpl::at< c_type::child_list_type, mpl::int_<2> >::type d_class_type;
  BOOST_CHECK( mpl::size< d_class_type::param_list_type >::value == 0 );
  BOOST_CHECK( mpl::size< d_class_type::child_list_type >::value == 2 );
#endif
}

namespace t4
{
  using namespace protox;

  // Class name
  struct Class_A { HLA_NAME("Class_A") };

  // Parameter names
  struct A1 : protox::hla::param< int > { HLA_NAME("A1") };
  struct A2 : protox::hla::param< int > { HLA_NAME("A2") };

  struct c_type : hla::i_class< Class_A, hla::params< A1, A2 > > {};
}

BOOST_AUTO_TEST_CASE( test_i_class_children_with_params )
{
  using namespace t4;

  BOOST_CHECK( boost::mpl::size<c_type::param_list_type>::value == 2 );

  //typedef mpl::at< c_type::param_list_type, mpl::int_<0> >::type a1_type;
  //BOOST_CHECK( a1_type::name() == std::string("A1") );

  //typedef mpl::at< c_type::param_list_type, mpl::int_<1> >::type a2_type;
  //BOOST_CHECK( a2_type::name() == std::string("A2") );
}

/**************************************************************************************************/

} // namespace test_protox_hla_i_class

/**************************************************************************************************/

#endif

/**************************************************************************************************/
