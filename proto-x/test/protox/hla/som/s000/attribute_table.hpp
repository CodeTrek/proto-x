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

namespace som_s000 {

/******************************************************************************/

////// Attribute Table /////////////////////////////////////////////////////////
//     +----------- --------------------+
//     | Name                           |
//     +--------------------------------+
  struct Class_A {HLA_NAME( "Class_A" )};
  struct Class_B {HLA_NAME( "Class_B" )};
  struct Class_C {HLA_NAME( "Class_C" )};
  struct Class_D {HLA_NAME( "Class_D" )};
  struct Class_E {HLA_NAME( "Class_E" )};
  struct Class_F {HLA_NAME( "Class_F" )};
  struct Class_G {HLA_NAME( "Class_G" )};
  struct Class_H {HLA_NAME( "Class_H" )};

/******************************************************************************/

}

/******************************************************************************/

#endif

/******************************************************************************/
