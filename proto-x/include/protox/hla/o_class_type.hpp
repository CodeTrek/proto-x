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
#include <vector>
#include <set>

#include <RTI.hh>

#include <boost/shared_ptr.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/inherit_linearly.hpp>
#include <boost/mpl/placeholders.hpp>

#include <protox/hla/o_class_attr_vector.hpp>
#include <protox/hla/x_class_vector.hpp>
#include <protox/hla/attr.hpp>
#include <protox/hla/build_full_name.hpp>

#include <protox/algorithm/string/tokenize.hpp>

/******************************************************************************/

namespace protox { namespace hla {

/******************************************************************************/

template< typename SOM,
          typename QUALIFIED_NAME_VECTOR >
struct o_class_type
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
    attr_inherit< attr_base< boost::mpl::placeholders::_2 >,
                  boost::mpl::placeholders::_1 >
  >::type attrs_type;

  struct type : attrs_type
  {
    private:
      typedef typename
        x_class_vector< typename SOM::o_class_table,
                        QUALIFIED_NAME_VECTOR >::type x_class_vector_type;

      static void make_set( const std::string &names,
                            std::set< std::string > &name_set )
      {
        std::vector< std::string > name_vec;
        protox::algorithm::string::tokenize( names, '.', name_vec );

        if( name_vec.empty() )
        {
          return;
        }

        name_set.insert( name_vec.begin(), name_vec.end() );
      }

    public:
      static const std::string &get_name()
      {
        static bool initialized = false;
        static std::string name;

        if( !initialized )
        {
          boost::mpl::for_each< x_class_vector_type >
            ( build_full_name( name ) );

          initialized = true;
        }

        return name;
      }

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
      
      static RTI::ULong get_num_attrs()
      {
        return attrs_type::count_attrs();
      }
      
      /**
       * Publish all class attributes.
       */
      static void publish( RTI::RTIambassador &rti_amb )
      {
        boost::shared_ptr<RTI::AttributeHandleSet> ahs
          ( RTI::AttributeHandleSetFactory::create( type::get_num_attrs() ) );
          
        attrs_type::template collect_handles< SOM >( type::get_name(),
                                                     std::set< std::string >(),
                                                     *ahs );

        rti_amb.publishObjectClass( type::get_handle(), *ahs );
      }

      /**
       * Publish a set of class attributes.
       */
      static void publish( RTI::RTIambassador &rti_amb,
                           const std::string &attrs )
      {
        std::set< std::string > name_set;
        make_set( attrs, name_set );

        if( name_set.empty() )
        {
          return;
        }

        const RTI::ULong set_size = (RTI::ULong) name_set.size();

        boost::shared_ptr< RTI::AttributeHandleSet >
          ahs( RTI::AttributeHandleSetFactory::create( set_size ) );
          
        attrs_type::template collect_handles< SOM >( type::get_name(),
                                                     name_set,
                                                     *ahs );

        rti_amb.publishObjectClass( type::get_handle(), *ahs );
      }

      /**
       * Unpublish this class.
       */
      static void unpublish( RTI::RTIambassador &rti_amb )
      {
        rti_amb.unpublishObjectClass( type::get_handle() );
      }

      type()
      {
        attrs_type::template init_handles< SOM >( type::get_name() );
      }
  };
};

/******************************************************************************/

}} // protox::hla

/******************************************************************************/

#endif

/******************************************************************************/
