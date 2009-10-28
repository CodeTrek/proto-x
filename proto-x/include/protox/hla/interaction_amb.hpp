/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_INTERACTION_AMB_HPP
#define PROTOX_HLA_INTERACTION_AMB_HPP

/**************************************************************************************************/

#include <cstddef>

#include <boost/mpl/inherit_linearly.hpp>
#include <boost/mpl/placeholders.hpp>

#include <RTI.hh>

#include <protox/hla/recv_interaction.hpp>

/**************************************************************************************************/

namespace protox {
namespace hla {

/**************************************************************************************************/

template< typename CLASS_TYPE_VECTOR >
struct interaction_amb
{
  typedef typename boost::mpl::inherit_linearly<
    CLASS_TYPE_VECTOR,
    recv_interaction_inherit<
      recv_interaction_base< boost::mpl::placeholders::_2 >,
      boost::mpl::placeholders::_1
    >
  >::type recv_interactions_type;

  struct type : recv_interactions_type {};
};
  
/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
