/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_ANGULAR_VELOCITY_VECTOR_STRUCT_HPP
#define PROTOX_OM_RPR_ANGULAR_VELOCITY_VECTOR_STRUCT_HPP

/**********************************************************************************************************************/

#include <boost/mpl/vector.hpp>

#include <protox/hla_13/complex_type.hpp>
#include <protox/hla_13/basic_data_representation_table.hpp>

/**********************************************************************************************************************/

using namespace boost;
using namespace protox;
using namespace protox::dtl;
using namespace protox::hla_13;

/**********************************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**********************************************************************************************************************/

//      +-----------------------------+------------------------------------------+----------------------+
//      |                             | Field                                    |                      |
//      | Record Name                 +------------------+-----------------------+ Encoding             |
//      |                             | Name             | Type                  |                      |
//      +-----------------------------+------------------+-----------------------+----------------------+
namespace AngularVelocityVectorStruct {
                                 struct XAngularVelocity : field< HLA13float > {};
                                 struct YAngularVelocity : field< HLA13float > {};
                                 struct ZAngularVelocity : field< HLA13float > {};
//      +-----------------------------+------------------+-----------------------+
                                                                     struct type : hla_13::complex_type < mpl::vector< XAngularVelocity, YAngularVelocity, ZAngularVelocity > > {}; }
//      +------------------------------------------------------------------------+----------------------+

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/

