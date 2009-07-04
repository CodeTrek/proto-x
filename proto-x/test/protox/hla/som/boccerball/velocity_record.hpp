/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef SOM_BOCCERBALL_VELOCITY_RECORD_HPP
#define SOM_BOCCERBALL_VELOCITY_RECORD_HPP

/******************************************************************************/

#include <boost/mpl/vector.hpp>

#include <protox/hla_1516/fixed_record.hpp>

#include <test/protox/hla/som/boccerball/simple_datatype_table.hpp>

/******************************************************************************/

namespace som { namespace boccerball {

/******************************************************************************/

using namespace boost;
using namespace protox;

/******************************************************************************/

//      +----------------+-----------------------------+-----------------------+ 
//      |                | Field                       |                       |
//      | Record         +------+----------------------+ Encoding              |
//      | name           | Name     | Type             |                       |
//      +----------------+----------+------------------+-----------------------+ 
namespace VelocityVector {
//      +----------------+----------+------------------+
                    struct X        : field< Speed > {};
//                       +----------+------------------+
                    struct Y        : field< Speed > {};
//      +----------------+----------+------------------+
                                           struct type : hla_1516::fixed_record < mpl::vector< X, Y > > {}; }
//      +----------------------------------------------+------------------------+

/******************************************************************************/

}}

/******************************************************************************/

#endif

/******************************************************************************/

