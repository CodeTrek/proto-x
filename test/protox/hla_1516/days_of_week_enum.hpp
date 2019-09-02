/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

#ifndef TEST_HLA_1516_DAYS_OF_WEEK_ENUM16_HPP
#define TEST_HLA_1516_DAYS_OF_WEEK_ENUM16_HPP

/**********************************************************************************************************************/

#include "protox/dtl/enum_pp.hpp"

#include "protox/hla_1516/enumerated.hpp"
#include "protox/hla_1516/basic_data_representation_table.hpp"

/**********************************************************************************************************************/

namespace test_hla1516 { namespace  DaysOfWeekEnum16 {

/**********************************************************************************************************************/

  PROTOX_ENUM_TYPE(protox::hla_1516::HLAinteger16BE, protox::hla_1516::enumerated, 1);

  PROTOX_ENUM_VALUE(Sun, 1);
  PROTOX_ENUM_VALUE(Mon, 2);
  PROTOX_ENUM_VALUE(Tue, 3);
  PROTOX_ENUM_VALUE(Wed, 4);
  PROTOX_ENUM_VALUE(Thr, 5);
  PROTOX_ENUM_VALUE(Fri, 6);
  PROTOX_ENUM_VALUE(Sat, 7);

  // PROTOX_ENUM_EQUALITY_OPERATOR;
  // PROTOX_ENUM_DEFAULT(Sun);

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
