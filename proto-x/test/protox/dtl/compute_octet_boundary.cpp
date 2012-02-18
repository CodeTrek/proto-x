/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#define BOOST_AUTO_TEST_MAIN

#include <boost/test/included/unit_test_framework.hpp>
#include <boost/test/auto_unit_test.hpp>

/******************************************************************************/

#include <protox/dtl/compute_octet_boundary.hpp>

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_1bit )
{
  BOOST_CHECK( protox::dtl::compute_octet_boundary< 1 >::type::value == 1 );
}

BOOST_AUTO_TEST_CASE( test_7bits )
{
  BOOST_CHECK( protox::dtl::compute_octet_boundary< 7 >::type::value == 1 );
}

BOOST_AUTO_TEST_CASE( test_8bits )
{
  BOOST_CHECK( protox::dtl::compute_octet_boundary< 8 >::type::value == 1 );
}

BOOST_AUTO_TEST_CASE( test_9bits )
{
  BOOST_CHECK( protox::dtl::compute_octet_boundary< 9 >::type::value == 2 );
}

BOOST_AUTO_TEST_CASE( test_15bits )
{
  BOOST_CHECK( protox::dtl::compute_octet_boundary< 15 >::type::value == 2 );
}

BOOST_AUTO_TEST_CASE( test_16bits )
{
  BOOST_CHECK( protox::dtl::compute_octet_boundary< 16 >::type::value == 2 );
}

BOOST_AUTO_TEST_CASE( test_17bits )
{
  BOOST_CHECK( protox::dtl::compute_octet_boundary< 17 >::type::value == 4 );
}

BOOST_AUTO_TEST_CASE( test_24bits )
{
  BOOST_CHECK( protox::dtl::compute_octet_boundary< 24 >::type::value == 4 );
}

BOOST_AUTO_TEST_CASE( test_31bits )
{
  BOOST_CHECK( protox::dtl::compute_octet_boundary< 31 >::type::value == 4 );
}

BOOST_AUTO_TEST_CASE( test_32bits )
{
  BOOST_CHECK( protox::dtl::compute_octet_boundary< 32 >::type::value == 4 );
}

BOOST_AUTO_TEST_CASE( test_33bits )
{
  BOOST_CHECK( protox::dtl::compute_octet_boundary< 33 >::type::value == 8 );
}

BOOST_AUTO_TEST_CASE( test_63bits )
{
  BOOST_CHECK( protox::dtl::compute_octet_boundary< 63 >::type::value == 8 );
}

BOOST_AUTO_TEST_CASE( test_64bits )
{
  BOOST_CHECK( protox::dtl::compute_octet_boundary< 64 >::type::value == 8 );
}

BOOST_AUTO_TEST_CASE( test_658bits )
{
  BOOST_CHECK( protox::dtl::compute_octet_boundary< 65 >::type::value == 16 );
}

BOOST_AUTO_TEST_CASE( test_127bits )
{
  BOOST_CHECK( protox::dtl::compute_octet_boundary< 127 >::type::value == 16 );
}

BOOST_AUTO_TEST_CASE( test_128bits )
{
  BOOST_CHECK( protox::dtl::compute_octet_boundary< 128 >::type::value == 16 );
}



