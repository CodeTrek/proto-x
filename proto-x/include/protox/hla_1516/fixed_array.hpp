/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_1516_FIXED_ARRAY_HPP
#define PROTOX_HLA_1516_FIXED_ARRAY_HPP

/**************************************************************************************************/

#include <protox/dtl/fixed_array.hpp>
#include <protox/hla_1516/codec_tags.hpp>

/**************************************************************************************************/

namespace protox {
namespace hla_1516 {

/**************************************************************************************************/

/**
 * Defines an HLA 1516 fixed array of size \a N with elements of type \a T.
 *
 * \tparam T The array's element type.
 * \tparam N The size of the array i.e., the number of elements.
 *
 * Example:
 *
 * \code
 * //   +----------+----------------------+---------------+-------------+
 * //   | Name     | Encoding             | Element type  | Cardinality |
 * //   +----------+----------------------+---------------+-------------+
 * struct FixedMsg : hla_1516::fixed_array< HLAASCIIchar,   5 > {};
 * //   +----------+----------------------+---------------+-------------+
 *
 * FixedMsg msg;
 *
 * msg[ 0 ] = 'a';
 * msg[ 1 ] = 'b';
 * msg[ 2 ] = 'c';
 *
 * \endcode
 *
 */

template< typename T, int N >
struct fixed_array : protox::dtl::fixed_array< T, N, HLAfixedArray > {};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
