/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROROX_EXAMPLE_RGB_INTER_CLASS_TABLE_HPP
#define PROROX_EXAMPLE_RGB_INTER_CLASS_TABLE_HPP

/**************************************************************************************************/

#include <protox/hla/i_class.hpp>
#include <protox/hla/keywords.hpp>

#include "parameter_table.hpp"

/**************************************************************************************************/

using namespace protox::hla;

/**************************************************************************************************/

//// Interaction Class Table /////////////////////////////////////////////////
   struct inter_class_table : i_class< HLAinteractionRoot, none, child<
// +------------------+
// | Class 1          |
// +------------------+
   i_class< StartMsg,   params< quantity > > > > {};
// +------------------+

/**************************************************************************************************/

#endif

/**************************************************************************************************/
