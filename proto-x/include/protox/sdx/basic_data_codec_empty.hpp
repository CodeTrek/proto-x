/**************************************************************************************************/

#ifndef PROTOX_SDX_BASIC_DATA_CODEC_HPP
#define PROTOX_SDX_BASIC_DATA_CODEC_HPP

/**************************************************************************************************/

#include <protox/sdx/codec_tags.hpp>

/**************************************************************************************************/

namespace protox {
namespace dtl {

/**************************************************************************************************/

template<> struct codec_impl< sdx::sdx_portable > {};

/**************************************************************************************************/

template<> struct codec_impl< sdx::sdx_unsigned_long > {};

/**************************************************************************************************/

template<> struct codec_impl< sdx::sdx_unsigned_short > {};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
