/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef SOM_RESTAURANT_PARAMETER_TABLE_HPP
#define SOM_RESTAURANT_PARAMETER_TABLE_HPP

/******************************************************************************/

#include <protox/hla/param.hpp>
#include <protox/hla/keywords.hpp>
#include <protox/hla/name.hpp>

/******************************************************************************/

namespace som { namespace restaurant {

/******************************************************************************/

using namespace protox::hla;

/******************************************************************************/

//////// Parameter Table //////////////////////////////////////
//     +------------------------------------------------------+---------------+---------------+--------------------------+
//     | Name                                                 | Parameter     | Datatype      | String Name              |
//     +------------------------------------------------------+---------------+---------------+--------------------------+
  struct HLAinteractionRoot  {HLA_NAME("HLAinteractionRoot")};
//     +------------------------------------------------------+---------------+---------------+--------------------------+
  struct CustomerTransaction {HLA_NAME("CustomerTransaction")};
//     +------------------------------------------------------+---------------+---------------+--------------------------+
  struct CustomerSeated      {HLA_NAME("CustomerSeated")};
                                                         struct TimeSeated    : param < int > { HLA_NAME("TimeSeated")};
//     +------------------------------------------------------+---------------+---------------+--------------------------+
  struct FoodServed          {HLA_NAME("FoodServed")};
                                                         struct TemperatureOk : param < int > { HLA_NAME("TemperatureOk")};
                                                         struct AccuracyOk    : param < int > { HLA_NAME("AccuracyOk")};
                                                         struct TimelinessOk  : param < int > { HLA_NAME("TimelinessOk")};
//     +------------------------------------------------------+---------------+---------------+--------------------------+

/******************************************************************************/

}}

/******************************************************************************/

#endif

/******************************************************************************/