/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_XDR_FIXED_LENGTH_OPAQUE_HPP
#define PROTOX_XDR_FIXED_LENGTH_OPAQUE_HPP

/**************************************************************************************************/

#include <protox/dtl/fixed_array.hpp>

#include <protox/xdr/codec_tags.hpp>
#include <protox/xdr/basic_data_representation_table.hpp>

/**************************************************************************************************/

namespace protox {
namespace xdr {

/**************************************************************************************************/

/**
 * Defines an xdr fixed length opaque of size \a N.
 *
 * \tparam N The size of the array i.e., the number of elements.
 *
 * Example:
 *
 * \code
 * //   +------+-------------------------+---------------+
 * //   | Name | Encoding                | Cardinality |
 * //   +------+-------------------------+---------------+
 * struct Data : xdr::fixed_length_opaque< 5             > {};
 * //   +------+-------------------------+---------------+
 *
 * Data data;
 *
 * data[ 0 ] = 0;
 * data[ 1 ] = 1;
 * data[ 2 ] = 2;
 *
 * \endcode
 */

/**************************************************************************************************/

template< int N >
struct fixed_length_opaque : protox::dtl::fixed_array< Opaque, N, xdr_fixed_length_opaque > {};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
