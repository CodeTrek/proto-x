/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef SOMS_YYABC_R1_RECORD_HPP
#define SOMS_YYABC_R1_RECORD_HPP

/******************************************************************************/

#include <boost/mpl/vector.hpp>

#include <protox/hla_1516/fixed_record.hpp>

#include <test/protox/hla/som/yyabc/simple_datatype_table.hpp>

/******************************************************************************/

namespace soms { namespace yyabc {

/******************************************************************************/

using namespace boost;
using namespace protox;
using namespace protox::dtl;

/******************************************************************************/

//      +----------------+----------------------------------+------------------------+ 
//      |                | Field                            |                        |
//      | Record         +----------+-----------------------+ Encoding               |
//      | name           | Name     | Type                  |                        |
//      +----------------+----------+-----------------------+------------------------+ 
namespace R1             {
//      +----------------+----------+-----------------------+
                    struct f1       : field< SimpleHLAoctet > {};
//                       +----------+-----------------------+
                    struct f2       : field< SimpleHLAoctet > {};
//                       +----------+-----------------------+
                    struct f3       : field< SimpleHLAoctet > {};
//      +----------------+----------+-----------------------+
                                                struct type : hla_1516::fixed_record < mpl::vector< f1, f2, f3 > > {}; }

/******************************************************************************/

}}

/******************************************************************************/

#endif

/******************************************************************************/
