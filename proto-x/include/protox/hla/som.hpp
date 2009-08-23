/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_HLA_SOM_HPP
#define PROTOX_HLA_SOM_HPP

/******************************************************************************/

#include <RTI.hh>

#include <assert.h>
#include <string>
#include <iostream>

#include <protox/hla/name_to_o_class_handle_map.hpp>
#include <protox/hla/class_handle_to_attr_handle_map.hpp>
#include <protox/hla/build_full_name.hpp>
#include <protox/hla/o_class.hpp>
#include <protox/hla/i_class.hpp>
#include <protox/hla/attr_dft.hpp>
#include <protox/hla/param_dft.hpp>

/******************************************************************************/

namespace protox { namespace hla {

/******************************************************************************/

template< typename ROOT_O_CLASS = null_o_class,
          typename ROOT_I_CLASS = null_i_class >
struct som
{
private:

  // Object class support
  typedef attr_dft< ROOT_O_CLASS > attr_dft_type;
    
  static hla::name_to_o_class_handle_map &
  get_name_to_o_class_handle_map()
  {
    static protox::hla::name_to_o_class_handle_map map;
    return map;
  }

  static hla::o_class_handle_to_attr_map &
  get_o_class_handle_to_attr_map()
  {
    static hla::o_class_handle_to_attr_map map;
    return map;
  }

  static void init_o_class_handles( RTI::RTIambassador &rtiAmb )
  {
    hla::name_to_o_class_handle_map &o_class_map
      = get_name_to_o_class_handle_map();
      
    // Maps is already populated? 
    if( !o_class_map.empty() )
      return;
      
    hla::o_class_handle_to_attr_map &attr_map
      = get_o_class_handle_to_attr_map();

    assert( attr_map.empty() );
      
    attr_dft_type::init_o_class_handles( rtiAmb, o_class_map, attr_map );
  }

  // Interaction class support
  typedef param_dft< ROOT_I_CLASS > param_dft_type;
    
  static hla::name_to_i_class_handle_map &get_name_to_i_class_handle_map()
  {
    static protox::hla::name_to_i_class_handle_map map;
    return map;
  }

  static hla::i_class_handle_to_param_map &get_i_class_handle_to_param_map()
  {
    static hla::i_class_handle_to_param_map map;
    return map;
  }

  static void init_i_class_handles( RTI::RTIambassador &rti_amb )
  {
    hla::name_to_i_class_handle_map &i_class_map
      = get_name_to_i_class_handle_map();
      
    // Map is already populated? 
    if( !i_class_map.empty() )
    {
      return;
    }
      
    hla::i_class_handle_to_param_map &param_map
      = get_i_class_handle_to_param_map();

    assert( param_map.empty() );
      
    param_dft_type::init_i_class_handles( rti_amb, i_class_map, param_map );
  }
  
public: 
  typedef ROOT_O_CLASS o_class_table;
  typedef ROOT_I_CLASS i_class_table;

  static RTI::ObjectClassHandle get_object_class_handle
    ( const std::string &name )
  {
    name_to_o_class_handle_map &class_map = get_name_to_o_class_handle_map();
    name_to_o_class_handle_map::const_iterator it = class_map.find(name);

    // Not found
    if( it == class_map.end() )
    {
      throw RTI::NameNotFound( name.c_str() );
    }

    return( (*it).second );
  }

  static RTI::AttributeHandle get_attr_handle( const std::string &name,
                                               RTI::ObjectClassHandle handle )
  {
    o_class_handle_to_attr_map &class_map = get_o_class_handle_to_attr_map();
    o_class_handle_to_attr_map::const_iterator i = class_map.find( handle );

    if( i == class_map.end() )
    {
      throw RTI::ObjectClassNotDefined( "" );
    }

    const attr_name_to_handle_map &attr_map = (*i).second;
    attr_name_to_handle_map::const_iterator j = attr_map.find( name );

    if( j == attr_map.end() )
    {
      throw RTI::NameNotFound( name.c_str() );
    }

    return( (*j).second );
  }

  static RTI::AttributeHandle get_attr_handle( const std::string &class_name,
                                               const std::string &attr_name )
  {
    if( class_name.empty() )
    {
      throw RTI::NameNotFound( attr_name.c_str() );
    }

    RTI::ObjectClassHandle class_handle = get_object_class_handle( class_name );

    RTI::AttributeHandle attr_handle;

    try
    {
      attr_handle = get_attr_handle( attr_name, class_handle );
    }
    catch( RTI::Exception & ) // Not found?
    {
      std::string parent = "";
      std::string::size_type pos = class_name.find_last_of( '.' );

      if( pos != std::string::npos )
      {
        parent = class_name.substr( 0, pos );
      }

      return get_attr_handle( parent, attr_name );
    }

    return attr_handle;
  }

  static std::size_t get_num_object_classes()
  {
    name_to_o_class_handle_map &class_map = get_name_to_o_class_handle_map();
    return class_map.size();
  }

  static RTI::InteractionClassHandle get_interaction_class_handle
    ( const std::string &name )
  {
    name_to_i_class_handle_map &class_map = get_name_to_i_class_handle_map();
    name_to_i_class_handle_map::const_iterator it = class_map.find( name );

    // Not found
    if( it == class_map.end() )
    {
      throw RTI::NameNotFound( name.c_str() );
    }

    return( (*it).second );
  }

  static RTI::ParameterHandle get_param_handle
    ( const std::string &name, RTI::InteractionClassHandle handle )
  {
    i_class_handle_to_param_map &class_map = get_i_class_handle_to_param_map();
    i_class_handle_to_param_map::const_iterator i = class_map.find( handle );

    if( i == class_map.end() )
    {
      throw RTI::InteractionClassNotDefined( "" );
    }

    const param_name_to_handle_map &param_map = (*i).second;
    param_name_to_handle_map::const_iterator j = param_map.find( name );

    if( j == param_map.end() )
    {
      throw RTI::NameNotFound( name.c_str() );
    }

    return( (*j).second );
  }

  static RTI::ParameterHandle get_param_handle( const std::string &class_name,
                                                const std::string &param_name )
  {
    if( class_name.empty() )
    {
      throw RTI::NameNotFound( param_name.c_str() );
    }

    RTI::InteractionClassHandle class_handle
      = get_interaction_class_handle( class_name );

    RTI::ParameterHandle param_handle;

    try
    {
      param_handle = get_param_handle( param_name, class_handle );
    }
    catch( RTI::Exception & ) // Not found?
    {
      std::string parent = "";
      std::string::size_type pos = class_name.find_last_of( '.' );

      if( pos != std::string::npos )
      {
        parent = class_name.substr( 0, pos );
      }

      return get_param_handle( parent, param_name );
    }

    return param_handle;
  }

  static std::size_t get_num_interaction_classes()
  {
    name_to_i_class_handle_map &class_map = get_name_to_i_class_handle_map();
    return class_map.size();
  }

  static void init_handles( RTI::RTIambassador &rti_amb )
  {
    init_o_class_handles( rti_amb );
    init_i_class_handles( rti_amb );
  }
 
  // Debug methods
  static void dump_stack()
  {
    attr_dft_type::dump_stack();
    param_dft_type::dump_stack();
  }

  static void print_object_class_handle_map()
  {
    name_to_o_class_handle_map &class_map = get_name_to_o_class_handle_map();
    name_to_o_class_handle_map::const_iterator it;
    for( it = class_map.begin(); it != class_map.end(); ++it )
    {
      std::cout << (*it).first << " = " << (*it).second << "\n";
    }
  }

  static void print_attr_handle_map()
  {
    o_class_handle_to_attr_map &class_map = get_o_class_handle_to_attr_map();
    o_class_handle_to_attr_map::const_iterator i;

    for( i = class_map.begin(); i != class_map.end(); ++i )
    {
      std::cout << (*i).first << " : " << "\n";

      const attr_name_to_handle_map &attr_map = (*i).second;
      attr_name_to_handle_map::const_iterator j;

      for( j = attr_map.begin(); j != attr_map.end(); ++j )
      {
        std::cout << "   " << (*j).first << " : " << (*j).second << "\n";
      }
    }
  }
};
  
/******************************************************************************/

}} // protox::hla

/******************************************************************************/

#endif

/******************************************************************************/
