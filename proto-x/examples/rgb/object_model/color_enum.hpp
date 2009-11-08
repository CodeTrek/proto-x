/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_EXAMPLE_RGB_COLOR_ENUM_HPP
#define PROTOX_EXAMPLE_RGB_COLOR_ENUM_HPP

/**************************************************************************************************/

#include "protox/dtl/enum_pp.hpp"

#include "protox/hla_1516/enumerated.hpp"
#include "protox/hla_1516/basic_data_representation_table.hpp"

/**************************************************************************************************/

using namespace protox;
using namespace protox::hla_1516;

/**************************************************************************************************/

//      +------------+-----------------------------------------------+------------+--------+ 
//      | Name       | Representation                                | Enumerator | Values |
//      +------------+-----------------------------------------------+------------+--------+
namespace ColorEnum  { PROTOX_ENUM_TYPE( HLAinteger16BE, hla_1516::enumerated );
//      +------------+-----------------------------------------------+------------+--------+
                                                    PROTOX_ENUM_VALUE( RED,         1     );
//                                                                   +------------+--------+
                                                    PROTOX_ENUM_VALUE( GREEN,       2     );
//                                                                   +------------+--------+
                                                    PROTOX_ENUM_VALUE( BLUE,        3     );
//      +------------+-----------------------------------------------+------------+--------+

PROTOX_ENUM_EQUALITY_OPERATOR;
PROTOX_ENUM_DEFAULT( BLUE );

/**************************************************************************************************/

}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
