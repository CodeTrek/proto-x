/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_RADIO_TYPE_STRUCT_HPP
#define PROTOX_OM_RPR_RADIO_TYPE_STRUCT_HPP

/**********************************************************************************************************************/

#include <boost/mpl/vector.hpp>

#include <protox/hla_13/complex_type.hpp>
#include <protox/hla_13/basic_data_representation_table.hpp>

#include <protox/om/rpr/nomenclature_version_enum8.hpp>
#include <protox/om/rpr/nomenclature_enum16.hpp>

/**********************************************************************************************************************/

using namespace boost;
using namespace protox;
using namespace protox::dtl;
using namespace protox::hla_13;

/**********************************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**********************************************************************************************************************/

//      +-----------------+-----------------------------------------------------------------+----------------------+
//      |                 | Field                                                           |                      |
//      | Record Name     +---------------------+-------------------------------------------+ Encoding             |
//      |                 | Name                | Type                                      |                      |
//      +-----------------+---------------------+-------------------------------------------+----------------------+
namespace RadioTypeStruct {
                     struct EntityKind          : field< HLA13octet                     > {};
                     struct Domain              : field< HLA13octet                     > {};
                     struct CountryCode         : field< HLA13unsigned_short            > {};
                     struct Category            : field< HLA13octet                     > {};
                     struct NomenclatureVersion : field< NomenclatureVersionEnum8::type > {};
                     struct Nomenclature        : field< NomenclatureEnum16::type       > {};
//      +-----------------+---------------------+-------------------------------------------+----------------------+
                                                                                struct type : hla_13::complex_type < mpl::vector< EntityKind, Domain, CountryCode, Category, NomenclatureVersion, Nomenclature > > {}; }
//      +-----------------------------------------------------------------------------------+----------------------+

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/

