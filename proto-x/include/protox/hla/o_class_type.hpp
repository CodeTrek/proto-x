/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_O_CLASS_TYPE_HPP
#define PROTOX_HLA_O_CLASS_TYPE_HPP

/**************************************************************************************************/

#include <boost/mpl/inherit_linearly.hpp>
#include <boost/mpl/placeholders.hpp>

#include <protox/hla/o_class_attr_vector.hpp>
#include <protox/hla/o_class_vector.hpp>
#include <protox/hla/attr.hpp>

/**************************************************************************************************/

namespace protox { namespace hla {

/**************************************************************************************************/

template<
  typename O_CLASS,
  typename QUALIFIED_NAME_VECTOR
> struct o_class_type
{
  // Construct the vector of attributes from the given
  // qualified name.
  typedef typename o_class_attr_vector<
    O_CLASS,
    QUALIFIED_NAME_VECTOR
  >::type attr_vector_type;

  // Construct the inheritence tree from the attribute vector.
  typedef typename mpl::inherit_linearly<
    attr_vector_type,
    attr_inherit< attr_base< boost::mpl::placeholders::_2 >, boost::mpl::placeholders::_1 >
  >::type attrs_type;

  struct type : attrs_type
  {
    private:
      static void init_handles( class RTI::RTIambassador &rtiAmb, type &obj )
      {
        typedef typename o_class_vector< O_CLASS, QUALIFIED_NAME_VECTOR >::type o_class_vector_type;
        obj.template init_handle< o_class_vector_type >(rtiAmb);
      }
    public:
      void init_handles(class RTI::RTIambassador &rtiAmb)
      {
        type::init_handles(rtiAmb, *this);
      }

      type()
      {
      }
  };
};

/**************************************************************************************************/

}} // namespace protox::hla

/**************************************************************************************************/

#endif

/**************************************************************************************************/
