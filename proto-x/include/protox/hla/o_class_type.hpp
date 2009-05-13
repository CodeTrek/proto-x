/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_HLA_O_CLASS_TYPE_HPP
#define PROTOX_HLA_O_CLASS_TYPE_HPP

/******************************************************************************/

#include <string>

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/inherit_linearly.hpp>
#include <boost/mpl/placeholders.hpp>

#include <protox/hla/o_class_attr_vector.hpp>
#include <protox/hla/o_class_vector.hpp>
#include <protox/hla/attr.hpp>
#include <protox/hla/build_full_name.hpp>

/******************************************************************************/

namespace protox { namespace hla {

/******************************************************************************/

template<
  typename SOM,
  typename QUALIFIED_NAME_VECTOR
> struct o_class_type
{
  // Construct the vector of attributes from the given
  // qualified name.
  typedef typename o_class_attr_vector<
    typename SOM::o_class_table,
    QUALIFIED_NAME_VECTOR
  >::type attr_vector_type;

  // Construct the inheritence tree from the attribute vector.
  typedef typename boost::mpl::inherit_linearly<
    attr_vector_type,
    attr_inherit<
      attr_base< boost::mpl::placeholders::_2 >,
      boost::mpl::placeholders::_1 >
  >::type attrs_type;

  struct type : attrs_type
  {
    private:
      typedef typename
        o_class_vector<
          typename SOM::o_class_table,
          QUALIFIED_NAME_VECTOR
        >::type o_class_vector_type;

      std::string full_name;
      RTI::ObjectClassHandle handle;

    public:
      static const std::string &get_name()
      {
        static bool initialized = false;
        static std::string name;

        if (!initialized)
        {
          boost::mpl::for_each< o_class_vector_type >(build_full_name(name));
          initialized = true;
        }

        return name;
      }

      static RTI::ObjectClassHandle get_handle()
      {
        static bool initialized = false;
        static RTI::ObjectClassHandle handle; 

        if (!initialized)
        {
          const std::string &name = type::get_name();
          handle = SOM::get_object_class_handle(name);
          initialized = true;
        }

        return handle;
      }

      type() {}
  };
};

/******************************************************************************/

}} // protox::hla

/******************************************************************************/

#endif

/******************************************************************************/
