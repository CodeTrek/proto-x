/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_1516_BOOLEAN_HPP
#define PROTOX_HLA_1516_BOOLEAN_HPP

/**************************************************************************************************/

#include <protox/dtl/enum_pp.hpp>
#include <protox/hla_1516/basic_data_representation_table.hpp>
#include <protox/hla_1516/enumerated.hpp>

/**************************************************************************************************/

/**
 * \class protox::hla_1516::HLAboolean::Type
 * HLAboolean enumerated type
 */

namespace protox {
namespace hla_1516 {

/**************************************************************************************************/


//      +----------------+-----------------------------------------------+------------+--------+
//      | Name           | Representation                                | Enumerator | Values |
//      +----------------+-----------------------------------------------+------------+--------+
namespace HLAboolean    {PROTOX_ENUM_TYPE( HLAinteger32BE, enumerated, 0 );
//      +----------------+-----------------------------------------------+------------+--------+
                                                        PROTOX_ENUM_VALUE( HLAfalse,        0 );
                                                        PROTOX_ENUM_VALUE( HLAtrue,         1 );
//      +----------------+-----------------------------------------------+------------+--------+


  // PROTOX_ENUM_EQUALITY_OPERATOR;
  // PROTOX_ENUM_DEFAULT( HLAfalse );
}

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
