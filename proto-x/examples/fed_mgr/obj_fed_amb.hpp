
/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_EXAMPLES_FED_MGR_OBJ_FED_AMB
#define PROTOX_EXAMPLES_FED_MGR_OBJ_FED_AMB

/******************************************************************************/

#include <boost/mpl/vector.hpp>

#include <protox/hla/o_class_type.hpp>
#include <protox/hla/object_amb.hpp>

#include "fed_mgr_som.hpp"

/******************************************************************************/

using namespace protox::hla;
using namespace boost;

/******************************************************************************/

typedef o_class_type< fed_mgr_som,
                      q_name< HLAmanager, HLAfederate > >::type federate_type;

/******************************************************************************/

typedef hla::object_amb< mpl::vector< federate_type > >::type obj_amb_type;

/******************************************************************************/

#endif

/******************************************************************************/
