/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_EXAMPLE_RGB_OBJ_CLASS_TABLE_HPP
#define PROTOX_EXAMPLE_RGB_OBJ_CLASS_TABLE_HPP

/******************************************************************************/

#include <protox/hla/o_class.hpp>
#include <protox/hla/keywords.hpp>

#include "attribute_table.hpp"

/******************************************************************************/

using namespace protox::hla;

/******************************************************************************/

//// Object Class Table ////////////////////////////////////////////////////////
   struct obj_class_table : o_class< HLAobjectRoot, attrs< HLAprivilegeToDeleteObject >, child<
// +------------------+
// | Class 1          |
// +------------------+
   o_class< Platform,   attrs< Position, Color > > > > {};
// +------------------+

/**************************************************************************************************/

#endif

/**************************************************************************************************/
