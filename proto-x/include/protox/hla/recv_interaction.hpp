/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_HLA_RECV_INTERACTION_HPP
#define PROTOX_HLA_RECV_INTERACTION_HPP

/******************************************************************************/

#include <RTI.hh>

#include <boost/mpl/empty_base.hpp>

/******************************************************************************/

namespace protox { namespace hla {

/******************************************************************************/

template< typename T >
struct recv_interaction_base
{
  void (*handler) ( const T &, const RTI::FedTime *time, const char *tag );

  recv_interaction_base() : handler(0) {}

  bool recv( RTI::InteractionClassHandle interaction_handle,
             const RTI::ParameterHandleValuePairSet &params,
             const RTI::FedTime *time,
             const char *tag )
  {
    if( T::get_handle() == interaction_handle )
    {
      T new_interaction;
      new_interaction.recv( params );

      if( handler != 0 )
      {
        (*handler)( new_interaction, time, tag ); 
      }

      return true;
    }

    return false;
  }
};

/******************************************************************************/

// Forward declaration
template< typename A, typename B > struct recv_interaction_inherit;

/******************************************************************************/

template< typename A >
struct recv_interaction_inherit< A, boost::mpl::empty_base > :
  A, boost::mpl::empty_base
{
  template< typename T >
  inline void set_handler
    ( void (*h)( const T &, const RTI::FedTime *, const char *tag ) )
  {
    static_cast< recv_interaction_base< T > & >( *this ).handler = h;
  }

  void recv_interaction( RTI::InteractionClassHandle interaction_handle,
                         const RTI::ParameterHandleValuePairSet &params,
                         const RTI::FedTime *time,
                         const char *tag )
  {
    bool received = A::recv( interaction_handle, params, time, tag );

    if( !received )
    {
      throw RTI::InteractionClassNotKnown( "" );
    }
  }
};

/******************************************************************************/

/**
 * A is recv_interaction and B is set of predecessor recv_interactions.
 */
template< typename A, typename B >
struct recv_interaction_inherit : A, B
{
public:
  template< typename T >
  inline void set_handler
    ( void (*h)( const T &, const RTI::FedTime *, const char *tag ) )
  {
    static_cast< recv_interaction_base< T > & >( *this ).handler = h;
  }

  void recv_interaction( RTI::InteractionClassHandle interaction_handle,
                         const RTI::ParameterHandleValuePairSet &params,
                         const RTI::FedTime *time,
                         const char *tag )
  {
    if( A::recv( interaction_handle, params, time, tag ) )
    {
      return;
    }

    B::recv_interaction( interaction_handle, params, time, tag );
  }
};

/******************************************************************************/

}} // protox::hla

/******************************************************************************/

#endif

/******************************************************************************/
