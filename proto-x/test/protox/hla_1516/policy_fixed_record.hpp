/*
    Copyright 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

#ifndef TEST_PROTOX_HLA_1516_FIXED_RECORD_HPP
#define TEST_PROTOX_HLA_1516_FIXED_RECORD_HPP

#include <math.h>

#include <boost/mpl/vector.hpp>

#include "protox/dtl/codec.hpp"
#include "protox/dtl/simple.hpp"

#include <protox/io/byte_data_sink.hpp>
#include <protox/io/byte_data_source.hpp>

#include <protox/hla_1516/basic_data_representation_table.hpp>
#include <protox/hla_1516/fixed_record.hpp>

namespace test_protox_dtl_hla_1516_codec_fixed_record
{
  using namespace boost;
  using namespace protox;
  using namespace protox::dtl;
  using namespace protox::hla_1516;

  namespace t1
  {
    struct SimpleHLAoctet : simple< HLAoctet > {};

    struct f1 : protox::dtl::field< SimpleHLAoctet > {};
    struct f2 : protox::dtl::field< SimpleHLAoctet > {};
    struct f3 : protox::dtl::field< SimpleHLAoctet > {};

    typedef hla_1516::fixed_record< mpl::vector < f1, f2, f3 > > R1;
  }

  BOOST_AUTO_TEST_CASE( test_static_size_3_no_padding )
  {
    BOOST_CHECK( codec::static_size_in_bytes< t1::R1 >::value == 3 );
  }

  namespace t2
  {
    struct f1 : protox::dtl::field< HLAfloat32LE > {};
    struct f2 : protox::dtl::field< HLAoctet > {};
    struct f3 : protox::dtl::field< HLAoctet > {};
    struct f4 : protox::dtl::field< HLAoctet > {};
  }

  BOOST_AUTO_TEST_CASE( test_static_size_7_no_padding )
  {
    typedef hla_1516::fixed_record< mpl::vector < t2::f1, t2::f2, t2::f3, t2::f4 > > R1;
    BOOST_CHECK( codec::static_size_in_bytes< R1 >::value == 7 );
  }

  namespace t3
  {
    struct f1 : protox::dtl::field< HLAfloat64LE > {};
    struct f2 : protox::dtl::field< HLAfloat64BE > {};
    struct f3 : protox::dtl::field< HLAoctet > {};
    struct f4 : protox::dtl::field< HLAoctet > {};
    struct f5 : protox::dtl::field< HLAoctet > {};
  }

  BOOST_AUTO_TEST_CASE( test_static_size_19_no_padding )
  {
    typedef hla_1516::fixed_record< mpl::vector < t3::f1, t3::f2, t3::f3, t3::f4, t3::f5 > > R1;
    BOOST_CHECK( codec::static_size_in_bytes< R1 >::value == 19 );
  }

  namespace t4
  {
    struct f1 : protox::dtl::field< HLAoctet > {};
    // 3 pad bytes
    struct f2 : protox::dtl::field< HLAfloat32LE > {};
  }

  BOOST_AUTO_TEST_CASE( test_static_size_8_with_padding )
  {
    typedef hla_1516::fixed_record< mpl::vector < t4::f1, t4::f2 > > R1;
    BOOST_CHECK( codec::static_size_in_bytes< R1 >::value == 8 );
  }

  namespace t5
  {
    struct f1 : protox::dtl::field< HLAoctet > {};
    // 3 pad bytes
    struct f2 : protox::dtl::field< HLAfloat32LE > {};
    // 0 bad bytes
    struct f3 : protox::dtl::field< HLAfloat64LE > {};
  }

  BOOST_AUTO_TEST_CASE( test_static_size_16_with_padding )
  {
    typedef hla_1516::fixed_record< mpl::vector < t5::f1, t5::f2, t5::f3 > > R1;
    BOOST_CHECK( codec::static_size_in_bytes< R1 >::value == 16 );
  }

  namespace t6
  {
    struct f1 : protox::dtl::field< HLAoctet > {};
    // 3 pad bytes
    struct f2 : protox::dtl::field< HLAfloat32LE > {};
    struct f3 : protox::dtl::field< HLAoctet > {};
    // 7 pad bytes
    struct f4 : protox::dtl::field< HLAfloat64LE > {};
  }

  BOOST_AUTO_TEST_CASE( test_static_size_20_with_padding )
  {
    typedef hla_1516::fixed_record< mpl::vector < t6::f1, t6::f2, t6::f3, t6::f4 > > R1;
    BOOST_CHECK( codec::static_size_in_bytes< R1 >::value == 24 );
  }

  namespace t7
  {
    struct f1 : protox::dtl::field< HLAoctet > {};
    struct f2 : protox::dtl::field< HLAoctet > {};
    struct f3 : protox::dtl::field< HLAoctet > {};
  }

  BOOST_AUTO_TEST_CASE( test_octet_1 )
  {
    typedef hla_1516::fixed_record< mpl::vector < t7::f1, t7::f2, t7::f3 > > R1;
    BOOST_CHECK( codec::octet_boundary< R1 >::value == 1 );
  }

  namespace t8
  {
    struct f1 : protox::dtl::field< HLAoctet > {};
    struct f2 : protox::dtl::field< HLAoctetPairBE > {};
    struct f3 : protox::dtl::field< HLAoctet > {};
  }

  BOOST_AUTO_TEST_CASE( test_octet_2 )
  {
    typedef hla_1516::fixed_record< mpl::vector < t8::f1, t8::f2, t8::f3 > > R1;
    BOOST_CHECK( codec::octet_boundary< R1 >::value == 2 );
  }

  namespace t9
  {
    struct f1 : protox::dtl::field< HLAoctet > {};
    struct f2 : protox::dtl::field< HLAinteger32BE > {};
    struct f3 : protox::dtl::field< HLAoctet > {};
  }

  BOOST_AUTO_TEST_CASE( test_octet_4 )
  {
    typedef hla_1516::fixed_record< mpl::vector < t9::f1, t9::f2, t9::f3 > > R1;
    BOOST_CHECK( codec::octet_boundary< R1 >::value == 4 );
  }

  namespace t10
  {
    struct SimpleHLAoctet : simple< HLAoctet > {};
    struct SimpleHLAinteger64BE : simple< HLAinteger64BE > {};

    struct f1 : protox::dtl::field< SimpleHLAoctet > {};
    struct f2 : protox::dtl::field< SimpleHLAinteger64BE > {};
    struct f3 : protox::dtl::field< SimpleHLAoctet > {};
  }

  BOOST_AUTO_TEST_CASE( test_octet_8 )
  {
    typedef hla_1516::fixed_record< mpl::vector < t10::f1, t10::f2, t10::f3 > > R1;
    BOOST_CHECK( codec::octet_boundary< R1 >::value == 8 );
  }

  namespace t11
  {
    struct f1 : protox::dtl::field< HLAoctet > {};
    struct f2 : protox::dtl::field< HLAoctet > {};
    struct f3 : protox::dtl::field< HLAoctet > {};

    typedef hla_1516::fixed_record< mpl::vector < f1, f2, f3 > > R1;

    struct f4 : protox::dtl::field< R1 > {};
    struct f5 : protox::dtl::field< R1 > {};
  }

  BOOST_AUTO_TEST_CASE( test_static_size_6_no_padding_nested )
  {
    typedef hla_1516::fixed_record< mpl::vector < t11::f4, t11::f5 > > R2;

    BOOST_CHECK( codec::static_size_in_bytes< R2 >::value == 6 );
  }

  namespace t12
  {
    struct f1 : protox::dtl::field< HLAinteger16BE > {};
    struct f2 : protox::dtl::field< HLAinteger16BE > {};
    struct f3 : protox::dtl::field< HLAinteger16BE > {};
    struct f4 : protox::dtl::field< HLAinteger16BE > {};

    typedef hla_1516::fixed_record< mpl::vector < f1, f2, f3, f4 > > R1;

    struct f5 : protox::dtl::field< HLAfloat64LE > {};
    struct f6 : protox::dtl::field< HLAfloat64LE > {};

    typedef hla_1516::fixed_record< mpl::vector < f5, f6 > > R2;

    struct f7 : protox::dtl::field< R1 > {};
    struct f8 : protox::dtl::field< R2 > {};
  }

  BOOST_AUTO_TEST_CASE( test_static_size_24_no_padding_nested )
  {
    typedef hla_1516::fixed_record< mpl::vector < t12::f7, t12::f8 > > R3;
    BOOST_CHECK( codec::static_size_in_bytes< R3 >::value == 24 );
  }

  namespace t13
  {
    struct f1 : protox::dtl::field< HLAinteger16BE > {};
    struct f2 : protox::dtl::field< HLAoctet > {};
    struct f3 : protox::dtl::field< HLAinteger16BE > {};
    struct f4 : protox::dtl::field< HLAinteger16BE > {};
    typedef hla_1516::fixed_record< mpl::vector < f1, f2, f3, f4 > > R1;

    struct f5 : protox::dtl::field< HLAoctet > {};
    struct f6 : protox::dtl::field< HLAfloat64LE > {};
    typedef hla_1516::fixed_record< mpl::vector < f5, f6 > > R2;

    struct f7 : protox::dtl::field< R1 > {};
    struct f8 : protox::dtl::field< R2 > {};
  }

  BOOST_AUTO_TEST_CASE( test_static_size_24_padding_nested )
  {
    typedef hla_1516::fixed_record< mpl::vector < t13::f7, t13::f8 > > R3;
    BOOST_CHECK( codec::static_size_in_bytes< R3 >::value == 24 );
  }

  namespace t14
  {
    struct f1 : protox::dtl::field< HLAoctet > {};
    struct f2 : protox::dtl::field< HLAoctet > {};
    struct f3 : protox::dtl::field< HLAoctet > {};

    typedef hla_1516::fixed_record< mpl::vector < f1, f2, f3 > > R1;

    struct f4 : protox::dtl::field< R1 > {};
    struct f5 : protox::dtl::field< R1 > {};

    typedef hla_1516::fixed_record< mpl::vector < f4, f5 > > R2;
  }

  BOOST_AUTO_TEST_CASE( test_octet_1_nested )
  {
    BOOST_CHECK( codec::octet_boundary< t14::R2 >::value == 1 );
  }

  namespace t15
  {
    struct f1 : protox::dtl::field< HLAoctet > {};
    struct f2 : protox::dtl::field< HLAoctetPairLE > {};
    struct f3 : protox::dtl::field< HLAoctet > {};

    typedef hla_1516::fixed_record< mpl::vector < f1, f2, f3 > > R1;

    struct f4 : protox::dtl::field< R1 > {};
    struct f5 : protox::dtl::field< R1 > {};

    typedef hla_1516::fixed_record< mpl::vector < f4, f5 > > R2;
  }

  BOOST_AUTO_TEST_CASE( test_octet_2_nested )
  {
    BOOST_CHECK( codec::octet_boundary< t15::R2 >::value == 2 );
  }

  namespace t16
  {
    struct f1 : protox::dtl::field< HLAinteger16BE > {};
    struct f2 : protox::dtl::field< HLAoctet > {};
    struct f3 : protox::dtl::field< HLAinteger16BE > {};
    struct f4 : protox::dtl::field< HLAinteger32BE > {};
    typedef hla_1516::fixed_record< mpl::vector < f1, f2, f3, f4 > > R1;

    struct f5 : protox::dtl::field< HLAoctet > {};
    struct f6 : protox::dtl::field< HLAoctetPairLE > {};
    typedef hla_1516::fixed_record< mpl::vector < f5, f6 > > R2;

    struct f7 : protox::dtl::field< R1 > {};
    struct f8 : protox::dtl::field< R2 > {};

    typedef hla_1516::fixed_record< mpl::vector < f7, f8 > > R3;
  }

  BOOST_AUTO_TEST_CASE( test_octet_4_nested )
  {
    BOOST_CHECK( codec::octet_boundary< t16::R3 >::value == 4 );
  }

  namespace t17
  {
    struct f1 : protox::dtl::field< HLAfloat64LE > {};
    struct f2 : protox::dtl::field< HLAoctet > {};
    struct f3 : protox::dtl::field< HLAinteger16BE > {};
    struct f4 : protox::dtl::field< HLAinteger32BE > {};
    typedef hla_1516::fixed_record< mpl::vector < f1, f2, f3, f4 > > R1;

    struct f5 : protox::dtl::field< HLAoctet > {};
    struct f6 : protox::dtl::field< HLAoctetPairLE > {};
    typedef hla_1516::fixed_record< mpl::vector < f5, f6 > > R2;

    struct f7 : protox::dtl::field< R1 > {};
    struct f8 : protox::dtl::field< R2 > {};

    typedef hla_1516::fixed_record< mpl::vector < f7, f8 > > R3;
  }

  BOOST_AUTO_TEST_CASE( test_octet_8_nested )
  {
    BOOST_CHECK( codec::octet_boundary< t17::R3 >::value == 8 );
  }

  namespace t18
  {
    struct f1 : protox::dtl::field< HLAoctet > {};
    struct f2 : protox::dtl::field< HLAoctet > {};
    struct f3 : protox::dtl::field< HLAoctet > {};

    typedef hla_1516::fixed_record< mpl::vector < f1, f2, f3 > > R1;
  }

  BOOST_AUTO_TEST_CASE( test_codec_no_padding_flat )
  {
	using namespace t18;

    t18::R1 r10;
    r10.f_<f1>() = 'q';
    r10.f_<f2>() = 'r';
    r10.f_<f3>() = 's';

    protox::io::byte_data_sink sink;
    sink.encode( r10 );

    t18::R1 r11;
    protox::io::byte_data_source source(sink);
    source.decode( r11 );

    BOOST_CHECK( r11.f_<f1>() == 'q' );
    BOOST_CHECK( r11.f_<f2>() == 'r' );
    BOOST_CHECK( r11.f_<f3>() == 's' );

    BOOST_CHECK(  r11 == r10 );
  }

  namespace t19
  {
    struct f1 : protox::dtl::field< HLAoctet > {};
    struct f2 : protox::dtl::field< HLAfloat64BE > {};
    struct f3 : protox::dtl::field< HLAoctet > {};

    typedef hla_1516::fixed_record< mpl::vector < f1, f2, f3 > > R1;
  }

  BOOST_AUTO_TEST_CASE( test_codec_padding_flat )
  {
    t19::R1 r10;
    r10.f_<t19::f1>() = 'q';
    r10.f_<t19::f2>() = 3.14159;;
    r10.f_<t19::f3>() = 's';

    protox::io::byte_data_sink sink;
    sink.encode( r10 );

    t19::R1 r11;
    r11.f_<t19::f2>() = 0.0;
    BOOST_CHECK( fabs(r11.f_<t19::f2>() - r10.f_<t19::f2>()) > 3.0 );
    protox::io::byte_data_source source(sink);
    source.decode( r11 );

    BOOST_CHECK( r11.f_<t19::f1>() == 'q' );
    BOOST_CHECK( fabs(r11.f_<t19::f2>() - r10.f_<t19::f2>()) < 0.0000001 );
    BOOST_CHECK( r11.f_<t19::f3>() == 's' );

    BOOST_CHECK(  r11 == r10 );
  }

  namespace t20
  {
    struct f1 : protox::dtl::field< HLAoctet > {};
    struct f2 : protox::dtl::field< HLAoctet > {};
    struct f3 : protox::dtl::field< HLAoctet > {};

    typedef hla_1516::fixed_record< mpl::vector < f1, f2, f3 > > R1;

    struct f4 : protox::dtl::field< R1 > {};
    struct f5 : protox::dtl::field< R1 > {};

    typedef hla_1516::fixed_record< mpl::vector < f4, f5 > > R2;
  }

  BOOST_AUTO_TEST_CASE( test_codec_no_padding_nested )
  {
  	using namespace t20;

    t20::R2 r20;
    r20.f_<f4>().f_<f1>() = 'q';
    r20.f_<f4>().f_<f2>() = 'r';
    r20.f_<f4>().f_<f3>() = 's';

    r20.f_<f5>().f_<f1>() = 'h';
    r20.f_<f5>().f_<f2>() = 'i';
    r20.f_<f5>().f_<f3>() = 'j';

    protox::io::byte_data_sink sink;
    sink.encode( r20 );

    t20::R2 r21;
    protox::io::byte_data_source source(sink);
    source.decode( r21 );

    BOOST_CHECK( r21.f_<f4>().f_<f1>() == 'q' );
    BOOST_CHECK( r21.f_<f4>().f_<f2>() == 'r' );
    BOOST_CHECK( r21.f_<f4>().f_<f3>() == 's' );

    BOOST_CHECK( r21.f_<f5>().f_<f1>() == 'h' );
    BOOST_CHECK( r21.f_<f5>().f_<f2>() == 'i' );
    BOOST_CHECK( r21.f_<f5>().f_<f3>() == 'j' );

    BOOST_CHECK(  r21 == r20 );
  }

  namespace t21
  {
  	struct f1 : protox::dtl::field< HLAoctet > {};
    struct f2 : protox::dtl::field< HLAfloat64BE > {};
    struct f3 : protox::dtl::field< HLAoctet > {};

    typedef hla_1516::fixed_record< mpl::vector < f1, f2, f3 > > R1;

    struct f4 : protox::dtl::field< R1 > {};
    struct f5 : protox::dtl::field< R1 > {};

    typedef hla_1516::fixed_record< mpl::vector < f4, f5 > > R2;
  }

  BOOST_AUTO_TEST_CASE( test_codec_padding_nested )
  {
    using namespace t21;

    R2 r20;
    r20.f_<f4>().f_<f1>() = 'q';
    r20.f_<f4>().f_<f2>() = 3.14159;;
    r20.f_<f4>().f_<f3>() = 's';

    r20.f_<f5>().f_<f1>() = 'h';
    r20.f_<f5>().f_<f2>() = 123e-5;;
    r20.f_<f5>().f_<f3>() = 'j';

    protox::io::byte_data_sink sink;
    sink.encode( r20 );

    R2 r21;
    protox::io::byte_data_source source(sink);
    source.decode( r21 );

    BOOST_CHECK( r21.f_<f4>().f_<f1>() == 'q' );
    BOOST_CHECK( abs(r21.f_<f4>().f_<f2>() - r20.f_<f4>().f_<f2>()) < 0.0000001 );
    BOOST_CHECK( r21.f_<f4>().f_<f3>() == 's' );

    BOOST_CHECK( r21.f_<f5>().f_<f1>() == 'h' );
    BOOST_CHECK( abs(r21.f_<f5>().f_<f2>() - r20.f_<f5>().f_<f2>()) < 0.0000001 );
    BOOST_CHECK( r21.f_<f5>().f_<f3>() == 'j' );

    BOOST_CHECK( r21 == r20 );
  }

  namespace t22
  {
  	struct D1 : protox::dtl::field< protox::hla_1516::HLAfloat64BE > {};
    struct D2 : protox::dtl::field< protox::hla_1516::HLAfloat64BE > {};

    typedef hla_1516::fixed_record< mpl::vector < D1, D2 > > DD;
    struct DF : protox::dtl::field< DD > {};

    struct X : protox::dtl::field< protox::hla_1516::HLAfloat32BE > {};
    typedef hla_1516::fixed_record< mpl::vector < X > > R1;
    struct Y : protox::dtl::field< R1 > {};

    typedef hla_1516::fixed_record< mpl::vector < Y, DF > > r1_type;
  }

  BOOST_AUTO_TEST_CASE( test_fixed_record )
  {
    using namespace t22;

    r1_type r1;
    r1.f_< DF >().f_< D1 >() = 3.145;

    protox::io::byte_data_sink sink;

    BOOST_CHECK( 8 == codec::octet_boundary< r1_type >::value );

    sink.encode( r1 );

    protox::io::byte_data_source source(sink);

    r1_type r2;
    r2.f_< DF >().f_< D1 >() = 0;

    source.decode( r2 );
    BOOST_CHECK( abs(r2.f_< DF >().f_< D1 >() - 3.145) < 0.0001 );

    BOOST_CHECK( codec::dynamic_size( r2 ) == 24 );

    BOOST_CHECK( r2 == r1 );

    r2.f_< Y >().f_< X >() = 5.0f;

    BOOST_CHECK( r2 != r1 );
  }

}

#endif
