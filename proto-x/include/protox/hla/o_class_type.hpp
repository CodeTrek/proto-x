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

      RTI::RTIambassador *rti_amb;
      RTI::ObjectHandle obj_handle;
      std::string obj_name;

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

        std::set< std::string > empty_name_set;

        attrs_type::template collect_handles< SOM >( type::get_name(),
                                                     empty_name_set,
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

      /**
       * Subscribe all class attributes.
       */
      static void subscribe( RTI::RTIambassador &rti_amb )
      {
        boost::shared_ptr<RTI::AttributeHandleSet> ahs
          ( RTI::AttributeHandleSetFactory::create( type::get_num_attrs() ) );

        std::set< std::string > empty_name_set;

        attrs_type::template collect_handles< SOM >( type::get_name(),
                                                     empty_name_set,
                                                     *ahs );

        rti_amb.subscribeObjectClassAttributes( type::get_handle(), *ahs );
      }

      /**
       * Subscribe a set of class attributes.
       */
      static void subscribe( RTI::RTIambassador &rti_amb,
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

        rti_amb.subscribeObjectClassAttributes( type::get_handle(), *ahs );
      }

      /**
       * Unsubscribe this class.
       */
      static void unsubscribe( RTI::RTIambassador &rti_amb )
      {
        rti_amb.unsubscribeObjectClass( type::get_handle() );
      }

      type() : rti_amb(0)
      {
        attrs_type::template init_handles< SOM >( type::get_name() );
      }

      type( RTI::RTIambassador &rti_amb ) : rti_amb(&rti_amb)
      {
        attrs_type::template init_handles< SOM >( type::get_name() );
      }

      void set_obj_name( const std::string &name ) { obj_name = name; }
      const std::string &get_obj_name() const { return obj_name; }

      void set_rti( RTI::RTIambassador &rti_amb )
      {
        this->rti_amb = &rti_amb;
      }

      void register_obj( const std::string &name )
      {
        if( rti_amb == 0 )
        {
          // TODO: throw exception
          return;
        }

        if( name.empty() )
        {
          obj_handle = rti_amb->registerObjectInstance( type::get_handle() );
        }
        else
        {
          set_obj_name( name );
          obj_handle = rti_amb->registerObjectInstance( type::get_handle(),
                                                        name.c_str() );
        }
      }

      void register_obj() { register_obj(""); }
    
      void update( RTI::FedTime *time = 0 )
      {
        if( rti_amb == 0 )
        {
          // TODO: throw exception
          return;
        }

        std::vector< RTI::AttributeHandle > attr_handles;

        // Get updated attributes
        attrs_type::collect_updated_attrs( attr_handles );

        if( attr_handles.empty() )
        {
          return;
        }

        RTI::AttributeHandleValuePairSet *set
          = RTI::AttributeSetFactory::create
            ( (RTI::ULong) attr_handles.size() );

        boost::shared_ptr< RTI::AttributeHandleValuePairSet > set_ptr( set );

        attrs_type::update_values( set_ptr );
        //attrs_type::clear_modified_flag( set_ptr );

        if( time == 0 )
        {
          rti_amb->updateAttributeValues( obj_handle, *set_ptr, "" );
        }
        else
        {
          rti_amb->updateAttributeValues( obj_handle, *set_ptr, *time, "" );
        }

      }
  };
};

/******************************************************************************/

}} // protox::hla

/******************************************************************************/

#endif

/******************************************************************************/
