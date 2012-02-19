/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#define BOOST_AUTO_TEST_MAIN

#include <boost/test/included/unit_test_framework.hpp>
#include <boost/test/auto_unit_test.hpp>

/**********************************************************************************************************************/

#include <protox/platform.hpp>

#include <boost/mpl/sizeof.hpp>

#include <protox/dtl/simple.hpp>

#include <protox/io/byte_data_sink.hpp>
#include <protox/io/byte_data_source.hpp>

#include <test/protox/custom/custom_data_representation_table.hpp>

/**********************************************************************************************************************/

namespace t1 {
    using namespace protox::dtl;
    using namespace test::custom;

    struct SimpleUnsigned16BE : simple< UnsignedInt16BE > { PROTOX_SIMPLE( SimpleUnsigned16BE ) };
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_encode_UnsignedInt16BE) {
    using namespace t1;
    protox::io::byte_data_sink sink;

    SimpleUnsigned16BE uint16BE = 23171;
    sink.encode(uint16BE);

    BOOST_CHECK(sink.size() == 2);
    BOOST_CHECK(ntohs(*((SimpleUnsigned16BE *) sink.getDataBuffer())) == 23171);
}

/**********************************************************************************************************************/

namespace t2 {
    using namespace protox::dtl;
    using namespace test::custom;

    struct SimpleUnsigned32BE : simple< UnsignedInt32BE > { PROTOX_SIMPLE(SimpleUnsigned32BE) };
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_encode_UnsignedInt32BE) {
    using namespace t2;
    protox::io::byte_data_sink sink;

    SimpleUnsigned32BE uint32BE = 368974;
    sink.encode(uint32BE);

    BOOST_CHECK(sink.size() == 4);

    SimpleUnsigned32BE value = SYS_NTOHL(*((SimpleUnsigned32BE *) sink.getDataBuffer()));

    BOOST_CHECK(value == 368974);
}

/**********************************************************************************************************************/

namespace t3 {
    using namespace protox::dtl;
    using namespace test::custom;

    struct SimpleUnsigned32BE : simple< UnsignedInt32BE > { PROTOX_SIMPLE(SimpleUnsigned32BE) };

    struct SimpleUnsigned64BE : simple< UnsignedInt64BE > { PROTOX_SIMPLE(SimpleUnsigned64BE) };
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE( test_encode_UnsignedInt64BE ) {
    using namespace t3;
    protox::io::byte_data_sink sink;

    SimpleUnsigned64BE uint64BE = 3684294UL;
    sink.encode(uint64BE);

    BOOST_CHECK(sink.size() == 8);

    SimpleUnsigned32BE lowBytes = SYS_NTOHL(*((SimpleUnsigned32BE *) (sink.getDataBuffer() + 4)));

    SimpleUnsigned32BE highBytes = SYS_NTOHL(*((SimpleUnsigned32BE *) sink.getDataBuffer()));

    SimpleUnsigned64BE value = 0;
    char *vp = (char *) &value;
    vp[0] = sink.getDataBuffer()[7];
    vp[1] = sink.getDataBuffer()[6];
    vp[2] = sink.getDataBuffer()[5];
    vp[3] = sink.getDataBuffer()[4];
    vp[4] = sink.getDataBuffer()[3];
    vp[5] = sink.getDataBuffer()[2];
    vp[6] = sink.getDataBuffer()[1];
    vp[7] = sink.getDataBuffer()[0];

    BOOST_CHECK(value == 3684294UL);
}

/**********************************************************************************************************************/

namespace t4 {
    using namespace protox::dtl;
    using namespace test::custom;

    struct SimpleUnsigned16BE : simple< UnsignedInt16BE > { PROTOX_SIMPLE(SimpleUnsigned16BE) };
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_decode_Unsigned16BE) {
    using namespace t4;
    protox::io::byte_data_sink sink;

    SimpleUnsigned16BE uint16BE = 23171;
    sink.encode(uint16BE);

    BOOST_CHECK(sink.size() == 2);
    BOOST_CHECK(ntohs(*((SimpleUnsigned16BE *) sink.getDataBuffer())) == 23171);

    protox::io::byte_data_source source(sink);
    SimpleUnsigned16BE uint16BE_d = 0;
    source.decode(uint16BE_d);

    BOOST_CHECK(uint16BE_d == 23171);
}

/**********************************************************************************************************************/

namespace t5 {
    using namespace protox::dtl;
    using namespace test::custom;

    struct SimpleUnsigned32BE : simple< UnsignedInt32BE > { PROTOX_SIMPLE(SimpleUnsigned32BE) };
 }

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_decode_HLAinteger32BE) {
    using namespace t5;
    protox::io::byte_data_sink sink;

    SimpleUnsigned32BE uint32BE = 36894;
    sink.encode(uint32BE);

    BOOST_CHECK(sink.size() == 4);

    SimpleUnsigned32BE value = SYS_NTOHL(*((SimpleUnsigned32BE *) sink.getDataBuffer()));

    BOOST_CHECK(value == 36894);

    protox::io::byte_data_source source(sink);
    SimpleUnsigned32BE uint32BE_d = 0;
    source.decode(uint32BE_d);

    BOOST_CHECK(uint32BE_d == 36894);
}

/**********************************************************************************************************************/

namespace t6 {
    using namespace protox::dtl;
    using namespace test::custom;

    struct SimpleUnsigned64BE : simple< UnsignedInt64BE > { PROTOX_SIMPLE(SimpleUnsigned64BE) };
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_decode_HLAinteger64BE) {
    using namespace t6;
    protox::io::byte_data_sink sink;

    SimpleUnsigned64BE uint64BE = 3386894UL;
    sink.encode(uint64BE);

    BOOST_CHECK(sink.size() == 8);

    protox::io::byte_data_source source(sink);
    SimpleUnsigned64BE uint64BE_d = 0;
    source.decode(uint64BE_d);

    BOOST_CHECK(uint64BE_d == 3386894UL);
}
