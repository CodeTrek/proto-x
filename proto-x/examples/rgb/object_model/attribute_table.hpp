/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_EXAMPLE_ATTRIBUTE_TABLE_HPP
#define PROTOX_EXAMPLE_ATTRIBUTE_TABLE_HPP

/******************************************************************************/

#include <protox/hla/attr.hpp>
#include <protox/hla/keywords.hpp>
#include <protox/hla/name.hpp>

#include "color_enum.hpp"
#include "position_vector.hpp"

/******************************************************************************/

using namespace protox;
using namespace protox::hla;

/******************************************************************************/

////// Attribute Table /////////////////////////////////////////////////////////
//     +--------------------------------------------+----------------------------+----------------------------------+-------------------------------------------+
//     | Name                                       | Attribute                  | Datatype                         | String Name                               |
//     +--------------------------------------------+----------------------------+----------------------------------+-------------------------------------------+
  struct HLAobjectRoot {HLA_NAME( "HLAobjectRoot" )};
                                               struct HLAprivilegeToDeleteObject : attr< hla_1516::HLAoctet   >       {HLA_NAME( "HLAprivilegeToDeleteObject" )};
//     +--------------------------------------------+----------------------------+----------------------------------+-------------------------------------------+
  struct Platform      {HLA_NAME( "Platform" )};
                                               struct Position                   : attr< PositionVector::type >       {HLA_NAME( "Position"                   )};
//                                                  +----------------------------+----------------------------------+-------------------------------------------+
                                               struct Color                      : attr< ColorEnum::Type      >       {HLA_NAME( "Color"                      )};
//     +--------------------------------------------+----------------------------+----------------------------------+-------------------------------------------+

/******************************************************************************/

#endif

/******************************************************************************/
