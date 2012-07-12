/*
    Copyright (c) 2012 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_FED_MGR_OBJECT_MODEL_ATTRIBUTE_TABLE_HPP
#define PROTOX_FED_MGR_OBJECT_MODEL_ATTRIBUTE_TABLE_HPP

/**********************************************************************************************************************/

#include <protox/hla/attr.hpp>
#include <protox/hla/keywords.hpp>
#include <protox/hla/name.hpp>

#include <protox/fed/mgr/object_model/hla_handle.hpp>

/**********************************************************************************************************************/

namespace protox { namespace fed { namespace mgr { namespace object_model {

/**********************************************************************************************************************/

using namespace protox;
using namespace protox::hla;

/**********************************************************************************************************************/

//   +--------------------------------------------+----------------------------+----------------------------+-----------------------------------------+
//   | Name                                       | Attribute                  | Datatype                   | String Name                             |
//   +--------------------------------------------+----------------------------+----------------------------+-----------------------------------------+
struct HLAobjectRoot { HLA_NAME("HLAobjectRoot") };
                                             struct HLAprivilegeToDeleteObject : attr< hla_1516::HLAoctet > { HLA_NAME("HLAprivilegeToDeleteObject") };
struct HLAmanager    { HLA_NAME("HLAmanager"   ) };
struct HLAfederate   { HLA_NAME("HLAfederate"  ) };
                                             struct HLAfederateHandle          : attr< HLAhandle          > { HLA_NAME("HLAfederateHandle"         ) };
//   +--------------------------------------------+----------------------------+----------------------------+-----------------------------------------+

/**********************************************************************************************************************/

}}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
