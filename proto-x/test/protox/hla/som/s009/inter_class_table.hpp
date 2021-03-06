/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef SOM_S009_OBJ_CLASS_TABLE_HPP
#define SOM_S009_OBJ_CLASS_TABLE_HPP

/**********************************************************************************************************************/

#include <protox/hla/i_class.hpp>
#include <protox/hla/keywords.hpp>

#include <test/protox/hla/som/s009/parameter_table.hpp>

/**********************************************************************************************************************/

namespace som_s009 {

/**********************************************************************************************************************/

using namespace protox::hla;

/**********************************************************************************************************************/

////// Interaction Class Table /////////////////////////////////////////////////////////////////////////////////////////
struct inter_class_table :
//   +------------------+------------------+------------------+----------------------+
//   | Class 1          | Class 2          | Class 3          | Class 4              |
//   +------------------+------------------+------------------+----------------------+
       i_class< Class_A ,                                                                  params< A3 >,
                   child< i_class< Class_B ,                                               params< A1, A2 >,
                                      child< i_class< Class_E >,
                                             i_class< Class_F >,
                                             i_class< Class_C > > >,
//   +                  +------------------+------------------+----------------------+
                          i_class< Class_C ,                                               params< A1, A2 >,
                                      child< i_class< Class_A ,                            none,
                                                         child< i_class< Class_E > > >,
//   +                  +                  +------------------+----------------------+
                                             i_class< Class_C >,
                                             i_class< Class_E > > >,
//   +                  +------------------+------------------+----------------------+
                          i_class< Class_D ,                                               params< A1, A2 >,
                                      child< i_class< Class_G >,
                                             i_class< Class_H > > > > > {};
//   +------------------+------------------+------------------+----------------------+

/**********************************************************************************************************************/

}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
