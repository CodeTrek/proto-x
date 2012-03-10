
/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#include <iostream>

#include <RTI.hh>

#include <protox/hla/o_class_type.hpp>
#include <protox/hla/som.hpp>
#include <protox/om/rpr/obj_class_table.hpp>

#include "fedlet/fedlet_base.hpp"
#include "fedlet/fed_amb.hpp"


using namespace boost;
using namespace protox::hla;
using namespace protox::rpr_fom;
using namespace protox::examples;

class test_federate : public fedlet::fedlet_base
{
protected:
  virtual void declare_interests()
  {
    typedef protox::hla::som< obj_class_table > rpr_som;
    typedef o_class_type< rpr_som, q_name< BaseEntity > >::type base_entity_type;

    typedef o_class_type< rpr_som, q_name<
      BaseEntity,
      PhysicalEntity
    > >::type physical_entity_type;

    typedef o_class_type< rpr_som, q_name<
       BaseEntity,
       PhysicalEntity,
       Platform,
       Aircraft
    > >::type aircraft_type;

     try
     {
       rpr_som::init_handles(rti_amb);
     }
     catch( RTI::Exception &e )
     {
       std::cout << e << "\n";
     }

     base_entity_type base_entity_obj;

     physical_entity_type pysical_entity_obj;

     aircraft_type aircraft_obj;

     aircraft_obj.a_< RunningLightsOn >() = 5;

     FederateIdentifierStruct::type &fi = aircraft_obj.a_< IsPartOf >().f_< HostEntityIdentifier >().f_< FederateIdentifier >();

     fi.f_< SiteID >() = 222;
     fi.f_< ApplicationID >() = 225;

     aircraft_obj
       .a_< IsPartOf >()
         .f_< HostEntityIdentifier >()
           .f_< FederateIdentifier >()
             .f_< SiteID >() = 215;

     std::cout
       << "Site id = "
       << aircraft_obj
            .a_< IsPartOf >()
              .f_< HostEntityIdentifier >()
                .f_< FederateIdentifier >()
                  .f_< SiteID >()
       << "\n";
  }

  virtual void populate()
  {
    std::cout << "TODO: populate\n";
  }

  virtual void execute()
  {
    std::cout << "TODO: execute\n";
  }

  virtual void resign()
  {
    std::cout << "TODO: resign\n";
  }

public:
  test_federate( RTI::RTIambassador &rti_amb, fedlet::fed_amb &fed_amb ) :
    fedlet::fedlet_base(rti_amb, fed_amb)
  {}
};

/**************************************************************************************************/

int main( int argc, char *argv[] )
{
  RTI::RTIambassador rti_amb;
  fedlet::fed_amb fed_amb;

  test_federate federate( rti_amb, fed_amb );

  federate.run( "rpr", "rpr_test" );

  return 0;
}

/**************************************************************************************************/
