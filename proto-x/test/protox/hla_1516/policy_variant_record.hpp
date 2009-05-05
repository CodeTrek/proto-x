/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

#ifndef TEST_PROTOX_HLA_1516_VARIANT_RECORD_HPP
#define TEST_PROTOX_HLA_1516_VARIANT_RECORD_HPP

#include <math.h>
#include <vector>

#include <boost/mpl/vector.hpp>

#include "./test_days_of_week_enum.hpp"
#include "./test_color_enum.hpp"
#include "./test_suite_enum.hpp"

#include "protox/dtl/codec.hpp"
#include "protox/dtl/unknown_static_size.hpp"

#include "protox/io/byte_data_sink.hpp"
#include "protox/io/byte_data_source.hpp"

#include "protox/hla_1516/variant_record.hpp"
#include "protox/hla_1516/basic_data_representation_table.hpp"
#include "protox/hla_1516/fixed_record.hpp"

using namespace boost;
using namespace protox;
using namespace protox::dtl;
using namespace protox::hla_1516;
using namespace test_hla1516;
using namespace test_hla1516::DaysOfWeekEnum16;
using namespace test_hla1516::ColorEnum16;
using namespace test_hla1516::SuiteEnum8;

namespace test_protox_dtl_hla_1516_policy_variant_record
{
  namespace t1
  {
    struct x : public field<HLAoctet> {};
    struct y : public field<HLAfloat32LE> {};
    struct z : public field<HLAfloat64BE> {};

    typedef hla_1516::fixed_record< mpl::vector< x, y, z> > Vector3D;

    typedef hla_1516::fixed_array< HLAfloat32BE, 3 > Vector3DArray;
    typedef hla_1516::fixed_array< Vector3DArray, 3 > Vector3DMatrix;

    struct alt_1 : discriminant< mpl::vector< Sun, Tue >, HLAinteger16LE > {};
    struct alt_2 : discriminant< mpl::vector< Fri >,      Vector3D > {};
  }

  BOOST_AUTO_TEST_CASE( tests_default_constructor )
  {
    using namespace t1;

    typedef hla_1516::variant_record<
      DaysOfWeekEnum16::Type,
      mpl::vector< alt_1, alt_2 >
    > VarRecord01;

    typedef hla_1516::variant_record<
      DaysOfWeekEnum16::Type,
      mpl::vector< alt_1, alt_2 >,
      dtl::discriminant_other< HLAfloat32BE > // This is optional
    > VarRecord02;
  }

  namespace t2
  {
    struct alt_1 : dtl::discriminant< mpl::vector< Sun, Tue >, HLAoctet > {};
    struct alt_2 : dtl::discriminant< mpl::vector< Fri >,      HLAoctet > {};
    struct alt_3 : dtl::discriminant< mpl::vector< Sat >,      HLAoctet > {};
  }

  BOOST_AUTO_TEST_CASE( tests_octet_boundary_discriminant )
  {
    using namespace t2;

    typedef hla_1516::variant_record<
      DaysOfWeekEnum16::Type,
      mpl::vector< alt_1, alt_2, alt_3 >
    > VarRecord01;

   BOOST_CHECK( codec::octet_boundary< VarRecord01 >::value == 2 );
  }

  namespace t3
  {
    struct alt_1 : dtl::discriminant< mpl::vector< Sun, Tue >, HLAinteger16LE > {};
    struct alt_2 : dtl::discriminant< mpl::vector< Fri >,      HLAoctet > {};
    struct alt_3 : dtl::discriminant< mpl::vector< Sat >,      HLAoctet > {};
  }

  BOOST_AUTO_TEST_CASE( tests_octet_boundary_2 )
  {
    using namespace t3;

    typedef hla_1516::variant_record<
      DaysOfWeekEnum16::Type,
      mpl::vector< alt_1, alt_2, alt_3 >
    > VarRecord01;

    BOOST_CHECK( codec::octet_boundary< VarRecord01 >::value == 2 );
  }


  namespace t4
  {
    struct alt_1 : dtl::discriminant< mpl::vector< Sun, Tue >, HLAinteger16BE > {};
    struct alt_2 : dtl::discriminant< mpl::vector< Fri >,      HLAinteger32BE > {};
    struct alt_3 : dtl::discriminant< mpl::vector< Sat >,      HLAoctet > {};
  }

  BOOST_AUTO_TEST_CASE( tests_octet_boundary_4 )
  {
    using namespace t4;

    typedef hla_1516::variant_record<
      DaysOfWeekEnum16::Type,
      mpl::vector< alt_1, alt_2, alt_3 >
    > VarRecord01;

    BOOST_CHECK( codec::octet_boundary< VarRecord01 >::value == 4 );
  }

  namespace t5
  {
    struct alt_1 : dtl::discriminant< mpl::vector< Sun, Tue >, HLAinteger16BE > {};
    struct alt_2 : dtl::discriminant< mpl::vector< Fri >,      HLAinteger64BE > {};
    struct alt_3 : dtl::discriminant< mpl::vector< Sat >,      HLAoctet > {};
  }

  BOOST_AUTO_TEST_CASE( tests_octet_boundary_8 )
  {
    using namespace t5;

    typedef hla_1516::variant_record<
      DaysOfWeekEnum16::Type,
      mpl::vector< alt_1, alt_2, alt_3 >
    > VarRecord01;

    BOOST_CHECK( codec::octet_boundary< VarRecord01 >::value == 8 );
  }

  namespace t6
  {
    struct alt_1 : dtl::discriminant< mpl::vector< Sun, Tue >, HLAinteger16BE > {};
    struct alt_2 : dtl::discriminant< mpl::vector< Fri >,      HLAinteger16BE > {};
    struct alt_3 : dtl::discriminant< mpl::vector< Sat >,      HLAoctet > {};
  }

  BOOST_AUTO_TEST_CASE( tests_octet_boundary_other )
  {
    using namespace t6;

    typedef hla_1516::variant_record<
      DaysOfWeekEnum16::Type,
      mpl::vector< alt_1, alt_2, alt_3 >,
      dtl::discriminant_other< HLAfloat32BE > // This is optional
    > VarRecord01;

    BOOST_CHECK( codec::octet_boundary< VarRecord01 >::value == 4 );
  }

  namespace t7
  {
    struct x : public field<HLAoctet> {};
    struct y : public field<HLAfloat32LE> {};
    struct z : public field<HLAfloat64BE> {};
    typedef hla_1516::fixed_record< mpl::vector< x, y, z> > Vector3D;

    typedef hla_1516::fixed_array< HLAfloat32BE, 3 > Vector3DArray;
    typedef hla_1516::fixed_array< Vector3DArray, 3 > Vector3DMatrix;

    struct alt_1 : discriminant< mpl::vector< Sun, Tue >, HLAinteger16LE > {};
    struct alt_2 : discriminant< mpl::vector< Fri >,      Vector3D > {};
    struct alt_3 : dtl::discriminant< mpl::vector< Sat >,      HLAoctet > {};
  }

  BOOST_AUTO_TEST_CASE( tests_octet_boundary_composite )
  {
    using namespace t7;

    typedef hla_1516::variant_record<
      DaysOfWeekEnum16::Type,
      mpl::vector< alt_1, alt_2, alt_3 >
    > VarRecord01;

    BOOST_CHECK( codec::octet_boundary< VarRecord01 >::value == 8 );
  }

  namespace t8
  {
    struct alt_1 : dtl::discriminant< mpl::vector< Sun, Tue >, HLAinteger16BE > {};
    struct alt_2 : dtl::discriminant< mpl::vector< Fri >,      HLAinteger16BE > {};
    struct alt_3 : dtl::discriminant< mpl::vector< Sat >,      HLAoctet > {};
  }

  BOOST_AUTO_TEST_CASE( test_equality_operator_simple )
  {
    using namespace t8;

    typedef hla_1516::variant_record<
      DaysOfWeekEnum16::Type,
      mpl::vector< alt_1, alt_2, alt_3 >,
      dtl::discriminant_other< HLAfloat32BE > // This is optional
    > VarRecord01;

    VarRecord01 vr1;

    vr1.discriminant = Fri::value();
    vr1.alt_< alt_2 >( 5 );
    vr1.alt_< alt_3 >( 'b' );

    BOOST_CHECK( vr1 == vr1 );

    VarRecord01 vr2;

    BOOST_CHECK( vr1 != vr2 );
    BOOST_CHECK( vr2 != vr1 );

    vr2.discriminant = Sat::value();
    vr2.alt_< alt_2 >( 5 );
    vr2.alt_< alt_3 >( 'b' );

    BOOST_CHECK( vr2 == vr2 );

    BOOST_CHECK( vr1 != vr2 );
    BOOST_CHECK( vr2 != vr1 );

    vr1.discriminant = Sat::value();

    BOOST_CHECK( vr1 == vr2 );
    BOOST_CHECK( vr2 == vr1 );

    VarRecord01 vr3;
    vr3.discriminant = Sat::value();

    BOOST_CHECK( vr3 != vr1 );
    BOOST_CHECK( vr3 != vr2 );
  }

  namespace t9
  {
    struct alt_1 : dtl::discriminant< mpl::vector< Sun, Tue >, HLAinteger16BE > {};
    struct alt_2 : dtl::discriminant< mpl::vector< Fri >,      HLAinteger16BE > {};
    struct alt_3 : dtl::discriminant< mpl::vector< Sat >,      HLAoctet > {};

    typedef hla_1516::variant_record<
      DaysOfWeekEnum16::Type,
      mpl::vector< alt_1, alt_2, alt_3 >,
      dtl::discriminant_other< HLAfloat32BE > // This is optional
    > VarRecord01;

    struct alt_4 : dtl::discriminant< mpl::vector< Red >,  VarRecord01 > {};
    struct alt_5 : dtl::discriminant< mpl::vector< Blue >, HLAfloat32BE > {};

    typedef hla_1516::variant_record<
      ColorEnum16::Type,
      mpl::vector< alt_4, alt_5 >,
      dtl::discriminant_other< HLAfloat32BE > // This is optional
    > VarRecord02;
  }

  BOOST_AUTO_TEST_CASE( test_equality_operator_composite )
  {
    using namespace t9;

    VarRecord01 vr1;
    VarRecord02 vr2;

    vr1.discriminant = Tue::value();
    vr1.alt_< alt_1 >(25);

    vr2.discriminant = Red::value();
    vr2.alt_< alt_4 >(vr1);

    BOOST_CHECK( vr2 == vr2 );

    vr2.alt_< alt_4 >()->discriminant = Sat::value();
    vr2.alt_< alt_4 >()->alt_< alt_3 >('v');

    BOOST_CHECK( *(vr2.alt_< alt_4 >()) != vr1 );

    vr1.discriminant = Sat::value();
    vr1.alt_< alt_3 >('v');

    BOOST_CHECK( vr1 == *(vr2.alt_< alt_4 >()) );

    vr2.alt_< alt_4 >()->discriminant = Wed::value();
    vr2.alt_< alt_4 >()->other_( 72.0f );

    BOOST_CHECK( vr1 != *(vr2.alt_< alt_4 >()) );

    vr1.discriminant = Wed::value();
    vr1.other_(72.0f);

    BOOST_CHECK( vr1 == *(vr2.alt_< alt_4 >()) );
  }

  namespace t10
  {
    struct alt_1 : dtl::discriminant< mpl::vector< Club >,  HLAinteger32BE > {};
    struct alt_2 : dtl::discriminant< mpl::vector< Heart >, HLAfloat64BE > {};
    struct alt_3 : dtl::discriminant< mpl::vector< Spade >, HLAoctet > {};
  }

  BOOST_AUTO_TEST_CASE( test_dynamic_size_padding )
  {
    using namespace t10;

    typedef hla_1516::variant_record<
      SuiteEnum8::Type,
      mpl::vector< alt_1, alt_2, alt_3 >
    > VarRecord01;

    VarRecord01 vr1;

    vr1.discriminant = Club::value();
    vr1.alt_< alt_1 >( 8 );

    // 1 + 7 (padding) + 4
    BOOST_CHECK( protox::dtl::codec::dynamic_size( vr1 ) == 12 );

    vr1.discriminant = Spade::value();
    // 1 + 7 (padding)
    BOOST_CHECK( protox::dtl::codec::dynamic_size( vr1 ) == 8 );

    vr1.alt_< alt_3 >('k');
    // 1 + 7 (padding) + 1
    BOOST_CHECK( protox::dtl::codec::dynamic_size( vr1 ) == 9 );

    vr1.discriminant = Heart::value();
    vr1.alt_< alt_2 >(3.145);
    // 1 + 7 (padding) + 8
    BOOST_CHECK( protox::dtl::codec::dynamic_size( vr1 ) == 16 );
  }

  namespace t11
  {
    struct alt_1 : dtl::discriminant< mpl::vector< Sun >, HLAinteger16BE > {};
    struct alt_2 : dtl::discriminant< mpl::vector< Fri >, HLAoctetPairBE > {};
    struct alt_3 : dtl::discriminant< mpl::vector< Sat >, HLAoctet > {};
  }

  BOOST_AUTO_TEST_CASE( test_dynamic_size_no_padding )
  {
    using namespace t11;

    typedef hla_1516::variant_record<
      DaysOfWeekEnum16::Type,
      mpl::vector< alt_1, alt_2, alt_3 >,
      dtl::discriminant_other< HLAoctet > // This is optional
    > VarRecord01;

    VarRecord01 vr1;

    vr1.discriminant = Sun::value();
    vr1.alt_< alt_1 >( (HLAinteger16BE) 8 );

    // 2 + 2
    BOOST_CHECK( protox::dtl::codec::dynamic_size( vr1 ) == 4 );

    vr1.discriminant = Fri::value();
    // 2
    BOOST_CHECK( protox::dtl::codec::dynamic_size( vr1 ) == 2 );

    vr1.discriminant = Sat::value();
    vr1.alt_< alt_3 >('n');
    // 2 + 1
    BOOST_CHECK( protox::dtl::codec::dynamic_size( vr1 ) == 3 );

    vr1.discriminant = Wed::value();

    // 2
    BOOST_CHECK( protox::dtl::codec::dynamic_size( vr1 ) == 2 );

    vr1.other_('t');
    // 2 + 1
    BOOST_CHECK( protox::dtl::codec::dynamic_size( vr1 ) == 3 );
  }

  namespace t12
  {
    struct alt_1 : dtl::discriminant< mpl::vector< Club >,  HLAinteger32BE > {};
    struct alt_2 : dtl::discriminant< mpl::vector< Heart >, HLAfloat64BE > {};
    struct alt_3 : dtl::discriminant< mpl::vector< Spade >, HLAoctet > {};
  }

  BOOST_AUTO_TEST_CASE( test_codec_padding )
  {
    using namespace t12;

    typedef hla_1516::variant_record<
      SuiteEnum8::Type,
      mpl::vector< alt_1, alt_2, alt_3 >
    > VarRecord01;

    VarRecord01 vr1;

    vr1.discriminant = Club::value();
    vr1.alt_< alt_1 >( 8 );

    VarRecord01 vr2;

    vr2.discriminant = Heart::value();
    vr2.alt_< alt_2 >( 32.0 );

    BOOST_CHECK( vr1 != vr2 );

    protox::io::byte_data_sink sink;
    sink.encode( vr1 );

    protox::io::byte_data_source source(sink);
    source.decode( vr2 );

    BOOST_CHECK( vr2.discriminant == Club::value() );
    BOOST_CHECK( (*vr2.alt_< alt_1 >()) == 8 );
    BOOST_CHECK( vr1 == vr2 );
  }

  namespace t13
  {
    struct alt_1 : dtl::discriminant< mpl::vector< Sun >, HLAinteger16BE > {};
    struct alt_2 : dtl::discriminant< mpl::vector< Fri >, HLAoctetPairBE > {};
    struct alt_3 : dtl::discriminant< mpl::vector< Sat >, HLAoctet > {};
  }

  BOOST_AUTO_TEST_CASE( test_codec_no_padding )
  {
    using namespace t13;

    typedef hla_1516::variant_record<
      DaysOfWeekEnum16::Type,
      mpl::vector< alt_1, alt_2, alt_3 >,
      dtl::discriminant_other< HLAoctet > // This is optional
    > VarRecord01;

    VarRecord01 vr1;

    vr1.discriminant = Sun::value();
    vr1.alt_< alt_1 >(25);

    VarRecord01 vr2;

    vr2.discriminant = Sat::value();
    vr2.alt_< alt_2 >('g');

    BOOST_CHECK( vr1 != vr2 );

    protox::io::byte_data_sink sink;
    sink.encode( vr1 );

    protox::io::byte_data_source source(sink);
    source.decode( vr2 );

    BOOST_CHECK( vr2.discriminant == Sun::value() );
    BOOST_CHECK( (*vr2.alt_< alt_1 >()) == 25 );
    BOOST_CHECK( vr1 == vr2 );
  }

  namespace t14
  {
    struct alt_1 : dtl::discriminant< mpl::vector< Sun >, HLAinteger16BE > {};
    struct alt_2 : dtl::discriminant< mpl::vector< Fri >, HLAoctetPairBE > {};
    struct alt_3 : dtl::discriminant< mpl::vector< Sat >, HLAoctet > {};
  }

  BOOST_AUTO_TEST_CASE( test_codec_other )
  {
    using namespace t14;

    typedef hla_1516::variant_record<
      DaysOfWeekEnum16::Type,
      mpl::vector< alt_1, alt_2, alt_3 >,
      dtl::discriminant_other< HLAoctet > // This is optional
    > VarRecord01;

    VarRecord01 vr1;

    vr1.discriminant = Sun::value();
    vr1.alt_< alt_1 >(25);

    VarRecord01 vr2;

    vr2.discriminant = Sat::value();
    vr2.alt_< alt_2 >('g');

    BOOST_CHECK( vr1 != vr2 );

    protox::io::byte_data_sink sink;
    sink.encode( vr1 );

    {
      protox::io::byte_data_source source(sink);
      source.decode( vr2 );

      BOOST_CHECK( vr2.discriminant == Sun::value() );
      BOOST_CHECK( (*vr2.alt_< alt_1 >()) == 25 );
      BOOST_CHECK( vr1 == vr2 );
    }

    vr1.discriminant = Wed::value();
    vr1.other_('y');

    BOOST_CHECK( vr1 != vr2 );

    sink.clear();
    sink.encode( vr1 );

    {
      protox::io::byte_data_source source(sink);
      source.decode( vr2 );

      BOOST_CHECK( vr2.discriminant == Wed::value() );
      BOOST_CHECK( (*vr2.other_()) == 'y' );
      BOOST_CHECK( vr1 == vr2 );
    }
  }
}

#endif
