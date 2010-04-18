/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_SOM_HPP
#define PROTOX_HLA_SOM_HPP

/**************************************************************************************************/

#include <RTI.hh>

#include <assert.h>
#include <string>
#include <iostream>

#include <protox/hla/name_to_o_class_handle_map.hpp>
#include <protox/hla/name_to_i_class_handle_map.hpp>
#include <protox/hla/o_class_child_to_parent_map.hpp>
#include <protox/hla/i_class_child_to_parent_map.hpp>
#include <protox/hla/class_handle_to_attr_handle_map.hpp>
#include <protox/hla/build_full_name.hpp>
#include <protox/hla/o_class.hpp>
#include <protox/hla/i_class.hpp>
#include <protox/hla/attr_dft.hpp>
#include <protox/hla/param_dft.hpp>

/**************************************************************************************************/

/**
 * \namespace protox::hla
 *
 * Contains the API used to define an HLA simulation object model (SOM).
 */
namespace protox {
namespace hla {

/**************************************************************************************************/

/**
 * This class combines object and interaction class tables to form a single interface to your
 * simulation object model (SOM) components. You use this interface to intialize RTI handles
 * (e.g., object and interaction class handles as well as attribute and parameter handles).
 *
 * \tparam ROOT_O_CLASS An object class table definition.
 * \tparam ROOT_I_CLASS An interaction class table definition.
 *
 * \sa protox::hla::o_class
 * \sa protox::hla::i_class
 *
 * Example:
 * \code
 *
 * // Define SOM type.
 * typedef hla::som< obj_class_table, interaction_class_table > som_type;
 *
 * // Join a federation
 * RTI::RTIambassador rti_amb;
 * rti_amb.joinFederationExecution( federate_name, federation_name, &fed_amb );
 *
 * // Create a SOM object.
 * som_type a_som;
 *
 * // Initialize class, attribute, and parameter handles.
 * a_som::init_handles( rti_amb );
 *
 * \endcode
 */
template< typename ROOT_O_CLASS = null_o_class, typename ROOT_I_CLASS = null_i_class >
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
    hla::name_to_o_class_handle_map &o_class_map = get_name_to_o_class_handle_map();
      
    // Maps is already populated? 
    if (!o_class_map.empty())
    {
      return;
    }
      
    hla::o_class_handle_to_attr_map &attr_map = get_o_class_handle_to_attr_map();

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
    hla::name_to_i_class_handle_map &i_class_map = get_name_to_i_class_handle_map();
      
    // Map is already populated? 
    if (!i_class_map.empty())
    {
      return;
    }
      
    hla::i_class_handle_to_param_map &param_map = get_i_class_handle_to_param_map();

    assert( param_map.empty() );
      
    param_dft_type::init_i_class_handles( rti_amb, i_class_map, param_map );
  }
  
  static hla::o_class_child_to_parent_map &get_o_class_child_to_parent_map()
  {
    static protox::hla::o_class_child_to_parent_map map;
    return map;
  }

  static void init_o_class_ancestors()
  {
    const hla::name_to_o_class_handle_map &class_map = get_name_to_o_class_handle_map();
    hla::o_class_child_to_parent_map &parent_map = get_o_class_child_to_parent_map();

    if (!parent_map.empty())
    {
      return;
    }

    attr_dft_type::init_o_class_ancestors( class_map, parent_map );
  }

  static hla::i_class_child_to_parent_map &get_i_class_child_to_parent_map()
  {
    static protox::hla::i_class_child_to_parent_map map;
    return map;
  }

  static void init_i_class_ancestors()
  {
    const hla::name_to_i_class_handle_map &class_map = get_name_to_i_class_handle_map();
    hla::i_class_child_to_parent_map &parent_map = get_i_class_child_to_parent_map();

    if (!parent_map.empty())
    {
      return;
    }

    param_dft_type::init_i_class_ancestors( class_map, parent_map );
  }

public: 
  /**
   * The SOM's object class table.
   *
   * \sa protox::hla::o_class
   */
  typedef ROOT_O_CLASS o_class_table;

  /**
   * The SOM's interactionn class table.
   *
   * \sa protox::hla::i_class
   */
  typedef ROOT_I_CLASS i_class_table;

  /**
   * \param parent An object class handle.
   * \param child An object class handle.
   *
   * \return true, if the given parent class handle identifies a class that is an ancestor of the
   *         class identified by the given child class handle.
   */
  static bool is_o_class_ancstor( RTI::ObjectClassHandle parent, RTI::ObjectClassHandle child )
  {
    hla::o_class_child_to_parent_map &parent_map = get_o_class_child_to_parent_map();
    hla::o_class_child_to_parent_map::const_iterator it = parent_map.find( child );

    if (it == parent_map.end())
    {
      return false;
    }

    if (it->second == parent)
    {
      return true;
    }

    return is_o_class_ancestor( parent, it->second );
  }

  /**
   * \param parent An interaction class handle.
   * \param child An interaction class handle.
   *
   * \return true, if the given parent class handle identifies a class that is an ancestor of the
   *         class identified by the given child class handle.
   */
  static bool is_i_class_ancstor( RTI::InteractionClassHandle parent,
                                  RTI::InteractionClassHandle child )
  {
    hla::i_class_child_to_parent_map &parent_map = get_i_class_child_to_parent_map();

    hla::i_class_child_to_parent_map::const_iterator it = parent_map.find( child );

    if (it == parent_map.end())
    {
      return false;
    }

    if (it->second == parent)
    {
      return true;
    }

    return is_i_class_ancestor( parent, it->second );
  }

  /**
   * \param name A fully qualified object class name.
   *
   * \return The handle of the object class identified by the given fully qualified name.
   *
   * \throws RTI::NameNotFound.
   */
  static RTI::ObjectClassHandle get_object_class_handle( const std::string &name )
  {
    name_to_o_class_handle_map &class_map = get_name_to_o_class_handle_map();
    name_to_o_class_handle_map::const_iterator it = class_map.find(name);

    // Not found
    if (it == class_map.end())
    {
      throw RTI::NameNotFound( name.c_str() );
    }

    return ((*it).second);
  }

  /**
   * \param name An attribute name.
   * \param handle An object class handle.
   *
   * \return The handle of the attribute identified by the given name and object class handle.
   *
   * \throws RTI::ObjectClassNotDefined.
   * \throws RTI::NameNotDefined.
   */
  static RTI::AttributeHandle get_attr_handle( const std::string &name,
                                               RTI::ObjectClassHandle handle )
  {
    o_class_handle_to_attr_map &class_map = get_o_class_handle_to_attr_map();
    o_class_handle_to_attr_map::const_iterator i = class_map.find( handle );

    if (i == class_map.end())
    {
      throw RTI::ObjectClassNotDefined( "" );
    }

    const attr_name_to_handle_map &attr_map = (*i).second;
    attr_name_to_handle_map::const_iterator j = attr_map.find( name );

    if (j == attr_map.end())
    {
      throw RTI::NameNotFound( name.c_str() );
    }

    return ((*j).second);
  }

  /**
   * \param class_name A fully qualified object classs name.
   * \param attr_name An attribute name.
   *
   * \return The handle of the attribute identified by the given object class name and
   *         attribute name.
   *
   * \throws RTI::NameNotDefined.
   */
  static RTI::AttributeHandle get_attr_handle( const std::string &class_name,
                                               const std::string &attr_name )
  {
    if (class_name.empty())
    {
      throw RTI::NameNotFound( attr_name.c_str() );
    }

    RTI::ObjectClassHandle class_handle = get_object_class_handle( class_name );

    RTI::AttributeHandle attr_handle;

    try
    {
      attr_handle = get_attr_handle( attr_name, class_handle );
    }
    catch (RTI::Exception &) // Not found?
    {
      std::string parent = "";
      std::string::size_type pos = class_name.find_last_of( '.' );

      if (pos != std::string::npos)
      {
        parent = class_name.substr( 0, pos );
      }

      return get_attr_handle( parent, attr_name );
    }

    return attr_handle;
  }

  /**
   * \return The number of object classes in this SOM's object class table.
   */
  static std::size_t get_num_object_classes()
  {
    name_to_o_class_handle_map &class_map = get_name_to_o_class_handle_map();
    return class_map.size();
  }

  /**
   * \param name A fully qualified interaction class name.
   *
   * \return The handle of the interaction class identified by the given fully qualified name.
   *
   * \throws RTI::NameNotFound.
   */
  static RTI::InteractionClassHandle get_interaction_class_handle( const std::string &name )
  {
    name_to_i_class_handle_map &class_map = get_name_to_i_class_handle_map();
    name_to_i_class_handle_map::const_iterator it = class_map.find( name );

    // Not found
    if (it == class_map.end())
    {
      throw RTI::NameNotFound( name.c_str() );
    }

    return ((*it).second);
  }

  /**
   * \param name A parameter name.
   * \param handle An interaction class handle.
   *
   * \return The handle of the parameter identified by the given name and interaction class handle.
   *
   * \throws RTI::InteractionClassNotDefined.
   * \throws RTI::NameNotDefined.
   */
  static RTI::ParameterHandle get_param_handle( const std::string &name,
                                                RTI::InteractionClassHandle handle )
  {
    i_class_handle_to_param_map &class_map = get_i_class_handle_to_param_map();
    i_class_handle_to_param_map::const_iterator i = class_map.find( handle );

    if (i == class_map.end())
    {
      throw RTI::InteractionClassNotDefined( "" );
    }

    const param_name_to_handle_map &param_map = (*i).second;
    param_name_to_handle_map::const_iterator j = param_map.find( name );

    if (j == param_map.end())
    {
      throw RTI::NameNotFound( name.c_str() );
    }

    return ((*j).second);
  }

  /**
   * \param class_name A fully qualified interaction class name.
   * \param param_name A parameter name.
   *
   * \return The handle of the parameter identified by the given interaction class name and
   *         parameter name.
   *
   * \throws RTI::NameNotDefined.
   */
  static RTI::ParameterHandle get_param_handle( const std::string &class_name,
                                                const std::string &param_name )
  {
    if (class_name.empty())
    {
      throw RTI::NameNotFound( param_name.c_str() );
    }

    RTI::InteractionClassHandle class_handle = get_interaction_class_handle( class_name );

    RTI::ParameterHandle param_handle;

    try
    {
      param_handle = get_param_handle( param_name, class_handle );
    }
    catch( RTI::Exception & ) // Not found?
    {
      std::string parent = "";
      std::string::size_type pos = class_name.find_last_of( '.' );

      if (pos != std::string::npos)
      {
        parent = class_name.substr( 0, pos );
      }

      return get_param_handle( parent, param_name );
    }

    return param_handle;
  }

  /**
   * \return The number of interaction classes in this SOM's interaction class table.
   */
  static std::size_t get_num_interaction_classes()
  {
    name_to_i_class_handle_map &class_map = get_name_to_i_class_handle_map();
    return class_map.size();
  }

  /**
   * Uses the given RTI ambassador to initialze the class, attribute, and parameter handles defined
   * in this SOM's object and interaction class tables.
   *
   * \param rti_amb The RTI ambassador used to intialize this SOM's class, attribute, and parameter
   *                handles.
   */
  static void init_handles( RTI::RTIambassador &rti_amb )
  {
    init_o_class_handles( rti_amb );
    init_i_class_handles( rti_amb );

    init_o_class_ancestors();
    init_i_class_ancestors();
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

    for (it = class_map.begin(); it != class_map.end(); ++it)
    {
      std::cout << (*it).first << " = " << (*it).second << "\n";
    }
  }

  static void print_attr_handle_map()
  {
    o_class_handle_to_attr_map &class_map = get_o_class_handle_to_attr_map();
    o_class_handle_to_attr_map::const_iterator i;

    for (i = class_map.begin(); i != class_map.end(); ++i)
    {
      std::cout << (*i).first << " : " << "\n";

      const attr_name_to_handle_map &attr_map = (*i).second;
      attr_name_to_handle_map::const_iterator j;

      for (j = attr_map.begin(); j != attr_map.end(); ++j)
      {
        std::cout << "   " << (*j).first << " : " << (*j).second << "\n";
      }
    }
  }
};
  
/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
