/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_HLA_CLASS_HANDLE_TO_PARAM_HANDLE_MAP_HPP
#define PROTOX_HLA_CLASS_HANDLE_TO_PARAM_HANDLE_MAP_HPP

/******************************************************************************/

#include <map>
#include <string>

#include <RTI.hh>

/******************************************************************************/

namespace protox { namespace hla {

/******************************************************************************/

typedef std::map<
  std::string,
  RTI::ParameterHandle
> param_name_to_handle_map;

/******************************************************************************/

typedef std::map<
  RTI::InteractionClassHandle,
  param_name_to_handle_map
> i_class_handle_to_param_map;

/******************************************************************************/

}} // namespace protox::hla

/******************************************************************************/

#endif

/******************************************************************************/
