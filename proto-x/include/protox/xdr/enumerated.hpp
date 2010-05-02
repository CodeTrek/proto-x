/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_XDR_ENUMERATED_HPP
#define PROTOX_XDR_ENUMERATED_HPP

/**************************************************************************************************/

#include <protox/dtl/enumerated.hpp>
#include <protox/dtl/codec_impl.hpp>

#include <protox/xdr/codec_tags.hpp>

/**************************************************************************************************/

namespace protox {
namespace xdr {

/**************************************************************************************************/

/**
 * Defines an XDR enumerated type.
 *
 * \tparam E The concrete enumerated type.
 * \tparam T The basic data type used to represent values of the enumerated type.
 *
 * Example:
 *
 * \code
 * //      +----------------+-------------------------------------------+------------+--------+
 * //      | Name           | Representation                            | Enumerator | Values |
 * //      +----------------+-------------------------------------------+------------+--------+
 * namespace SkillLevelEnum { PROTOX_ENUM_TYPE( Long, enumerated );
 * //      +----------------+-------------------------------------------+------------+--------+
 *                                                     PROTOX_ENUM_VALUE( POOR,        1     );
 * //                                                                   +------------+--------+
 *                                                     PROTOX_ENUM_VALUE( GOOD,        2     );
 * //                                                                   +------------+--------+
 *                                                     PROTOX_ENUM_VALUE( EXCELLENT,   3     );
 * //      +----------------+-------------------------------------------+------------+--------+
 *
 * PROTOX_ENUM_EQUALITY_OPERATOR;
 * PROTOX_ENUM_DEFAULT( GOOD );  }
 *
 * using namespace SkillLevelEnum;
 *
 * SkillLevelEnum::type skillLevel = GOOD::value();
 * \endcode
 *
 * \sa enum_pp.hpp
 */

/**************************************************************************************************/

template< typename E, typename T >
struct enumerated : protox::dtl::enumerated< E, T, protox::xdr::xdr_enumerated >
{
  friend struct protox::dtl::codec_impl< protox::xdr::xdr_enumerated >;

  enumerated() {}
  enumerated( T const v ) : protox::dtl::enumerated< E, T, protox::xdr::xdr_enumerated >( v ) {}
  enumerated( enumerated const &v )
    : protox::dtl::enumerated< E, T, protox::xdr::xdr_enumerated >( v )
  {}
  
  int to_int() const
  {
    return value;
  }
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
