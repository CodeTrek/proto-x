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
#include <protox/om/rpr/designator_code_name_enum16.hpp>
#include <protox/om/rpr/rti_object_id_struct.hpp>
#include <protox/om/rpr/designator_code_enum16.hpp>
#include <protox/om/rpr/world_location_struct.hpp>
#include <protox/om/rpr/relative_position_struct.hpp>
#include <protox/om/rpr/beam_function_code_enum8.hpp>
#include <protox/om/rpr/event_identifier_struct.hpp>
#include <protox/om/rpr/emitter_function_code_enum8.hpp>
#include <protox/om/rpr/emitter_type_enum16.hpp>
#include <protox/om/rpr/opacity_code_enum32.hpp>
#include <protox/om/rpr/rti_object_id_array_struct.hpp>
#include <protox/om/rpr/stance_code_enum32.hpp>
#include <protox/om/rpr/weapon_state_enum32.hpp>
#include <protox/om/rpr/articulated_parameter_struct_array.hpp>
#include <protox/om/rpr/camouflage_enum32.hpp>
#include <protox/om/rpr/damage_status_enum32.hpp>
#include <protox/om/rpr/force_identifier_enum8.hpp>
#include <protox/om/rpr/marking_struct.hpp>
#include <protox/om/rpr/trailing_effects_code_enum32.hpp>
#include <protox/om/rpr/hatch_state_enum32.hpp>
#include <protox/om/rpr/receiver_operational_status_enum16.hpp>

/**********************************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**********************************************************************************************************************/

using namespace protox;
using namespace protox::hla;

/**********************************************************************************************************************/

//   +--------------------------------------------------------+-------------------------------+-------------------------------------------+--------------------------------------------+
//   | Name                                                   | Attribute                     | Datatype                                  | String Name                                |
//   +--------------------------------------------------------+-------------------------------+-------------------------------------------+--------------------------------------------+
struct HLAobjectRoot   { HLA_NAME("HLAobjectRoot")           };
//   +--------------------------------------------------------+-------------------------------+-------------------------------------------+--------------------------------------------+
struct BaseEntity      { HLA_NAME("BaseEntity")              };
                                                         struct AccelerationVector            : attr< AngularVelocityVectorStruct::type > { HLA_NAME("AccelerationVector")            };
                                                         struct AngularVelocityVector         : attr< AngularVelocityVectorStruct::type > { HLA_NAME("AngularVelocityVector")         };
                                                         struct DeadReckoningAlgorithm        : attr< DeadReckoningAlgorithmEnum8::type > { HLA_NAME("DeadReckoningAlgorithm")        };
                                                         struct EntityType                    : attr< EntityTypeStruct::type            > { HLA_NAME("EntityType")                    };
                                                         struct EntityIdentifier              : attr< EntityIdentifierStruct::type      > { HLA_NAME("EntityIdentifier")              };
                                                         struct IsFrozen                      : attr< BoolEnum8::type                   > { HLA_NAME("IsFrozen")                      };
                                                         struct Orientation                   : attr< OrientationStruct::type           > { HLA_NAME("Orientation")                   };
                                                         struct WorldLocation                 : attr< WorldLocationStruct::type         > { HLA_NAME("WorldLocation")                 };
                                                         struct VelocityVector                : attr< VelocityVectorStruct::type        > { HLA_NAME("VelocityVector")                };
//   +--------------------------------------------------------+-------------------------------+-------------------------------------------+--------------------------------------------+
struct CulturalFeature { HLA_NAME("CulturalFeature")         };
                                                         struct ExternalLightsOn              : attr< BoolEnum8::type                   > { HLA_NAME("ExternalLightsOn")              };
                                                         struct InternalHeatSourceOn          : attr< BoolEnum8::type                   > { HLA_NAME("InternalHeatSourceOn")          };
                                                         struct InternalLightsOn              : attr< BoolEnum8::type                   > { HLA_NAME("InternalLightsOn")              };
//   +--------------------------------------------------------+-------------------------------+-------------------------------------------+--------------------------------------------+
struct Designator { HLA_NAME("Designator")                   };
                                                         struct CodeName                      : attr< DesignatorCodeNameEnum16::type    > { HLA_NAME("CodeName")                      };
                                                         struct DesignatedObjectIdentifier    : attr< RTIObjectIdStruct::type           > { HLA_NAME("DesignatedObjectIdentifier")    };
                                                         struct DesignatorCode                : attr< DesignatorCodeEnum16::type        > { HLA_NAME("DesignatorCode")                };
                                                         struct DesignatorEmissionWavelength  : attr< hla_13::HLA13float                > { HLA_NAME("DesignatorEmissionWavelength")  };
                                                         struct DesignatorOutputPower         : attr< hla_13::HLA13float                > { HLA_NAME("DesignatorOutputPower")         };
                                                         struct DesignatorSpotLocation        : attr< WorldLocationStruct::type         > { HLA_NAME("DesignatorSpotLocation")        };
                                                      // struct DeadReckoningAlgorithm        : attr< DeadReckoningAlgorithmEnum8::type > { HLA_NAME("DeadReckoningAlgorithm")        };
                                                         struct RelativeSpotLocation          : attr< RelativePositionStruct::type      > { HLA_NAME("RelativeSpotLocation")          };
                                                         struct SpotLinearAccelerationVector  : attr< AccelerationVectorStruct::type    > { HLA_NAME("SpotLinearAccelerationVector")  };
//   +--------------------------------------------------------+-------------------------------+-------------------------------------------+--------------------------------------------+
struct EmbeddedSystem { HLA_NAME("EmbeddedSystem")           };
                                                      // struct EntityIdentifier              : attr< EntityIdentifierStruct::type      > { HLA_NAME("EntityIdentifier")              };
                                                         struct HostObjectIdentifier          : attr< RTIObjectIdStruct::type           > { HLA_NAME("HostObjectIdentifier")          };
                                                         struct RelativePosition              : attr< RelativePositionStruct::type      > { HLA_NAME("RelativePosition")              };
//   +--------------------------------------------------------+-------------------------------+-------------------------------------------+--------------------------------------------+
struct EmitterBeam { HLA_NAME("EmitterBeam")                 };
                                                         struct BeamAzimuthCenter             : attr< hla_13::HLA13float                > { HLA_NAME("BeamAzimuthCenter")             };
                                                         struct BeamAzimuthSweep              : attr< hla_13::HLA13float                > { HLA_NAME("BeamAzimuthSweep")              };
                                                         struct BeamElevationCenter           : attr< hla_13::HLA13float                > { HLA_NAME("BeamElevationCenter")           };
                                                         struct BeamElevationSweep            : attr< hla_13::HLA13float                > { HLA_NAME("BeamElevationSweep")            };
                                                         struct BeamFunctionCode              : attr< BeamFunctionCodeEnum8::type       > { HLA_NAME("BeamFunctionCode")              };
                                                         struct BeamIdentifier                : attr< hla_13::HLA13octet                > { HLA_NAME("BeamIdentifier")                };
                                                         struct BeamParameterIndex            : attr< hla_13::HLA13unsigned_short       > { HLA_NAME("BeamParameterIndex")            };
                                                         struct EffectiveRadiatedPower        : attr< hla_13::HLA13float                > { HLA_NAME("EffectiveRadiatedPower")        };
                                                         struct EmissionFrequency             : attr< hla_13::HLA13float                > { HLA_NAME("EmissionFrequency")             };
                                                         struct EmitterSystemIdentifier       : attr< RTIObjectIdStruct::type           > { HLA_NAME("EmitterSystemIdentifier")       };
                                                         struct EventIdentifier               : attr< EventIdentifierStruct::type       > { HLA_NAME("EventIdentifier")               };
                                                         struct FrequencyRange                : attr< hla_13::HLA13float                > { HLA_NAME("FrequencyRange")                };
                                                         struct PulseRepetitionFrequency      : attr< hla_13::HLA13float                > { HLA_NAME("PulseRepetitionFrequency")      };
                                                         struct PulseWidth                    : attr< hla_13::HLA13float                > { HLA_NAME("PulseWidth")                    };
                                                         struct SweepSynch                    : attr< hla_13::HLA13float                > { HLA_NAME("SweepSynch")                    };
//   +--------------------------------------------------------+-------------------------------+-------------------------------------------+--------------------------------------------+
struct EmitterSystem { HLA_NAME("EmitterSystem")             };
                                                         struct EmitterFunctionCode           : attr< BeamFunctionCodeEnum8::type       > { HLA_NAME("EmitterFunctionCode")           };
                                                         struct EmitterType                   : attr< EmitterTypeEnum16::type           > { HLA_NAME("EmitterType")                   };
                                                         struct EmitterIndex                  : attr< hla_13::HLA13octet                > { HLA_NAME("EmitterIndex")                  };
                                                     //  struct EventIdentifier               : attr< EventIdentifierStruct::type       > { HLA_NAME("EventIdentifier")               };
//   +--------------------------------------------------------+-------------------------------+-------------------------------------------+--------------------------------------------+
struct EnvironmentalEntity { HLA_NAME("EnvironmentalEntity") };
                                                         struct OpacityCode                   : attr< OpacityCodeEnum32::type           > { HLA_NAME("OpacityCode")                   };
//   +--------------------------------------------------------+-------------------------------+-------------------------------------------+--------------------------------------------+
struct JammerBeam { HLA_NAME("JammerBeam")                   };
                                                         struct JammingModeSequence           : attr< hla_13::HLA13unsigned_long        > { HLA_NAME("JammingModeSequence")           };
                                                         struct JammedObjectIdentifiers       : attr< RTIObjectIdArrayStruct::type      > { HLA_NAME("JammedObjectIdentifiers")       };
                                                         struct HighDensityJam                : attr< BoolEnum8::type                   > { HLA_NAME("HighDensityJam")                };
//   +--------------------------------------------------------+-------------------------------+-------------------------------------------+--------------------------------------------+
struct Lifeform { HLA_NAME("Lifeform")                       };
                                                         struct FlashLightsOn                 : attr< BoolEnum8::type                   > { HLA_NAME("FlashLightsOn")                 };
                                                         struct StanceCode                    : attr< StanceCodeEnum32::type            > { HLA_NAME("StanceCode")                    };
                                                         struct PrimaryWeaponState            : attr< WeaponStateEnum32::type           > { HLA_NAME("PrimaryWeaponState")            };
                                                         struct SecondaryWeaponState          : attr< WeaponStateEnum32::type           > { HLA_NAME("SecondaryWeaponState")          };
//   +--------------------------------------------------------+-------------------------------+-------------------------------------------+--------------------------------------------+
struct Munition { HLA_NAME("Munition")                       };
                                                         struct LauncherFlashPresent          : attr< BoolEnum8::type                   > { HLA_NAME("LauncherFlashPresent")          };
//   +--------------------------------------------------------+-------------------------------+-------------------------------------------+--------------------------------------------+
struct PhysicalEntity { HLA_NAME("PhysicalEntity")           };
                                                         struct AlternateEntityType           : attr< EntityTypeStruct::type            > { HLA_NAME("AlternateEntityType")           };
                                                         struct ArticulatedParametersArray    : attr< ArticulatedParameterStructArray   > { HLA_NAME("ArticulatedParametersArray")    };
                                                         struct CamouflageType                : attr< CamouflageEnum32 ::type           > { HLA_NAME("CamouflageType")                };
                                                         struct DamageState                   : attr< DamageStatusEnum32 ::type         > { HLA_NAME("DamageState")                   };
                                                         struct EngineSmokeOn                 : attr< BoolEnum8::type                   > { HLA_NAME("EngineSmokeOn")                 };
                                                         struct FirePowerDisabled             : attr< BoolEnum8::type                   > { HLA_NAME("FirePowerDisabled")             };
                                                         struct FlamesPresent                 : attr< BoolEnum8::type                   > { HLA_NAME("FlamesPresent")                 };
                                                         struct ForceIdentifier               : attr< ForceIdentifierEnum8::type        > { HLA_NAME("ForceIdentifier")               };
                                                         struct HasAmmunitionSupplyCap        : attr< BoolEnum8::type                   > { HLA_NAME("HasAmmunitionSupplyCap")        };
                                                         struct HasFuelSupplyCap              : attr< BoolEnum8::type                   > { HLA_NAME("HasFuelSupplyCap")              };
                                                         struct HasRecoveryCap                : attr< BoolEnum8::type                   > { HLA_NAME("HasRecoveryCap")                };
                                                         struct HasRepairCap                  : attr< BoolEnum8::type                   > { HLA_NAME("HasRepairCap")                  };
                                                         struct Immobilized                   : attr< BoolEnum8::type                   > { HLA_NAME("Immobilized")                   };
                                                         struct IsConcealed                   : attr< BoolEnum8::type                   > { HLA_NAME("IsConcealed")                   };
                                                         struct Marking                       : attr< MarkingStruct::type               > { HLA_NAME("Marking")                       };
                                                         struct PowerPlantOn                  : attr< BoolEnum8::type                   > { HLA_NAME("PowerPlantOn")                  };
                                                         struct SmokePlumePresent             : attr< BoolEnum8::type                   > { HLA_NAME("SmokePlumePresent")             };
                                                         struct TentDeployed                  : attr< BoolEnum8::type                   > { HLA_NAME("TentDeployed")                  };
                                                         struct TrailingEffectsCode           : attr< BoolEnum8::type                   > { HLA_NAME("TrailingEffectsCode")           };
//   +--------------------------------------------------------+-------------------------------+-------------------------------------------+--------------------------------------------+
struct Platform { HLA_NAME("Platform")                       };
                                                         struct AfterburnerOn                 : attr< BoolEnum8::type                   > { HLA_NAME("AfterburnerOn")                 };
                                                         struct AntiCollisionLightsOn         : attr< BoolEnum8::type                   > { HLA_NAME("AntiCollisionLightsOn")         };
                                                         struct BlackOutBrakeLightsOn         : attr< BoolEnum8::type                   > { HLA_NAME("BlackOutBrakeLightsOn")         };
                                                         struct BlackOutLightsOn              : attr< BoolEnum8::type                   > { HLA_NAME("BlackOutLightsOn")              };
                                                         struct BrakeLightsOn                 : attr< BoolEnum8::type                   > { HLA_NAME("BrakeLightsOn")                 };
                                                         struct FormationLightsOn             : attr< BoolEnum8::type                   > { HLA_NAME("FormationLightsOn")             };
                                                         struct HatchState                    : attr< HatchStateEnum32::type            > { HLA_NAME("HatchState")                    };
                                                         struct HeadLightsOn                  : attr< BoolEnum8::type                   > { HLA_NAME("HeadLightsOn")                  };
                                                         struct InteriorLightsOn              : attr< BoolEnum8::type                   > { HLA_NAME("InteriorLightsOn")              };
                                                         struct LandingLightsOn               : attr< BoolEnum8::type                   > { HLA_NAME("LandingLightsOn")               };
                                                         struct LauncherRaised                : attr< BoolEnum8::type                   > { HLA_NAME("LauncherRaised")                };
                                                         struct NavigationLightsOn            : attr< BoolEnum8::type                   > { HLA_NAME("NavigationLightsOn")            };
                                                         struct RampDeployed                  : attr< BoolEnum8::type                   > { HLA_NAME("RampDeployed")                  };
                                                         struct RunningLightsOn               : attr< BoolEnum8::type                   > { HLA_NAME("RunningLightsOn")               };
                                                         struct SpotLightsOn                  : attr< BoolEnum8::type                   > { HLA_NAME("SpotLightsOn")                  };
                                                         struct TailLightsOn                  : attr< BoolEnum8::type                   > { HLA_NAME("TailLightsOn")                  };
//   +--------------------------------------------------------+-------------------------------+-------------------------------------------+--------------------------------------------+
struct RadarBeam { HLA_NAME("RadarBeam")                     };
                                                         struct HighDensityTrack              : attr< BoolEnum8::type                   > { HLA_NAME("HighDensityTrack")              };
                                                         struct TrackObjectIdentifiers        : attr< RTIObjectIdArrayStruct::type      > { HLA_NAME("TrackObjectIdentifiers")        };
//   +--------------------------------------------------------+-------------------------------+-------------------------------------------+--------------------------------------------+
struct RadioReceiver { HLA_NAME("RadioReceiver")             };
                                                         struct RadioIndex                    : attr< hla_13::HLA13unsigned_short       > { HLA_NAME("RadioIndex")                    };
                                                         struct ReceivedPower                 : attr< hla_13::HLA13float                > { HLA_NAME("ReceivedPower")                 };
                                                         struct ReceivedTransmitterIdentifier : attr< RTIObjectIdStruct::type           > { HLA_NAME("ReceivedTransmitterIdentifier") };
/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
