/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_HLA_PRINT_STACK_HPP
#define PROTOX_HLA_PRINT_STACK_HPP

/******************************************************************************/

#include <iostream>

/******************************************************************************/

namespace protox { namespace hla {

/******************************************************************************/

struct print_stack
{
  print_stack() {}

  template< typename N >
  void operator()(N)
  {
    std::cout << N::name_type::name() << ".";
  }
};

/******************************************************************************/

}} // protox::hla

/******************************************************************************/

#endif

/******************************************************************************/
