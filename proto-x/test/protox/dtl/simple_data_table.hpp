/*
    Copyright 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef TEST_PROTOX_DTL_SIMPLE_DATA_TABLE_HPP
#define TEST_PROTOX_DTL_SIMPLE_DATA_TABLE_HPP

/**********************************************************************************************************************/

#include <protox/dtl/simple.hpp>

#include <test/protox/dtl/basic_data_table.hpp>

/**********************************************************************************************************************/

namespace test { namespace protox_dtl {

/**********************************************************************************************************************/

using namespace protox::dtl;

/**********************************************************************************************************************/

typedef simple< Integer32LE > Simple32LE;
typedef simple< Integer16BE > Simple16BE;
typedef simple< Float32LE   > SimpleFloat32LE;

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
