/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_DTL_VARIABLE_ARRAY_HPP
#define PROTOX_DTL_VARIABLE_ARRAY_HPP

/******************************************************************************/

namespace protox { namespace dtl {

/******************************************************************************/

// Defines a variable length array based on a container of type T.
template< typename T, typename CODEC_TAG >
struct variable_array : public T
{
  typedef typename T::value_type value_type;
  typedef CODEC_TAG codec_tag;

  variable_array() {}
};

/******************************************************************************/

}} // protox::dtl

/******************************************************************************/

#endif

/******************************************************************************/
