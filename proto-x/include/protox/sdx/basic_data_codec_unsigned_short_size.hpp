/**************************************************************************************************/

#ifndef PROTOX_SDX_BASIC_DATA_CODEC_HPP
#define PROTOX_SDX_BASIC_DATA_CODEC_HPP

/**************************************************************************************************/

#include <boost/mpl/int.hpp>

#include <protox/dtl/codec_interface.hpp>
#include <protox/dtl/compute_octet_boundary.hpp>

#include <protox/sdx/codec_tags.hpp>

/**************************************************************************************************/

namespace protox {
namespace dtl {

/**************************************************************************************************/

template<> struct codec_impl< sdx::sdx_unsigned_short >
{
  // ...

  template< typename T >
  struct static_size_in_bytes
  {
    typedef typename
      boost::mpl::int_< (T::size_in_bits/8) + (((T::size_in_bits % 8) == 0) ? 0 : 1) >::type type;
  };

  template< typename T >
  inline static std::size_t dynamic_size( T )
  {
    return static_size_in_bytes< T >::type::value;
  }

  // ...
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
