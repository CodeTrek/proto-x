/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_HLA_13_ENUMERATED_HPP
#define PROTOX_HLA_13_ENUMERATED_HPP

/**********************************************************************************************************************/

#include <protox/dtl/enumerated.hpp>
#include <protox/hla_13/codec_tags.hpp>
#include <protox/dtl/codec_impl.hpp>

/**********************************************************************************************************************/

namespace protox {
namespace hla_13 {

/**********************************************************************************************************************/

/**
 * Defines an HLA 13 enumerated type.
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
 * namespace SkillLevelEnum { PROTOX_ENUM_TYPE( HLA13short, enumerated );
 * //      +----------------+-------------------------------------------+------------+--------+
 *                                                     PROTOX_ENUM_VALUE( POOR,        1     );
 *                                                     PROTOX_ENUM_VALUE( GOOD,        2     );
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

/**********************************************************************************************************************/

template< typename E, typename T >
struct enumerated : protox::dtl::enumerated< E, T, HLA13enumerated > {
    friend struct protox::dtl::codec_impl< protox::hla_13::HLA13enumerated >;

    enumerated() {}
    enumerated(T const v) : protox::dtl::enumerated< E, T, HLA13enumerated >(v) {}
    enumerated(enumerated const &v) : protox::dtl::enumerated< E, T, HLA13enumerated >(v) {}
};

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
