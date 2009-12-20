/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_I_CLASS_CHILD_TO_PARENT_MAP_HPP
#define PROTOX_HLA_I_CLASS_CHILD_TO_PARENT_MAP_HPP

/**************************************************************************************************/

#include <map>
#include <RTI.hh>

/**************************************************************************************************/

namespace protox {
namespace hla {

/**************************************************************************************************/

typedef std::map< RTI::InteractionClassHandle,
                  RTI::InteractionClassHandle > i_class_child_to_parent_map;

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
