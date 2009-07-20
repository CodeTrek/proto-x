/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef SOM_S000_ATTRIBUTE_TABLE_HPP
#define SOM_S000_ATTRIBUTE_TABLE_HPP

/******************************************************************************/

#include <protox/hla/keywords.hpp>
#include <protox/hla/name.hpp>

/******************************************************************************/

namespace som { namespace s000 {

/******************************************************************************/

////// Attribute Table /////////////////////////////////////////////////////////
//     +----------- --------------------+
//     | Name                           |
//     +--------------------------------+
  struct Class_A {HLA_NAME( "Class_A" )};
  struct Class_B {HLA_NAME( "Class_B" )};
  struct Class_C {HLA_NAME( "Class_C" )};
  struct Class_D {HLA_NAME( "Class_D" )};

}}

/******************************************************************************/

#endif

/******************************************************************************/
