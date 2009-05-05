/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_DTL_FIELD_HPP
#define PROTOX_DTL_FIELD_HPP

/**************************************************************************************************/

namespace protox { namespace dtl {

/**************************************************************************************************/

// The templates field_base and field are used to represent a field in
// a fixed_record definition.

// Holds a field's value.
template< typename T >
struct field_base
{
  typename T::value_type value;
};

// Defines an HLA 1516 fixed record field datatype.
template< typename T >
struct field
{
  typedef T value_type;
};

/**************************************************************************************************/

}} // protox::dtl

/**************************************************************************************************/

#endif

/**************************************************************************************************/
