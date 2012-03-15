/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_ATTRIBUTE_PAIR_STRUCT_HPP
#define PROTOX_OM_RPR_ATTRIBUTE_PAIR_STRUCT_HPP

/**********************************************************************************************************************/

#include <boost/mpl/vector.hpp>

#include <protox/hla_13/complex_type.hpp>
#include <protox/hla_13/basic_data_representation_table.hpp>

#include <protox/om/rpr/any_array.hpp>

/**********************************************************************************************************************/

using namespace boost;
using namespace protox;
using namespace protox::dtl;
using namespace protox::hla_13;

/**********************************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**********************************************************************************************************************/

//      +---------------------+---------------------------------------------------+----------------------+
//      |                     | Field                                             |                      |
//      | Record Name         +-----------------+---------------------------------+ Encoding             |
//      |                     | Name            | Type                            |                      |
//      +---------------------+-----------------+---------------------------------+----------------------+
namespace AttributePairStruct {
                         struct AttributeHandle : field< HLA13unsigned_long   > {};
                         struct ValueLength     : field< HLA13unsigned_long   > {};
                         struct Value           : field< protox::om::rpr::any > {};
//      +---------------------+-----------------+---------------------------------+----------------------+
                                                                      struct type : hla_13::complex_type < mpl::vector< AttributeHandle, ValueLength, Value > > {}; }
//      +---------------------+-----------------+---------------------------------+----------------------+

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
