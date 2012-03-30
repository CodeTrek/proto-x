/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_ATTRIBUTE_TABLE_HPP
#define PROTOX_OM_RPR_ATTRIBUTE_TABLE_HPP

/**********************************************************************************************************************/

#include <protox/hla/attr.hpp>
#include <protox/hla/keywords.hpp>
#include <protox/hla/name.hpp>

#include <protox/hla_13/basic_data_representation_table.hpp>

#include <protox/om/rpr/acceleration_vector_struct.hpp>
#include <protox/om/rpr/angular_velocity_vector_struct.hpp>
#include <protox/om/rpr/dead_reckoning_algorithm_enum8.hpp>
#include <protox/om/rpr/entity_type_struct.hpp>
#include <protox/om/rpr/entity_identifier_struct.hpp>
#include <protox/om/rpr/bool_enum8.hpp>
#include <protox/om/rpr/orientation_struct.hpp>
#include <protox/om/rpr/world_location_struct.hpp>
#include <protox/om/rpr/velocity_vector_struct.hpp>

/**********************************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**********************************************************************************************************************/

using namespace protox;
using namespace protox::hla;

/**********************************************************************************************************************/

//   +------------------------------------------------+------------------------+-----------------------------------------+---------------------------------------+
//   | Name                                           | Attribute              | Datatype                                | String Name                           |
//   +------------------------------------------------+------------------------+-----------------------------------------+---------------------------------------+
struct HLAobjectRoot   { HLA_NAME("HLAobjectRoot")   };
//   +------------------------------------------------+------------------------+-----------------------------------------+---------------------------------------+
struct BaseEntity      { HLA_NAME("BaseEntity")      };
                                                 struct AccelerationVector     : attr< AngularVelocityVectorStruct::type > { HLA_NAME("AccelerationVector")     };
                                                 struct AngularVelocityVector  : attr< AngularVelocityVectorStruct::type > { HLA_NAME("AngularVelocityVector")  };
                                                 struct DeadReckoningAlgorithm : attr< DeadReckoningAlgorithmEnum8::type > { HLA_NAME("DeadReckoningAlgorithm") };
                                                 struct EntityType             : attr< EntityTypeStruct::type            > { HLA_NAME("EntityType")             };
                                                 struct EntityIdentifier       : attr< EntityIdentifierStruct::type      > { HLA_NAME("EntityIdentifier")       };
                                                 struct IsFrozen               : attr< BoolEnum8::type                   > { HLA_NAME("IsFrozen")               };
                                                 struct Orientation            : attr< OrientationStruct::type           > { HLA_NAME("Orientation")            };
                                                 struct WorldLocation          : attr< WorldLocationStruct::type         > { HLA_NAME("WorldLocation")          };
                                                 struct VelocityVector         : attr< VelocityVectorStruct::type        > { HLA_NAME("VelocityVector")         };
//   +------------------------------------------------+------------------------+-----------------------------------------+---------------------------------------+
struct CulturalFeature { HLA_NAME("CulturalFeature") };
                                                 struct ExternalLightsOn       : attr< BoolEnum8::type                   > { HLA_NAME("ExternalLightsOn")       };
                                                 struct InternalHeatSourceOn   : attr< BoolEnum8::type                   > { HLA_NAME("InternalHeatSourceOn")   };
                                                 struct InternalLightsOn       : attr< BoolEnum8::type                   > { HLA_NAME("InternalLightsOn")       };
//   +------------------------------------------------+------------------------+-----------------------------------------+---------------------------------------+

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
