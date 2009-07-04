/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_HLA_ATTR_HPP
#define PROTOX_HLA_ATTR_HPP

/******************************************************************************/

#include <string>
#include <set>

#include <RTI.hh>

#include <boost/mpl/empty_base.hpp>

#include <protox/io/byte_data_source.hpp>

/******************************************************************************/

namespace protox { namespace hla {

/******************************************************************************/

template< typename T >
struct attr_base
{
  enum state { PUBLISHED = 1L << 0, MODIFIED = 1L << 1 };

  typedef T attr_type;
  typename T::value_type value;

  RTI::AttributeHandle handle;

  unsigned short state_vector;

  static char const *name() { return T::name(); }

  attr_base() : handle(0), state_vector((state) 0) {}

  void set( state s ) { state_vector |= s; }
  void clear( state s ) { state_vector &= (~s); }

  bool is_set( state s ) const { return( (state_vector & s) != 0 ); }

protected:
  template< typename S >
  void init_handle( const std::string &class_name )
  {
    handle = S::get_attr_handle( class_name, name() );
  }
  
  void add_handle( RTI::AttributeHandleSet &ahs )
  {
    ahs.add( handle );
  }

  void reflect( const RTI::AttributeHandleValuePairSet &ahv_set,
                const RTI::FedTime *time )
  {
    for( RTI::ULong i = 0; i < ahv_set.size(); ++i )
    {
      RTI::AttributeHandle h = ahv_set.getHandle( i );

      if( h == this->handle )
      {
        RTI::ULong length = 0;
        char *data = ahv_set.getValuePointer( i, length );
        protox::io::byte_data_source ds( data, length );
        ds.decode( this->value );

        return;
      }
    }
  }
};

/******************************************************************************/

template< typename T >
struct attr
{
  typedef T value_type;
};

/******************************************************************************/

// Forward declaration
template< typename A, typename B > struct attr_inherit;

/******************************************************************************/

template< typename A >
struct attr_inherit< A, boost::mpl::empty_base > : A, boost::mpl::empty_base
{
protected:
  template< typename T >
  void init_handles( const std::string &class_name )
  {
    A::template init_handle< T >( class_name );
  }
  
  template< typename T >
  static void collect_handles( const std::string &class_name,
                               std::set< std::string > &attr_names,
                               RTI::AttributeHandleSet &ahs )
  {
    bool in_set = true;

    if( !attr_names.empty() )
    {
      in_set = (attr_names.find(A::name()) != attr_names.end());
    }

    if( in_set )
    {
      RTI::AttributeHandle handle = T::get_attr_handle( class_name, A::name() );
      ahs.add( handle );
      attr_names.erase( A::name() );
    }

    // Undefined attributes?
    if (!attr_names.empty())
    {
      std::string name = *attr_names.begin();

      throw RTI::AttributeNotDefined( (name + " not defined").c_str() );
    }
  }
  
  static RTI::ULong count_attrs()
  {
    return 1;
  }

  void reflect( const RTI::AttributeHandleValuePairSet &ahv_set,
                const RTI::FedTime *time )
  {
    A::reflect( ahv_set, time );
  }
};

/******************************************************************************/

/**
 * A is an attribute and B is set of predecessor attributes.
 */
template< typename A, typename B >
struct attr_inherit : A, B
{
protected:
  template< typename T >
  void init_handles( const std::string &class_name )
  {
    A::template init_handle< T >( class_name );
    B::template init_handles< T >( class_name );
  }
  
  static RTI::ULong count_attrs()
  {
    unsigned int total = 1 + B::count_attrs();
    return total;
  }

  template< typename T >
  static void collect_handles( const std::string &class_name,
                               std::set< std::string > &attr_names,
                               RTI::AttributeHandleSet &ahs )
  {
    bool in_set = true;

    if( !attr_names.empty() )
    {
      in_set = (attr_names.find( A::name() ) != attr_names.end());
    }

    if( in_set )
    {
      RTI::AttributeHandle handle = T::get_attr_handle( class_name, A::name() );
      ahs.add( handle );
      attr_names.erase( A::name() );
    }

    B::template collect_handles< T >( class_name, attr_names, ahs );
  }

public:
  template< typename T >
  inline typename T::value_type const &a_() const
  {
    return (static_cast< attr_base< T > const & >( *this ).value);
  }

  template< typename T >
  inline typename T::value_type &a_()
  {
    return (static_cast< attr_base< T > & >( *this ).value);
  }
  
  template< typename T >
  inline RTI::AttributeHandle get_attr_handle()
  {
    return (static_cast< attr_base< T > & >( *this ).handle);
  }

  void reflect( const RTI::AttributeHandleValuePairSet &ahv_set,
                const RTI::FedTime *time )
  {
    A::reflect( ahv_set, time );
    B::reflect( ahv_set, time );
  }
};

/******************************************************************************/

}} // protox::hla

/******************************************************************************/

#endif

/******************************************************************************/
