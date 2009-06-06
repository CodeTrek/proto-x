/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_HLA_REMOTE_OBJECT_HPP
#define PROTOX_HLA_REMOTE_OBJECT_HPP

/******************************************************************************/

#include <map>

#include <RTI.hh>

#include <boost/mpl/empty_base.hpp>

/******************************************************************************/

namespace protox { namespace hla {

/******************************************************************************/

template< typename T >
struct remote_object_base
{
  typedef T remote_object_type;
  typedef std::map< RTI::ObjectHandle, remote_object_type > map_type;
  typedef typename map_type::const_iterator const_it;

  map_type objects;

  remote_object_base() {}

  bool add_object( RTI::ObjectClassHandle class_handle,
                   RTI::ObjectHandle object_handle,
                   const char *object_name )
  {
    if( remote_object_type::get_handle() != class_handle )
    {
      return false;
    }

    objects[ object_handle ] = remote_object_type();

    if( object_name != 0 )
    {
      objects[ object_handle ].set_obj_name( std::string( object_name ) ); 
    }

    return true;
  }
};

/******************************************************************************/

// Forward declaration
template< typename A, typename B > struct remote_object_inherit;

/******************************************************************************/

template< typename A >
struct remote_object_inherit< A, boost::mpl::empty_base > :
  A, boost::mpl::empty_base
{
protected:
  void discover_object( RTI::ObjectClassHandle class_handle,
                        RTI::ObjectHandle object_handle,
                        const char *object_name )
  {
    bool obj_added = A::add_object( class_handle, object_handle, object_name );

    if( !obj_added )
    {
      throw RTI::ObjectClassNotKnown("");
    }
  }
};

/******************************************************************************/

/**
 * A is remote_object and B is set of predecessor remote_objects.
 */
template< typename A, typename B >
struct remote_object_inherit : A, B
{
public:
  void discover_object( RTI::ObjectClassHandle class_handle,
                        RTI::ObjectHandle object_handle,
                        const char *object_name )
  {
    if( A::add_object( class_handle, object_handle, object_name ) )
    {
      return;
    }

    B::discover_object( class_handle, object_handle, object_name );
  }

  template< typename T >
  inline typename remote_object_base< T >::const_it begin() const
  {
    return( static_cast< remote_object_base< T > const & >( *this )
      .objects.begin() );
  }

  template< typename T >
  inline typename remote_object_base< T >::const_it end() const
  {
    return (static_cast< remote_object_base< T > const & >( *this )
      .objects.end() );
  }

  template< typename T >
  inline std::size_t size() const
  {
    return (static_cast< remote_object_base< T > const & >( *this )
      .objects.size() );
  }

  template< typename T >
  inline bool empty() const
  {
    return (static_cast< remote_object_base< T > const & >( *this )
      .objects.empty() );
  }
};

/******************************************************************************/

}} // protox::hla

/******************************************************************************/

#endif

/******************************************************************************/
