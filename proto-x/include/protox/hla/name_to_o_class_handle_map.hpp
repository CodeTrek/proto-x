/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_HLA_NAME_TO_O_CLASS_HANDLE_MAP_HPP
#define PROTOX_HLA_NAME_TO_O_CLASS_HANDLE_MAP_HPP

/******************************************************************************/

#include <map>
#include <string>
#include <RTI.hh>

/******************************************************************************/

namespace protox { namespace hla {

/******************************************************************************/

typedef std::map<
  std::string,
  RTI::ObjectClassHandle
> name_to_o_class_handle_map;

/******************************************************************************/

}} // protox::hla

/******************************************************************************/

#endif

/******************************************************************************/
