/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef SOM_BOCCERBALL_OBJ_CLASS_TABLE_HPP
#define SOM_BOCCERBALL_OBJ_CLASS_TABLE_HPP

/**********************************************************************************************************************/

#include <protox/hla/o_class.hpp>
#include <protox/hla/keywords.hpp>

#include <test/protox/hla/som/boccerball/attribute_table.hpp>

/**********************************************************************************************************************/

namespace som { namespace boccerball {

/**********************************************************************************************************************/

using namespace protox::hla;

/**********************************************************************************************************************/

////// Object Class Table //////////////////////////////////////////////////////////////////////////////////////////////
struct obj_class_table : o_class< HLAobjectRoot, attrs< HLAprivilegeToDeleteObject >, child<
//   +---------------------+-----------------+
//   | Class 1             | Class 2         |
//   +---------------------+-----------------+
       o_class< Table,                           attrs< Width, Height > >,
       o_class< GameObject ,                     attrs< Position, Velocity, Acceleration >,
                      child< o_class< Target ,   attrs< Target::State > >,
                             o_class< Marble ,   attrs< State > > > >,
//   +---------------------+-----------------+
       o_class< Player,                          attrs< Name, Score >,
                      child< o_class< Human >,
                             o_class< AI,        attrs< SkillLevel > > > > > > {};
//   +---------------------+-----------------+

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
