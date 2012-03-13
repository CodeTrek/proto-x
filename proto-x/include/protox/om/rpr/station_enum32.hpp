/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_STATION_ENUM32_HPP
#define PROTOX_OM_RPR_STATION_ENUM32_HPP

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

//      +---------------+----------------------------------------------------------+------------------+---------+
//      | Name          | Representation                                           | Enumerator       | Values  |
//      +---------------+----------------------------------------------------------+------------------+---------+
namespace StationEnum32 { PROTOX_ENUM_TYPE(HLA13unsigned_long, hla_13::enumerated) ;
                                                                  PROTOX_ENUM_VALUE( Nothing_Empty,           0 );
                                                                  PROTOX_ENUM_VALUE( Fuselage_Station1,     512 );
                                                                  PROTOX_ENUM_VALUE( Fuselage_Station2,     513 );
                                                                  PROTOX_ENUM_VALUE( Fuselage_Station3,     514 );
                                                                  PROTOX_ENUM_VALUE( Fuselage_Station4,     515 );
                                                                  PROTOX_ENUM_VALUE( Fuselage_Station5,     516 );
                                                                  PROTOX_ENUM_VALUE( Fuselage_Station6,     517 );
                                                                  PROTOX_ENUM_VALUE( Fuselage_Station7,     518 );
                                                                  PROTOX_ENUM_VALUE( Fuselage_Station8,     519 );
                                                                  PROTOX_ENUM_VALUE( Fuselage_Station9,     520 );
                                                                  PROTOX_ENUM_VALUE( LeftWingStation1,      640 );
                                                                  PROTOX_ENUM_VALUE( LeftWingStation2,      641 );
                                                                  PROTOX_ENUM_VALUE( LeftWingStation3,      642 );
                                                                  PROTOX_ENUM_VALUE( LeftWingStation4,      643 );
                                                                  PROTOX_ENUM_VALUE( LeftWingStation5,      644 );
                                                                  PROTOX_ENUM_VALUE( LeftWingStation6,      645 );
                                                                  PROTOX_ENUM_VALUE( LeftWingStation7,      646 );
                                                                  PROTOX_ENUM_VALUE( LeftWingStation8,      647 );
                                                                  PROTOX_ENUM_VALUE( LeftWingStation9,      648 );
                                                                  PROTOX_ENUM_VALUE( RightWingStation1,     768 );
                                                                  PROTOX_ENUM_VALUE( RightWingStation2,     769 );
                                                                  PROTOX_ENUM_VALUE( RightWingStation3,     770 );
                                                                  PROTOX_ENUM_VALUE( RightWingStation4,     771 );
                                                                  PROTOX_ENUM_VALUE( RightWingStation5,     772 );
                                                                  PROTOX_ENUM_VALUE( RightWingStation6,     773 );
                                                                  PROTOX_ENUM_VALUE( RightWingStation7,     774 );
                                                                  PROTOX_ENUM_VALUE( RightWingStation8,     775 );
                                                                  PROTOX_ENUM_VALUE( RightWingStation9,     775 );
                                                                  PROTOX_ENUM_VALUE( M16A42_rifle,          896 );
                                                                  PROTOX_ENUM_VALUE( M249_SAW,              897 );
                                                                  PROTOX_ENUM_VALUE( M60_Machine_gun,       898 );
                                                                  PROTOX_ENUM_VALUE( M203_Grenade_Launcher, 899 );
                                                                  PROTOX_ENUM_VALUE( M136_AT4,              900 );
                                                                  PROTOX_ENUM_VALUE( M47_Dragon,            901 );
                                                                  PROTOX_ENUM_VALUE( AAWS_M_Javelin,        902 );
                                                                  PROTOX_ENUM_VALUE( M18A1_Claymore_Mine,   903 );
                                                                  PROTOX_ENUM_VALUE( MK19_Grenade_Launcher, 904 );
                                                                  PROTOX_ENUM_VALUE( M2_Machine_Gun,        905 );
                                                                  PROTOX_ENUM_VALUE( Other_attached_parts,  906 );
PROTOX_ENUM_EQUALITY_OPERATOR;
PROTOX_ENUM_DEFAULT(Nothing_Empty);

/**********************************************************************************************************************/

}

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
