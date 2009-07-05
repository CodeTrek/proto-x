/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef SOM_BOCCERBALL_ATTRIBUTE_TABLE_HPP
#define SOM_BOCCERBALL_ATTRIBUTE_TABLE_HPP

/******************************************************************************/

#include <protox/hla/attr.hpp>
#include <protox/hla/keywords.hpp>
#include <protox/hla/name.hpp>

#include <test/protox/hla/som/boccerball/skill_level_enum.hpp>
#include <test/protox/hla/som/boccerball/marble_state_enum.hpp>
#include <test/protox/hla/som/boccerball/target_state_enum.hpp>
#include <test/protox/hla/som/boccerball/position_record.hpp>
#include <test/protox/hla/som/boccerball/velocity_record.hpp>
#include <test/protox/hla/som/boccerball/acceleration_record.hpp>

#include <test/protox/hla/som/boccerball/ascii_char_array.hpp>

/******************************************************************************/

namespace som { namespace boccerball {

/******************************************************************************/

using namespace protox::hla;

/******************************************************************************/

////// Attribute Table /////////////////////////////////////////////////////////
//     +--------------------------------------------+----------------------------+----------------------------------+--------------------------------------------+
//     | Name                                       | Attribute                  | Datatype                          | String Name                               |
//     +--------------------------------------------+----------------------------+----------------------------------+--------------------------------------------+
  struct HLAobjectRoot {HLA_NAME( "HLAobjectRoot" )};
                                               struct HLAprivilegeToDeleteObject : attr< int >                        {HLA_NAME( "HLAprivilegeToDeleteObject" )};
//     +--------------------------------------------+----------------------------+----------------------------------+--------------------------------------------+
  struct Player        {HLA_NAME( "Player" )};
                                               struct Name                       : attr< ASCIIString >                {HLA_NAME( "Name" )};
//                                                  +----------------------------+----------------------------------+--------------------------------------------+
                                               struct Score                      : attr< Count >                      {HLA_NAME( "Score" )};
//     +--------------------------------------------+----------------------------+----------------------------------+--------------------------------------------+
  struct Human         {HLA_NAME( "Human" )};
//     +--------------------------------------------+----------------------------+----------------------------------+--------------------------------------------+
  struct AI            {HLA_NAME( "AI" )};
                                               struct SkillLevel                 : attr< SkillLevelEnum::Type >       {HLA_NAME( "SkillLevel" )};
//     +--------------------------------------------+----------------------------+----------------------------------+--------------------------------------------+
  struct Table         {HLA_NAME( "Table" )};
                                               struct Width                      : attr< Distance >                   {HLA_NAME( "Width" )};
//                                                  +----------------------------+----------------------------------+--------------------------------------------+
                                               struct Height                     : attr< Distance >                   {HLA_NAME( "Height" )};
//     +--------------------------------------------+----------------------------+----------------------------------+--------------------------------------------+
  struct GameObject    {HLA_NAME( "GameObject" )};
                                               struct Position                   : attr< PositionVector::type >       {HLA_NAME( "Position" )};
//                                                  +----------------------------+----------------------------------+--------------------------------------------+
                                               struct Velocity                   : attr< VelocityVector::type >       {HLA_NAME( "Velocity" )};
//                                                  +----------------------------+----------------------------------+--------------------------------------------+
                                               struct Acceleration               : attr< AccelerationVector::type >   {HLA_NAME( "Acceleration" )};
//     +--------------------------------------------+----------------------------+----------------------------------+--------------------------------------------+
  struct Target        {HLA_NAME( "Target" )
                                               struct State                      : attr< TargetStateEnum::Type >      {HLA_NAME( "State" )}; };
//     +--------------------------------------------+----------------------------+----------------------------------+--------------------------------------------+
  struct Marble        {HLA_NAME( "Marble" )};
                                               struct State                      : attr< MarbleStateEnum::Type >      {HLA_NAME( "State" )};
//     +--------------------------------------------+----------------------------+----------------------------------+--------------------------------------------+

}}

/******************************************************************************/

#endif

/******************************************************************************/
