/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_NAME_HPP
#define PROTOX_HLA_NAME_HPP

/**************************************************************************************************/

/**
 * \file name.hpp
 *
 * \def HLA_NAME(N)
 *
 * This macro generates a name representation that can be used as part of a class, attribute, or
 * parameter definition. The argument \a N is the string representation of the name.
 *
 * Example:
 *
 * \code
 *
 * HLA_NAME("HLAobjectRoot")
 *
 * \endcode
 */

#define HLA_NAME(N) static char const *name() { return N; }

/**************************************************************************************************/

namespace protox {
namespace hla {

/**************************************************************************************************/

struct null_name { HLA_NAME( "" ) };

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
