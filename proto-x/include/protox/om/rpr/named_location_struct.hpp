/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_RPR_NAMED_LOCATION_STRUCT_HPP
#define PROTOX_RPR_NAMED_LOCATION_STRUCT_HPP

/**************************************************************************************************/

#include <boost/mpl/vector.hpp>

#include <protox/hla_13/complex_type.hpp>
#include <protox/hla_13/basic_data_representation_table.hpp>

/**************************************************************************************************/

namespace protox {
namespace rpr_fom {

/**************************************************************************************************/

using namespace boost;
using namespace protox;
using namespace protox::dtl;
using namespace protox::hla_13;

/**************************************************************************************************/

//      +---------------------+------------------------------------------------------------------------------+----------------------+
//      |                     | Field                                                                        |                      |
//      | Record              +-------------------------+----------------------------------------------------+ Encoding             |
//      | name                | Name                    | Type                                               |                      |
//      +---------------------+-------------------------+----------------------------------------------------+----------------------+
namespace NamedLocationStruct {
//      +---------------------+-------------------------+----------------------------------------------------+
                         struct StationNumber           : field< HLA13short > {};
                         struct StationName             : field< HLA13octet > {};
                         struct Padding                 : field< HLA13octet > {};
                         struct RelativeLocation        : field< HLA13octet > {};
                         struct RelativeRangeAndBearing : field< HLA13octet > {};
//      +---------------------+-------------------------+----------------------------------------------------+
                                                                                                 struct type : hla_13::complex_type < mpl::vector< StationNumber, StationName, Padding, RelativeLocation, RelativeRangeAndBearing > > {}; }
//      +----------------------------------------------------------------------------------------------------+----------------------+

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/

