/**************************************************************************************************/

#ifndef PROTOX_SDX_BASIC_DATA_CODEC_HPP
#define PROTOX_SDX_BASIC_DATA_CODEC_HPP

/**************************************************************************************************/

#include <protox/dtl/codec_interface.hpp>

#include <protox/sdx/codec_tags.hpp>

/**************************************************************************************************/

namespace protox {
namespace dtl {

/**************************************************************************************************/

template<> struct codec_impl< sdx::sdx_portable >
{
  template< typename T >
  struct octet_boundary
  {
    typedef boost::mpl::int_< 1 >::type type;
  };

  template< typename T >
  struct static_size_in_bytes
  {
    typedef boost::mpl::int_< 1 >::type type;
  };

  template< typename T >
  inline static std::size_t dynamic_size( T )
  {
    return static_size_in_bytes< T >::type::value;
  }

  template< typename S, typename T >
  inline static void encode( S &s, const T &value )
  {
    s.push_back( value );
  }

  template< typename S, typename T >
  inline static void decode( T &v, const S &s, std::size_t &offset )
  {
    v = s[ offset ];
    ++offset;
  }
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
