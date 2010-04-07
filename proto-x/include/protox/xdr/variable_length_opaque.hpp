/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_XDR_VARIABLE_LENGTH_OPAQUE_HPP
#define PROTOX_XDR_VARIABLE_LENGTH_OPAQUE_HPP

/**************************************************************************************************/

#include <protox/dtl/variable_array.hpp>

#include <protox/xdr/codec_tags.hpp>
#include <protox/xdr/basic_data_representation_table.hpp>


/**************************************************************************************************/

namespace protox {
namespace xdr {

/**************************************************************************************************/

/**
 * Defines an HLA 13 variable size array with \a T as the container type.
 *
 * \tparam T The container type used to store the elements of the array.
 *
 * Example:
 *
 * \code
 * xdr::variable_length_opaque< 12 > data;
 *
 * data.push_back(0);
 * data.push_back(1);
 * data.push_back(2);
 *
 * \endcode
 *
 */

/**************************************************************************************************/

template< unsigned N = 4294967295 >
struct variable_length_opaque : protox::dtl::variable_array< Opaque, xdr_variable_length_opaque >
{
  static const xdr::UnsignedInteger UPPER_BOUND = N;
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
