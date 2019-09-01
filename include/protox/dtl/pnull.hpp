/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_DTL_PNULL_HPP
#define PROTOX_DTL_PNULL_HPP

/**********************************************************************************************************************/

#include <protox/dtl/endian_enum.hpp>

#include <protox/null_value/null_tag.hpp>


/**********************************************************************************************************************/

namespace protox { namespace dtl {

/**********************************************************************************************************************/

/**
 * A type generator for a null value.
 *
 * Example:
 *
 * \code
 *       +-------------------+
 *       | Name   | Encoding |
 *       +-------------------+
 *  struct MyNull : pnull {};
 *       +-------------------+
 *
 * \endcode
 *
 */

/**********************************************************************************************************************/

struct pnull {
    typedef protox::null_value::null_tag codec_tag;
    typedef endian::na endianess;
    typedef struct {} value_type;

    enum { size_in_bits = 0 };

    value_type value; // ignored

    bool operator==(const pnull &) const { return true; }
};

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
