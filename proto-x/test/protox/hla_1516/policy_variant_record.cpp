/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

#define BOOST_AUTO_TEST_MAIN

#include <boost/test/included/unit_test_framework.hpp>
#include <boost/test/auto_unit_test.hpp>

/**********************************************************************************************************************/

#include <math.h>
#include <vector>

#include <boost/mpl/vector.hpp>

#include "./test_days_of_week_enum.hpp"
#include "./test_color_enum.hpp"
#include "./test_suite_enum.hpp"

#include "protox/codec/codecs.hpp"
#include "protox/dtl/unknown_static_size.hpp"

#include "protox/io/byte_data_sink.hpp"
#include "protox/io/byte_data_source.hpp"

#include "protox/hla_1516/variant_record.hpp"
#include "protox/hla_1516/basic_data_representation_table.hpp"
#include "protox/hla_1516/fixed_record.hpp"
#include "protox/hla_1516/fixed_array.hpp"

/**********************************************************************************************************************/

#if 0

// +-------------+-----------------------------------------------+------------------------+------------------------+
// |             | Alternative                                   |                        |                        |
// | Record Name +-----------------------------------------------+ Disciminant Enumerator | Encoding               |
// |             | Name  | Type                                  |                        |                        |
// +-------------+-------+---------------------------------------+------------------------+------------------------+
namespace name   {
            struct alt_1 : dtl::discriminant<      HLAinteger16BE, mpl::vector< Sun,
//                                                               +------------------------+
                                                                                Tue > > {};
//               +-------+---------------------------------------+------------------------+
            struct alt_2 : dtl::discriminant<      HLAinteger16BE, mpl::vector< Fri > > {};
//               +-------+---------------------------------------+------------------------+
            struct alt_3 : dtl::discriminant<      HLAoctet,       mpl::vector< Sat > > {};
//               +-------+---------------------------------------+------------------------+
                                                                               struct type : hla_1516::variant_record< DaysOfWeekEnum16::type, mpl::vector< alt_1, alt_2, alt_3 >,
//                       +---------------------------------------+
                           dtl::discriminant_other< HLAfloat32BE > > {};
//                       +---------------------------------------+
}
#endif

/**********************************************************************************************************************/

using namespace boost;
using namespace protox;
using namespace protox::dtl;
using namespace protox::hla_1516;
using namespace test_hla1516;
using namespace test_hla1516::DaysOfWeekEnum16;
using namespace test_hla1516::ColorEnum16;
using namespace test_hla1516::SuiteEnum8;

/**********************************************************************************************************************/

namespace t1 {
    struct x : public field< HLAoctet     > {};
    struct y : public field< HLAfloat32LE > {};
    struct z : public field< HLAfloat64BE > {};

    typedef hla_1516::fixed_record< mpl::vector< x, y, z> > Vector3D;

    typedef hla_1516::fixed_array< HLAfloat32BE,  3 > Vector3DArray;
    typedef hla_1516::fixed_array< Vector3DArray, 3 > Vector3DMatrix;

    struct alt_1 : discriminant< HLAinteger16LE, mpl::vector< Sun, Tue > > {};
    struct alt_2 : discriminant< Vector3D,       mpl::vector< Fri > > {};
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(tests_default_constructor) {

    typedef hla_1516::variant_record<
        DaysOfWeekEnum16::type,
        mpl::vector< t1::alt_1, t1::alt_2 >
    > VarRecord01;

    typedef hla_1516::variant_record<
        DaysOfWeekEnum16::type,
        mpl::vector< t1::alt_1, t1::alt_2 >,
        dtl::discriminant_other< HLAfloat32BE > // This is optional
    > VarRecord02;
}

/**********************************************************************************************************************/

namespace t2 {
    struct alt_1 : dtl::discriminant< HLAoctet, mpl::vector< Sun, Tue > > {};
    struct alt_2 : dtl::discriminant< HLAoctet, mpl::vector< Fri >      > {};
    struct alt_3 : dtl::discriminant< HLAoctet, mpl::vector< Sat >      > {};
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(tests_octet_boundary_discriminant) {

    typedef hla_1516::variant_record<
        DaysOfWeekEnum16::type,
        mpl::vector< t2::alt_1, t2::alt_2, t2::alt_3 >
    > VarRecord01;

   BOOST_CHECK(codec::octet_boundary< VarRecord01 >::value == 2);
}

/**********************************************************************************************************************/

namespace t3 {
    struct alt_1 : dtl::discriminant< HLAinteger16LE,  mpl::vector< Sun, Tue > > {};
    struct alt_2 : dtl::discriminant< HLAoctet,        mpl::vector< Fri >      > {};
    struct alt_3 : dtl::discriminant< HLAoctet,        mpl::vector< Sat >      > {};
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(tests_octet_boundary_2) {

    typedef hla_1516::variant_record<
        DaysOfWeekEnum16::type,
        mpl::vector< t3::alt_1, t3::alt_2, t3::alt_3 >
    > VarRecord01;

    BOOST_CHECK(codec::octet_boundary< VarRecord01 >::value == 2);
}

/**********************************************************************************************************************/

namespace t4 {
    struct alt_1 : dtl::discriminant< HLAinteger16BE, mpl::vector< Sun, Tue >  > {};
    struct alt_2 : dtl::discriminant< HLAinteger32BE, mpl::vector< Fri >       > {};
    struct alt_3 : dtl::discriminant< HLAoctet,       mpl::vector< Sat >       > {};
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(tests_octet_boundary_4) {

    typedef hla_1516::variant_record<
        DaysOfWeekEnum16::type,
        mpl::vector< t4::alt_1, t4::alt_2, t4::alt_3 >
    > VarRecord01;

    BOOST_CHECK(codec::octet_boundary< VarRecord01 >::value == 4);
}

/**********************************************************************************************************************/

namespace t5 {
    struct alt_1 : dtl::discriminant< HLAinteger16BE, mpl::vector< Sun, Tue >  > {};
    struct alt_2 : dtl::discriminant< HLAinteger64BE, mpl::vector< Fri >       > {};
    struct alt_3 : dtl::discriminant< HLAoctet,       mpl::vector< Sat >       > {};
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(tests_octet_boundary_8) {

    typedef hla_1516::variant_record<
        DaysOfWeekEnum16::type,
        mpl::vector< t5::alt_1, t5::alt_2, t5::alt_3 >
    > VarRecord01;

    BOOST_CHECK(codec::octet_boundary< VarRecord01 >::value == 8);
}

/**********************************************************************************************************************/

namespace t6 {
    struct alt_1 : dtl::discriminant< HLAinteger16BE, mpl::vector< Sun, Tue >  > {};
    struct alt_2 : dtl::discriminant< HLAinteger16BE, mpl::vector< Fri >       > {};
    struct alt_3 : dtl::discriminant< HLAoctet,       mpl::vector< Sat >       > {};
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(tests_octet_boundary_other) {

    typedef hla_1516::variant_record<
        DaysOfWeekEnum16::type,
        mpl::vector< t6::alt_1, t6::alt_2, t6::alt_3 >,
        dtl::discriminant_other< HLAfloat32BE > // This is optional
    > VarRecord01;

    BOOST_CHECK(codec::octet_boundary< VarRecord01 >::value == 4);
}

/**********************************************************************************************************************/

namespace t7 {
    struct x : public field< HLAoctet     > {};
    struct y : public field< HLAfloat32LE > {};
    struct z : public field< HLAfloat64BE > {};
    typedef hla_1516::fixed_record< mpl::vector< x, y, z> > Vector3D;

    typedef hla_1516::fixed_array< HLAfloat32BE,  3 > Vector3DArray;
    typedef hla_1516::fixed_array< Vector3DArray, 3 > Vector3DMatrix;

    struct alt_1 : dtl::discriminant< HLAinteger16LE, mpl::vector< Sun, Tue >  > {};
    struct alt_2 : dtl::discriminant< Vector3D,       mpl::vector< Fri >       > {};
    struct alt_3 : dtl::discriminant< HLAoctet,       mpl::vector< Sat >       > {};
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(tests_octet_boundary_composite) {

    typedef hla_1516::variant_record<
        DaysOfWeekEnum16::type,
        mpl::vector< t7::alt_1, t7::alt_2, t7::alt_3 >
    > VarRecord01;

    BOOST_CHECK(codec::octet_boundary< VarRecord01 >::value == 8);
}

/**********************************************************************************************************************/

namespace t8 {
    struct alt_1 : dtl::discriminant< HLAinteger16BE, mpl::vector< Sun, Tue >  > {};
    struct alt_2 : dtl::discriminant< HLAinteger16BE, mpl::vector< Fri >       > {};
    struct alt_3 : dtl::discriminant< HLAoctet,       mpl::vector< Sat >       > {};
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_equality_operator_simple) {

    typedef hla_1516::variant_record<
        DaysOfWeekEnum16::type,
        mpl::vector< t8::alt_1, t8::alt_2, t8::alt_3 >,
        dtl::discriminant_other< HLAfloat32BE > // This is optional
    > VarRecord01;

    VarRecord01 vr1;

    vr1.discriminant = Fri::value();
    vr1.alt_< t8::alt_2 >( 5 );
    vr1.alt_< t8::alt_3 >( 'b' );

    BOOST_CHECK(vr1 == vr1);

    VarRecord01 vr2;

    BOOST_CHECK(vr1 != vr2);
    BOOST_CHECK(vr2 != vr1);

    vr2.discriminant = Sat::value();
    vr2.alt_< t8::alt_2 >(5);
    vr2.alt_< t8::alt_3 >('b');

    BOOST_CHECK(vr2 == vr2);

    BOOST_CHECK(vr1 != vr2);
    BOOST_CHECK(vr2 != vr1);

    vr1.discriminant = Sat::value();

    BOOST_CHECK(vr1 == vr2);
    BOOST_CHECK(vr2 == vr1);

    VarRecord01 vr3;
    vr3.discriminant = Sat::value();

    BOOST_CHECK(vr3 != vr1);
    BOOST_CHECK(vr3 != vr2);
}

/**********************************************************************************************************************/

namespace t9 {
    struct alt_1 : dtl::discriminant< HLAinteger16BE, mpl::vector< Sun, Tue >  > {};
    struct alt_2 : dtl::discriminant< HLAinteger16BE, mpl::vector< Fri >       > {};
    struct alt_3 : dtl::discriminant< HLAoctet,       mpl::vector< Sat >       > {};

    typedef hla_1516::variant_record<
        DaysOfWeekEnum16::type,
        mpl::vector< alt_1, alt_2, alt_3 >,
        dtl::discriminant_other< HLAfloat32BE > // This is optional
    > VarRecord01;

    struct alt_4 : dtl::discriminant< VarRecord01,  mpl::vector< Red  >  > {};
    struct alt_5 : dtl::discriminant< HLAfloat32BE, mpl::vector< Blue >  > {};

    typedef hla_1516::variant_record<
        ColorEnum16::type,
        mpl::vector< alt_4, alt_5 >,
        dtl::discriminant_other< HLAfloat32BE > // This is optional
    > VarRecord02;
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_equality_operator_composite) {

    t9::VarRecord01 vr1;
    t9::VarRecord02 vr2;

    vr1.discriminant = Tue::value();
    vr1.alt_< t9::alt_1 >(25);

    vr2.discriminant = Red::value();
    vr2.alt_< t9::alt_4 >(vr1);

    BOOST_CHECK(vr2 == vr2);

    vr2.alt_< t9::alt_4 >()->discriminant = Sat::value();
    vr2.alt_< t9::alt_4 >()->alt_< t9::alt_3 >('v');

    BOOST_CHECK(*(vr2.alt_< t9::alt_4 >()) != vr1);

    vr1.discriminant = Sat::value();
    vr1.alt_< t9::alt_3 >('v');

    BOOST_CHECK(vr1 == *(vr2.alt_< t9::alt_4 >()));

    vr2.alt_< t9::alt_4 >()->discriminant = Wed::value();
    vr2.alt_< t9::alt_4 >()->other_(72.0f);

    BOOST_CHECK(vr1 != *(vr2.alt_< t9::alt_4 >()));

    vr1.discriminant = Wed::value();
    vr1.other_(72.0f);

    BOOST_CHECK(vr1 == *(vr2.alt_< t9::alt_4 >()));
}

/**********************************************************************************************************************/

namespace t10 {
    struct alt_1 : dtl::discriminant< HLAinteger32BE,  mpl::vector< Club  > > {};
    struct alt_2 : dtl::discriminant< HLAfloat64BE,    mpl::vector< Heart > > {};
    struct alt_3 : dtl::discriminant< HLAoctet,        mpl::vector< Spade > > {};
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_dynamic_size_padding) {

    typedef hla_1516::variant_record<
        SuiteEnum8::type,
        mpl::vector< t10::alt_1, t10::alt_2, t10::alt_3 >
    > VarRecord01;

    VarRecord01 vr1;

    vr1.discriminant = Club::value();
    vr1.alt_< t10::alt_1 >(8);

    // 1 + 7 (padding) + 4
    BOOST_CHECK(protox::dtl::codec::dynamic_size(vr1) == 12);

    vr1.discriminant = Spade::value();
    // 1 + 7 (padding)
    BOOST_CHECK(protox::dtl::codec::dynamic_size(vr1) == 8);

    vr1.alt_< t10::alt_3 >('k');
    // 1 + 7 (padding) + 1
    BOOST_CHECK(protox::dtl::codec::dynamic_size(vr1) == 9);

    vr1.discriminant = Heart::value();
    vr1.alt_< t10::alt_2 >(3.145);
    // 1 + 7 (padding) + 8
    BOOST_CHECK(protox::dtl::codec::dynamic_size(vr1) == 16);
}

/**********************************************************************************************************************/

namespace t11 {
    struct alt_1 : dtl::discriminant< HLAinteger16BE, mpl::vector< Sun > > {};
    struct alt_2 : dtl::discriminant< HLAoctetPairBE, mpl::vector< Fri > > {};
    struct alt_3 : dtl::discriminant< HLAoctet,       mpl::vector< Sat > > {};
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_dynamic_size_no_padding) {

    typedef hla_1516::variant_record<
        DaysOfWeekEnum16::type,
        mpl::vector< t11::alt_1, t11::alt_2, t11::alt_3 >,
        dtl::discriminant_other< HLAoctet > // This is optional
    > VarRecord01;

    VarRecord01 vr1;

    vr1.discriminant = Sun::value();
    vr1.alt_< t11::alt_1 >((HLAinteger16BE) 8);

    // 2 + 2
    BOOST_CHECK(protox::dtl::codec::dynamic_size(vr1) == 4);

    vr1.discriminant = Fri::value();
    // 2
    BOOST_CHECK(protox::dtl::codec::dynamic_size(vr1) == 2);

    vr1.discriminant = Sat::value();
    vr1.alt_< t11::alt_3 >('n');
    // 2 + 1
    BOOST_CHECK(protox::dtl::codec::dynamic_size(vr1) == 3);

    vr1.discriminant = Wed::value();

    // 2
    BOOST_CHECK(protox::dtl::codec::dynamic_size(vr1) == 2);

    vr1.other_('t');
    // 2 + 1
    BOOST_CHECK(protox::dtl::codec::dynamic_size(vr1) == 3);
}

/**********************************************************************************************************************/

namespace t12 {
    struct alt_1 : dtl::discriminant< HLAinteger32BE,  mpl::vector< Club  > > {};
    struct alt_2 : dtl::discriminant< HLAfloat64BE,    mpl::vector< Heart > > {};
    struct alt_3 : dtl::discriminant< HLAoctet,        mpl::vector< Spade > > {};
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_codec_padding) {

    typedef hla_1516::variant_record<
        SuiteEnum8::type,
        mpl::vector< t12::alt_1, t12::alt_2, t12::alt_3 >
    > VarRecord01;

    VarRecord01 vr1;

    vr1.discriminant = Club::value();
    vr1.alt_< t12::alt_1 >(8);

    VarRecord01 vr2;

    vr2.discriminant = Heart::value();
    vr2.alt_< t12::alt_2 >(32.0);

    BOOST_CHECK( vr1 != vr2 );

    protox::io::byte_data_sink sink;
    sink.encode(vr1);

    protox::io::byte_data_source source(sink);
    source.decode(vr2);

    BOOST_CHECK(vr2.discriminant            == Club::value());
    BOOST_CHECK((*vr2.alt_< t12::alt_1 >()) == 8            );
    BOOST_CHECK(vr1                         == vr2          );
}

/**********************************************************************************************************************/

namespace t13 {
    struct alt_1 : dtl::discriminant< HLAinteger16BE, mpl::vector< Sun > > {};
    struct alt_2 : dtl::discriminant< HLAoctetPairBE, mpl::vector< Fri > > {};
    struct alt_3 : dtl::discriminant< HLAoctet,       mpl::vector< Sat > > {};
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_codec_no_padding) {

    typedef hla_1516::variant_record<
        DaysOfWeekEnum16::type,
        mpl::vector< t13::alt_1, t13::alt_2, t13::alt_3 >,
        dtl::discriminant_other< HLAoctet > // This is optional
    > VarRecord01;

    VarRecord01 vr1;

    vr1.discriminant = Sun::value();
    vr1.alt_< t13::alt_1 >(25);

    VarRecord01 vr2;

    vr2.discriminant = Sat::value();
    vr2.alt_< t13::alt_2 >('g');

    BOOST_CHECK(vr1 != vr2);

    protox::io::byte_data_sink sink;
    sink.encode(vr1);

    protox::io::byte_data_source source(sink);
    source.decode(vr2);

    BOOST_CHECK(vr2.discriminant            == Sun::value());
    BOOST_CHECK((*vr2.alt_< t13::alt_1 >()) == 25          );
    BOOST_CHECK(vr1                         == vr2         );
}

/**********************************************************************************************************************/

namespace t14 {
    struct alt_1 : dtl::discriminant< HLAinteger16BE, mpl::vector< Sun > > {};
    struct alt_2 : dtl::discriminant< HLAoctetPairBE, mpl::vector< Fri > > {};
    struct alt_3 : dtl::discriminant< HLAoctet,       mpl::vector< Sat > > {};
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_codec_other) {

    typedef hla_1516::variant_record<
        DaysOfWeekEnum16::type,
        mpl::vector< t14::alt_1, t14::alt_2, t14::alt_3 >,
        dtl::discriminant_other< HLAoctet > // This is optional
    > VarRecord01;

    VarRecord01 vr1;

    vr1.discriminant = Sun::value();
    vr1.alt_< t14::alt_1 >(25);

    VarRecord01 vr2;

    vr2.discriminant = Sat::value();
    vr2.alt_< t14::alt_2 >('g');

    BOOST_CHECK(vr1 != vr2);

    protox::io::byte_data_sink sink;
    sink.encode(vr1);

    {
        protox::io::byte_data_source source(sink);
        source.decode(vr2);

        BOOST_CHECK(vr2.discriminant            == Sun::value());
        BOOST_CHECK((*vr2.alt_< t14::alt_1 >()) == 25          );
        BOOST_CHECK(vr1                         == vr2         );
    }

    vr1.discriminant = Wed::value();
    vr1.other_('y');

    BOOST_CHECK(vr1 != vr2);

    sink.clear();
    sink.encode(vr1);

    {
        protox::io::byte_data_source source(sink);
        source.decode(vr2);

        BOOST_CHECK(vr2.discriminant == Wed::value());
        BOOST_CHECK((*vr2.other_())  == 'y'         );
        BOOST_CHECK(vr1              == vr2         );
    }
}
