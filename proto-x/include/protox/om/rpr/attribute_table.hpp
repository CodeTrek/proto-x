/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_OM_RPR_ATTRIBUTE_TABLE_HPP
#define PROTOX_OM_RPR_ATTRIBUTE_TABLE_HPP

/**************************************************************************************************/

#include <protox/hla/attr.hpp>
#include <protox/hla/keywords.hpp>
#include <protox/hla/name.hpp>

#include <protox/hla_13/basic_data_representation_table.hpp>

#include <protox/om/rpr/acceleration_vector_struct.hpp>
#include <protox/om/rpr/angular_velocity_vector_struct.hpp>

/**************************************************************************************************/

namespace protox { namespace om { namespace rpr {

/**************************************************************************************************/

using namespace protox;
using namespace protox::hla;

/**************************************************************************************************/

////// Attribute Table /////////////////////////////////////////////////////////
//     +--------------------------------------------------------+---------------------------------+------------------------------------+-----------------------------------------------+
//     | Name                                                   | Attribute                       | Datatype                           | String Name                                   |
//     +--------------------------------------------------------+---------------------------------+------------------------------------+-----------------------------------------------+
  struct HLAobjectRoot       {HLA_NAME( "HLAobjectRoot"       )};
                                                           struct HLAprivilegeToDeleteObject      : attr< hla_13::HLA13octet           > {HLA_NAME( "HLAprivilegeToDeleteObject" )};
//     +--------------------------------------------------------+---------------------------------+------------------------------------+-----------------------------------------------+
  struct BaseEntity { HLA_NAME("BaseEntity") };
      struct AccelerationVector    : attr< AccelerationVector::type    > {HLA_NAME( "AccelerationVector"    )};
      struct AngularVelocityVector : attr< AngularVelocityVector::type > {HLA_NAME( "AngularVelocityVector" )};

/**************************************************************************************************/

}}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
