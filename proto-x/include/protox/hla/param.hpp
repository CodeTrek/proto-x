/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_PARAM_HPP
#define PROTOX_HLA_PARAM_HPP

/**************************************************************************************************/

#include <string>

#include <RTI.hh>

#include <boost/shared_ptr.hpp>
#include <boost/mpl/empty_base.hpp>

#include <protox/io/byte_data_sink.hpp>
#include <protox/io/byte_data_source.hpp>

/**************************************************************************************************/

namespace protox {
namespace hla {

/**************************************************************************************************/

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

  void add_value( boost::shared_ptr< RTI::ParameterHandleValuePairSet > set_ptr )
  {
    protox::io::byte_data_sink sink;
    sink.encode( value );
    set_ptr->add( handle, sink.getDataBuffer(), (unsigned long) sink.getDataBufferSize() );
  }
  
  void recv_value( const RTI::ParameterHandleValuePairSet &ph_set )
  {
    for (RTI::ULong i = 0; i < ph_set.size(); ++i)
    {
      const RTI::Handle h = ph_set.getHandle( i );
      
      if (handle == h)
      {
        RTI::ULong length = 0;
        char *buff = ph_set.getValuePointer( i, length );
        
        protox::io::byte_data_source source( buff, length );
        source.decode( value );
        
        break;
      }
    }
  }
};

/**************************************************************************************************/

/**
 * Use this template to generate an parameter definition type that can be used as part of an
 * interaction class definition in a parameter table.
 *
 * \tparam T The parameter's type.
 *
 * Example:
 * \code
 * // Define an parameter called AccuracyOk of type HLAboolean.
 * struct FoodServed : param< HLAboolean::type > {HLA_NAME("AccuracyOk")};
 * \endcode
 *
 * Example use in a parameter table:
 * \code
 * //////// Parameter Table ////////////////////
 * //     +------------------------------------+---------------+-------------------------+----------------------------+
 * //     | Name                               | Parameter     | Datatype                | String Name                |
 * //     +------------------------------------+---------------+-------------------------+----------------------------+
 *   struct FoodServed {HLA_NAME("FoodServed")};
 *                                        struct TemperatureOk : param< HLAboolean::type > {HLA_NAME("TemperatureOk")};
 *                                        struct AccuracyOk    : param< HLAboolean::type > {HLA_NAME("AccuracyOk"   )};
 *                                        struct TimelinessOk  : param< HLAboolean::type > {HLA_NAME("TimelinessOk" )};
 * //     +------------------------------------+---------------+-------------------------+----------------------------+
 * \endcode
 *
 */
template< typename T >
struct param
{
  typedef T value_type;
};

/**************************************************************************************************/

// Forward declaration
template< typename A, typename B > struct param_inherit;

/**************************************************************************************************/

struct param_empty_base
{
  static RTI::ULong count_params() { return 0; }

  template< typename T >
  void init_handles( const std::string &class_name ) {}

  void recv_values( const RTI::ParameterHandleValuePairSet & ) {}

  template< typename T >
  inline RTI::ParameterHandle get_param_handle()
  {
    throw RTI::InteractionParameterNotDefined( "parameter not defined" );
  }

  void add_values( boost::shared_ptr< RTI::ParameterHandleValuePairSet > ) {}
};

/**************************************************************************************************/

template< typename A >
struct param_inherit< A, param_empty_base > : A, param_empty_base
{
  template< typename T >
  void init_handles( const std::string &class_name )
  {
    A::template init_handle< T >( class_name );
  }

  void add_values( boost::shared_ptr< RTI::ParameterHandleValuePairSet> set_ptr )
  {
    A::add_value( set_ptr );
  }
  
  void recv_values( const RTI::ParameterHandleValuePairSet &ph_set )
  {
    A::recv_value( ph_set );
  }

  static RTI::ULong count_params()
  {
    return 1;
  }

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
  inline typename T::value_type const &get_parameter() const
  {
    return( static_cast< param_base< T > const & >( *this ).value );
  }

  template< typename T >
  inline typename T::value_type &get_parameter()
  {
    return( static_cast< param_base< T > & >( *this ).value );
  }

  template< typename T >
  inline RTI::ParameterHandle get_param_handle()
  {
    return( static_cast< param_base< T > & >( *this ).handle );
  }
};

/**************************************************************************************************/

 // A is an parameter and B is set of predecessor parameters.
template< typename A, typename B >
struct param_inherit : A, B
{
  template< typename T >
  void init_handles( const std::string &class_name )
  {
    A::template init_handle< T >( class_name );
    B::template init_handles< T >( class_name );
  }

  void add_values( boost::shared_ptr< RTI::ParameterHandleValuePairSet > set_ptr )
  {
    A::add_value( set_ptr );
    B::add_values( set_ptr );
  }
  
  void recv_values( const RTI::ParameterHandleValuePairSet &ph_set )
  {
    A::recv_value( ph_set );
    B::recv_values( ph_set );
  }

  static RTI::ULong count_params()
  {
    unsigned int total = 1 + B::count_params();
    return total;
  }

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
  inline typename T::value_type const &get_parameter() const
  {
    return( static_cast< param_base< T > const & >( *this ).value );
  }

  template< typename T >
  inline typename T::value_type &get_parameter()
  {
    return( static_cast< param_base< T > & >( *this ).value );
  }

  template< typename T >
  inline RTI::ParameterHandle get_param_handle()
  {
    return( static_cast< param_base< T > & >( *this ).handle );
  }
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
