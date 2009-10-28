/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_INIT_CLASS_HANDLE_HPP
#define PROTOX_HLA_INIT_CLASS_HANDLE_HPP

/**************************************************************************************************/

#include <protox/hla/keywords.hpp>

/**************************************************************************************************/

namespace protox {
namespace hla {

/**************************************************************************************************/

struct init_class_handle
{
  class RTI::RTIambassador &rtiAmb;
  const char *parentName;
  
  init_class_handle( class RTI::RTIambassador &r, char const *name ) : rtiAmb(r), parentName(name)
  {}
  
  template< typename C >
  void operator()( C )
  {
    C::init_handles( rtiAmb, parentName );
  }
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
