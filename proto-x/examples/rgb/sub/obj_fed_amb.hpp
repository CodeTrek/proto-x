
/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_EXAMPLES_OBJ_FED_AMB
#define PROTOX_EXAMPLES_OBJ_FED_AMB

/******************************************************************************/

#include <boost/mpl/vector.hpp>

#include <protox/hla/o_class_type.hpp>
#include <protox/hla/object_amb.hpp>

#include "rgb_som.hpp"

/******************************************************************************/

using namespace protox::hla;
using namespace boost;

/******************************************************************************/

typedef o_class_type< rgb_som, q_name< Platform > >::type platform_type;

/******************************************************************************/

typedef hla::object_amb< mpl::vector< platform_type > >::type obj_amb_type;

/******************************************************************************/

#endif

/******************************************************************************/
