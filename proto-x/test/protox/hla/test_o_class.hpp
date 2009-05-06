/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef TEST_PROTOX_HLA_O_CLASS_HPP
#define TEST_PROTOX_HLA_O_CLASS_HPP

/**************************************************************************************************/

#include <RTI.hh>

#include <boost/mpl/size.hpp>
//#include <boost/mpl/at.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/int.hpp>

#include <protox/hla/o_class.hpp>
#include <protox/hla/keywords.hpp>
#include <protox/hla/attr.hpp>
#include <protox/hla/name.hpp>

/**************************************************************************************************/

namespace test_protox_hla_o_class {

/**************************************************************************************************/

namespace t1
{
  struct Class_A { HLA_NAME("Class_A") };
  struct c_type : protox::hla::o_class< Class_A > {};
}

BOOST_AUTO_TEST_CASE( test_o_class_empty )
{
  using namespace t1;

  BOOST_CHECK( c_type::name_type::name() == std::string("Class_A") );
  BOOST_CHECK( c_type::name_type::name() != std::string("Class_B") );
}

namespace t2
{
  using namespace protox::hla;

  // Class names
  struct Class_A { HLA_NAME("Class_A") };
  struct Class_B { HLA_NAME("Class_B") };
  struct Class_C { HLA_NAME("Class_C") };
  struct Class_D { HLA_NAME("Class_D") };

  // Structure
  struct c_type :
    o_class< Class_A,
               none,
               child< o_class< Class_B >,
                      o_class< Class_C >,
                      o_class< Class_D > > > {};


}

BOOST_AUTO_TEST_CASE( test_o_class_children )
{
  using namespace t2;
  using namespace boost;

  BOOST_CHECK( c_type::name_type::name() == std::string("Class_A") );

  // No attributes?
  BOOST_CHECK( mpl::size<c_type::attr_list_type>::value == 0 );

  // 3 child classes?
  BOOST_CHECK( mpl::size<c_type::child_list_type>::value == 3 );
}

namespace t3
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

  // Structure
  struct c_type :
    o_class< Class_A,
               none,
               child< o_class< Class_B,    // index 0
                                 none,
                                 child< o_class< Class_E >,
                                        o_class< Class_F >,
                                        o_class< Class_C > > >,
                      o_class< Class_C,    // index 1
                                 none,
                                 child< o_class< Class_A >,
                                        o_class< Class_C > > >,
                      o_class< Class_D,    // index 2
                                 none,
                                 child< o_class< Class_G >,
                                        o_class< Class_H > > > > > {};

}

BOOST_AUTO_TEST_CASE( test_o_class_nested_children )
{
  using namespace boost;
  using namespace t3;

  BOOST_CHECK( c_type::name_type::name() == std::string("Class_A") );

  // No attributes?
  BOOST_CHECK( mpl::size<c_type::attr_list_type>::value == 0 );

  // Class_A has 3 child classes?
  BOOST_CHECK( mpl::size<c_type::child_list_type>::value == 3 );

#if 0
  // Class_B has 3 child classes?
  typedef mpl::front< c_type::child_list_type >::type b_class_type;

  BOOST_CHECK( mpl::size< b_class_type::attr_list_type >::value == 0 );
  BOOST_CHECK( mpl::size< b_class_type::child_list_type >::value == 3 );

  // Class_C has 2 child classes?
  typedef mpl::at< c_type::child_list_type, mpl::int_<1> >::type c_class_type;
  BOOST_CHECK( mpl::size< c_class_type::attr_list_type >::value == 0 );
  BOOST_CHECK( mpl::size< c_class_type::child_list_type >::value == 2 );

  // Class_D has 2 child classes?
  typedef mpl::at< c_type::child_list_type, mpl::int_<2> >::type d_class_type;
  BOOST_CHECK( mpl::size< d_class_type::attr_list_type >::value == 0 );
  BOOST_CHECK( mpl::size< d_class_type::child_list_type >::value == 2 );
#endif
}

namespace t4
{
  using namespace protox;

  // Class name
  struct Class_A { HLA_NAME("Class_A") };

  // Attribute names
  struct A1 : protox::hla::attr< int > { HLA_NAME("A1") };
  struct A2 : protox::hla::attr< int > { HLA_NAME("A2") };

  struct c_type : hla::o_class< Class_A, hla::attrs< A1, A2 > > {};
}

BOOST_AUTO_TEST_CASE( test_o_class_children_with_attrs )
{
  using namespace t4;

  BOOST_CHECK( boost::mpl::size<c_type::attr_list_type>::value == 2 );

  //typedef mpl::at< c_type::attr_list_type, mpl::int_<0> >::type a1_type;
  //BOOST_CHECK( a1_type::name() == std::string("A1") );

  //typedef mpl::at< c_type::attr_list_type, mpl::int_<1> >::type a2_type;
  //BOOST_CHECK( a2_type::name() == std::string("A2") );
}

namespace t5
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

  // Structure
  struct som :
    o_class< Class_A,
               none,
               child< o_class< Class_B,    // index 0
                                 none,
                                 child< o_class< Class_E >,
                                        o_class< Class_F >,
                                        o_class< Class_C > > >,
                      o_class< Class_C,    // index 1
                                 none,
                                 child< o_class< Class_A >,
                                        o_class< Class_C > > >,
                      o_class< Class_D,    // index 2
                                 none,
                                 child< o_class< Class_G >,
                                        o_class< Class_H > > > > > {};
}

BOOST_AUTO_TEST_CASE( test_o_class_init_handle )
{
  using namespace t5;
  using namespace boost;

  RTI::RTIambassador rtiAmb;

  som::init_handles(rtiAmb);
}

/**************************************************************************************************/

} // namespace test_protox_hla_o_class

/**************************************************************************************************/

#endif

/**************************************************************************************************/
