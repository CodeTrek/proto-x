/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_HLA_O_CLASS_HPP
#define PROTOX_HLA_O_CLASS_HPP

/**********************************************************************************************************************/

#include <boost/static_assert.hpp>

#include <protox/hla/keywords.hpp>
#include <protox/hla/has_duplicate_class_names.hpp>
#include <protox/hla/has_duplicate_attr_names.hpp>
#include <protox/hla/name.hpp>

/**********************************************************************************************************************/

namespace protox {
namespace hla {

/**********************************************************************************************************************/

/**
 * Use this template to build an object class table from object classes and attributes
 * defined in an attribute table.
 *
 * \tparam NAME The object class type definition that identifies this class. This type is
 *              is defined in an attribute table.
 *
 * \tparam ATTR_SET The attributes defined for this class. \a ATTR_SET is a vector of attribute
 *                  types defined in an attribute table.
 *
 * \tparam CHILD_SET The child classes defined for this class. \a CHILD_SET is a vector of
 *                   \c o_class definitions.
 *
 * \sa protox::hla::attr
 *
 * \code
 * // Use the o_class class template to define an HLA object structure table. Note how o_class
 * // is recursively nested to create "is-a" class relationships.
 *
 *   struct obj_class_table : o_class< HLAobjectRoot, attrs< HLAprivilegeToDeleteObject >, child<
 * // +---------------------+-------------------------+
 * // | Class 1             | Class 2                 |
 * // +---------------------+-------------------------+
 *      o_class< Table,                                     attrs< Width, Height > >,
 * // +---------------------+-------------------------+
 *      o_class< GameObject ,                               attrs< Position, Velocity, Acceleration >,
 *                     child< o_class< Target,              attrs< Target::State > >,
 * //                       +-------------------------+
 *                            o_class< Marble,              attrs< State > > > >,
 * // +---------------------+-------------------------+
 *      o_class< Player,                                    attrs< Name, Score >,
 *                     child< o_class< Human >,
 * //                       +-------------------------+
 *                            o_class< AI,                  attrs< SkillLevel > > > > > > {};
 * // +---------------------+-------------------------+
 *
 * \endcode
 */
template< typename NAME, typename ATTR_SET = protox::hla::none, typename CHILD_SET = protox::hla::none >
struct o_class {
    // Check for duplicate child classes.
    BOOST_STATIC_ASSERT((has_duplicate_class_names< CHILD_SET >::type::value == false));
  
    // Check for duplicate attributes.
    BOOST_STATIC_ASSERT((has_duplicate_attr_names< ATTR_SET >::type::value == false));

    typedef NAME name_type;
 
    typedef ATTR_SET attr_list_type;
    typedef CHILD_SET child_list_type;
};

/**********************************************************************************************************************/

struct null_o_class : o_class< null_name > {};

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
