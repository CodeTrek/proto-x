/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_13_VARIABLE_ARRAY_HPP
#define PROTOX_HLA_13_VARIABLE_ARRAY_HPP

/**************************************************************************************************/

#include <protox/dtl/variable_array.hpp>
#include <protox/hla_13/codec_tags.hpp>

/**************************************************************************************************/

namespace protox {
namespace hla_13 {

/**************************************************************************************************/

/**
 * Defines an HLA 13 variable size array with \a T as the container type.
 *
 * \tparam T The container type used to store the elements of the array.
 *
 * Example:
 *
 * \code
 * //   +-------------+------------------------------------+-----------------+-------------+
 * //   | Name        | Encodin                            | Element type    | Cardinality |
 * //   +-------------+------------------------------------+-----------------+-------------+
 * struct ASCIIString : hla_13::variable_array< std::vector< ASCIIchar > > {}; // Dynamic  |
 * //   +-------------+------------------------------------+-----------------+-------------+
 *
 * const std::string hw_str = "hello, world";
 *
 * ASCIIString str( hw_str.begin(), hw_str.end() );
 *
 * \endcode
 *
 */

/**************************************************************************************************/

template< typename T >
struct variable_array : protox::dtl::variable_array< T, HLA13variableArray > {};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
