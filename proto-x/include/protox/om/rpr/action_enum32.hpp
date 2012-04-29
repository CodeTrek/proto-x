/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_ACTION_ENUM32_HPP
#define PROTOX_OM_RPR_ACTION_ENUM32_HPP

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

//      +--------------+----------------------------------------------------------+-------------------------------------------------+--------+
//      | Name         | Representation                                           | Enumerator                                      | Values |
//      +--------------+----------------------------------------------------------+-------------------------------------------------+--------+
namespace ActionEnum32 { PROTOX_ENUM_TYPE(HLA13unsigned_long, hla_13::enumerated) ;
                                                                 PROTOX_ENUM_VALUE( Other,                                                0 );
                                                                 PROTOX_ENUM_VALUE( LocalStorageOfTheRequestedInformation,                1 );
                                                                 PROTOX_ENUM_VALUE( InformSimulationManagerOfRanOutOfAmmunitionEvent,     2 );
                                                                 PROTOX_ENUM_VALUE( InformSimulationManagerOfKilledInActionEvent,         3 );
                                                                 PROTOX_ENUM_VALUE( InformSimulationManagerOfDamageEvent,                 4 );
                                                                 PROTOX_ENUM_VALUE( InformSimulationManagerOfMobilityDisabledEvent,       5 );
                                                                 PROTOX_ENUM_VALUE( InformSimulationManagerOfFireDisabledEvent,           6 );
                                                                 PROTOX_ENUM_VALUE( InformSimulationManagerOfRanOutOfFuelEvent,           7 );
                                                                 PROTOX_ENUM_VALUE( RecallCheckpointData,                                 8 );
                                                                 PROTOX_ENUM_VALUE( RecallInitialParameters,                              9 );
                                                                 PROTOX_ENUM_VALUE( InitiateTetherLead,                                  10 );
                                                                 PROTOX_ENUM_VALUE( InitiateTetherFollow,                                11 );
                                                                 PROTOX_ENUM_VALUE( Untether,                                            12 );
                                                                 PROTOX_ENUM_VALUE( InitiateServiceStationResupply,                      13 );
                                                                 PROTOX_ENUM_VALUE( InitiateTailgateResupply,                            14 );
                                                                 PROTOX_ENUM_VALUE( InitiateHitchLead,                                   15 );
                                                                 PROTOX_ENUM_VALUE( InitiateHitchFollow,                                 16 );
                                                                 PROTOX_ENUM_VALUE( Unhitch,                                             17 );
                                                                 PROTOX_ENUM_VALUE( Mount,                                               18 );
                                                                 PROTOX_ENUM_VALUE( Dismount,                                            19 );
                                                                 PROTOX_ENUM_VALUE( StartDailyReadinessCheck,                            20 );
                                                                 PROTOX_ENUM_VALUE( StopDailyReadinessCheck,                             21 );
                                                                 PROTOX_ENUM_VALUE( DataQuery,                                           22 );
                                                                 PROTOX_ENUM_VALUE( StatusRequest,                                       23 );
                                                                 PROTOX_ENUM_VALUE( SendObjectStateData,                                 24 );
                                                                 PROTOX_ENUM_VALUE( Reconstitute,                                        25 );
                                                                 PROTOX_ENUM_VALUE( LockSiteConfiguration,                               26 );
                                                                 PROTOX_ENUM_VALUE( UnlockSiteConfiguration,                             27 );
                                                                 PROTOX_ENUM_VALUE( UpdateSiteConfiguration,                             28 );
                                                                 PROTOX_ENUM_VALUE( QuerySiteConfiguration,                              29 );
                                                                 PROTOX_ENUM_VALUE( TetheringInformation,                                30 );
                                                                 PROTOX_ENUM_VALUE( MountIntent,                                         31 );
                                                                 PROTOX_ENUM_VALUE( AcceptSubscription,                                  32 );
                                                                 PROTOX_ENUM_VALUE( Unsubscribe,                                         33 );
                                                                 PROTOX_ENUM_VALUE( TeleportEntity,                                      34 );
                                                                 PROTOX_ENUM_VALUE( ChangeAggregateState,                                35 );
                                                                 PROTOX_ENUM_VALUE( RequestStartPDU,                                     36 );
                                                                 PROTOX_ENUM_VALUE( WakeupGetReadyForInitialization,                     37 );
                                                                 PROTOX_ENUM_VALUE( InitializeInternalParameters,                        38 );
                                                                 PROTOX_ENUM_VALUE( SendPlanData,                                        39 );
                                                                 PROTOX_ENUM_VALUE( SynchronizeInternalClocks,                           40 );
                                                                 PROTOX_ENUM_VALUE( Run,                                                 41 );
                                                                 PROTOX_ENUM_VALUE( SaveInternalParameters,                              42 );
                                                                 PROTOX_ENUM_VALUE( SimulateMalfunction,                                 43 );
                                                                 PROTOX_ENUM_VALUE( JoinExercise,                                        44 );
                                                                 PROTOX_ENUM_VALUE( ResignExercise,                                      45 );
                                                                 PROTOX_ENUM_VALUE( TimeAdvance,                                         46 );
                                                                 PROTOX_ENUM_VALUE( TACCSF_LOS_Request_Type1,                           100 );
                                                                 PROTOX_ENUM_VALUE( TACCSF_LOS_Request_Type2,                           102 );
//      +-------------------------------------------------------------------------+-------------------------------------------------+--------+

PROTOX_ENUM_EQUALITY_OPERATOR;
PROTOX_ENUM_DEFAULT(Other);

}

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
