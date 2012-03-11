/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_ANTENNA_PATTERN_STRUCT_HPP
#define PROTOX_OM_RPR_ANTENNA_PATTERN_STRUCT_HPP

/**********************************************************************************************************************/

#include <boost/mpl/vector.hpp>

#include <protox/dtl/pnull.hpp>

#include <protox/hla_13/variant_record.hpp>
#include <protox/hla_13/basic_data_representation_table.hpp>

#include <protox/om/rpr/antenna_pattern_type_enum32.hpp>
#include <protox/om/rpr/beam_antenna_struct.hpp>
#include <protox/om/rpr/spherical_harmonic_antenna_struct.hpp>

/**********************************************************************************************************************/

using namespace boost;
using namespace protox;
using namespace protox::dtl;
using namespace protox::hla_13;

/**********************************************************************************************************************/

namespace protox { namespace om { namespace rpr {

using namespace protox::om::rpr::AntennaPatternTypeEnum32;

/**********************************************************************************************************************/

// +---------------------------+------------------------------------------------------------------------------------+--------------------------------------+-----------------------+
// |                           | Alternative                                                                        |                                      |                       |
// | Record Name               +------------------------------------------------------------------------------------+ Disciminant Enumerator(s)            | Encoding              |
// |                           | Name                     | Type                                                    |                                      |                       |
// +---------------------------+--------------------------+---------------------------------------------------------+--------------------------------------+-----------------------+
namespace AntennaPatternStruct {
                          struct BeamAntenna              : dtl::discriminant< BeamAntennaStruct::type              , mpl::vector< Beam              > > {};
                          struct SphericalHarmonicAntenna : dtl::discriminant< SphericalHarmonicAntennaStruct::type , mpl::vector< SphericalHarmonic > > {};
                                                                                                                                               struct type : hla_13::variant_record< AntennaPatternTypeEnum32::type, mpl::vector< BeamAntenna, SphericalHarmonicAntenna >,
//                                                        +---------------------------------------------------------+
                                                            dtl::discriminant_other< dtl::pnull                     > > {};
//                                                        +---------------------------------------------------------+

}

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
