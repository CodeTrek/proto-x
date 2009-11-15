
/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#include <iostream>

#include <protox/hla/o_class_type.hpp>
#include <protox/hla/som.hpp>

#include "./object_model/obj_class_table.hpp"

using namespace boost;
using namespace protox::hla;
using namespace protox::rpr_fom;

/**************************************************************************************************/

int main( int argc, char *argv[] )
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

  base_entity_type base_entity_obj;

  physical_entity_type pysical_entity_obj;

  aircraft_type aircraft_obj;

  aircraft_obj.a_< RunningLightsOn >() = 5;

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
               .f_< SiteID >();

  return 0;
}

/**************************************************************************************************/
