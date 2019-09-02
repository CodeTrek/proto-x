/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_1516_FIXED_RECORD_HPP
#define PROTOX_HLA_1516_FIXED_RECORD_HPP

/**************************************************************************************************/

#include <protox/dtl/fixed_record.hpp>
#include <protox/hla_1516/codec_tags.hpp>

/**************************************************************************************************/

namespace protox {
namespace hla_1516 {

/**************************************************************************************************/

/**
 *
 * Defines an HLA 1516 fixed record from the given vector of field types.
 *
 * \tparam FIELD_VECTOR This record's field vector.
 *
 * Example:
 *
 * \code
 * //      +----------------+--------------------------------+------------------------+
 * //      |                | Field                          |                        |
 * //      | Recor          +----------+---------------------+ Encoding               |
 * //      | name           | Name     | Type                |                        |
 * //      +----------------+----------+---------------------+------------------------+
 * namespace PositionVector {
 * //      +----------------+----------+---------------------+
 *                     struct X        : field< Distance > {};
 *                     struct Y        : field< Distance > {};
 * //      +----------------+----------+---------------------+
 *                                               struct type : hla_1516::fixed_record < mpl::vector< X, Y > > {}; }
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
struct fixed_record : protox::dtl::fixed_record< FIELD_VECTOR, HLAfixedRecord > {};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
