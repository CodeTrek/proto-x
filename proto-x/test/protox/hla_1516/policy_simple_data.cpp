/*
    Copyright 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#define BOOST_AUTO_TEST_MAIN

#include <boost/test/included/unit_test_framework.hpp>
#include <boost/test/auto_unit_test.hpp>

/******************************************************************************/

#include <protox/platform.hpp>

#include <boost/mpl/sizeof.hpp>

#include <protox/dtl/simple.hpp>
#include <protox/hla_1516/basic_data_representation_table.hpp>

#include <protox/io/byte_data_sink.hpp>
#include <protox/io/byte_data_source.hpp>

/******************************************************************************/

using namespace boost;
using namespace protox::dtl;
using namespace protox::hla_1516;

/******************************************************************************/

namespace t1
{
  struct SimpleHLAoctet : simple< HLAoctet >
    { PROTOX_SIMPLE( SimpleHLAoctet ) }; 
}

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_encode_HLAoctet )
{
  using namespace t1;

  protox::io::byte_data_sink sink;

  SimpleHLAoctet octet = 'Q';
  sink.encode( octet );

  BOOST_CHECK( sink.size() == 1 );
  BOOST_CHECK( sink.getDataBuffer()[ 0 ] == 'Q' );
}

/******************************************************************************/

namespace t2
{
  struct SimpleHLAoctetPairBE : simple< HLAoctetPairBE >
    { PROTOX_SIMPLE( SimpleHLAoctetPairBE ) }; 

  struct SimpleHLAoctetPairLE : simple< HLAoctetPairLE >
    { PROTOX_SIMPLE( SimpleHLAoctetPairLE ) }; 
}

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_encode_HLAoctetPairBE )
{
  using namespace t2;
  protox::io::byte_data_sink sink;

  SimpleHLAoctetPairBE octet_pair = 'X';
  sink.encode( octet_pair );

  BOOST_CHECK( sink.size() == 2 );
  BOOST_CHECK( sink.getDataBuffer()[ 0 ] == 0 );
  BOOST_CHECK( sink.getDataBuffer()[ 1 ] == 'X' );
}

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_encode_HLAoctetPairLE )
{
  using namespace t2;
  protox::io::byte_data_sink sink;

  SimpleHLAoctetPairLE octet_pair = 'X';
  sink.encode( octet_pair );

  BOOST_CHECK( sink.size() == 2 );
  BOOST_CHECK( sink.getDataBuffer()[ 0 ] == 'X' );
  BOOST_CHECK( sink.getDataBuffer()[ 1 ] == 0 );
}

/******************************************************************************/

namespace t3
{
  struct SimpleHLAinteger16BE : simple< HLAinteger16BE >
    { PROTOX_SIMPLE( SimpleHLAinteger16BE ) }; 

  struct SimpleHLAinteger16LE : simple< HLAinteger16LE >
    { PROTOX_SIMPLE( SimpleHLAinteger16LE ) }; 
}

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_encode_HLAinteger16BE )
{
  using namespace t3;
  protox::io::byte_data_sink sink;

  SimpleHLAinteger16BE int16BE = 23171;
  sink.encode( int16BE );

  BOOST_CHECK( sink.size() == 2 );

  BOOST_CHECK(
    ntohs( *((SimpleHLAinteger16BE *) sink.getDataBuffer()) ) == 23171
  );
}

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_encode_HLAinteger16LE )
{
  using namespace t3;
  protox::io::byte_data_sink sink;

  SimpleHLAinteger16LE int16LE = 23171;
  sink.encode( int16LE );

  BOOST_CHECK( sink.size() == 2 );
  BOOST_CHECK( *((SimpleHLAinteger16LE *) sink.getDataBuffer()) == 23171 );
}

/******************************************************************************/

namespace t4
{
  struct SimpleHLAinteger32BE : simple< HLAinteger32BE >
    { PROTOX_SIMPLE( SimpleHLAinteger32BE ) }; 

  struct SimpleHLAinteger32LE : simple< HLAinteger32LE >
    { PROTOX_SIMPLE( SimpleHLAinteger32LE ) }; 
}

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_encode_HLAinteger32BE )
{
  using namespace t4;
  protox::io::byte_data_sink sink;

  SimpleHLAinteger32BE int32BE = -36894;
  sink.encode( int32BE );

  BOOST_CHECK( sink.size() == 4 );

  SimpleHLAinteger32BE value
    = SYS_NTOHL( *((SimpleHLAinteger32BE *) sink.getDataBuffer()));

  BOOST_CHECK( value == -36894 );
}

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_encode_HLAinteger32LE )
{
  using namespace t4;
  protox::io::byte_data_sink sink;

  SimpleHLAinteger32LE int32LE = -36894;
  sink.encode( int32LE );

  BOOST_CHECK( sink.size() == 4 );
  SimpleHLAinteger32LE value = *((SimpleHLAinteger32LE *) sink.getDataBuffer());
  BOOST_CHECK( value == -36894 );
}

/******************************************************************************/

namespace t5
{
  struct SimpleHLAinteger64BE : simple< HLAinteger64BE >
    { PROTOX_SIMPLE( SimpleHLAinteger64BE ) }; 

  struct SimpleHLAinteger64LE : simple< HLAinteger64LE >
    { PROTOX_SIMPLE( SimpleHLAinteger64LE ) }; 
}

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_encode_HLAinteger64BE )
{
  using namespace t5;
  protox::io::byte_data_sink sink;

  SimpleHLAinteger64BE int64BE = -36894;
  sink.encode( int64BE );

  BOOST_CHECK( sink.size() == 8 );

  SimpleHLAinteger64BE value = 0;
  char *vp = (char *) &value;
  vp[0] = sink.getDataBuffer()[7];
  vp[1] = sink.getDataBuffer()[6];
  vp[2] = sink.getDataBuffer()[5];
  vp[3] = sink.getDataBuffer()[4];
  vp[4] = sink.getDataBuffer()[3];
  vp[5] = sink.getDataBuffer()[2];
  vp[6] = sink.getDataBuffer()[1];
  vp[7] = sink.getDataBuffer()[0];

  BOOST_CHECK( value == -36894 );
}

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_encode_HLAinteger64LE )
{
  using namespace t5;
  protox::io::byte_data_sink sink;

  SimpleHLAinteger64LE int64LE = -36894;
  sink.encode( int64LE );

  BOOST_CHECK( sink.size() == 8 );

  SimpleHLAinteger64LE value = *((SimpleHLAinteger64LE *) sink.getDataBuffer());

  BOOST_CHECK( value == -36894 );
}

/******************************************************************************/

namespace t6
{
  struct SimpleHLAfloat32BE : simple< HLAfloat32BE >
    { PROTOX_SIMPLE( SimpleHLAfloat32BE ) }; 

  struct SimpleHLAfloat32LE : simple< HLAfloat32LE >
    { PROTOX_SIMPLE( SimpleHLAfloat32LE ) }; 

  struct SimpleHLAinteger32BE : simple< HLAinteger32BE >
    { PROTOX_SIMPLE( SimpleHLAinteger32BE ) };
}

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_encode_HLAfloat32BE )
{
  using namespace t6;
  protox::io::byte_data_sink sink;

  SimpleHLAfloat32BE float32BE = 5.67e-3f;
  sink.encode( float32BE );

  BOOST_CHECK( sink.size() == 4 );
  SimpleHLAinteger32BE leValue
    = SYS_NTOHL( *((SimpleHLAinteger32BE *) sink.getDataBuffer()) );

  SimpleHLAfloat32BE *value = (SimpleHLAfloat32BE *) &leValue;

  BOOST_CHECK( ((*value) - 5.67e-3) <= 0.00001 );
}

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_encode_HLAfloat32LE )
{
  using namespace t6;
  protox::io::byte_data_sink sink;

  SimpleHLAfloat32LE float32LE = 5.67e-3f;
  sink.encode( float32LE );

  BOOST_CHECK( sink.size() == 4 );

  SimpleHLAfloat32LE value = *((SimpleHLAfloat32LE *) sink.getDataBuffer());

  BOOST_CHECK( (value - 5.67e-3) <= 0.00001 );
}

/******************************************************************************/

namespace t7
{
  struct SimpleHLAfloat64BE : simple< HLAfloat64BE >
    { PROTOX_SIMPLE( SimpleHLAfloat64BE ) }; 

  struct SimpleHLAfloat64LE : simple< HLAfloat64LE >
    { PROTOX_SIMPLE( SimpleHLAfloat64LE ) }; 
}

/******************************************************************************/

BOOST_AUTO_TEST_CASE( test_encode_HLAfloat64BE )
{
  using namespace t7;
  protox::io::byte_data_sink sink;

  SimpleHLAfloat64BE float64BE = 5.67e-3;
  sink.encode( float64BE );

  BOOST_CHECK( sink.size() == 8 );

  SimpleHLAfloat64BE value;
  char *vp = (char *) &value;

  vp[0] = sink.getDataBuffer()[7];
  vp[1] = sink.getDataBuffer()[6];
  vp[2] = sink.getDataBuffer()[5];
  vp[3] = sink.getDataBuffer()[4];
  vp[4] = sink.getDataBuffer()[3];
  vp[5] = sink.getDataBuffer()[2];
  vp[6] = sink.getDataBuffer()[1];
  vp[7] = sink.getDataBuffer()[0];

  BOOST_CHECK( (value - 5.67e-3) <= 0.00001 );
}

/******************************************************************************/

  BOOST_AUTO_TEST_CASE( test_encode_HLAfloat64LE )
  {
    using namespace t7;
    protox::io::byte_data_sink sink;

    SimpleHLAfloat64LE float64LE = 5.67e-3;
    sink.encode( float64LE );

    BOOST_CHECK( sink.size() == 8 );

    SimpleHLAfloat64LE value = *((SimpleHLAfloat64LE *) sink.getDataBuffer());

    BOOST_CHECK( (value - 5.67e-3) <= 0.00001 );
  }

/******************************************************************************/

  namespace t8
  {
    struct SimpleHLAoctet : simple<HLAoctet> {PROTOX_SIMPLE(SimpleHLAoctet)}; 
  }

/******************************************************************************/

  BOOST_AUTO_TEST_CASE( test_decode_HLAoctet )
  {
    using namespace t8;
    protox::io::byte_data_sink sink;

    SimpleHLAoctet octet = 'Q';
    sink.encode( octet );

    BOOST_CHECK( sink.size() == 1 );
    BOOST_CHECK( sink.getDataBuffer()[0] == 'Q' );

    protox::io::byte_data_source source(sink);

    SimpleHLAoctet octet_d = 0;
    source.decode( octet_d );

    BOOST_CHECK( octet_d == 'Q' );
  }

/******************************************************************************/

  namespace t9
  {
    struct SimpleHLAoctetPairBE : simple<HLAoctetPairBE> {PROTOX_SIMPLE(SimpleHLAoctetPairBE)}; 
    struct SimpleHLAoctetPairLE : simple<HLAoctetPairLE> {PROTOX_SIMPLE(SimpleHLAoctetPairLE)}; 
  }

/******************************************************************************/

  BOOST_AUTO_TEST_CASE( test_decode_HLAoctetPairBE )
  {
    using namespace t9;
    protox::io::byte_data_sink sink;

    SimpleHLAoctetPairBE octet_pair = 'X';
    sink.encode( octet_pair );

    BOOST_CHECK( sink.size() == 2 );
    BOOST_CHECK( sink.getDataBuffer()[0] == 0 );
    BOOST_CHECK( sink.getDataBuffer()[1] == 'X' );

    protox::io::byte_data_source source(sink);

    SimpleHLAoctetPairBE octet_pair_d = 0;
    source.decode( octet_pair_d );

    BOOST_CHECK( octet_pair_d == 'X' );
  }

/******************************************************************************/

  BOOST_AUTO_TEST_CASE( test_decode_HLAoctetPairLE )
  {
    using namespace t9;
    protox::io::byte_data_sink sink;

    SimpleHLAoctetPairLE octet_pair = 'X';
    sink.encode( octet_pair );

    BOOST_CHECK( sink.size() == 2 );
    BOOST_CHECK( sink.getDataBuffer()[0] == 'X' );
    BOOST_CHECK( sink.getDataBuffer()[1] == 0 );

    protox::io::byte_data_source source(sink);

    SimpleHLAoctetPairLE octet_pair_d = 0;
    source.decode( octet_pair_d );

    BOOST_CHECK( octet_pair_d == 'X' );
  }

/******************************************************************************/

  namespace t10
  {
    struct SimpleHLAinteger16BE : simple<HLAinteger16BE> {PROTOX_SIMPLE(SimpleHLAinteger16BE)}; 
    struct SimpleHLAinteger16LE : simple<HLAinteger16LE> {PROTOX_SIMPLE(SimpleHLAinteger16LE)}; 
  }

/******************************************************************************/

  BOOST_AUTO_TEST_CASE( test_decode_HLAinteger16BE )
  {
    using namespace t10;
    protox::io::byte_data_sink sink;

    SimpleHLAinteger16BE int16BE = 23171;
    sink.encode( int16BE );

    BOOST_CHECK( sink.size() == 2 );
    BOOST_CHECK( ntohs( *((SimpleHLAinteger16BE *) sink.getDataBuffer()) ) == 23171 );

    protox::io::byte_data_source source(sink);
    SimpleHLAinteger16BE int16BE_d = 0;
    source.decode( int16BE_d );

    BOOST_CHECK( int16BE_d == 23171 );
  }

/******************************************************************************/

  BOOST_AUTO_TEST_CASE( test_decode_HLAinteger16LE )
  {
    using namespace t10;
    protox::io::byte_data_sink sink;

    SimpleHLAinteger16LE int16LE = 23171;
    sink.encode( int16LE );

    BOOST_CHECK( sink.size() == 2 );
    BOOST_CHECK( *((SimpleHLAinteger16LE *) sink.getDataBuffer()) == 23171 );

    protox::io::byte_data_source source(sink);
    SimpleHLAinteger16LE int16LE_d = 0;
    source.decode( int16LE_d );

    BOOST_CHECK( int16LE_d == 23171 );
  }

/******************************************************************************/

  namespace t11
  {
    struct SimpleHLAinteger32BE : simple<HLAinteger32BE> {PROTOX_SIMPLE(SimpleHLAinteger32BE)}; 
  }

/******************************************************************************/

  BOOST_AUTO_TEST_CASE( test_decode_HLAinteger32BE )
  {
    using namespace t11;
    protox::io::byte_data_sink sink;

    SimpleHLAinteger32BE int32BE = -36894;
    sink.encode( int32BE );

    BOOST_CHECK( sink.size() == 4 );
    SimpleHLAinteger32BE value = SYS_NTOHL( *((SimpleHLAinteger32BE *) sink.getDataBuffer()) );
    BOOST_CHECK( value == -36894 );

    protox::io::byte_data_source source(sink);
    SimpleHLAinteger32BE int32BE_d = 0;
    source.decode( int32BE_d );

    BOOST_CHECK( int32BE_d == -36894 );
  }

/******************************************************************************/

  namespace t12
  {
    struct SimpleHLAinteger64BE : simple<HLAinteger64BE> {PROTOX_SIMPLE(SimpleHLAinteger64BE)}; 
  }

/******************************************************************************/

  BOOST_AUTO_TEST_CASE( test_decode_HLAinteger64BE )
  {
    using namespace t12;
    protox::io::byte_data_sink sink;

    SimpleHLAinteger64BE int64BE = -36894;
    sink.encode( int64BE );

    BOOST_CHECK( sink.size() == 8 );

    protox::io::byte_data_source source(sink);
    SimpleHLAinteger64BE int64BE_d = 0;
    source.decode( int64BE_d );

    BOOST_CHECK( int64BE_d == -36894 );
  }

/******************************************************************************/

  namespace t13
  {
    struct SimpleHLAfloat32BE : simple<HLAfloat32BE> {PROTOX_SIMPLE(SimpleHLAfloat32BE)}; 
    struct SimpleHLAinteger32BE : simple<HLAinteger32BE> {PROTOX_SIMPLE(SimpleHLAinteger32BE)}; 
  }

/******************************************************************************/

  BOOST_AUTO_TEST_CASE( test_decode_HLAfloat32BE )
  {
    using namespace t13;
    protox::io::byte_data_sink sink;

    SimpleHLAfloat32BE float32BE = 5.67e-3f;
    sink.encode( float32BE );

    BOOST_CHECK( sink.size() == 4 );
    SimpleHLAinteger32BE leValue = SYS_NTOHL( *((SimpleHLAinteger32BE *) sink.getDataBuffer()) );

    SimpleHLAfloat32BE *value = (SimpleHLAfloat32BE *) &leValue;

    BOOST_CHECK( ((*value) - 5.67e-3) <= 0.00001 );

    protox::io::byte_data_source source(sink);
    SimpleHLAfloat32BE float32BE_d = 0.0f;
    source.decode( float32BE_d );

    BOOST_CHECK( fabs(float32BE_d - 5.67e-3) <= 0.00001 );
  }

/******************************************************************************/

  namespace t14
  {
    struct SimpleHLAfloat64BE : simple<HLAfloat64BE> {PROTOX_SIMPLE(SimpleHLAfloat64BE)}; 
  }

/******************************************************************************/

  BOOST_AUTO_TEST_CASE( test_decode_HLAfloat64BE )
  {
    using namespace t14;
    protox::io::byte_data_sink sink;

    SimpleHLAfloat64BE float64BE = 5.67e-3;
    sink.encode( float64BE );

    BOOST_CHECK( sink.size() == 8 );

    protox::io::byte_data_source source(sink);
    SimpleHLAfloat64BE float64BE_d = 0.0;
    source.decode( float64BE_d );

    BOOST_CHECK( fabs(float64BE_d - 5.67e-3) <= 0.00001 );
  }
