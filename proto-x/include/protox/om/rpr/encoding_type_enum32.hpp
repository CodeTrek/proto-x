/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_OM_RPR_ENCODING_TYPE_ENUM32_HPP
#define PROTOX_OM_RPR_ENCODING_TYPE_ENUM32_HPP

/**********************************************************************************************************************/

#include "protox/dtl/enum_pp.hpp"

#include "protox/hla_13/enumerated.hpp"
#include "protox/hla_13/basic_data_representation_table.hpp"

/**********************************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**********************************************************************************************************************/

using namespace protox;
using namespace protox::hla_13;

/**********************************************************************************************************************/

//      +--------------------+----------------------------------------------------------+---------------------------+--------+
//      | Name               | Representation                                           | Enumerator                | Values |
//      +--------------------+----------------------------------------------------------+---------------------------+--------+
namespace EncodingTypeEnum32 { PROTOX_ENUM_TYPE(HLA13unsigned_long, hla_13::enumerated) ;
                                                                       PROTOX_ENUM_VALUE( Encoding_8_bit_mu_law,          1 );
                                                                       PROTOX_ENUM_VALUE( CVSD_per_MIL_STD_188_113,       2 );
                                                                       PROTOX_ENUM_VALUE( ADPCM_per_CCITT_G721,           3 );
                                                                       PROTOX_ENUM_VALUE( Encoding_16_bit_linear_PCM,     4 );
                                                                       PROTOX_ENUM_VALUE( Encoding_8_bit_linear_PCM,      5 );
                                                                       PROTOX_ENUM_VALUE( VQ_Vector_Quantization,         6 );
//      +--------------------+----------------------------------------------------------+---------------------------+--------+


PROTOX_ENUM_EQUALITY_OPERATOR;
PROTOX_ENUM_DEFAULT(Encoding_8_bit_mu_law);

}

/**********************************************************************************************************************/

}}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
