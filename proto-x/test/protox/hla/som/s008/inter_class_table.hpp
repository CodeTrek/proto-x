/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef SOM_S008_OBJ_CLASS_TABLE_HPP
#define SOM_S008_OBJ_CLASS_TABLE_HPP

/******************************************************************************/

#include <protox/hla/i_class.hpp>
#include <protox/hla/keywords.hpp>

#include <test/protox/hla/som/s008/param_table.hpp>

/******************************************************************************/

namespace som_s008 {

/******************************************************************************/

using namespace protox::hla;

//// Interaction Class Table ///////////////////////////////////////////////////
  struct inter_class_table :
// +-----------------+
// | Class 1         |
// +-----------------+
     i_class< Class_A, params< A1, A2 > > {};
// +-----------------+

/******************************************************************************/

}

/******************************************************************************/

#endif

/******************************************************************************/
