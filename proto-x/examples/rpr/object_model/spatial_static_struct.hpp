/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_RPR_SPATIAL_STATIC_STRUCT_HPP
#define PROTOX_RPR_SPATIAL_STATIC_STRUCT_HPP

/**************************************************************************************************/

#include <boost/mpl/vector.hpp>

#include <protox/hla_13/complex_type.hpp>
#include <protox/hla_13/basic_data_representation_table.hpp>

#include "./world_location_struct.hpp"
#include "./boolean_enum.hpp"
#include "./pad_3.hpp"
#include "./orientation_struct.hpp"

/**************************************************************************************************/

using namespace boost;
using namespace protox;
using namespace protox::dtl;
using namespace protox::hla_13;

/**************************************************************************************************/

namespace protox {
namespace rpr_fom {

/**************************************************************************************************/

//      +---------------------+------------------------------------------------------+----------------------+
//      |                     | Field                                                |                      |
//      | Record              +---------------+--------------------------------------+ Encoding             |
//      | name                | Name          | Type                                 |                      |
//      +---------------------+---------------+--------------------------------------+----------------------+
namespace SpatialStaticStruct {
//      +---------------------+---------------+--------------------------------------+
                         struct WorldLocation : field< WorldLocationStruct::type > {};
//                            +---------------+--------------------------------------+
                         struct IsFrozen      : field< BooleanEnum::Type         > {};
//                            +---------------+--------------------------------------+
                         struct Padding       : field< Pad_3::type               > {};
//                            +---------------+--------------------------------------+
                         struct Orientation   : field< OrientationStruct::type   > {};
//      +---------------------+---------------+--------------------------------------+
                                                                         struct type : hla_13::complex_type < mpl::vector<  WorldLocation, IsFrozen, Padding, Orientation > > {};}
//      +----------------------------------------------------------------------------+----------------------+

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/

