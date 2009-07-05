/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef SOM_ABC_POPULATED_PARAMETER_TABLE_HPP
#define SOM_ABC_POPULATED_PARAMETER_TABLE_HPP

/******************************************************************************/

#include <protox/hla/param.hpp>
#include <protox/hla/keywords.hpp>
#include <protox/hla/name.hpp>

/******************************************************************************/

namespace som { namespace abc_populated {

/******************************************************************************/

using namespace protox::hla;

/******************************************************************************/

////// Parameter Table /////////////////////////////////////////////////////////
//     +------------------------------+-----------+-----------------+-----------------+
//     | Name                         | Attribute | Datatype        | String Name     |
//     +------------------------------+-----------+-----------------+-----------------+
  struct IClass_A {HLA_NAME("IClass_A")};
                                 struct pa1        : param< int >     { HLA_NAME("pa1") };
                                 struct pa2        : param< int >     { HLA_NAME("pa2") };
//     +------------------------------+-----------+-----------------+-----------------+
  struct IClass_B {HLA_NAME("IClass_B")};
                                 struct pb1        : param< int >     { HLA_NAME("pb1") };
//     +------------------------------+-----------+-----------------+-----------------+
  struct IClass_C {HLA_NAME("IClass_C")};
//     +------------------------------+-----------+-----------------+-----------------+
  struct IClass_D {HLA_NAME("IClass_D")};
//     +------------------------------+-----------+-----------------+-----------------+
  struct IClass_E {HLA_NAME("IClass_E")};
//     +------------------------------+-----------+-----------------+-----------------+
  struct IClass_F {HLA_NAME("IClass_F")};
//     +------------------------------+-----------+-----------------+-----------------+
  struct IClass_G {HLA_NAME("IClass_G")};
                                 struct pg1        : param< int >     { HLA_NAME("pg1") };
                                 struct pg2        : param< int >     { HLA_NAME("pg2") };
//     +------------------------------+-----------+-----------------+-----------------+
  struct IClass_H {HLA_NAME("IClass_H")};
//     +------------------------------+-----------+-----------------+-----------------+

}}

/******************************************************************************/

#endif

/******************************************************************************/
