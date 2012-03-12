/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_ARTICULATED_PARTS_TYPE_ENUM32_HPP
#define PROTOX_OM_RPR_ARTICULATED_PARTS_TYPE_ENUM32_HPP

/**********************************************************************************************************************/

#include "protox/dtl/enum_pp.hpp"

#include "protox/hla_13/enumerated.hpp"
#include "protox/hla_13/basic_data_representation_table.hpp"

/**********************************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**********************************************************************************************************************/

using namespace protox;
using namespace protox::hla_13;

/**********************************************************************************************************************/

//      +----------------------------+----------------------------------------------------------+-----------------------------+--------+
//      | Name                       | Representation                                           | Enumerator                  | Values |
//      +----------------------------+----------------------------------------------------------+-----------------------------+--------+
namespace ArticulatedPartsTypeEnum32 { PROTOX_ENUM_TYPE(HLA13unsigned_long, hla_13::enumerated) ;
                                                                               PROTOX_ENUM_VALUE( Other,                            0 );
                                                                               PROTOX_ENUM_VALUE( Rudder,                        1024 );
                                                                               PROTOX_ENUM_VALUE( LeftFlap ,                     1056 );
                                                                               PROTOX_ENUM_VALUE( RightFlap,                     1088 );
                                                                               PROTOX_ENUM_VALUE( LeftAileron,                   1120 );
                                                                               PROTOX_ENUM_VALUE( RightAileron,                  1152 );
                                                                               PROTOX_ENUM_VALUE( HelicopterMainRotor,           1184 );
                                                                               PROTOX_ENUM_VALUE( HelicopterTailRotor,           1216 );
                                                                               PROTOX_ENUM_VALUE( OtherAircraftControlSurfaces,  1248 );
                                                                               PROTOX_ENUM_VALUE( Periscope,                     2048 );
                                                                               PROTOX_ENUM_VALUE( GenericAntenna,                2080 );
                                                                               PROTOX_ENUM_VALUE( Snorkel,                       2112 );
                                                                               PROTOX_ENUM_VALUE( OtherExtendableParts,          2144 );
                                                                               PROTOX_ENUM_VALUE( LandingGear,                   3072 );
                                                                               PROTOX_ENUM_VALUE( TailHook,                      3104 );
                                                                               PROTOX_ENUM_VALUE( SpeedBrake,                    3136 );
                                                                               PROTOX_ENUM_VALUE( LeftWeaponBayDoors,            3168 );
                                                                               PROTOX_ENUM_VALUE( RightWeaponBayDoors,           3200 );
                                                                               PROTOX_ENUM_VALUE( TankOrAPChatch,                3232 );
                                                                               PROTOX_ENUM_VALUE( Wingsweep,                     3264 );
                                                                               PROTOX_ENUM_VALUE( BridgeLauncher,                3296 );
                                                                               PROTOX_ENUM_VALUE( BridgeSection1,                3328 );
                                                                               PROTOX_ENUM_VALUE( BridgeSection2,                3360 );
                                                                               PROTOX_ENUM_VALUE( BridgeSection3,                3392 );
                                                                               PROTOX_ENUM_VALUE( PrimaryBlade1,                 3424 );
                                                                               PROTOX_ENUM_VALUE( PrimaryBlade2,                 3456 );
                                                                               PROTOX_ENUM_VALUE( PrimaryBoom,                   3488 );
                                                                               PROTOX_ENUM_VALUE( PrimaryLauncherArm,            3520 );
                                                                               PROTOX_ENUM_VALUE( OtherFixedPositionParts,       3552 );
                                                                               PROTOX_ENUM_VALUE( PrimaryTurretNumber1,          4096 );
                                                                               PROTOX_ENUM_VALUE( PrimaryTurretNumber2,          4128 );
                                                                               PROTOX_ENUM_VALUE( PrimaryTurretNumber3,          4160 );
                                                                               PROTOX_ENUM_VALUE( PrimaryTurretNumber4,          4192 );
                                                                               PROTOX_ENUM_VALUE( PrimaryTurretNumber5,          4224 );
                                                                               PROTOX_ENUM_VALUE( PrimaryTurretNumber6,          4256 );
                                                                               PROTOX_ENUM_VALUE( PrimaryTurretNumber7,          4288 );
                                                                               PROTOX_ENUM_VALUE( PrimaryTurretNumber8,          4320 );
                                                                               PROTOX_ENUM_VALUE( PrimaryTurretNumber9,          4352 );
                                                                               PROTOX_ENUM_VALUE( PrimaryTurretNumber10,         4384 );
                                                                               PROTOX_ENUM_VALUE( PrimaryGunNumber1,             4416 );
                                                                               PROTOX_ENUM_VALUE( PrimaryGunNumber2,             4448 );
                                                                               PROTOX_ENUM_VALUE( PrimaryGunNumber3,             4480 );
                                                                               PROTOX_ENUM_VALUE( PrimaryGunNumber4,             4512 );
                                                                               PROTOX_ENUM_VALUE( PrimaryGunNumber5,             4544 );
                                                                               PROTOX_ENUM_VALUE( PrimaryGunNumber6,             4576 );
                                                                               PROTOX_ENUM_VALUE( PrimaryGunNumber7,             4608 );
                                                                               PROTOX_ENUM_VALUE( PrimaryGunNumber8,             4640 );
                                                                               PROTOX_ENUM_VALUE( PrimaryGunNumber9,             4672 );
                                                                               PROTOX_ENUM_VALUE( PrimaryGunNumber10,            4704 );
                                                                               PROTOX_ENUM_VALUE( PrimaryLauncher1,              4736 );
                                                                               PROTOX_ENUM_VALUE( PrimaryLauncher2,              4768 );
                                                                               PROTOX_ENUM_VALUE( PrimaryLauncher3,              4800 );
                                                                               PROTOX_ENUM_VALUE( PrimaryLauncher4,              4832 );
                                                                               PROTOX_ENUM_VALUE( PrimaryLauncher5,              4864 );
                                                                               PROTOX_ENUM_VALUE( PrimaryLauncher6,              4896 );
                                                                               PROTOX_ENUM_VALUE( PrimaryLauncher7,              4928 );
                                                                               PROTOX_ENUM_VALUE( PrimaryLauncher8,              4960 );
                                                                               PROTOX_ENUM_VALUE( PrimaryLauncher9,              4992 );
                                                                               PROTOX_ENUM_VALUE( PrimaryLauncher10,             5024 );
                                                                               PROTOX_ENUM_VALUE( PrimaryDefenseSystems1,        5056 );
                                                                               PROTOX_ENUM_VALUE( PrimaryDefenseSystems2,        5088 );
                                                                               PROTOX_ENUM_VALUE( PrimaryDefenseSystems3,        5120 );
                                                                               PROTOX_ENUM_VALUE( PrimaryDefenseSystems4,        5152 );
                                                                               PROTOX_ENUM_VALUE( PrimaryDefenseSystems5,        5184 );
                                                                               PROTOX_ENUM_VALUE( PrimaryDefenseSystems6,        5216 );
                                                                               PROTOX_ENUM_VALUE( PrimaryDefenseSystems7,        5248 );
                                                                               PROTOX_ENUM_VALUE( PrimaryDefenseSystems8,        5280 );
                                                                               PROTOX_ENUM_VALUE( PrimaryDefenseSystems9,        5312 );
                                                                               PROTOX_ENUM_VALUE( PrimaryDefenseSystems10,       5344 );
                                                                               PROTOX_ENUM_VALUE( PrimaryRadar1,                 5376 );
                                                                               PROTOX_ENUM_VALUE( PrimaryRadar2,                 5408 );
                                                                               PROTOX_ENUM_VALUE( PrimaryRadar3,                 5440 );
                                                                               PROTOX_ENUM_VALUE( PrimaryRadar4,                 5472 );
                                                                               PROTOX_ENUM_VALUE( PrimaryRadar5,                 5504 );
                                                                               PROTOX_ENUM_VALUE( PrimaryRadar6,                 5536 );
                                                                               PROTOX_ENUM_VALUE( PrimaryRadar7,                 5568 );
                                                                               PROTOX_ENUM_VALUE( PrimaryRadar8,                 5600 );
                                                                               PROTOX_ENUM_VALUE( PrimaryRadar9,                 5632 );
                                                                               PROTOX_ENUM_VALUE( PrimaryRadar10,                5664 );
                                                                               PROTOX_ENUM_VALUE( SecondaryTurretNumber1,        5696 );
                                                                               PROTOX_ENUM_VALUE( SecondaryTurretNumber2,        5728 );
                                                                               PROTOX_ENUM_VALUE( SecondaryTurretNumber3,        5760 );
                                                                               PROTOX_ENUM_VALUE( SecondaryTurretNumber4,        5792 );
                                                                               PROTOX_ENUM_VALUE( SecondaryTurretNumber5,        5824 );
                                                                               PROTOX_ENUM_VALUE( SecondaryTurretNumber6,        5856 );
                                                                               PROTOX_ENUM_VALUE( SecondaryTurretNumber7,        5888 );
                                                                               PROTOX_ENUM_VALUE( SecondaryTurretNumber8,        5920 );
                                                                               PROTOX_ENUM_VALUE( SecondaryTurretNumber9,        5952 );
                                                                               PROTOX_ENUM_VALUE( SecondaryTurretNumber10,       5984 );
                                                                               PROTOX_ENUM_VALUE( SecondaryGunNumber1,           6016 );
                                                                               PROTOX_ENUM_VALUE( SecondaryGunNumber2,           6048 );
                                                                               PROTOX_ENUM_VALUE( SecondaryGunNumber3,           6080 );
                                                                               PROTOX_ENUM_VALUE( SecondaryGunNumber4,           6112 );
                                                                               PROTOX_ENUM_VALUE( SecondaryGunNumber5,           6144 );
                                                                               PROTOX_ENUM_VALUE( SecondaryGunNumber6,           6176 );
                                                                               PROTOX_ENUM_VALUE( SecondaryGunNumber7,           6208 );
                                                                               PROTOX_ENUM_VALUE( SecondaryGunNumber8,           6240 );
                                                                               PROTOX_ENUM_VALUE( SecondaryGunNumber9,           6272 );
                                                                               PROTOX_ENUM_VALUE( SecondaryGunNumber10,          6304 );
                                                                               PROTOX_ENUM_VALUE( SecondaryLauncher1,            6336 );
                                                                               PROTOX_ENUM_VALUE( SecondaryLauncher2,            6368 );
                                                                               PROTOX_ENUM_VALUE( SecondaryLauncher3,            6400 );
                                                                               PROTOX_ENUM_VALUE( SecondaryLauncher4,            6432 );
                                                                               PROTOX_ENUM_VALUE( SecondaryLauncher5,            6464 );
                                                                               PROTOX_ENUM_VALUE( SecondaryLauncher6,            6496 );
                                                                               PROTOX_ENUM_VALUE( SecondaryLauncher7,            6528 );
                                                                               PROTOX_ENUM_VALUE( SecondaryLauncher8,            6560 );
                                                                               PROTOX_ENUM_VALUE( SecondaryLauncher9,            6592 );
                                                                               PROTOX_ENUM_VALUE( SecondaryLauncher10,           6624 );
                                                                               PROTOX_ENUM_VALUE( SecondaryDefenseSystems1,      6656 );
                                                                               PROTOX_ENUM_VALUE( SecondaryDefenseSystems2,      6688 );
                                                                               PROTOX_ENUM_VALUE( SecondaryDefenseSystems3,      6720 );
                                                                               PROTOX_ENUM_VALUE( SecondaryDefenseSystems4,      6752 );
                                                                               PROTOX_ENUM_VALUE( SecondaryDefenseSystems5,      6784 );
                                                                               PROTOX_ENUM_VALUE( SecondaryDefenseSystems6,      6816 );
                                                                               PROTOX_ENUM_VALUE( SecondaryDefenseSystems7,      6848 );
                                                                               PROTOX_ENUM_VALUE( SecondaryDefenseSystems8,      6880 );
                                                                               PROTOX_ENUM_VALUE( SecondaryDefenseSystems9,      6912 );
                                                                               PROTOX_ENUM_VALUE( SecondaryDefenseSystems10,     6944 );
                                                                               PROTOX_ENUM_VALUE( SecondaryRadar1,               6976 );
                                                                               PROTOX_ENUM_VALUE( SecondaryRadar2,               7008 );
                                                                               PROTOX_ENUM_VALUE( SecondaryRadar3,               7040 );
                                                                               PROTOX_ENUM_VALUE( SecondaryRadar4,               7072 );
                                                                               PROTOX_ENUM_VALUE( SecondaryRadar5,               7104 );
                                                                               PROTOX_ENUM_VALUE( SecondaryRadar6,               7136 );
                                                                               PROTOX_ENUM_VALUE( SecondaryRadar7,               7168 );
                                                                               PROTOX_ENUM_VALUE( SecondaryRadar8,               7200 );
                                                                               PROTOX_ENUM_VALUE( SecondaryRadar9,               7232 );
                                                                               PROTOX_ENUM_VALUE( SecondaryRadar10,              7264 );
PROTOX_ENUM_EQUALITY_OPERATOR;
PROTOX_ENUM_DEFAULT(Other);

/**********************************************************************************************************************/

}

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
