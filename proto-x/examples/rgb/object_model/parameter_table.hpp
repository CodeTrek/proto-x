/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_EXAMPLE_RGB_PARAMETER_TABLE_HPP
#define PROTOX_EXAMPLE_RGB_PARAMETER_TABLE_HPP

/******************************************************************************/

#include <protox/hla/param.hpp>
#include <protox/hla/keywords.hpp>
#include <protox/hla/name.hpp>

#include "simple_datatype_table.hpp"

/******************************************************************************/

using namespace protox::hla;

/******************************************************************************/

//////// Parameter Table //////////////////////////////////////
//     +------------------------------------------------------+-------------+-----------------+---------------------------+
//     | Name                                                 | Parameter   | Datatype        | String Name               |
//     +------------------------------------------------------+-------------+-----------------+---------------------------+
  struct HLAinteractionRoot {HLA_NAME( "HLAinteractionRoot" )};
//     +------------------------------------------------------+-------------+-----------------+---------------------------+
  struct StartMsg           {HLA_NAME( "StartMsg"           )};
                                                         struct quantity    : param < Int16 >   {HLA_NAME( "quantity" )};
//     +------------------------------------------------------+-------------+-----------------+---------------------------+

/******************************************************************************/

#endif

/******************************************************************************/