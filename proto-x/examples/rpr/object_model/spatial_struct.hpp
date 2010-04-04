/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_RPR_SPATIAL_STRUCT_HPP
#define PROTOX_RPR_SPATIAL_STRUCT_HPP

/**************************************************************************************************/

#include <boost/mpl/vector.hpp>

#include <protox/hla_13/complex_type.hpp>
#include <protox/hla_13/basic_data_representation_table.hpp>

#include "./dead_reckoning_algorithm_enum8.hpp"
#include "./pad_7.hpp"
#include "./spatial_static_struct_var.hpp"
#include "./spatial_fp_struct_var.hpp"
#include "./spatial_rp_struct_var.hpp"
#include "./spatial_rv_struct_var.hpp"
#include "./spatial_fv_struct_var.hpp"

/**************************************************************************************************/

namespace protox {
namespace rpr_fom {

/**************************************************************************************************/

using namespace boost;
using namespace protox;
using namespace protox::dtl;
using namespace protox::hla_13;

/**************************************************************************************************/

//      +---------------+------------------------------------------------------------------------------+----------------------+
//      |               | Field                                                                        |                      |
//      | Record        +-------------------------+----------------------------------------------------+ Encoding             |
//      | name          | Name                    | Type                                               |                      |
//      +---------------+-------------------------+----------------------------------------------------+----------------------+
namespace SpatialStruct {
//      +---------------+-------------------------+----------------------------------------------------+
                   struct DeadReckoningAlgorithm  : field< DeadReckoningAlgorithmEnum8::type > {};
//      +---------------+-------------------------+----------------------------------------------------+
                   struct Padding                 : field< Pad_7::type > {};
//      +---------------+-------------------------+----------------------------------------------------+
                   struct SpatialStatic           : field< SpatialStaticStructVar::type > {};
//      +---------------+-------------------------+----------------------------------------------------+
                   struct SpatialFPW              : field< SpatialFPStructVar::type > {};
//      +---------------+-------------------------+----------------------------------------------------+
                   struct SpatialRPW              : field< SpatialRPStructVar::type > {};
//      +---------------+-------------------------+----------------------------------------------------+
                   struct SpatialRVW              : field< SpatialRVStructVar::type > {};
//      +---------------+-------------------------+----------------------------------------------------+
                   struct SpatialFVW              : field< SpatialFVStructVar::type > {};
//      +---------------+-------------------------+----------------------------------------------------+
                   struct SpatialFPB              : field< SpatialFPStructVar::type > {};
//      +---------------+-------------------------+----------------------------------------------------+
                   struct SpatialRPB              : field< SpatialRPStructVar::type > {};
//      +---------------+-------------------------+----------------------------------------------------+
                   struct SpatialRVB              : field< SpatialRVStructVar::type > {};
//      +---------------+-------------------------+----------------------------------------------------+
                   struct SpatialFVB              : field< SpatialFVStructVar::type > {};
//      +---------------+-------------------------+----------------------------------------------------+
                                                                                           struct type : hla_13::complex_type < mpl::vector< DeadReckoningAlgorithm, Padding, SpatialStatic, SpatialFPW, SpatialRPW, SpatialRVW, SpatialFVW, SpatialFPB, SpatialRPB, SpatialRVB, SpatialFVB > > {}; }
//      +----------------------------------------------------------------------------------------------+----------------------+

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/

