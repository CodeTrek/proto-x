/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_DTL_HLA_13_SIZE_TYPE_HPP
#define PROTOX_DTL_HLA_13_SIZE_TYPE_HPP

/**************************************************************************************************/

#include <cstddef>

#include <protox/hla_13/basic_data_representation_table.hpp>

/**************************************************************************************************/

namespace protox {
namespace hla_13 {

/**************************************************************************************************/

struct size_type : HLA13long
{
  size_type( std::size_t s )
  {
    value = (HLA13long::value_type) s;
  }

  size_type &operator=( std::size_t s )
  {
    value = (HLA13long::value_type) s;
    return *this;
  }
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
