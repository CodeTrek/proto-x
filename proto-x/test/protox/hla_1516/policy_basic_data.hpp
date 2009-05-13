/*
    Copyright 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

#ifndef TEST_PROTOX_HLA_1516_BASIC_DATA_CODEC_HPP
#define TEST_PROTOX_HLA_1516_BASIC_DATA_CODEC_HPP

#include <protox/platform.hpp>

#include <boost/mpl/sizeof.hpp>

#include <protox/hla_1516/basic_data_representation_table.hpp>

#include <protox/io/byte_data_sink.hpp>
#include <protox/io/byte_data_source.hpp>

namespace test_protox_dtl_hla_1516_codec_basic_data
{
  using namespace boost;
  using namespace protox::dtl;
  using namespace protox::hla_1516;

  BOOST_AUTO_TEST_CASE( test_basic_data_representation_table )
  {
    typedef protox::dtl::codec codec;

    // Check static byte sizes for all basic data types.
    BOOST_CHECK( 1 == codec::static_size_in_bytes< HLAoctet >::value );
    BOOST_CHECK( 2 == codec::static_size_in_bytes< HLAoctetPairBE >::value );
    BOOST_CHECK( 2 == codec::static_size_in_bytes< HLAinteger16BE >::value );
    BOOST_CHECK( 4 == codec::static_size_in_bytes< HLAinteger32BE >::value );
    BOOST_CHECK( 8 == codec::static_size_in_bytes< HLAinteger64BE >::value );
    BOOST_CHECK( 4 == codec::static_size_in_bytes< HLAfloat32BE >::value );
    BOOST_CHECK( 8 == codec::static_size_in_bytes< HLAfloat64BE >::value );

    BOOST_CHECK( 2 == codec::static_size_in_bytes< HLAoctetPairLE >::value );
    BOOST_CHECK( 2 == codec::static_size_in_bytes< HLAinteger16LE >::value );
    BOOST_CHECK( 4 == codec::static_size_in_bytes< HLAinteger32LE >::value );
    BOOST_CHECK( 8 == codec::static_size_in_bytes< HLAinteger64LE >::value );
    BOOST_CHECK( 4 == codec::static_size_in_bytes< HLAfloat32LE >::value );
    BOOST_CHECK( 8 == codec::static_size_in_bytes< HLAfloat64LE >::value );

    BOOST_CHECK( (unsigned) mpl::sizeof_<HLAoctet::value_type>::value       == codec::static_size_in_bytes< HLAoctet >::value );
    BOOST_CHECK( (unsigned)  mpl::sizeof_<HLAoctetPairBE::value_type>::value == codec::static_size_in_bytes< HLAoctetPairBE >::value );
    BOOST_CHECK( (unsigned)  mpl::sizeof_<HLAinteger16BE::value_type>::value == codec::static_size_in_bytes< HLAinteger16BE >::value );
    BOOST_CHECK( (unsigned)  mpl::sizeof_<HLAinteger32BE::value_type>::value == codec::static_size_in_bytes< HLAinteger32BE >::value );
    BOOST_CHECK( (unsigned)  mpl::sizeof_<HLAinteger64BE::value_type>::value == codec::static_size_in_bytes< HLAinteger64BE >::value );
    BOOST_CHECK( (unsigned)  mpl::sizeof_<HLAfloat32BE::value_type>::value   == codec::static_size_in_bytes< HLAfloat32BE >::value );
    BOOST_CHECK( (unsigned)  mpl::sizeof_<HLAfloat64BE::value_type>::value   == codec::static_size_in_bytes< HLAfloat64BE >::value );

    BOOST_CHECK( (unsigned)  mpl::sizeof_<HLAoctetPairLE::value_type>::value == codec::static_size_in_bytes< HLAoctetPairLE >::value );
    BOOST_CHECK( (unsigned)  mpl::sizeof_<HLAinteger16LE::value_type>::value == codec::static_size_in_bytes< HLAinteger16LE >::value );
    BOOST_CHECK( (unsigned)  mpl::sizeof_<HLAinteger32LE::value_type>::value == codec::static_size_in_bytes< HLAinteger32LE >::value );
    BOOST_CHECK( (unsigned)  mpl::sizeof_<HLAinteger64LE::value_type>::value == codec::static_size_in_bytes< HLAinteger64LE >::value );
    BOOST_CHECK( (unsigned)  mpl::sizeof_<HLAfloat32LE::value_type>::value   == codec::static_size_in_bytes< HLAfloat32LE >::value );
    BOOST_CHECK( (unsigned)  mpl::sizeof_<HLAfloat64LE::value_type>::value   == codec::static_size_in_bytes< HLAfloat64LE >::value );

    BOOST_CHECK( codec::octet_boundary< HLAoctet >::value       == 1UL );
    BOOST_CHECK( codec::octet_boundary< HLAoctetPairBE >::value == 2UL );
    BOOST_CHECK( codec::octet_boundary< HLAinteger16BE >::value == 2UL );
    BOOST_CHECK( codec::octet_boundary< HLAinteger32BE >::value == 4UL );
    BOOST_CHECK( codec::octet_boundary< HLAinteger64BE >::value == 8UL );
    BOOST_CHECK( codec::octet_boundary< HLAfloat32BE >::value   == 4UL );
    BOOST_CHECK( codec::octet_boundary< HLAfloat64BE >::value   == 8UL );

    BOOST_CHECK( codec::octet_boundary< HLAoctetPairLE >::value == 2UL );
    BOOST_CHECK( codec::octet_boundary< HLAinteger16LE >::value == 2UL );
    BOOST_CHECK( codec::octet_boundary< HLAinteger32LE >::value == 4UL );
    BOOST_CHECK( codec::octet_boundary< HLAinteger64LE >::value == 8UL );
    BOOST_CHECK( codec::octet_boundary< HLAfloat32LE >::value   == 4UL );
    BOOST_CHECK( codec::octet_boundary< HLAfloat64LE >::value   == 8UL );
  }

  BOOST_AUTO_TEST_CASE( test_basic_data_dynamic_size )
  {
    BOOST_CHECK( (unsigned)  codec::dynamic_size(HLAoctet()) ==  (unsigned) codec::static_size_in_bytes< HLAoctet >::value );
    BOOST_CHECK( (unsigned)  codec::dynamic_size(HLAoctetPairBE()) ==  (unsigned) codec::static_size_in_bytes< HLAoctetPairBE >::value );
    BOOST_CHECK( (unsigned)  codec::dynamic_size(HLAinteger16BE()) ==  (unsigned) codec::static_size_in_bytes< HLAinteger16BE >::value );
    BOOST_CHECK( (unsigned)  codec::dynamic_size(HLAinteger32BE()) ==  (unsigned) codec::static_size_in_bytes< HLAinteger32BE >::value );
    BOOST_CHECK( (unsigned)  codec::dynamic_size(HLAinteger64BE()) ==  (unsigned) codec::static_size_in_bytes< HLAinteger64BE >::value );
    BOOST_CHECK( (unsigned)  codec::dynamic_size(HLAfloat32BE()) ==  (unsigned) codec::static_size_in_bytes< HLAfloat32BE >::value );
    BOOST_CHECK( (unsigned)  codec::dynamic_size(HLAfloat64BE()) ==  (unsigned) codec::static_size_in_bytes< HLAfloat64BE >::value );

    BOOST_CHECK( (unsigned)  codec::dynamic_size(HLAoctetPairLE()) ==  (unsigned) codec::static_size_in_bytes< HLAoctetPairLE >::value );
    BOOST_CHECK( (unsigned)  codec::dynamic_size(HLAinteger16LE()) ==  (unsigned) codec::static_size_in_bytes< HLAinteger16LE >::value );
    BOOST_CHECK( (unsigned)  codec::dynamic_size(HLAinteger32LE()) ==  (unsigned) codec::static_size_in_bytes< HLAinteger32LE >::value );
    BOOST_CHECK( (unsigned)  codec::dynamic_size(HLAinteger64LE()) ==  (unsigned) codec::static_size_in_bytes< HLAinteger64LE >::value );
    BOOST_CHECK( (unsigned)  codec::dynamic_size(HLAfloat32LE()) ==  (unsigned) codec::static_size_in_bytes< HLAfloat32LE >::value );
    BOOST_CHECK( (unsigned)  codec::dynamic_size(HLAfloat64LE()) ==  (unsigned) codec::static_size_in_bytes< HLAfloat64LE >::value );
  }

  BOOST_AUTO_TEST_CASE( test_encode_HLAoctet )
  {
    protox::io::byte_data_sink sink;

    HLAoctet octet = 'Q';
    sink.encode( octet );

    BOOST_CHECK( sink.size() == 1 );
    BOOST_CHECK( sink.getDataBuffer()[0] == 'Q' );
  }

  BOOST_AUTO_TEST_CASE( test_encode_HLAoctetPairBE )
  {
    protox::io::byte_data_sink sink;

    HLAoctetPairBE octet_pair = 'X';
    sink.encode( octet_pair );

    BOOST_CHECK( sink.size() == 2 );
    BOOST_CHECK( sink.getDataBuffer()[0] == 0 );
    BOOST_CHECK( sink.getDataBuffer()[1] == 'X' );
  }

  BOOST_AUTO_TEST_CASE( test_encode_HLAinteger16BE )
  {
    protox::io::byte_data_sink sink;

    HLAinteger16BE int16BE = 23171;
    sink.encode( int16BE );

    BOOST_CHECK( sink.size() == 2 );
    BOOST_CHECK( ntohs( *((HLAinteger16BE *) sink.getDataBuffer()) ) == 23171 );
  }

  BOOST_AUTO_TEST_CASE( test_encode_HLAinteger32BE )
  {
    protox::io::byte_data_sink sink;

    HLAinteger32BE int32BE = -36894;
    sink.encode( int32BE );

    BOOST_CHECK( sink.size() == 4 );
    HLAinteger32BE value = SYS_NTOHL( *((HLAinteger32BE *) sink.getDataBuffer()));
    BOOST_CHECK( value == -36894 );
  }

  BOOST_AUTO_TEST_CASE( test_encode_HLAinteger64BE )
  {
    protox::io::byte_data_sink sink;

    HLAinteger64BE int64BE = -36894;
    sink.encode( int64BE );

    BOOST_CHECK( sink.size() == 8 );
    HLAinteger32BE lowBytes = SYS_NTOHL( *((HLAinteger32BE *) (sink.getDataBuffer() + 4)) );
    HLAinteger32BE highBytes = SYS_NTOHL( *((HLAinteger32BE *) sink.getDataBuffer()) );

    HLAinteger64BE value = 0;
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

  BOOST_AUTO_TEST_CASE( test_encode_HLAfloat32BE )
  {
    protox::io::byte_data_sink sink;

    HLAfloat32BE float32BE = 5.67e-3f;
    sink.encode( float32BE );

    BOOST_CHECK( sink.size() == 4 );
    HLAinteger32BE leValue = SYS_NTOHL( *((HLAinteger32BE *) sink.getDataBuffer()) );

    HLAfloat32BE *value = (HLAfloat32BE *) &leValue;

    BOOST_CHECK( ((*value) - 5.67e-3) <= 0.00001 );
  }

  BOOST_AUTO_TEST_CASE( test_encode_HLAfloat64BE )
  {
    protox::io::byte_data_sink sink;

    HLAfloat64BE float64BE = 5.67e-3;
    sink.encode( float64BE );

    BOOST_CHECK( sink.size() == 8 );

    HLAfloat64BE value;
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


  BOOST_AUTO_TEST_CASE( test_decode_HLAoctet )
  {
    protox::io::byte_data_sink sink;

    HLAoctet octet = 'Q';
    sink.encode( octet );

    BOOST_CHECK( sink.size() == 1 );
    BOOST_CHECK( sink.getDataBuffer()[0] == 'Q' );

    protox::io::byte_data_source source(sink);

    HLAoctet octet_d = 0;
    source.decode( octet_d );

    BOOST_CHECK( octet_d == 'Q' );
  }

  BOOST_AUTO_TEST_CASE( test_decode_HLAoctetPairBE )
  {
    protox::io::byte_data_sink sink;

    HLAoctetPairBE octet_pair = 'X';
    sink.encode( octet_pair );

    BOOST_CHECK( sink.size() == 2 );
    BOOST_CHECK( sink.getDataBuffer()[0] == 0 );
    BOOST_CHECK( sink.getDataBuffer()[1] == 'X' );

    protox::io::byte_data_source source(sink);

    HLAoctetPairBE octet_pair_d = 0;
    source.decode( octet_pair_d );

    BOOST_CHECK( octet_pair_d == 'X' );
  }

  BOOST_AUTO_TEST_CASE( test_decode_HLAinteger16BE )
  {
    protox::io::byte_data_sink sink;

    HLAinteger16BE int16BE = 23171;
    sink.encode( int16BE );

    BOOST_CHECK( sink.size() == 2 );
    BOOST_CHECK( ntohs( *((HLAinteger16BE *) sink.getDataBuffer()) ) == 23171 );

    protox::io::byte_data_source source(sink);
    HLAinteger16BE int16BE_d = 0;
    source.decode( int16BE_d );

    BOOST_CHECK( int16BE_d == 23171 );
  }

  BOOST_AUTO_TEST_CASE( test_decode_HLAinteger32BE )
  {
    protox::io::byte_data_sink sink;

    HLAinteger32BE int32BE = -36894;
    sink.encode( int32BE );

    BOOST_CHECK( sink.size() == 4 );
    HLAinteger32BE value = SYS_NTOHL( *((HLAinteger32BE *) sink.getDataBuffer()) );
    BOOST_CHECK( value == -36894 );

    protox::io::byte_data_source source(sink);
    HLAinteger32BE int32BE_d = 0;
    source.decode( int32BE_d );

    BOOST_CHECK( int32BE_d == -36894 );
  }

  BOOST_AUTO_TEST_CASE( test_decode_HLAinteger64BE )
  {
    protox::io::byte_data_sink sink;

    HLAinteger64BE int64BE = -36894;
    sink.encode( int64BE );

    BOOST_CHECK( sink.size() == 8 );

    protox::io::byte_data_source source(sink);
    HLAinteger64BE int64BE_d = 0;
    source.decode( int64BE_d );

    BOOST_CHECK( int64BE_d == -36894 );
  }

  BOOST_AUTO_TEST_CASE( test_decode_HLAfloat32BE )
  {
    protox::io::byte_data_sink sink;

    HLAfloat32BE float32BE = 5.67e-3f;
    sink.encode( float32BE );

    BOOST_CHECK( sink.size() == 4 );
    HLAinteger32BE leValue = SYS_NTOHL( *((HLAinteger32BE *) sink.getDataBuffer()) );

    HLAfloat32BE *value = (HLAfloat32BE *) &leValue;

    BOOST_CHECK( ((*value) - 5.67e-3) <= 0.00001 );

    protox::io::byte_data_source source(sink);
    HLAfloat32BE float32BE_d = 0.0f;
    source.decode( float32BE_d );

    BOOST_CHECK( fabs(float32BE_d - 5.67e-3) <= 0.00001 );
  }

  BOOST_AUTO_TEST_CASE( test_decode_HLAfloat64BE )
  {
    protox::io::byte_data_sink sink;

    HLAfloat64BE float64BE = 5.67e-3;
    sink.encode( float64BE );

    BOOST_CHECK( sink.size() == 8 );

    protox::io::byte_data_source source(sink);
    HLAfloat64BE float64BE_d = 0.0;
    source.decode( float64BE_d );

    BOOST_CHECK( fabs(float64BE_d - 5.67e-3) <= 0.00001 );
  }
}

#endif
