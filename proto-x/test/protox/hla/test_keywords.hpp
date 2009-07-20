/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef TEST_PROTOX_HLA_KEYWORDS_HPP
#define TEST_PROTOX_HLA_KEYWORDS_HPP

/******************************************************************************/

#include <boost/mpl/size.hpp>
#include <boost/mpl/vector.hpp>
#include <protox/hla/keywords.hpp>

/******************************************************************************/

namespace test_protox_hla_keywords {

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_attrs_keyword )
{
  typedef protox::hla::attrs<> a0;
  typedef protox::hla::attrs< int > a1;
  typedef protox::hla::attrs< int, float > a2;
  typedef protox::hla::attrs< int, float, double > a3;
  typedef protox::hla::attrs< int, float, double, char > a4;

  BOOST_CHECK( boost::mpl::size<a0>::value == 0 );
  BOOST_CHECK( boost::mpl::size<a1>::value == 1 );
  BOOST_CHECK( boost::mpl::size<a2>::value == 2 );
  BOOST_CHECK( boost::mpl::size<a3>::value == 3 );
  BOOST_CHECK( boost::mpl::size<a4>::value == 4 );
}

BOOST_AUTO_TEST_CASE( test_params_keyword )
{
  typedef protox::hla::params<> p0;
  typedef protox::hla::params< int > p1;
  typedef protox::hla::params< int, float > p2;
  typedef protox::hla::params< int, float, double > p3;
  typedef protox::hla::params< int, float, double, char > p4;

  BOOST_CHECK( boost::mpl::size<p0>::value == 0 );
  BOOST_CHECK( boost::mpl::size<p1>::value == 1 );
  BOOST_CHECK( boost::mpl::size<p2>::value == 2 );
  BOOST_CHECK( boost::mpl::size<p3>::value == 3 );
  BOOST_CHECK( boost::mpl::size<p4>::value == 4 );
}

BOOST_AUTO_TEST_CASE( test_child_keyword )
{
  typedef protox::hla::child<> c0;
  typedef protox::hla::child< int > c1;
  typedef protox::hla::child< int, float > c2;
  typedef protox::hla::child< int, float, double > c3;
  typedef protox::hla::child< int, float, double, char > c4;

  BOOST_CHECK( boost::mpl::size<c0>::value == 0 );
  BOOST_CHECK( boost::mpl::size<c1>::value == 1 );
  BOOST_CHECK( boost::mpl::size<c2>::value == 2 );
  BOOST_CHECK( boost::mpl::size<c3>::value == 3 );
  BOOST_CHECK( boost::mpl::size<c4>::value == 4 );
}

BOOST_AUTO_TEST_CASE( test_q_name_keyword )
{
  typedef protox::hla::q_name<> q0;
  typedef protox::hla::q_name< int > q1;
  typedef protox::hla::q_name< int, float > q2;
  typedef protox::hla::q_name< int, float, double > q3;
  typedef protox::hla::q_name< int, float, double, char > q4;

  BOOST_CHECK( boost::mpl::size<q0>::value == 0 );
  BOOST_CHECK( boost::mpl::size<q1>::value == 1 );
  BOOST_CHECK( boost::mpl::size<q2>::value == 2 );
  BOOST_CHECK( boost::mpl::size<q3>::value == 3 );
  BOOST_CHECK( boost::mpl::size<q4>::value == 4 );
}

/******************************************************************************/

}

/******************************************************************************/

#endif

/******************************************************************************/
