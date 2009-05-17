/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_HLA_I_CLASS_TYPE_HPP
#define PROTOX_HLA_I_CLASS_TYPE_HPP

/******************************************************************************/

#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/inherit_linearly.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/size.hpp>

#include <RTI.hh>

#include <protox/hla/i_class_param_vector.hpp>
#include <protox/hla/x_class_vector.hpp>
#include <protox/hla/param.hpp>
#include <protox/hla/build_full_name.hpp>

/******************************************************************************/

namespace protox { namespace hla {

/******************************************************************************/

template<
  typename SOM,
  typename QUALIFIED_NAME_VECTOR
> struct i_class_type
{
  // Construct the vector of paramibutes from the given
  // qualified name.
  typedef typename i_class_param_vector<
    typename SOM::i_class_table,
    QUALIFIED_NAME_VECTOR
  >::type param_vector_type;

  // Construct the inheritence tree from the paramibute vector.
  typedef typename boost::mpl::inherit_linearly<
    param_vector_type,
    param_inherit<
      param_base< boost::mpl::placeholders::_2 >,
      boost::mpl::placeholders::_1 >
  >::type params_type;

  struct type : params_type
  {
    private:
      typedef typename
        x_class_vector<
          typename SOM::i_class_table,
          QUALIFIED_NAME_VECTOR
        >::type x_class_vector_type;

      RTI::RTIambassador *rti_amb;

    public:
      static const std::string &get_name()
      {
        static bool initialized = false;
        static std::string name;

        if (!initialized)
        {
          boost::mpl::for_each< x_class_vector_type >(build_full_name(name));
          initialized = true;
        }

        return name;
      }

      static RTI::InteractionClassHandle get_handle()
      {
        static bool initialized = false;
        static RTI::InteractionClassHandle handle; 

        if (!initialized)
        {
          const std::string &name = type::get_name();
          handle = SOM::get_interaction_class_handle(name);
          initialized = true;
        }

        return handle;
      }

      static void publish(RTI::RTIambassador &rti_amb)
      {
        rti_amb.publishInteractionClass(type::get_handle());
      }

      static void unpublish(RTI::RTIambassador &rti_amb)
      {
        rti_amb.unpublishInteractionClass(type::get_handle());
      }

      static unsigned long get_num_parameters()
      {
        return boost::mpl::size<param_vector_type>::value;
      }

      type() : rti_amb(0)
      {
        params_type::template init_handles< SOM >(type::get_name());
      }

      type(RTI::RTIambassador &rti_amb) : rti_amb(&rti_amb)
      {
        params_type::template init_handles< SOM >(type::get_name());
      }

      void set_rti(RTI::RTIambassador &rti_amb)
      {
        this->rti_amb = &rti_amb;
      }

      void send()
      {
        if (rti_amb == 0)
        {
          // TODO: throw exception
          return;
        }

        RTI::ParameterHandleValuePairSet *set
          = RTI::ParameterSetFactory::create(type::get_num_parameters());

        boost::shared_ptr<RTI::ParameterHandleValuePairSet> set_ptr(set);

        params_type::add_values(set_ptr);
      }
  };
};

/******************************************************************************/

}} // protox::hla

/******************************************************************************/

#endif

/******************************************************************************/
