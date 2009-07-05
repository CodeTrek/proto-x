/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef SOM_RESTAURANT_INTER_CLASS_TABLE_HPP
#define SOM_RESTAURANT_INTER_CLASS_TABLE_HPP

/******************************************************************************/

#include <protox/hla/i_class.hpp>
#include <protox/hla/keywords.hpp>

#include <test/protox/hla/som/restaurant/parameter_table.hpp>

/******************************************************************************/

namespace som { namespace restaurant {

/******************************************************************************/

using namespace protox::hla;

/******************************************************************************/

//// Interaction Class Table /////////////////////////////////////////////////
   struct inter_class_table : i_class< HLAinteractionRoot, none, child<
// +-------------------------------+-------------------------------+
// | Class 1                       | Class 2                       |
// +-------------------------------+-------------------------------+
     i_class< CustomerTransaction,
     none,
//                                 +-------------------------------+
                                     child< i_class< CustomerSeated,  params< TimeSeated > >,
//                                 +-------------------------------+
                                            i_class< FoodServed,      params< TemperatureOk, AccuracyOk, TimelinessOk > > > > > > {};
// +-------------------------------+-------------------------------+

/******************************************************************************/

}}

/******************************************************************************/

#endif

/******************************************************************************/
