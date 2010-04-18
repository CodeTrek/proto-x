/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_I_CLASS_TYPE_HPP
#define PROTOX_HLA_I_CLASS_TYPE_HPP

/**************************************************************************************************/

#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/inherit_linearly.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/back.hpp>

#include <RTI.hh>

#include <protox/hla/i_class_param_vector.hpp>
#include <protox/hla/x_class_vector.hpp>
#include <protox/hla/param.hpp>
#include <protox/hla/build_full_name.hpp>

/**************************************************************************************************/

namespace protox {
namespace hla {

/**************************************************************************************************/

template< typename SOM, typename Q_NAME_VECTOR >
struct i_class_type_impl
{
  // Computes this class' parent class.
  template< bool PARENT_NAME_IS_NULL, typename PARENT_Q_NAME  > struct parent_type_impl;

  template< typename PARENT_Q_NAME >
  struct parent_type_impl< true, PARENT_Q_NAME >
  {
    /**
     * Defines the root interaction class of an interaction class hierarchy.
     */
    struct type
    {
    private:
      typedef typename boost::mpl::inherit_linearly<
          typename SOM::i_class_table::param_list_type,
          param_inherit< param_base< boost::mpl::placeholders::_2 >, boost::mpl::placeholders::_1 >,
          param_empty_base
        >::type root_params_type;

      root_params_type params;

    protected:
      RTI::RTIambassador *rti_amb;

      type() : rti_amb(0)
      {
        params.init_handles< SOM >( type::get_name() );
      }

      type( RTI::RTIambassador &rti_amb ) : rti_amb(&rti_amb)
      {
        params.init_handles< SOM >( type::get_name() );
      }

      void add_values( boost::shared_ptr< RTI::ParameterHandleValuePairSet > set_ptr )
      {
        params.add_values( set_ptr );
      }

    public:
      /**
       * \return This class' fully qualified name.
       */
      static const std::string &get_name()
      {
        static std::string name = SOM::i_class_table::name_type::name();
        return name;
      }

      /**
       * \return This class' RTI assigned handle.
       */
      static RTI::ObjectClassHandle get_handle()
      {
        static bool initialized = false;
        static RTI::ObjectClassHandle handle;

        if (!initialized)
        {
          const std::string &name = type::get_name();
          handle = SOM::get_interaction_class_handle( name );
          initialized = true;
        }

        return handle;
      }

      /**
       * \return The number of parameters defined for this class.
       */
      static RTI::ULong get_num_params()
      {
        return root_params_type::count_params();
      }

      /**
       * Sets the RTI ambassador used to access interaction management services.
       */
      void set_rti( RTI::RTIambassador &rti_amb )
      {
        this->rti_amb = &rti_amb;
      }

      /**
       * \return A read/write reference to the value of the parameter identified by \a T.
       *
       * \tparam T The type name of the parameter being retrieved.
       *
       * Example:
       *
       * \code
       *
       *  // Get the value of the Target parameter.
       *  value_type &value = fire_event.p_< Target >();
       *
       * \endcode
       */
      template< typename T >
      inline typename T::value_type &p_()
      {
        return params.get_parameter< T >();
      }

      /**
       * \return A read-only reference to the value of the parameter identified by \a T.
       *
       * \tparam T The type name of the parameter being retrieved.
       *
       * Example:
       *
       * \code
       *
       *  // Get the value of the Target parameter.
       *  const value_type &value = fire_event.p_< Target >();
       *
       * \endcode
       */
      template< typename T >
      inline typename T::value_type const &p_() const
      {
        return params.get_parameter< T >();
      }

      /**
       * \return The RTI handle assigned to the parameter identified by \a T.
       *
       * \tparam T The type name of the parameter.
       *
       * Example:
       *
       * \code
       *
       *  // Get the the handle of the Target parameter.
       *  RTI::ParameterHandle handle = fire_event.get_attr_handle< Target >();
       *
       * \endcode
       */
      template< typename T >
      inline RTI::ParameterHandle get_param_handle()
      {
        return params.get_param_handle< T >();
      }

      void recv( const RTI::ParameterHandleValuePairSet &param_set )
      {
        params.recv_values( param_set );
      }
    };
  };

  // Query the SOM for this class' parameter definitions
  typedef typename boost::mpl::back<
    typename x_class_vector<
      typename SOM::i_class_table,
      Q_NAME_VECTOR
    >::type
  >::type::param_list_type param_defs_type;

  // Construct the local attribute vector from the attribute definitions
  typedef typename boost::mpl::inherit_linearly<
    param_defs_type,
    param_inherit< param_base< boost::mpl::placeholders::_2 >, boost::mpl::placeholders::_1 >,
    param_empty_base
  >::type params_type;

  template< typename PARENT_Q_NAME >
  struct parent_type_impl< false, PARENT_Q_NAME >
  {
    typedef typename i_class_type_impl< SOM, PARENT_Q_NAME >::type type;
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

  template< bool B, typename T > struct compute_param_getter;

  template< typename T >
  struct compute_param_getter< true, T >
  {
    static typename T::value_type const &get_param( const params_type &params,
                                                    const parent_class_type * )
    {
      return params.get_parameter< T >();
    }

    static typename T::value_type &get_param( params_type &params, parent_class_type * )
    {
      return params.get_parameter< T >();
    }
  };

  template< typename T >
  struct compute_param_getter< false, T >
  {
    static typename T::value_type const &get_param( const params_type &,
                                                    const parent_class_type *parent )
    {
      return parent->p_< T >();
    }

    static typename T::value_type &get_param( params_type &, parent_class_type *parent )
    {
      return parent->p_< T >();
    }
  };

  template< bool B, typename T > struct compute_get_param_handle;

  template< typename T >
  struct compute_get_param_handle< true, T >
  {
    static RTI::ParameterHandle get( params_type &params, parent_class_type * )
    {
      return params.get_param_handle< T >();
    }
  };

  template< typename T >
  struct compute_get_param_handle< false, T >
  {
    static RTI::ParameterHandle get( params_type &, parent_class_type *parent )
    {
      return parent->get_param_handle< T >();
    }
  };

  /**
   * Defines a child interaction class.
   */
  struct type : parent_class_type
  {
  private:
    params_type params;

    typedef typename
      x_class_vector< typename SOM::i_class_table, Q_NAME_VECTOR >::type x_class_vector_type;

  protected:
    void add_values( boost::shared_ptr< RTI::ParameterHandleValuePairSet > set_ptr )
    {
      params.add_values( set_ptr );
      parent_class_type::add_values( set_ptr );
    }

  public:
    /**
     * \return This class' fully qualified name.
     */
    static const std::string &get_name()
    {
      static bool initialized = false;
      static std::string name;

      if (!initialized)
      {
        boost::mpl::for_each< x_class_vector_type >( build_full_name( name ) );
        initialized = true;
      }

      return name;
    }

    type()
    {
      params.params_type::template init_handles< SOM >( type::get_name() );
    }

    type( RTI::RTIambassador &rti_amb ) : parent_class_type(rti_amb)
    {
      params.params_type::template init_handles< SOM >( type::get_name() );
    }

    /**
     * \return A read/write reference to the value of the parameter identified by \a T.
     *
     * \tparam T The type name of the parameter being retrieved.
     *
     * Example:
     *
     * \code
     *
     *  // Get the value of the Target parameter.
     *  value_type &value = fire_event.p_< Target >();
     *
     * \endcode
     */
    template< typename T >
    inline typename T::value_type const &p_() const
    {
      return compute_param_getter< boost::mpl::contains< param_defs_type, T >::value,
                                   T >::get_param( params, this  );
    }

    /**
     * \return A read-only reference to the value of the parameter identified by \a T.
     *
     * \tparam T The type name of the parameter being retrieved.
     *
     * Example:
     *
     * \code
     *
     *  // Get the value of the Target parameter.
     *  const value_type &value = fire_event.p_< Target >();
     *
     * \endcode
     */
    template< typename T >
    inline typename T::value_type &p_()
    {
      return compute_param_getter< boost::mpl::contains< param_defs_type, T >::value,
                                   T >::get_param( params, this  );
    }

    /**
     * \return The RTI handle assigned to the parameter identified by \a T.
     *
     * \tparam T The type name of the parameter.
     *
     * Example:
     *
     * \code
     *
     *  // Get the the handle of the Target parameter.
     *  RTI::ParameterHandle handle = fire_event.get_attr_handle< Target >();
     *
     * \endcode
     */
    template< typename T >
    inline RTI::ParameterHandle get_param_handle()
    {
      return compute_get_param_handle< boost::mpl::contains< param_defs_type, T >::value,
                                       T >::get( params, this );
    }

    /**
     * \return This class' RTI assigned handle.
     */
    static RTI::InteractionClassHandle get_handle()
    {
      static bool initialized = false;
      static RTI::InteractionClassHandle handle;

      if (!initialized)
      {
        const std::string &name = type::get_name();
        handle = SOM::get_interaction_class_handle( name );
        initialized = true;
      }

      return handle;
    }

    /**
     * \return The number of parameters defined for this class.
     */
    static unsigned long get_num_params()
    {
      return params_type::count_params() + parent_class_type::get_num_params();
    }

    /**
     * Publish this interaction.
     *
     * \param rti_amb The RTI abmassador used to publish this class.
     *
     * \code
     *
     * FireEvent::publish( rti_amb );
     *
     * \endcode
     */
    static void publish( RTI::RTIambassador &rti_amb )
    {
      rti_amb.publishInteractionClass( type::get_handle() );
    }

    /**
     * Un-publish this interaction.
     *
     * \param rti_amb The RTI abmassador used to un-publish this class.
     *
     * \code
     *
     * FireEvent::unpublish( rti_amb );
     *
     * \endcode
     */
    static void unpublish( RTI::RTIambassador &rti_amb )
    {
      rti_amb.unpublishInteractionClass( type::get_handle() );
    }

    /**
     * Subscribe this interaction.
     *
     * \param rti_amb The RTI abmassador used to subscribe this class.
     *
     * \code
     *
     * FireEvent::subscribe( rti_amb );
     *
     * \endcode
     */
    static void subscribe( RTI::RTIambassador &rti_amb )
    {
      rti_amb.subscribeInteractionClass( type::get_handle() );
    }

    /**
     * Un-subscribe this interaction.
     *
     * \param rti_amb The RTI abmassador used to un-subscribe this class.
     *
     * \code
     *
     * FireEvent::unsubscribe( rti_amb );
     *
     * \endcode
     */
    static void unsubscribe( RTI::RTIambassador &rti_amb )
    {
      rti_amb.unsubscribeInteractionClass( type::get_handle() );
    }

    /**
     * Send an instance of this interaction at the given time.
     *
     * \param time (optional) The interaction's time.
     *
     * \code
     *
     * fire_event.send( rti_amb );
     *
     * \endcode
     */
    void send( const RTI::FedTime *time = 0 )
    {
      if (rti_amb == 0)
      {
        // TODO: throw exception
        return;
      }

      RTI::ParameterHandleValuePairSet *
        set = RTI::ParameterSetFactory::create( type::get_num_params() );

      boost::shared_ptr< RTI::ParameterHandleValuePairSet > set_ptr( set );

      add_values( set_ptr );

      if (time == 0)
      {
        rti_amb->sendInteraction( type::get_handle(), *set_ptr, "" );
      }
      else
      {
        rti_amb->sendInteraction( type::get_handle(), *set_ptr, *time, "" );
      }
    }

    void recv( const RTI::ParameterHandleValuePairSet &param_set )
    {
      params.recv_values( param_set );
      parent_class_type::recv( param_set );
    }
  };
};

/**************************************************************************************************/

/**
 * Generates an interaction class type from the given SOM and fully qualified name.
 *
 * \tparam SOM A SOM that contains an interaction class table.
 * \tparam A fully qualified name in the form of a vector of name types.
 *
 * \sa protox::hla::param
 * \sa protox::hla::i_class
 * \sa HLA_NAME
 *
 * Example:
 * \code
 *
 * typedef protox::hla::som< obj_class_table, interaction_class_table > som;
 *
 * // Generate a type for the "Event.FireEvent" object class.
 * typedef i_class_type< som, q_name< Event, FireEvent > >::type fire_event_type;
 *
 * fire_event_type fire;
 *
 * // Initialize fire's Target parameter.
 * fire.p_< Target >() = 20;
 *
 * \endcode
 */
template< typename SOM, typename Q_NAME_VECTOR >
struct i_class_type
{
  // Trim in trailing mpl::na types in the Q_NAME_VECTOR.

  // Ad a garbage item to Q_NAME_VECTOR and then remove it to yield the "trimmed"
  // Q_NAME_VECTOR.
  typedef typename boost::mpl::push_back< Q_NAME_VECTOR, int >::type Q_NAME_VECTOR_GARBAGE;

  typedef typename boost::mpl::erase<
    Q_NAME_VECTOR_GARBAGE,
    typename boost::mpl::prior< typename boost::mpl::end< Q_NAME_VECTOR_GARBAGE >::type >::type
  >::type TRIMMED_Q_NAME;

  typedef typename i_class_type_impl< SOM, TRIMMED_Q_NAME >::type type;
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
