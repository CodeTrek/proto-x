/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_CODEC_CODEC_HPP
#define PROTOX_CODEC_CODEC_HPP

/**************************************************************************************************/

// HLA 13 codec policies
#include <protox/hla_13/basic_data_codec.hpp>

#include <protox/hla_13/complex_type_codec.hpp>
#include <protox/hla_13/fixed_array_codec.hpp>
#include <protox/hla_13/variable_array_codec.hpp>
#include <protox/hla_13/enumerated_codec.hpp>

// HLA 1516 codec policies
#include <protox/hla_1516/basic_data_codec.hpp>
#include <protox/hla_1516/fixed_record_codec.hpp>
#include <protox/hla_1516/fixed_array_codec.hpp>
#include <protox/hla_1516/variable_array_codec.hpp>
#include <protox/hla_1516/enumerated_codec.hpp>
#include <protox/hla_1516/variant_record_codec.hpp>

// XDR codec policies
#include <protox/xdr/basic_data_codec.hpp>
#include <protox/xdr/structure_codec.hpp>
#include <protox/xdr/fixed_length_array_codec.hpp>
#include <protox/xdr/variable_length_array_codec.hpp>
#include <protox/xdr/fixed_length_opaque_codec.hpp>
#include <protox/xdr/variable_length_opaque_codec.hpp>
#include <protox/xdr/enumerated_codec.hpp>
#include <protox/xdr/string_codec.hpp>

// Custom test tags
#include <test/protox/custom/custom_data_codec.hpp>

// Add additional protocol codec policies here...

/**************************************************************************************************/

#endif

/**************************************************************************************************/
