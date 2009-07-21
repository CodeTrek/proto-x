/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef SOM_S000_OBJ_CLASS_TABLE_HPP
#define SOM_S000_OBJ_CLASS_TABLE_HPP

/******************************************************************************/

#include <protox/hla/o_class.hpp>
#include <protox/hla/keywords.hpp>

#include <test/protox/hla/som/s000/attribute_table.hpp>

/******************************************************************************/

namespace som { namespace s000 {

/******************************************************************************/

using namespace protox::hla;

//// Object Class Table ////////////////////////////////////////////////////////
  struct obj_class_table :
// +------------------+-------------------------+
// | Class 1          | Class2                  |
// +------------------+-------------------------+
    o_class< Class_A,
               none,
                        child< o_class< Class_B >,
//                    +-------------------------+
                               o_class< Class_C >,
//                    +-------------------------+
                               o_class< Class_D > > > {};
//                    +-------------------------+
// +------------------+

/******************************************************************************/

}}

/******************************************************************************/

#endif

/******************************************************************************/
