/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_BEAM_ANTENNA_STRUCT_HPP
#define PROTOX_OM_RPR_BEAM_ANTENNA_STRUCT_HPP

/**********************************************************************************************************************/

#include <boost/mpl/vector.hpp>

#include <protox/hla_13/complex_type.hpp>
#include <protox/hla_13/basic_data_representation_table.hpp>

#include <protox/om/rpr/orientation_struct.hpp>
#include <protox/om/rpr/reference_system_enum8.hpp>

/**********************************************************************************************************************/

using namespace boost;
using namespace protox;
using namespace protox::dtl;
using namespace protox::hla_13;

/**********************************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**********************************************************************************************************************/

//      +-------------------+-----------------------------------------------------------------------+----------------------+
//      |                   | Field                                                                 |                      |
//      | Record Name       +-------------------------------+---------------------------------------+ Encoding             |
//      |                   | Name                          | Type                                  |                      |
//      +-------------------+-------------------------------+---------------------------------------+----------------------+
namespace BeamAntennaStruct {
                              struct BeamOrientation        : field< OrientationStruct::type    > {};
                              struct BeamAzimuthBeamwidth   : field< HLA13float                 > {};
                              struct BeamElevationBeamwidth : field< HLA13float                 > {};
                              struct ReferenceSystem        : field< ReferenceSystemEnum8::type > {};
                              struct Padding1               : field< HLA13octet                 > {};
                              struct Padding2               : field< HLA13short                 > {};
                              struct Ez                     : field< HLA13float                 > {};
                              struct Ex                     : field< HLA13float                 > {};
                              struct BeamPhaseAngle         : field< HLA13float                 > {};
//      +-------------------+-------------------------------+---------------------------------------+----------------------+
                                                                                        struct type : hla_13::complex_type < mpl::vector< BeamOrientation, BeamAzimuthBeamwidth, BeamElevationBeamwidth, ReferenceSystem, Padding1, Padding2, Ez, Ex, BeamPhaseAngle > > {}; }
//      +-------------------+-------------------------------+---------------------------------------+----------------------+

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
