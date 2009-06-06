/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_HLA_PARAM_HPP
#define PROTOX_HLA_PARAM_HPP

/******************************************************************************/

#include <string>

#include <RTI.hh>

#include <boost/shared_ptr.hpp>
#include <boost/mpl/empty_base.hpp>

#include <protox/io/byte_data_sink.hpp>

/******************************************************************************/

namespace protox { namespace hla {

/******************************************************************************/

template< typename T >
struct param_base
{
  typedef T param_type;
  typename T::value_type value;

  RTI::ParameterHandle handle;

  static char const *name() { return T::name(); }

  param_base() : handle(0) {}

protected:
  template< typename S >
  void init_handle(const std::string &class_name)
  {
    handle = S::get_param_handle( class_name, name() );
  }

  void add_value
    ( boost::shared_ptr< RTI::ParameterHandleValuePairSet > set_ptr )
  {
    protox::io::byte_data_sink sink;

    sink.encode( value );

    set_ptr->add( handle,
                  sink.getDataBuffer(),
                  (unsigned long) sink.getDataBufferSize() );
  }
};

/******************************************************************************/

template< typename T >
struct param
{
  typedef T value_type;
};

/******************************************************************************/

// Forward declaration
template< typename A, typename B > struct param_inherit;

/******************************************************************************/

template< typename A >
struct param_inherit< A, boost::mpl::empty_base > : A, boost::mpl::empty_base
{
protected:
  template< typename T >
  void init_handles( const std::string &class_name )
  {
    A::template init_handle< T >( class_name );
  }

  void add_values(boost::shared_ptr< RTI::ParameterHandleValuePairSet> set_ptr )
  {
    A::add_value( set_ptr );
  }
};

/******************************************************************************/

/**
 * A is an attribute and B is set of predecessor parameters.
 */
template< typename A, typename B >
struct param_inherit : A, B
{
protected:
  template< typename T >
  void init_handles( const std::string &class_name )
  {
    A::template init_handle< T >( class_name );
    B::template init_handles< T >( class_name );
  }

  void add_values
    ( boost::shared_ptr< RTI::ParameterHandleValuePairSet > set_ptr )
  {
    A::add_value( set_ptr );
    B::add_values( set_ptr );
  }

public:
  template< typename T >
  inline typename T::value_type const &p_() const
  {
    return( static_cast< param_base< T > const & >( *this ).value );
  }

  template< typename T >
  inline typename T::value_type &p_()
  {
    return( static_cast< param_base< T > & >( *this ).value );
  }
  
  template< typename T >
  inline RTI::ParameterHandle get_param_handle()
  {
    return( static_cast< param_base< T > & >( *this ).handle );
  }
};

/******************************************************************************/

}} // protox::hla

/******************************************************************************/

#endif

/******************************************************************************/
