/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_RPR_OBJ_CLASS_TABLE_HPP
#define PROTOX_RPR_OBJ_CLASS_TABLE_HPP

/**************************************************************************************************/

#include <protox/hla/o_class.hpp>
#include <protox/hla/keywords.hpp>

#include "./attribute_table.hpp"

/**************************************************************************************************/

namespace protox {
namespace rpr_fom {

/**************************************************************************************************/

using namespace protox::hla;

/**************************************************************************************************/

//// Object Class Table ////////////////////////////////////////////////////////
   struct obj_class_table : o_class< HLAobjectRoot, attrs< HLAprivilegeToDeleteObject >, child<
// +----------------------+-------------------------------+-------------------------------+-------------------------------+
// | Class 1              | Class 2                       | Class 3                       | Class 4                       |
// +----------------------+-------------------------------+-------------------------------+-------------------------------+
     o_class< BaseEntity,                                                                                                   attrs< EntityType, EntityIdentifier, IsPartOf, Spatial, RelativeSpatial >,
                     child< o_class< AggregateEntity,                                                                       attrs< AggregateMarking, AggregateState, Dimensions, EntityIdentifiers, AggregateEntity::ForceIdentifier, Formation, NumberOfSilentEntities, NumberOfVariableDatums, SilentAggregates, SilentEntities, SubAggregateIdentifiers, VariableDatums > >,
// +                      +-------------------------------+-------------------------------+-------------------------------+
                            o_class< EnvironmentalEntity,                                                                   attrs< OpacityCode > >,
// +                      +-------------------------------+-------------------------------+-------------------------------+
                            o_class< PhysicalEntity,                                                                        attrs< AcousticSignatureIndex, AlternateEntityType, ArticulatedParametersArray, CamouflageType, DamageState, EngineSmokeOn, FirePowerDisabled, FlamesPresent, ForceIdentifier, HasAmmunitionSupplyCap, HasFuelSupplyCap, HasRecoveryCap, HasRepairCap, Immobilized, InfraredSignatureIndex, IsConcealed, LiveEntityMeasuredSpeed, Marking, PowerPlantOn, PropulsionSystemsData, RadarCrossSectionSignatureIndex, SmokePlumePresent, TentDeployed, TrailingEffectsCode, VectoringNozzleSystemData >,
                                                     child< o_class< Platform,                                              attrs< AfterburnerOn, AntiCollisionLightsOn, BlackOutBrakeLightsOn, BlackOutLightsOn, BrakeLightsOn, FormationLightsOn, HatchState, HeadLightsOn, InteriorLightsOn, LandingLightsOn, LauncherRaised, NavigationLightsOn, RampDeployed, RunningLightsOn, SpotLightsOn, TailLightsOn >,
                                                                                     child< o_class< Aircraft            >,
// +                      +                               +                               +-------------------------------+
                                                                                            o_class< AmphibiousVehicle   >,
// +                      +                               +                               +-------------------------------+
                                                                                            o_class< GroundVehicle       >,
// +                      +                               +                               +-------------------------------+
                                                                                            o_class< MultiDomainPlatform >,
// +                      +                               +                               +-------------------------------+
                                                                                            o_class< Spacecraft          >,
// +                      +                               +                               +-------------------------------+
                                                                                            o_class< SubmersibleVessel   >,
// +                      +                               +                               +-------------------------------+
                                                                                            o_class< SurfaceVessel   > > >,
// +                      +                               +-------------------------------+-------------------------------+
                                                            o_class< Lifeform,                                              attrs< FlashLightsOn, StanceCode, PrimaryWeaponState, SecondaryWeaponState, ComplianceState >,
                                                                                     child< o_class< Human               >,
// +                      +                               +                               +-------------------------------+
                                                                                            o_class< NonHuman        > > >,
// +                      +                               +-------------------------------+-------------------------------+
                                                            o_class< CulturalFeature,                                       attrs< ExternalLightsOn, InternalHeatSourceOn, InternalLightsOn > >,
// +                      +                               +-------------------------------+-------------------------------+
                                                            o_class< Expendables          >,
// +                      +                               +-------------------------------+-------------------------------+
                                                            o_class< Munition,                                              attrs< LauncherFlashPresent > >,
// +                      +                               +-------------------------------+-------------------------------+
                                                            o_class< Radio                >,
// +                      +                               +-------------------------------+-------------------------------+
                                                            o_class< Sensor,                                                attrs< AntennaRaised, BlackoutLightsOn, LightsOn, Sensor::InteriorLightsOn, MissionKill > >,
// +                      +                               +-------------------------------+-------------------------------+
                                                            o_class< Supplies             > > > > > > > {};
// +----------------------+-------------------------------+-------------------------------+-------------------------------+
}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
