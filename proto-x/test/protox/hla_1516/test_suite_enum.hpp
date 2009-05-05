/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

#ifndef TEST_SUITE_ENUM8_HPP
#define TEST_SUITE_ENUM8_HPP

#include "protox/dtl/enum_pp.hpp"

#include "protox/hla_1516/basic_data_representation_table.hpp"
#include "protox/hla_1516/enumerated.hpp"

namespace test_hla1516 { namespace SuiteEnum8
{
  PROTOX_ENUM_TYPE( protox::hla_1516::HLAoctet, protox::hla_1516::enumerated );

  PROTOX_ENUM_VALUE( Heart, 1 );
  PROTOX_ENUM_VALUE( Diamond, 2 );
  PROTOX_ENUM_VALUE( Club, 3 );
  PROTOX_ENUM_VALUE( Spade, 4 );

  PROTOX_ENUM_EQUALITY_OPERATOR;
  PROTOX_ENUM_DEFAULT( Club );
}}

#endif
