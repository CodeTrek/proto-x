/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

#ifndef TEST_COLOR_ENUM16_HPP
#define TEST_COLOR_ENUM16_HPP

#include "protox/dtl/enum_pp.hpp"
#include "protox/hla_1516/enumerated.hpp"

#include "protox/hla_1516/basic_data_representation_table.hpp"

namespace test_hla1516 { namespace ColorEnum16
{
  PROTOX_ENUM_TYPE( protox::hla_1516::HLAinteger16BE, protox::hla_1516::enumerated );

  PROTOX_ENUM_VALUE( Red, 1 );
  PROTOX_ENUM_VALUE( Green, 2 );
  PROTOX_ENUM_VALUE( Blue, 3 );
  PROTOX_ENUM_VALUE( Yellow, 4 );

  PROTOX_ENUM_EQUALITY_OPERATOR;
  PROTOX_ENUM_DEFAULT( Blue );
}}

#endif