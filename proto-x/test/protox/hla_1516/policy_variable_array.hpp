/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

#ifndef TEST_PROTOX_HLA_1516_VARIABLE_ARRAY_HPP
#define TEST_PROTOX_HLA_1516_VARIABLE_ARRAY_HPP

#include <math.h>
#include <vector>

#include <boost/mpl/vector.hpp>

#include <protox/codec/codecs.hpp>
#include <protox/dtl/unknown_static_size.hpp>

#include <protox/io/byte_data_sink.hpp>
#include <protox/io/byte_data_source.hpp>

#include <protox/hla_1516/variable_array.hpp>
#include <protox/hla_1516/basic_data_representation_table.hpp>


namespace test_protox_dtl_hla_1516_policy_variable_array
{
  using namespace boost;
  using namespace protox;
  using namespace protox::dtl;
  using namespace protox::hla_1516;

  BOOST_AUTO_TEST_CASE( tests_has_dynamic_size )
  {
    typedef hla_1516::variable_array< std::vector< HLAoctet > > A1;

    BOOST_CHECK( codec::static_size_in_bytes<A1>::value == protox::dtl::UNKNOWN_STATIC_SIZE::value );
  }

  BOOST_AUTO_TEST_CASE( test_octet_4 )
  {
    typedef hla_1516::variable_array< std::vector< HLAoctet > > A1;
    BOOST_CHECK( codec::octet_boundary< A1 >::value == 4 );
  }

  BOOST_AUTO_TEST_CASE( test_octet_8 )
  {
    typedef hla_1516::variable_array< std::vector< HLAfloat64BE > > A1;
    BOOST_CHECK( codec::octet_boundary< A1 >::value == 8 );
  }

  BOOST_AUTO_TEST_CASE( test_dynamic_size_empty )
  {
    typedef hla_1516::variable_array< std::vector< HLAfloat64BE > > A1;
    A1 a1;
    BOOST_CHECK( codec::dynamic_size(a1) == 4 );
  }

  BOOST_AUTO_TEST_CASE( test_dynamic_size_no_padding_after_header )
  {
    typedef hla_1516::variable_array< std::vector< HLAoctet > > A1;
    A1 a1;
    a1.push_back( 'a' );
    a1.push_back( 'b' );
    a1.push_back( 'c' );
    a1.push_back( 'd' );

    BOOST_CHECK( codec::dynamic_size(a1) == 8 );

    typedef hla_1516::variable_array< std::vector< HLAinteger32BE > > A2;
    A2 a2;
    a2.push_back( 1 );
    a2.push_back( 2 );
    a2.push_back( 3 );

    BOOST_CHECK( codec::dynamic_size(a2) == 16 );
  }

  BOOST_AUTO_TEST_CASE( test_dynamic_size_padding_after_header )
  {
    typedef hla_1516::variable_array< std::vector< HLAfloat64BE > > A1;
    A1 a1;
    a1.push_back( 1.0 );
    a1.push_back( 2.0 );

    BOOST_CHECK( codec::dynamic_size(a1) == (4 + 4 + (2 * 8)) );
  }

  BOOST_AUTO_TEST_CASE( test_dynamic_size_nested )
  {
    typedef hla_1516::variable_array< std::vector< HLAfloat64BE > > A1;
    typedef hla_1516::variable_array< std::vector< A1 > > A2;

    A2 a2;

    A1 a10;
    a10.push_back( 1.0 );
    a10.push_back( 2.0 );

    std::size_t const a10_size = (4 + 4 + (2*8));

    BOOST_CHECK( codec::dynamic_size(a10) == a10_size );

    a2.push_back( a10 );

    A1 a11;
    a11.push_back( 4.0 );
    a11.push_back( 5.0 );
    a11.push_back( 6.0 );

    std::size_t const a11_size = (4 + 4 + (3*8));
    BOOST_CHECK( codec::dynamic_size(a11) == a11_size );

    a2.push_back( a11 );

    BOOST_CHECK( codec::dynamic_size(a2) == (4 + 4 + a10_size + a11_size) );
  }

  namespace t1
  {
    struct f1 : protox::dtl::field< HLAfloat64BE > {};
    struct f2 : protox::dtl::field< HLAoctet > {};
  }

  BOOST_AUTO_TEST_CASE( test_dynamic_size_pad_between_elements_1 )
  {
    using namespace t1;

    typedef hla_1516::fixed_record< mpl::vector < f1, f2 > > R1;

    std::size_t const R1_size = codec::static_size_in_bytes<R1>::value;

    typedef hla_1516::variable_array< std::vector< R1 > > A1;
    A1 a1;

    a1.push_back( R1() );
    a1.push_back( R1() );
    a1.push_back( R1() );
    a1.push_back( R1() );

    int const pad_bytes = 7;
    BOOST_CHECK( codec::dynamic_size(a1) == (4 + 4 + (4*R1_size) + (3*pad_bytes)) );
  }

  namespace t2
  {
    struct f1 : protox::dtl::field< HLAfloat32BE > {};
    struct f2 : protox::dtl::field< HLAoctetPairBE > {};
  }

  BOOST_AUTO_TEST_CASE( test_dynamic_size_pad_between_elements_2 )
  {
    using namespace t2;

    typedef hla_1516::fixed_record< mpl::vector < f1, f2 > > R1;

    std::size_t const R1_size = codec::static_size_in_bytes<R1>::value;

    typedef hla_1516::variable_array< std::vector< R1 > > A1;
    A1 a1;

    a1.push_back( R1() );
    a1.push_back( R1() );
    a1.push_back( R1() );
    a1.push_back( R1() );

    int const pad_bytes = 2;
    BOOST_CHECK( codec::dynamic_size(a1) == (4 + (4*R1_size) + (3*pad_bytes)) );
  }

  BOOST_AUTO_TEST_CASE( test_codec_empty )
  {
    typedef hla_1516::variable_array< std::vector< HLAfloat64BE > > A1;
    A1 a10;
    BOOST_CHECK( codec::dynamic_size(a10) == 4 );

    protox::io::byte_data_sink sink;
    sink.encode( a10 );

    BOOST_CHECK( sink.size() == 4 );

    A1 a11;
    protox::io::byte_data_source source(sink);
    source.decode( a11 );

    BOOST_CHECK( a11.size() == 0 );
  }

  BOOST_AUTO_TEST_CASE( test_codec_no_padding )
  {
    typedef hla_1516::variable_array< std::vector< HLAoctet > > A1;
    A1 a10;

    a10.push_back( 'a' );
    a10.push_back( 'b' );
    a10.push_back( 'c' );
    a10.push_back( 'd' );
    a10.push_back( 'e' );

    protox::io::byte_data_sink sink;
    sink.encode( a10 );

    A1 a11;
    BOOST_CHECK( a11 != a10 );
    protox::io::byte_data_source source(sink);
    source.decode( a11 );

    BOOST_CHECK( a11.size() == 5 );
    BOOST_CHECK( a11[0] == 'a' );
    BOOST_CHECK( a11[1] == 'b' );
    BOOST_CHECK( a11[2] == 'c' );
    BOOST_CHECK( a11[3] == 'd' );
    BOOST_CHECK( a11[4] == 'e' );

    BOOST_CHECK( a11 == a10 );
  }

  BOOST_AUTO_TEST_CASE( test_codec_header_padding )
  {
    typedef hla_1516::variable_array< std::vector< HLAfloat64BE > > A1;
    A1 a10;

    a10.push_back( 1.0 );
    a10.push_back( 2.0 );
    a10.push_back( 3.0 );
    a10.push_back( 4.0 );
    a10.push_back( 5.0 );

    protox::io::byte_data_sink sink;
    sink.encode( a10 );

    A1 a11;
    BOOST_CHECK( a11 != a10 );
    protox::io::byte_data_source source(sink);
    source.decode( a11 );

    BOOST_CHECK( a11.size() == 5 );
    BOOST_CHECK( a11[0] == 1.0 );
    BOOST_CHECK( a11[1] == 2.0 );
    BOOST_CHECK( a11[2] == 3.0 );
    BOOST_CHECK( a11[3] == 4.0 );
    BOOST_CHECK( a11[4] == 5.0 );

    BOOST_CHECK( a11 == a10 );
  }

  BOOST_AUTO_TEST_CASE( test_codec_no_header_padding )
  {
    typedef hla_1516::variable_array< std::vector< HLAinteger32BE > > A1;
    A1 a10;

    a10.push_back( 1 );
    a10.push_back( 2 );
    a10.push_back( 3 );
    a10.push_back( 4 );
    a10.push_back( 5 );

    protox::io::byte_data_sink sink;
    sink.encode( a10 );

    A1 a11;
    BOOST_CHECK( a11 != a10 );
    protox::io::byte_data_source source(sink);
    source.decode( a11 );

    BOOST_CHECK( a11.size() == 5 );
    BOOST_CHECK( a11[0] == 1 );
    BOOST_CHECK( a11[1] == 2 );
    BOOST_CHECK( a11[2] == 3 );
    BOOST_CHECK( a11[3] == 4 );
    BOOST_CHECK( a11[4] == 5 );

    BOOST_CHECK( a11 == a10 );
  }

  namespace t3
  {
    struct f1 : protox::dtl::field< HLAfloat64BE > {};
    struct f2 : protox::dtl::field< HLAoctet > {};
  }

  BOOST_AUTO_TEST_CASE( test_codec_pad_between_elements_1 )
  {
    using namespace t3;

    typedef hla_1516::fixed_record< mpl::vector < f1, f2 > > R1;
    typedef hla_1516::variable_array< std::vector< R1 > > A1;

    A1 a10;

    unsigned i;
    for( i = 0; i < 4; ++i )
    {
      R1 r;
      r.f_<f1>() = 2.5 * (i + 1);
      r.f_<f2>() = 'e' + i;

      a10.push_back(r);
    }

    BOOST_CHECK( a10.size() == 4 );

    protox::io::byte_data_sink sink;
    sink.encode( a10 );

    A1 a11;
    BOOST_CHECK( a11 != a10 );

    protox::io::byte_data_source source(sink);
    source.decode( a11 );

    BOOST_CHECK( a11 == a10 );

    BOOST_CHECK( a11.size() == 4 );

    for( i = 0; i < a11.size(); ++i )
    {
      BOOST_CHECK( a11[i].f_<f1>() == (2.5 * (i + 1)) );
      BOOST_CHECK( a11[i].f_<f2>() == ('e' + i) );
    }
  }
}

#endif
