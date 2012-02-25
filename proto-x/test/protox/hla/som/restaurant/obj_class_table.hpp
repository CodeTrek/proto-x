/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef SOM_RESTAURANT_OBJ_CLASS_TABLE_HPP
#define SOM_RESTAURANT_OBJ_CLASS_TABLE_HPP

/**********************************************************************************************************************/

#include <protox/hla/o_class.hpp>
#include <protox/hla/keywords.hpp>

#include <test/protox/hla/som/restaurant/attribute_table.hpp>

/**********************************************************************************************************************/

namespace som { namespace restaurant {

/**********************************************************************************************************************/

using namespace protox::hla;

/**********************************************************************************************************************/

////// Object Class Table //////////////////////////////////////////////////////////////////////////////////////////////
struct obj_class_table : o_class< HLAobjectRoot, attrs< HLAprivilegeToDeleteObject >, child<
//   +-------------------+---------------------+-------------------------+
//   | Class 1           | Class 2             | Class 3                 |
//   +-------------------+---------------------+-------------------------+
       o_class< Employee ,                                                   attrs< PayRate, YearsOfService, HomeNumber, HomeAddress >,
                    child< o_class< Waiter ,                                 attrs< Efficiency, Cheerfulness, State > >,
                           o_class< DishWasher ,                             attrs< CleaningRate > > > >,
//   +-------------------+---------------------+-------------------------+
       o_class< Food     ,                                                   attrs< Price >,
                    child< o_class< Entree,                                  attrs< MenuItem >,
                                          child< o_class< Beef,              attrs< TypeOfCut > >,
                                                 o_class< Seafood > > >,
//   +                   +---------------------+-------------------------+
                           o_class< Dessert > > > > > {};
//   +-------------------+---------------------+-------------------------+

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
