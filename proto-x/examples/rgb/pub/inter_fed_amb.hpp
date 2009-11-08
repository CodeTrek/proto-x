
/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_EXAMPLES_INTER_FED_AMB
#define PROTOX_EXAMPLES_INTER_FED_AMB

/**************************************************************************************************/

#include <boost/mpl/vector.hpp>

#include <protox/hla/i_class_type.hpp>
#include <protox/hla/interaction_amb.hpp>

#include "rgb_som.hpp"

/**************************************************************************************************/

using namespace protox::hla;
using namespace boost;

/**************************************************************************************************/

typedef i_class_type< rgb_som, q_name< StartMsg > >::type start_msg_type;

/**************************************************************************************************/

typedef hla::interaction_amb< mpl::vector< start_msg_type > >::type inter_amb_type;

/**************************************************************************************************/

#endif

/**************************************************************************************************/
