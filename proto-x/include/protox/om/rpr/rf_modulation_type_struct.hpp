/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_RF_MODULATION_TYPE_STRUCT_HPP
#define PROTOX_OM_RPR_RF_MODULATION_TYPE_STRUCT_HPP

/**********************************************************************************************************************/

#include <boost/mpl/vector.hpp>

#include <protox/dtl/pnull.hpp>

#include <protox/hla_13/variant_record.hpp>
#include <protox/hla_13/basic_data_representation_table.hpp>

#include <protox/om/rpr/major_rf_modulation_type_enum16.hpp>

#include <protox/om/rpr/amplitude_modulation_type_enum16.hpp>
#include <protox/om/rpr/amplitude_angle_modulation_type_enum16.hpp>
#include <protox/om/rpr/angle_modulation_type_enum16.hpp>
#include <protox/om/rpr/combination_modulation_type_enum16.hpp>
#include <protox/om/rpr/pulse_modulation_type_enum16.hpp>
#include <protox/om/rpr/unmodulated_type_enum16.hpp>


/**********************************************************************************************************************/

using namespace boost;
using namespace protox;
using namespace protox::dtl;
using namespace protox::hla_13;

/**********************************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**********************************************************************************************************************/

namespace mrfmte16 = protox::om::rpr::MajorRFModulationTypeEnum16;

/**********************************************************************************************************************/

// +-----------------------------+-------------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------------------+
// |                             | Alternative                                                                               |                                                |                                                         |
// | Record Name                 +------------------------------+------------------------------------------------------------+ Disciminant Enumerator(s)                      | Encoding                                                |
// |                             | Name                         | Type                                                       |                                                |                                                         |
// +-----------------------------+------------------------------+------------------------------------------------------------+------------------------------------------------+---------------------------------------------------------+
namespace RFModulationTypeStruct {
                            struct AmplitudeModulationType      : dtl::discriminant< AmplitudeModulationTypeEnum16::type,      mpl::vector< mrfmte16::Amplitude         > > {};
                            struct AmplitudeAngleModulationType : dtl::discriminant< AmplitudeAngleModulationTypeEnum16::type, mpl::vector< mrfmte16::AmplitudeAndAngle > > {};
                            struct AngleModulationType          : dtl::discriminant< AngleModulationTypeEnum16::type,          mpl::vector< mrfmte16::Angle             > > {};
                            struct CombinationModulationType    : dtl::discriminant< CombinationModulationTypeEnum16::type,    mpl::vector< mrfmte16::Combination       > > {};
                            struct PulseModulationType          : dtl::discriminant< PulseModulationTypeEnum16::type,          mpl::vector< mrfmte16::Pulse             > > {};
                            struct UnmodulatedType              : dtl::discriminant< UnmodulatedTypeEnum16::type,              mpl::vector< mrfmte16::Unmodulated       > > {};
// +--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+----------------------------------------------------------+
                                                                                                                                                                  struct type : hla_13::variant_record< MajorRFModulationTypeEnum16::type, mpl::vector< AmplitudeModulationType, AmplitudeAngleModulationType, AngleModulationType, CombinationModulationType, PulseModulationType, UnmodulatedType > > {};
// +--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+----------------------------------------------------------+

}

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
