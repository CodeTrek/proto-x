/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_1516_VARIABLE_ARRAY_HPP
#define PROTOX_HLA_1516_VARIABLE_ARRAY_HPP

/**************************************************************************************************/

#include <protox/dtl/variable_array.hpp>
#include <protox/hla_1516/codec_tags.hpp>

/**************************************************************************************************/

namespace protox {
namespace hla_1516 {

/**************************************************************************************************/

/**
 * Defines an HLA 1516 variable size array with \a T as the container type.
 *
 * \tparam T The container type used to store the elements of the array.
 *
 * Example:
 *
 * \code
 * //   +-------------+--------------------------------------+-----------------+-------------+
 * //   | Name        | Encoding                             | Element type    | Cardinality |
 * //   +-------------+--------------------------------------+-----------------+-------------+
 * struct ASCIIString : hla_1516::variable_array< std::vector< ASCIIchar > > {}; // Dynamic  |
 * //   +-------------+--------------------------------------+-----------------+-------------+
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
struct variable_array : protox::dtl::variable_array< T, HLAvariableArray > {};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
