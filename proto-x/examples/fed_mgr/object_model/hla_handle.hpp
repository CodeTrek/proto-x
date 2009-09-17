
/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_EXAMPLE_HLA_HANDLE_HPP
#define PROTOX_EXAMPLE_HLA_HANDLE_HPP

/******************************************************************************/

#include <vector>

#include <protox/hla_1516/variable_array.hpp>
#include "simple_datatype_table.hpp"

/******************************************************************************/

using namespace protox;

/******************************************************************************/

//   +-----------+--------------------------------------+-----------------+-------------+
//   | Nam       | Encoding                             | Element type    | Cardinality |
//   +-----------+--------------------------------------+-----------------+-------------+
struct HLAhandle : hla_1516::variable_array< std::vector< HLAbyte > > {}; // Dynamic    |
//   +-----------+--------------------------------------+-----------------+-------------+

/******************************************************************************/

#endif

/******************************************************************************/
