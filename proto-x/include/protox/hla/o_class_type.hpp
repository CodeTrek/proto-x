/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_O_CLASS_TYPE_HPP
#define PROTOX_HLA_O_CLASS_TYPE_HPP

/**************************************************************************************************/

#include <string>
#include <vector>
#include <set>

#include <RTI.hh>

#include <boost/shared_ptr.hpp>

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/inherit_linearly.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/back.hpp>

#include <protox/hla/x_class_vector.hpp>
#include <protox/hla/attr.hpp>
#include <protox/hla/build_full_name.hpp>

#include <protox/algorithm/string/tokenize.hpp>

/**************************************************************************************************/

namespace protox {
namespace hla {

/**************************************************************************************************/

template< typename SOM, typename Q_NAME_VECTOR >
struct o_class_type_impl
{
  // Computes this class' parent class.
  template< bool PARENT_NAME_IS_NULL, typename PARENT_Q_NAME  > struct parent_type_impl;

  template< typename PARENT_Q_NAME >
  struct parent_type_impl< true, PARENT_Q_NAME >
  {
    /**
     * Defines the root object class of an object class hierarchy.
     */
    struct type
    {
    private:
      typedef typename boost::mpl::inherit_linearly<
          typename SOM::o_class_table::attr_list_type,
          attr_inherit< attr_base< boost::mpl::placeholders::_2 >, boost::mpl::placeholders::_1 >,
          attr_empty_base
        >::type root_attrs_type;

      root_attrs_type attrs;

    protected:
      RTI::RTIambassador *rti_amb;
      RTI::ObjectHandle   obj_handle;
      std::string         obj_name;

      type() : rti_amb(0)
      {
        attrs.init_handles< SOM >( type::get_name() );
      }

      type( RTI::RTIambassador &rti_amb ) : rti_amb(&rti_amb)
      {
        attrs.init_handles< SOM >( type::get_name() );
      }

      static void parse_names( const std::string &names, std::set< std::string > &name_set )
      {
        std::vector< std::string > name_vec;
        protox::algorithm::string::tokenize( names, '.', name_vec );

        if( name_vec.empty() )
        {
          return;
        }

        name_set.insert( name_vec.begin(), name_vec.end() );
      }

      static void get_attr_handles( const std::string &class_name,
                                    std::set< std::string > *name_set,
                                    RTI::AttributeHandleSet &ahs )
      {
        root_attrs_type::template collect_handles< SOM >( class_name, name_set, ahs );
      }

      void get_attr_handles( std::vector< RTI::AttributeHandle > &attr_handles )
      {
        attrs.collect_updated_attrs( attr_handles );
      }

      void update_values( boost::shared_ptr< RTI::AttributeHandleValuePairSet > set_ptr )
      {
        attrs.update_values( set_ptr );
      }

    public:
      /**
       * \return The number of attributes defined for this class.
       */
      static RTI::ULong get_num_attrs()
      {
        return root_attrs_type::count_attrs();
      }

      /**
       * \return This class' fully qualified name.
       */
      static const std::string &get_name()
      {
        static std::string name = SOM::o_class_table::name_type::name();
        return name;
      }

      /**
       * \return This class' RTI assigned handle.
       */
      static RTI::ObjectClassHandle get_handle()
      {
        static bool initialized = false;
        static RTI::ObjectClassHandle handle;

        if( !initialized )
        {
          const std::string &name = type::get_name();
          handle = SOM::get_object_class_handle( name );
          initialized = true;
        }

        return handle;
      }


      /**
       * Sets this object's name.
       *
       * \param name The object's new name.
       */
      void set_obj_name( const std::string &name )
      {
        obj_name = name;
      }

      /**
       * \return This object's name.
       */
      const std::string &get_obj_name() const
      {
        return obj_name;
      }

      /**
       * Sets the RTI ambassador used to access object management services.
       */
      void set_rti( RTI::RTIambassador &rti_amb )
      {
        this->rti_amb = &rti_amb;
      }

      /**
       * Deletes this object at the given time.
       *
       * \param time (optional) The time of object deletion.
       */
      void delete_obj( RTI::FedTime *time = 0 )
      {
        if (rti_amb == 0)
        {
          // TODO: throw exception
          return;
        }

        if (time == 0)
        {
          rti_amb->deleteObjectInstance( obj_handle, "" );
        }
        else
        {
          rti_amb->deleteObjectInstance( obj_handle, *time, "" );
        }
      }

      /**
       * \return A read/write reference to the value of the attribute identified by \a T.
       *
       * \tparam T The type name of the attribute being retrieved.
       *
       * Example:
       *
       * \code
       *
       *  // Get the value of the Position attribute.
       *  value_type &value = platform_obj.a_< Position >();
       *
       * \endcode
       */
      template< typename T >
      inline typename T::value_type &a_()
      {
        return attrs.get_attribute< T >();
      }

      /**
       * \return A read-only reference to the value of the attribute identified by \a T.
       *
       * \tparam T The type name of the attribute being retrieved.
       *
       * Example:
       *
       * \code
       *
       *  // Get the value of the Position attribute.
       *  const value_type &value = platform_obj.a_< Position >();
       *
       * \endcode
       */
      template< typename T >
      inline typename T::value_type const &a_() const
      {
        return attrs.get_attribute< T >();
      }

      /**
       * \return The RTI handle assigned to the attribute identified by \a T.
       *
       * \tparam T The type name of the attribute.
       *
       * Example:
       *
       * \code
       *
       *  // Get the the handle of the Position attribute.
       *  RTI::AttributeHandle handl = platform_obj.get_attr_handle< Position >();
       *
       * \endcode
       */
      template< typename T >
      inline RTI::AttributeHandle get_attr_handle()
      {
        return attrs.get_attr_handle< T >();
      }

      /**
       * Updates attributes that have been modified since the last time this function was called.
       *
       * \param time (optional) The time of the update.
       */
      void update( RTI::FedTime *time = 0 )
      {
        if (rti_amb == 0)
        {
          // TODO: throw exception
          return;
        }

        std::vector< RTI::AttributeHandle > attr_handles;

        get_attr_handles( attr_handles );

        if( attr_handles.empty() )
        {
          return;
        }

        RTI::AttributeHandleValuePairSet
          *set = RTI::AttributeSetFactory::create( (RTI::ULong) attr_handles.size() );

        boost::shared_ptr< RTI::AttributeHandleValuePairSet > set_ptr( set );

        update_values( set_ptr );

        if( time == 0 )
        {
          rti_amb->updateAttributeValues( obj_handle, *set_ptr, "" );
        }
        else
        {
          rti_amb->updateAttributeValues( obj_handle, *set_ptr, *time, "" );
        }
      }

      void reflect( const RTI::AttributeHandleValuePairSet &ahv_set, const RTI::FedTime *time )
      {
        attrs.reflect( ahv_set, time );
      }
    };
  };

  // Query the SOM for this class's attribute definitions
  typedef typename boost::mpl::back<
    typename x_class_vector<
      typename SOM::o_class_table,
      Q_NAME_VECTOR
    >::type
  >::type::attr_list_type attr_defs_type;

  // Construct the local attribute vector from the attribute definitions
  typedef typename boost::mpl::inherit_linearly<
    attr_defs_type,
    attr_inherit< attr_base< boost::mpl::placeholders::_2 >, boost::mpl::placeholders::_1 >,
    attr_empty_base
  >::type attrs_type;

  template< typename PARENT_Q_NAME >
  struct parent_type_impl< false, PARENT_Q_NAME >
  {
    typedef typename o_class_type_impl< SOM, PARENT_Q_NAME >::type type;
  };

  // Compute this class' parent class name
  typedef typename boost::mpl::erase<
     Q_NAME_VECTOR,
     typename boost::mpl::prior< typename boost::mpl::end< Q_NAME_VECTOR >::type >::type
   >::type PARENT_Q_NAME_VECTOR;

  typedef typename parent_type_impl<
    boost::mpl::empty< PARENT_Q_NAME_VECTOR >::value,
    PARENT_Q_NAME_VECTOR
  >::type parent_class_type;

  template< bool B, typename T > struct compute_attr_getter;

  template< typename T >
  struct compute_attr_getter< true, T >
  {
    static typename T::value_type const &get_attr( const attrs_type &attrs, const parent_class_type * )
    {
      return attrs.get_attribute< T >();
    }

    static typename T::value_type &get_attr( attrs_type &attrs, parent_class_type * )
    {
      return attrs.get_attribute< T >();
    }
  };

  template< typename T >
  struct compute_attr_getter< false, T >
  {
    static typename T::value_type const &get_attr( const attrs_type &attrs, const parent_class_type *parent )
    {
      return parent->a_< T >();
    }

    static typename T::value_type &get_attr( attrs_type &attrs, parent_class_type *parent )
    {
      return parent->a_< T >();
    }
  };

  template< bool B, typename T > struct compute_get_attr_handle;

  template< typename T >
  struct compute_get_attr_handle< true, T >
  {
    static RTI::AttributeHandle get( attrs_type &attrs, parent_class_type * )
    {
      return attrs.get_attr_handle< T >();
    }
  };

  template< typename T >
  struct compute_get_attr_handle< false, T >
  {
    static RTI::AttributeHandle get( attrs_type &, parent_class_type *parent )
    {
      return parent->get_attr_handle< T >();
    }
  };

  /**
   * Defines a child object class.
   */
  struct type : parent_class_type
  {
  private:
    attrs_type attrs;

  protected:
    static void get_attr_handles( const std::string &class_name,
                                  std::set< std::string > *name_set,
                                  RTI::AttributeHandleSet &ahs )
    {
      attrs_type::template collect_handles< SOM >( class_name, name_set, ahs );
      parent_class_type::get_attr_handles( class_name, name_set, ahs );
    }

    void get_attr_handles( std::vector< RTI::AttributeHandle > &attr_handles )
    {
      attrs.collect_updated_attrs( attr_handles );
      parent_class_type::get_attr_handles( attr_handles );
    }

    void update_values( boost::shared_ptr< RTI::AttributeHandleValuePairSet > set_ptr )
    {
      attrs.update_values( set_ptr );
      parent_class_type::update_values( set_ptr );
    }

  public:

    /**
     * \return A read-only reference to the value of the attribute identified by \a T.
     *
     * \tparam T The type name of the attribute being retrieved.
     *
     * Example:
     *
     * \code
     *
     *  // Get the value of the Position attribute.
     *  const value_type &value = platform_obj.a_< Position >();
     *
     * \endcode
     */
    template< typename T >
    inline typename T::value_type const &a_() const
    {
      return compute_attr_getter< boost::mpl::contains< attr_defs_type, T >::value,
                                  T >::get_attr( attrs, this  );
    }

    /**
     * \return A read/write reference to the value of the attribute identified by \a T.
     *
     * \tparam T The type name of the attribute being retrieved.
     *
     * Example:
     *
     * \code
     *
     *  // Get the value of the Position attribute.
     *  value_type &value = platform_obj.a_< Position >();
     *
     * \endcode
     */
    template< typename T >
    inline typename T::value_type &a_()
    {
      return compute_attr_getter< boost::mpl::contains< attr_defs_type, T >::value,
                                  T >::get_attr( attrs, this  );
    }

    /**
     * \return The RTI handle assigned to the attribute identified by \a T.
     *
     * \tparam T The type name of the attribute.
     *
     * Example:
     *
     * \code
     *
     *  // Get the the handle of the Position attribute.
     *  RTI::AttributeHandle handl = platform_obj.get_attr_handle< Position >();
     *
     * \endcode
     */
    template< typename T >
    inline RTI::AttributeHandle get_attr_handle()
    {
      return compute_get_attr_handle< boost::mpl::contains< attr_defs_type, T >::value,
                                      T >::get( attrs, this );
    }

    /**
     * \return This class' fully qualified name.
     */
    static const std::string &get_name()
    {
      typedef typename x_class_vector< typename SOM::o_class_table,
                                       Q_NAME_VECTOR >::type x_class_vector_type;

      static bool initialized = false;
      static std::string name;

      if (!initialized)
      {
        boost::mpl::for_each< x_class_vector_type >( build_full_name( name ) );
        initialized = true;
      }

      return name;
    }

    /**
     * \return The class' RTI assigned handle.
     */
    static RTI::ObjectClassHandle get_handle()
    {
      static bool initialized = false;
      static RTI::ObjectClassHandle handle;

      if (!initialized)
      {
        const std::string &name = type::get_name();
        handle = SOM::get_object_class_handle( name );
        initialized = true;
      }

      return handle;
    }

    /**
     * \return The number of attributes defined for this class.
     */
    static RTI::ULong get_num_attrs()
    {
      return attrs_type::count_attrs() + parent_class_type::get_num_attrs();
    }

    /**
     * Publish all class attributes using the given RTI ambassador.
     *
     * \param rti_amb The RTI abmassador used to publish the class attributes.
     */
    static void publish( RTI::RTIambassador &rti_amb )
    {
      boost::shared_ptr< RTI::AttributeHandleSet >
        ahs( RTI::AttributeHandleSetFactory::create( type::get_num_attrs() ) );

      type::get_attr_handles( type::get_name(), 0, *ahs );

      rti_amb.publishObjectClass( type::get_handle(), *ahs );
    }

    /**
     * Publish a set of class attributes.
     *
     * \param attrs A string representation of the set of attributes to be published.
     * \param rti_amb The RTI abmassador used to publish this class attributes.
     *
     * \code
     *
     * // Publish the Position and Velocity attributes of the Platform class.
     * Platform::publish( rti_amb, "Position.Velocity" );
     *
     * \endcode
     */
    static void publish( RTI::RTIambassador &rti_amb, const std::string &attrs )
    {
      std::set< std::string > name_set;
      parse_names( attrs, name_set );

      if (name_set.empty())
      {
        return;
      }

      const RTI::ULong set_size = (RTI::ULong) name_set.size();

      boost::shared_ptr< RTI::AttributeHandleSet >
        ahs( RTI::AttributeHandleSetFactory::create( set_size ) );

      type::get_attr_handles( type::get_name(), &name_set, *ahs );

      // Undefined attributes?
      if (!name_set.empty())
      {
        std::string name = *name_set.begin();
        throw RTI::AttributeNotDefined( (name + " not defined").c_str() );
      }

      rti_amb.publishObjectClass( type::get_handle(), *ahs );
    }

    /**
     * Unpublish this class.
     *
     * \param rti_amb The RTI abmassador used to unpublish this class.
     */
    static void unpublish( RTI::RTIambassador &rti_amb )
    {
      rti_amb.unpublishObjectClass( type::get_handle() );
    }

    /**
     * Subscribe all class attributes.
     *
     * \param rti_amb The RTI abmassador used to subscribe this class.
     */
    static void subscribe( RTI::RTIambassador &rti_amb )
    {
      boost::shared_ptr<RTI::AttributeHandleSet>
        ahs( RTI::AttributeHandleSetFactory::create( type::get_num_attrs() ) );

      type::get_attr_handles( type::get_name(), 0, *ahs );

      rti_amb.subscribeObjectClassAttributes( type::get_handle(), *ahs );
    }

    /**
     * Subscribe a set of class attributes.
     *
     * \param attrs A string representation of the set of attributes to be subscribed.
     * \param rti_amb The RTI abmassador used to subscribe the class attributes.
     *
     * \code
     *
     * // Subscribe the Position and Velocity attributes of the Platform class.
     * Platform::subscribe( rti_amb, "Position.Velocity" );
     *
     * \endcode
     */
    static void subscribe( RTI::RTIambassador &rti_amb, const std::string &attrs )
    {
      std::set< std::string > name_set;
      parse_names( attrs, name_set );

      if (name_set.empty())
      {
        return;
      }

      const RTI::ULong set_size = (RTI::ULong) name_set.size();

      boost::shared_ptr< RTI::AttributeHandleSet >
        ahs( RTI::AttributeHandleSetFactory::create( set_size ) );

      type::get_attr_handles( type::get_name(), &name_set, *ahs );

      rti_amb.subscribeObjectClassAttributes( type::get_handle(), *ahs );
    }

    /**
     * Unsubscribe this class.
     *
     * \param rti_amb The RTI abmassador used to unsubscribe the class.
     */
    static void unsubscribe( RTI::RTIambassador &rti_amb )
    {
      rti_amb.unsubscribeObjectClass( type::get_handle() );
    }

    type()
    {
      attrs.attrs_type::template init_handles< SOM >( type::get_name() );
    }

    type( RTI::RTIambassador &rti_amb ) : parent_class_type(rti_amb)
    {
      attrs.attrs_type::template init_handles< SOM >( type::get_name() );
    }

    /**
     * Register this object at the given time.
     *
     * \param name The object's name.
     *
     */
    void register_obj( const std::string &name )
    {
      if (rti_amb == 0)
      {
        // TODO: throw exception
        return;
      }

      if (name.empty())
      {
        obj_handle = rti_amb->registerObjectInstance( type::get_handle() );
      }
      else
      {
        set_obj_name( name );
        obj_handle = rti_amb->registerObjectInstance( type::get_handle(), name.c_str() );
      }
    }

    /**
     * Updates attributes that have been modified since the last time this function was called.
     *
     * \param time (optional) The time of the update.
     */
    void update( RTI::FedTime *time = 0 )
    {
      if (rti_amb == 0)
      {
        // TODO: throw exception
        return;
      }

      std::vector< RTI::AttributeHandle > attr_handles;

      get_attr_handles( attr_handles );

      if (attr_handles.empty())
      {
        return;
      }

      RTI::AttributeHandleValuePairSet
        *set = RTI::AttributeSetFactory::create( (RTI::ULong) attr_handles.size() );

      boost::shared_ptr< RTI::AttributeHandleValuePairSet > set_ptr( set );

      update_values( set_ptr );

      if (time == 0)
      {
        rti_amb->updateAttributeValues( obj_handle, *set_ptr, "" );
      }
      else
      {
        rti_amb->updateAttributeValues( obj_handle, *set_ptr, *time, "" );
      }
    }

    void reflect( const RTI::AttributeHandleValuePairSet &ahv_set, const RTI::FedTime *time )
    {
      attrs.reflect( ahv_set, time );
      parent_class_type::reflect( ahv_set, time );
    }
  };
};

/**
 * Generates an object class type from the given SOM and fully qualified name.
 *
 * \tparam SOM A SOM that contains an interaction class table.
 * \tparam A fully qualified name in the form of a vector of name types.
 *
 * \sa protox::hla::attr
 * \sa protox::hla::o_class
 * \sa HLA_NAME
 *
 * Example:
 * \code
 *
 * typedef protox::hla::som< obj_class_table > som;
 *
 * // Generate a type for the "Entity.Platform.Aircraft" object class.
 * typedef o_class_type< som, q_name< Entity, Platform, Aircraft > >::type aircraft_type;
 *
 * aircraft_type air1;
 *
 * // Initialize air1's position.
 * air1.a_< Position >().f_< X >() = 0.0f;
 * air1.a_< Position >().f_< Y >() = 0.0f;
 *
 * \endcode
 */
template< typename SOM, typename Q_NAME_VECTOR >
struct o_class_type
{
  // Trim in trailing mpl::na types in the Q_NAME_VECTOR.

  // Ad a garbage item to Q_NAME_VECTOR and then remove it to yield the "trimmed"
  // Q_NAME_VECTOR.
  typedef typename boost::mpl::push_back< Q_NAME_VECTOR, int >::type Q_NAME_VECTOR_GARBAGE;

  typedef typename boost::mpl::erase<
    Q_NAME_VECTOR_GARBAGE,
    typename boost::mpl::prior< typename boost::mpl::end< Q_NAME_VECTOR_GARBAGE >::type >::type
  >::type TRIMMED_Q_NAME;

  typedef typename o_class_type_impl< SOM, TRIMMED_Q_NAME >::type type;
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
