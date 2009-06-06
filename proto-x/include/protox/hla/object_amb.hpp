/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_HLA_OBJECT_AMB_HPP
#define PROTOX_HLA_OBJECT_AMB_HPP

/******************************************************************************/

#include <cstddef>

#include <boost/mpl/inherit_linearly.hpp>
#include <boost/mpl/placeholders.hpp>

#include <RTI.hh>

#include <protox/hla/remote_object.hpp>

/******************************************************************************/

namespace protox { namespace hla {

/******************************************************************************/

template< typename CLASS_TYPE_VECTOR >
struct object_amb
{
  typedef typename boost::mpl::inherit_linearly<
    CLASS_TYPE_VECTOR,
    remote_object_inherit< remote_object_base< boost::mpl::placeholders::_2 >,
                           boost::mpl::placeholders::_1 >
  >::type remote_objects_type;

  struct type : remote_objects_type
  {
  };

};
  
/******************************************************************************/

}} // protox::hla

/******************************************************************************/

#endif

/******************************************************************************/
