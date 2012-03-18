/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_FIXED_DATUM_STRUCT_HPP
#define PROTOX_OM_RPR_FIXED_DATUM_STRUCT_HPP

/**********************************************************************************************************************/

#include <boost/mpl/vector.hpp>

#include <protox/hla_13/complex_type.hpp>
#include <protox/hla_13/basic_data_representation_table.hpp>

#include <protox/om/rpr/datum_identifier_enum32.hpp>

/**********************************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**********************************************************************************************************************/

using namespace boost;
using namespace protox;
using namespace protox::dtl;
using namespace protox::hla_13;

/**********************************************************************************************************************/

//      +------------------+---------------------------------------------------------------+----------------------+
//      |                  | Field                                                         |                      |
//      | Record Name      +----------------------+----------------------------------------+ Encoding             |
//      |                  | Name                 | Type                                   |                      |
//      +------------------+----------------------+----------------------------------------+----------------------+
namespace FixedDatumStruct {
                      struct FixedDatumIdentifier : field< DatumIdentifierEnum32::type > {};
                      struct FixedDatumValue      : field< HLA13unsigned_long          > {};
//      +------------------+----------------------+----------------------------------------+----------------------+
                                                                               struct type : hla_13::complex_type < mpl::vector< FixedDatumIdentifier, FixedDatumValue > > {}; }
//                                                                                         +----------------------+

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
