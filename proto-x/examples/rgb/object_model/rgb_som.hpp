/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_EXAMPLE_RGB_SOM_HPP
#define PROTOX_EXAMPLE_RGB_SOM_HPP

/******************************************************************************/

#include <protox/hla/som.hpp>

#include "inter_class_table.hpp"
#include "obj_class_table.hpp"

/******************************************************************************/

typedef protox::hla::som< obj_class_table, inter_class_table > rgb_som;

/******************************************************************************/

#endif

/******************************************************************************/
