/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_ATTR_HPP
#define PROTOX_HLA_ATTR_HPP

/**************************************************************************************************/
#include <vector>
#include <string>

#include <RTI.hh>

#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/back_inserter.hpp>

/**************************************************************************************************/

namespace protox { namespace hla {

/**************************************************************************************************/

using namespace boost;

/**************************************************************************************************/

template< typename T >
struct attr_base
{
  typedef T attr_type;
  typename T::value_type value;

  RTI::AttributeHandle handle;

  static char const *name() { return T::name(); }

  attr_base() : handle(0) {}
};

/**************************************************************************************************/

template< typename T >
struct attr
{
  typedef T value_type;
};

/**************************************************************************************************/

// Forward declaration
template< typename A, typename B > struct attr_inherit;

/**************************************************************************************************/

template< typename A >
struct attr_inherit< A, mpl::empty_base > : A, mpl::empty_base
{
  template< bool DONE, typename O_CLASS_VECTOR > struct init_class_handles;

  template< typename O_CLASS_VECTOR >
  struct init_class_handles< true, O_CLASS_VECTOR >
  {
    static void init(
      RTI::RTIambassador &,
      std::vector<RTI::ObjectClassHandle> &,
      const char *parentName = 0)
    {};
  };

  template< typename O_CLASS_VECTOR >
  struct init_class_handles< false, O_CLASS_VECTOR >
  {
    static void init(
      RTI::RTIambassador &rtiAmb,
      std::vector<RTI::ObjectClassHandle> &handles,
      const char *parentName = 0)
    {
      typedef typename mpl::front< O_CLASS_VECTOR >::type front_class;
      typedef typename mpl::pop_front< O_CLASS_VECTOR >::type class_vector_tail;

      std::string fullName;

      if (parentName != 0)
      {
        fullName = std::string(parentName) + "." + front_class::name_type::name();
      }
      else
      {
        fullName = front_class::name_type::name();
      }

      handles.push_back(rtiAmb.getObjectClassHandle(fullName.c_str()));

      init_class_handles<
        mpl::empty< class_vector_tail >::value,
        class_vector_tail
      >::init(rtiAmb, handles, fullName.c_str());
    }
  };

  template< typename O_CLASS_VECTOR >
  static RTI::AttributeHandle get_handle(RTI::RTIambassador &rtiAmb, const char *attr_name)
  {
    // A list of class handles for this vector of attributes.
    // Index 0 contains the least derived class handle, and index
    // (class_handles.size() - 1) contains the most derived handle.
    static std::vector<RTI::ObjectClassHandle> class_handles;

    // Need to initialize class handles?
    if (class_handles.empty())
    {
      init_class_handles<
        mpl::empty< O_CLASS_VECTOR >::value,
        O_CLASS_VECTOR
      >::init(rtiAmb, class_handles);

      std::cout << "          num class handles = " << class_handles.size() << "\n";
    }

    assert( attr_name != 0 );
    std::cout << "          attr name = " << attr_name << "\n";
    return 0;
  }

  template< typename O_CLASS_VECTOR >
  void init_handle(RTI::RTIambassador &rtiAmb)
  {
    A::handle = get_handle< O_CLASS_VECTOR >(rtiAmb, A::name());
  }
};

/**************************************************************************************************/

template< typename A, typename B >
struct attr_inherit : A, B
{
  template< typename T >
  inline typename T::value_type const &a_() const
  {
    return (static_cast< attr_base< T > const & >(*this).value);
  }

  template< typename T >
  inline typename T::value_type &a_()
  {
    return (static_cast< attr_base< T > & >(*this).value);
  }

  template< typename O_CLASS_VECTOR >
  void init_handle(RTI::RTIambassador &rtiAmb)
  {
    A::handle = B::template get_handle< O_CLASS_VECTOR >(rtiAmb, A::name());
    B::template init_handle< O_CLASS_VECTOR >(rtiAmb);
  }
};

//template< typename A >
//std::vector<RTI::ObjectClassHandle> attr_inherit<A, mpl::empty_base >::class_handles;

/**************************************************************************************************/

}} // protox::hla

/**************************************************************************************************/

#endif

/**************************************************************************************************/
