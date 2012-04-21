/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_OM_RPR_OBJ_CLASS_TABLE_HPP
#define PROTOX_OM_RPR_OBJ_CLASS_TABLE_HPP

/**************************************************************************************************/

#include <protox/hla/o_class.hpp>
#include <protox/hla/keywords.hpp>

#include <protox/om/rpr/attribute_table.hpp>

/**************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**************************************************************************************************/

using namespace protox::hla;


/**************************************************************************************************/

//// Object Class Table ////////////////////////////////////////////////////////
//   struct obj_class_table : o_class< HLAobjectRoot, attrs< HLAprivilegeToDeleteObject >, child<
   struct obj_class_table : o_class< HLAobjectRoot, none, child<
// +--------------------------+-------------------------------+--------------------------+-------------------------------+
// | Class 1                  | Class 2                       | Class 3                  | Class 4                       |
// +--------------------------+-------------------------------+--------------------------+-------------------------------+
     o_class< BaseEntity,                                                                                                     attrs< AccelerationVector, AngularVelocityVector, DeadReckoningAlgorithm, EntityType, EntityIdentifier, IsFrozen, Orientation, WorldLocation, VelocityVector >,
                         child< o_class< EnvironmentalEntity,                                                                 attrs< OpacityCode > >,
// +                          +-------------------------------+--------------------------+-------------------------------+
                                o_class< PhysicalEntity,                                                                      attrs< AlternateEntityType, ArticulatedParametersArray, CamouflageType, DamageState, EngineSmokeOn, FirePowerDisabled, FlamesPresent, ForceIdentifier, HasAmmunitionSupplyCap, HasFuelSupplyCap, HasRecoveryCap, HasRepairCap, Immobilized, IsConcealed, Marking, PowerPlantOn, SmokePlumePresent, TentDeployed, TrailingEffectsCode >,
                                                         child< o_class< Platform,                                            attrs< AfterburnerOn, AntiCollisionLightsOn, BlackOutBrakeLightsOn, BlackOutLightsOn, BrakeLightsOn, FormationLightsOn, HatchState, HeadLightsOn, InteriorLightsOn, LandingLightsOn, LauncherRaised, NavigationLightsOn, RampDeployed, RunningLightsOn, SpotLightsOn, TailLightsOn >,
                                                                                    child< o_class< Aircraft            >,
                                                                                           o_class< AmphibiousVehicle   >,
                                                                                           o_class< GroundVehicle       >,
                                                                                           o_class< MultiDomainPlatform >,
                                                                                           o_class< Spacecraft          >,
                                                                                           o_class< SubmersibleVessel   >,
                                                                                           o_class< SurfaceVessel       > > >,
// +                          +                               +--------------------------+-------------------------------+
                                                                o_class< Lifeform,                                            attrs< FlashLightsOn, StanceCode, PrimaryWeaponState, SecondaryWeaponState >,
                                                                                    child< o_class< Human               >,
                                                                                           o_class< NonHuman            > > >,
// +                          +                               +--------------------------+-------------------------------+
                                                                o_class< CulturalFeature,                                     attrs< ExternalLightsOn, InternalHeatSourceOn, InternalLightsOn > >,
                                                                o_class< Expendables     >,
                                                                o_class< Munition,                                            attrs< LauncherFlashPresent > >,
                                                                o_class< Radio           >,
                                                                o_class< Sensor,                                              attrs< AntennaRaised, BlackoutLightsOn, LightsOn, InteriorLightsOn, MissionKill > >,
                                                                o_class< Supplies        > > > > >,
// +--------------------------+-------------------------------+--------------------------+-------------------------------+
     o_class< EmbeddedSystem,                                                                                                 attrs< EntityIdentifier, HostObjectIdentifier, RelativePosition >,
                         child< o_class< Designator,                                                                          attrs< CodeName, DesignatedObjectIdentifier, DesignatorCode, DesignatorEmissionWavelength, DesignatorOutputPower, DesignatorSpotLocation, DeadReckoningAlgorithm, RelativeSpotLocation, SpotLinearAccelerationVector > >,
                                o_class< EmitterSystem,                                                                       attrs< EmitterFunctionCode, EmitterType, EmitterIndex, EventIdentifier > >,
                                o_class< RadioReceiver,                                                                       attrs< RadioIndex, ReceivedPower, ReceivedTransmitterIdentifier > >,
                                o_class< RadioTransmitter,                                                                    attrs< AntennaPatternData, CryptographicMode, CryptoSystem, EncryptionKeyIdentifier, Frequency, FrequencyBandwidth, FrequencyHopInUse, ModulationParameters, PsuedoNoiseSpectrumInUse, RadioIndex, RadioInputSource, RadioSystemType, RFModulationSystemType, RFModulationType, TimeHopInUse, TransmittedPower, TransmitterOperationalStatus, WorldLocation > > > >,
// +--------------------------+-------------------------------+--------------------------+-------------------------------+
     o_class< EmitterBeam,                                                                                                    attrs< BeamAzimuthCenter, BeamAzimuthSweep, BeamElevationCenter, BeamElevationSweep, BeamFunctionCode, BeamIdentifier, BeamParameterIndex, EffectiveRadiatedPower, EmissionFrequency, EmitterSystemIdentifier, EventIdentifier, FrequencyRange, PulseRepetitionFrequency, PulseWidth, SweepSynch >,
                         child< o_class< RadarBeam,                                                                           attrs< HighDensityTrack, TrackObjectIdentifiers > >,
                                o_class< JammerBeam,                                                                          attrs< JammingModeSequence, JammedObjectIdentifiers, HighDensityJam > > > > > > {};
// +--------------------------+-------------------------------+--------------------------+-------------------------------+

/**************************************************************************************************/

}}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
