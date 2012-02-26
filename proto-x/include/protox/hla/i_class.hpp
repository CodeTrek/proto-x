/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_HLA_I_CLASS_HPP
#define PROTOX_HLA_I_CLASS_HPP

/**********************************************************************************************************************/

#include <boost/static_assert.hpp>

#include <protox/hla/keywords.hpp>
#include <protox/hla/has_duplicate_class_names.hpp>
#include <protox/hla/has_duplicate_param_names.hpp>
#include <protox/hla/name.hpp>

/**********************************************************************************************************************/

namespace protox {
namespace hla {

/**********************************************************************************************************************/

/**
 * Use this template to build an interaction class table from interaction classes and parameters defined in a parameter
 * table.
 *
 * \tparam NAME The interaction class type definition that identifies this interaction. This type is defined in a
 *              parameter table.
 *
 * \tparam PARAM_SET The parameters defined for this class. \a PARAM_SET is a vector of parameter types defined in a
 *                   parameter table.
 *
 * \tparam CHILD_SET The child classes defined for this class. \a CHILD_SET is a vector of \c i_class definitions.
 *
 * \sa protox::hla::param
 *
 * \code
 * // Use the i_class class template to define an HLA interaction class table. Note how i_class is recursively nested
 * // to create "is-a" class relationships.
 *
//// Interaction Class Table ///////////////////////////////////////
   struct inter_class_table : i_class< HLAinteractionRoot, none, child<
// +------------------------------+-------------------------+
// | Class 1                      | Class 2                 |
// +------------------------------+-------------------------+
     i_class< CustomerTransaction,                            none,
//                                +-------------------------+
                             child< i_class< CustomerSeated,  params< TimeSeated > >,
//                                +-------------------------+
                                    i_class< FoodServed,      params< TemperatureOk, AccuracyOk, TimelinessOk > > > > > > {};
// +------------------------------+-------------------------+
 *
 * \endcode
 */

template< typename NAME,
          typename PARAM_SET = protox::hla::none,
          typename CHILD_SET = protox::hla::none >
struct i_class {
    // Check for duplicate child classes.
    BOOST_STATIC_ASSERT((has_duplicate_class_names< CHILD_SET >::type::value == false));
  
    // Check for duplicate attributes.
    BOOST_STATIC_ASSERT((has_duplicate_param_names< PARAM_SET >::type::value == false));

    typedef NAME name_type;
 
    typedef PARAM_SET param_list_type;
    typedef CHILD_SET child_list_type;
};

/**********************************************************************************************************************/

struct null_i_class : i_class< null_name > {};

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
