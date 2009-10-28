/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_GET_NAME_TYPE_HPP
#define PROTOX_HLA_GET_NAME_TYPE_HPP

/**************************************************************************************************/

namespace protox {
namespace hla {

/**************************************************************************************************/

// Get T's name type
template< typename T >
struct get_name_type
{
  typedef typename T::name_type type;
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
