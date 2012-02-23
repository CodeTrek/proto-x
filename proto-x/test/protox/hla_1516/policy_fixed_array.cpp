/*
    Copyright 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#define BOOST_AUTO_TEST_MAIN

#include <boost/test/included/unit_test_framework.hpp>
#include <boost/test/auto_unit_test.hpp>

/**********************************************************************************************************************/

#include <math.h>

#include <boost/mpl/vector.hpp>

#include <protox/io/byte_data_sink.hpp>
#include <protox/io/byte_data_source.hpp>

#include <protox/codec/codecs.hpp>

#include <protox/hla_1516/basic_data_representation_table.hpp>
#include <protox/hla_1516/fixed_array.hpp>
#include <protox/hla_1516/fixed_record.hpp>

/**********************************************************************************************************************/

using namespace boost;
using namespace protox;
using namespace protox::dtl;
using namespace protox::hla_1516;

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_static_size_no_padding) {
    typedef hla_1516::fixed_array< HLAoctet, 20 > A1;
    BOOST_CHECK(codec::static_size_in_bytes< A1 >::value == (20 * codec::static_size_in_bytes< HLAoctet >::value));

    typedef hla_1516::fixed_array< HLAfloat32LE, 11 > A2;
    BOOST_CHECK(codec::static_size_in_bytes< A2 >::value == (11 * codec::static_size_in_bytes< HLAfloat32LE >::value));
}

/**********************************************************************************************************************/

namespace t1 {
  	struct f1 : field< HLAinteger32BE > {};
    struct f2 : field< HLAoctet > {};

    typedef hla_1516::fixed_record< mpl::vector< f1, f2 > > R1;
    typedef hla_1516::fixed_array< R1, 8 > A1;
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_static_size_padding) {
    using namespace t1;

    int padding = 3; // bytes
    BOOST_CHECK(codec::static_size_in_bytes< A1 >::value == ((8*codec::static_size_in_bytes< R1 >::value) + (7*padding)));
}

/**********************************************************************************************************************/

namespace t2 {
  	struct f1 : field< HLAinteger32BE > {};
    struct f2 : field< HLAoctet > {};

    typedef hla_1516::fixed_array< hla_1516::fixed_record< mpl::vector< f1, f2 > >, 8 > A1;
    typedef hla_1516::fixed_array< A1, 3 > A2;
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_static_size_padding_nested) {
  	using namespace t2;

    int padding = 3; // bytes
    BOOST_CHECK(codec::static_size_in_bytes< A2 >::value ==  ((3*codec::static_size_in_bytes<A1>::value) +(2*padding)));
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_octet_1) {
    typedef hla_1516::fixed_array< HLAoctet, 20 > A1;

    BOOST_CHECK(codec::octet_boundary< A1 >::value == 1);
}

/**********************************************************************************************************************/

namespace t3 {
  	struct f1 : field< HLAoctet > {};
    struct f2 : field< HLAoctetPairBE > {};
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_octet_2) {
  	using namespace t3;

    typedef hla_1516::fixed_array< HLAoctetPairLE, 5 > A1;

    BOOST_CHECK(codec::octet_boundary< A1 >::value == 2);

    typedef hla_1516::fixed_array< hla_1516::fixed_record< mpl::vector< f1, f2 > >, 8 > A2;

    BOOST_CHECK(codec::octet_boundary< A2 >::value == 2);
}

/**********************************************************************************************************************/

namespace t4 {
  	struct f1 : field< HLAfloat32BE > {};
    struct f2 : field< HLAoctetPairBE > {};
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_octet_4) {
  	using namespace t4;

    typedef hla_1516::fixed_array< HLAfloat32LE, 23 > A1;

    BOOST_CHECK(codec::octet_boundary< A1 >::value == 4);

    typedef hla_1516::fixed_array< hla_1516::fixed_record< mpl::vector< f1, f2 > >, 8 > A2;

    BOOST_CHECK(codec::octet_boundary< A2 >::value == 4);
}

/**********************************************************************************************************************/

namespace t5 {
    struct f1 : field< HLAfloat64BE > {};
    struct f2 : field< HLAoctetPairBE > {};
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_octet_8) {
  	using namespace t5;

    typedef hla_1516::fixed_array< HLAfloat64LE, 23 > A1;

    BOOST_CHECK(codec::octet_boundary< A1 >::value == 8);

    typedef hla_1516::fixed_array< hla_1516::fixed_record< mpl::vector< f1, f2 > >, 88 > A2;

    BOOST_CHECK(codec::octet_boundary< A2 >::value == 8);
}

/**********************************************************************************************************************/

namespace t6 {
  	struct f1 : field< HLAfloat64BE > {};
    struct f2 : field< HLAoctetPairBE > {};
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_octet_8_nested) {
  	using namespace t6;

    typedef hla_1516::fixed_array< HLAfloat64LE, 23 > A1;

    BOOST_CHECK(codec::octet_boundary< A1 >::value == 8);

    typedef hla_1516::fixed_array< hla_1516::fixed_array< hla_1516::fixed_record< mpl::vector< f1, f2 > >, 88 >, 4 > A2;

    BOOST_CHECK(codec::octet_boundary< A2 >::value == 8);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_codec_no_padding_flat) {

    typedef hla_1516::fixed_array< HLAoctet, 11 > A1;

    A1 a10;
    int i;

    for (i = 0; i < a10.static_num_elements; ++i) {
        a10[i] = 'a' + i;
    }

    protox::io::byte_data_sink sink;
    sink.encode(a10);

    A1 a11;

    for (i = 0; i < a11.static_num_elements; ++i) {
        a11[i] = 0;
    }

    BOOST_CHECK(a11 != a10);

    protox::io::byte_data_source source(sink);
    source.decode(a11);

    BOOST_CHECK(a11.static_num_elements == a10.static_num_elements);

    for (i = 0; i < a10.static_num_elements; ++i) {
        BOOST_CHECK( a11[i] == a10[i] );
    }

    BOOST_CHECK(a11 == a10);
}

/**********************************************************************************************************************/

namespace t7 {
    struct f1 : field< HLAinteger32BE > {};
    struct f2 : field< HLAoctet > {};
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_codec_padding_flat) {
    using namespace t7;

    typedef hla_1516::fixed_array< hla_1516::fixed_record< mpl::vector< f1, f2 > >, 7 > A1;

    A1 a10;
    int i;

    for(i = 0; i < a10.static_num_elements; ++i) {
        a10[i].f_<f1>() = i*2;
        a10[i].f_<f2>() = 'd' + i;
    }

    protox::io::byte_data_sink sink;
    sink.encode( a10 );

    A1 a11;

    for (i = 0; i < a11.static_num_elements; ++i) {
        a11[i].f_<f1>() = 0;
        a11[i].f_<f2>() = 0;
    }

    BOOST_CHECK(a11 != a10);

    protox::io::byte_data_source source(sink);
    source.decode(a11);

    BOOST_CHECK(a11.static_num_elements == a10.static_num_elements);

    for (i = 0; i < a10.static_num_elements; ++i) {
        BOOST_CHECK(a11[i] == a10[i]);
    }

    BOOST_CHECK(a11 == a10);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_codec_no_padding_nested) {
    typedef hla_1516::fixed_array< HLAoctet, 13 > A1;
    typedef hla_1516::fixed_array< A1, 2 > A2;

    A2 a20;
    int i, j;

    for (i = 0; i < A2::static_num_elements; ++i) {
        for (j = 0; j < A1::static_num_elements; ++j) {
            a20[i][j] = 'a' + i;
        }
    }

    protox::io::byte_data_sink sink;
    sink.encode( a20 );

    A2 a21;

    for (i = 0; i < A2::static_num_elements; ++i) {
        for (j = 0; j < A1::static_num_elements; ++j) {
            a21[i][j] = 0;
        }
    }

    BOOST_CHECK(a21 != a20);

    protox::io::byte_data_source source(sink);
    source.decode(a21);

    BOOST_CHECK(a21.static_num_elements == a20.static_num_elements);

    for (i = 0; i < A2::static_num_elements; ++i) {
        BOOST_CHECK(a21[i] == a20[i]);
    }

    BOOST_CHECK(a21 == a20);
}

/**********************************************************************************************************************/

namespace t8 {
    struct f1 : field< HLAinteger32LE > {};
    struct f2 : field< HLAoctet > {};
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_codec_padding_nested) {
    using namespace t8;

    typedef hla_1516::fixed_array< hla_1516::fixed_record< mpl::vector< f1, f2 > >, 13 > A1;
    typedef hla_1516::fixed_array< A1, 4 > A2;

    A2 a20;
    int i, j;

    for (i = 0; i < A2::static_num_elements; ++i) {
        for (j = 0; j < A1::static_num_elements; ++j) {
            a20[i][j].f_<f1>() = -((i+1)*(j+1));
            a20[i][j].f_<f2>() = 'a' + j;
        }
    }

    protox::io::byte_data_sink sink;
    sink.encode(a20);

    A2 a21;

    for (i = 0; i < A2::static_num_elements; ++i) {
        for (j = 0; j < A1::static_num_elements; ++j) {
            a21[i][j].f_<f1>() = 0;
            a21[i][j].f_<f2>() = 0;
        }
    }

    BOOST_CHECK(a21 != a20);

    protox::io::byte_data_source source(sink);
    source.decode(a21);

    BOOST_CHECK(a21.static_num_elements == a20.static_num_elements);

    for (i = 0; i < A2::static_num_elements; ++i) {
        BOOST_CHECK(a21[i] == a20[i]);
        BOOST_CHECK(a21[i][3].f_<f1>() < 0);
    }

    BOOST_CHECK(a21 == a20);
}
