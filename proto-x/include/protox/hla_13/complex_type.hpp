/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_13_COMPLEX_TYPE_HPP
#define PROTOX_HLA_13_COMPLEX_TYPE_HPP

/**************************************************************************************************/

#include <protox/dtl/fixed_record.hpp>
#include <protox/hla_13/codec_tags.hpp>

/**************************************************************************************************/

namespace protox {
namespace hla_13 {

/**************************************************************************************************/

/**
 *
 * Defines an HLA 13 complex type from the given vector of field types.
 *
 * \tparam FIELD_VECTOR This record's field vector.
 *
 * Example:
 *
 * \code
 * //      +----------------+--------------------------------+----------------------+
 * //      |                | Field                          |                      |
 * //      | Record         +----------+---------------------+ Encoding             |
 * //      | name           | Name     | Type                |                      |
 * //      +----------------+----------+---------------------+----------------------+
 * namespace PositionVector {
 * //      +----------------+----------+---------------------+
 *                     struct X        : field< Distance > {};
 * //                       +----------+---------------------+
 *                     struct Y        : field< Distance > {};
 * //      +----------------+----------+---------------------+
 *                                               struct type : hla_13::complex_type < mpl::vector< X, Y > > {}; }
 *
 * using namespace PositionVector;
 *
 * PositionVector::type pos_vec;
 *
 * pos_vec.f_< X >() = 5.0f;
 * pos_vec.f_< Y >() = 5.0f;
 *
 * \endcode
 *
 */
template< typename FIELD_VECTOR >
struct complex_type : protox::dtl::fixed_record< FIELD_VECTOR, HLA13complexType > {};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
