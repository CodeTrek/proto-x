/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_OBJECT_EVENT_TYPE_HPP
#define PROTOX_HLA_OBJECT_EVENT_TYPE_HPP

/**************************************************************************************************/

/**
 * \file object_event_type.hpp
 *
 * Constants used to identify object event types.
 */

/**************************************************************************************************/

namespace protox {
namespace hla {

/**************************************************************************************************/

enum object_event_type
{
  OBJ_DISCOVERED = 1,
  OBJ_REFLECTED,
  OBJ_REMOVED
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/