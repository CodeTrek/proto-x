/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_DTL_DISCRIMINANT_HPP
#define PROTOX_DTL_DISCRIMINANT_HPP

/**********************************************************************************************************************/

#include <boost/variant/get.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/int.hpp>

#include <protox/dtl/alternative.hpp>

/**********************************************************************************************************************/

namespace protox {
namespace dtl {

/**********************************************************************************************************************/

/**
 * Use this type to indicate that a variant record has no "other" discriminant option.
 *
 * Example:
 *
 * \code
 * typedef variant_record< DaysOfWeekEnum16::Type,
 *                         mpl::vector< alt_1, alt_2, alt_3 >,
 *                         dtl::discriminant_other_none,
 *                         hla1516::HLAvariantRecord >
 *
 * \endcode
 */
struct discriminant_other_none {
    typedef void *value_type;
};

/**********************************************************************************************************************/

/**
 * Defines a variant record discriminant in the form of an alternative/enumerator range pair.
 *
 * \tparam T The type of the alternative.
 * \tparam E_VECTOR A vector of enumerators that used to select the alternative.
 *
 * \sa protox::dtl::variant_record
 */

//
// E_Vector An enumerator range
template< typename T, typename E_VECTOR >
struct discriminant {
    typedef dtl::alternative< T > alternative;
    typedef E_VECTOR enumerator_vector;
};

/**********************************************************************************************************************/

// Designates the alternative type to be used by HLAOther, which denotes all enumerates not explicitly included in any
// of the enumerator ranges.
//
// T HLAOther alternative type
template< typename T >
struct discriminant_other {
    typedef T value_type;

    value_type value;

    discriminant_other() {}
    discriminant_other(const T &v) : value(v) {}
};

/**********************************************************************************************************************/

// Construct the complete alternative set by appending the HLAOther alternative type.
//
// Alternatives The set of alternatives
// Other        The HLAOther alternative
template< typename Alternatives, typename Other >
struct append_other {
    typedef typename boost::mpl::push_back< Alternatives, Other >::type type;
};

/**********************************************************************************************************************/

// This specialization handles the case when HLAOther is _not_ used.
template< typename Alternatives >
struct append_other< Alternatives, discriminant_other_none > {
    typedef Alternatives type;
};

/**********************************************************************************************************************/

// Define the function used to retieve a variant record's HLAOther value.
//
// Other The HLAOther representation type
// R     The variant record type
template< typename OTHER, typename R >
struct other_access {
    inline static typename OTHER::value_type const *get_value(const R &record) {
        OTHER const *other_ptr = boost::get< OTHER >(&record.value);

        if (other_ptr == 0) {
            return 0;
        }

        return &(other_ptr->value);
    }

    inline static void set_value(R &record, typename OTHER::value_type const &other_value) {
        record.value = static_cast< OTHER >(other_value);
    }
};

/**********************************************************************************************************************/

// This specialization ensures that there is no function definition for retrieving an HLAOther value for a variant
// record that has not defined an HLAOther value.
template< typename R > struct other_access< discriminant_other_none, R > {};

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
