/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_1516_VARIANT_RECORD_HPP
#define PROTOX_HLA_1516_VARIANT_RECORD_HPP

/**************************************************************************************************/

#include <protox/dtl/variant_record.hpp>
#include <protox/hla_1516/codec_tags.hpp>

/**************************************************************************************************/

namespace protox {
namespace hla_1516 {

/**************************************************************************************************/

/**
 * Defines an HLA 1516 variant record from the given vector of alternative types.
 *
 * \tparam D_TYPE This record's disriminant type. This type must be an enumerated type.
 * \tparam D_VECTOR This record's vector of descriminants. \sa protox::dtl::discriminant
 * \tparam OTHER (optional) The other alternative.
 *
 * Example:
 *
 * \code
 * // +--------------+-----------------------------------------------+------------------------+------------------------+
 * // |              | Alternative                                   |                        |                        |
 * // | Record Name  +-----------------------------------------------+ Disciminant Enumerator | Encoding               |
 * // |              | Name  | Type                                  |                        |                        |
 * // +--------------+-------+---------------------------------------+------------------------+------------------------+
 * namespace WeekDay {
 *              struct alt_1 : dtl::discriminant<      HLAinteger16BE, mpl::vector< Sun,
 * //                                                                +------------------------+
 *                                                                                  Tue > > {};
 * //                +-------+---------------------------------------+------------------------+
 *              struct alt_2 : dtl::discriminant<      HLAinteger16BE, mpl::vector< Fri > > {};
 * //                +-------+---------------------------------------+------------------------+
 *              struct alt_3 : dtl::discriminant<      HLAoctet,       mpl::vector< Sat > > {};
 * //                +-------+---------------------------------------+------------------------+
 *                                                                                struct type : hla_1516::variant_record< DaysOfWeekEnum16::Type, mpl::vector< alt_1, alt_2, alt_3 >,
 * //                        +---------------------------------------+
 *                            dtl::discriminant_other< HLAfloat32BE > > {};
 * //                        +---------------------------------------+
 *
 * using namespace WeekDay;
 *
 * WeekDay::type week_day;
 *
 * week_day.descriminant = Fri::value();
 * week_day.alt_< alt_2 >( 5 );
 *
 * \endcode
 */

template<
  typename D_Type,
  typename D_Vector,
  typename Other = protox::dtl::discriminant_other_none
>
struct variant_record : protox::dtl::variant_record< D_Type, D_Vector, Other, HLAvariantRecord > {};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
