/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_GET_CLASS_NAME_HPP
#define PROTOX_HLA_GET_CLASS_NAME_HPP

/**************************************************************************************************/

namespace protox {
namespace hla {

/**************************************************************************************************/

template< typename CLASS >
struct get_class_name
{
  typedef typename CLASS::name_type type;
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
