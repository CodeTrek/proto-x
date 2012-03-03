/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_DTL_VARIANT_RECORD_HPP
#define PROTOX_DTL_VARIANT_RECORD_HPP

/**********************************************************************************************************************/

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/max.hpp>
#include <boost/variant.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/vector.hpp>

#include <protox/dtl/alternative.hpp>
#include <protox/dtl/discriminant.hpp>

/**********************************************************************************************************************/

namespace protox {
namespace dtl {

/**********************************************************************************************************************/

/**
 * Constructs a variant record definition from the given vector of alternative types.
 *
 * \tparam D_TYPE This record's disriminant type. This type must be an enumerated type.
 * \tparam D_VECTOR This record's vector of descriminants. \sa protox::dtl::discriminant
 * \tparam OTHER (optional) The other alternative.
 * \tparam CODEC_TAG Identifies the codec policy used to code/decode records of this type.
 *
 * Example:
 *
 * \code
 *  // Define the alternatives.
 *
 *  struct alt_1 : dtl::discriminant< HLAinteger16LE, mpl::vector< Sun, Tue > > {};
 *  struct alt_2 : dtl::discriminant< HLAoctet,       mpl::vector< Fri >      > {};
 *  struct alt_3 : dtl::discriminant< HLAoctet,       mpl::vector< Sat >      > {};
 *
 *  // Define a variable record using 1516 variant record encoding
 *
 *  typedef variant_record< DaysOfWeekEnum16::Type,
 *                          mpl::vector< alt_1, alt_2, alt_3 >,
 *                          dtl::discriminant_other< HLAfloat32BE >,
 *                          hla1516::HLAvariantRecord >
 *  > var_rec_type;
 *
 * \endcode
 */

template<
    typename D_TYPE,   // Discriminant type
    typename D_VECTOR, // Vector of alternatives
    typename OTHER,    // HLAOTHER case (optional)
    typename CODEC_TAG
>
struct variant_record {
    variant_record() {}

    typedef CODEC_TAG codec_tag;

    typedef D_VECTOR d_vector;
    typedef OTHER other_type;

    typedef typename boost::mpl::fold<
        D_VECTOR,
        boost::mpl::vector<>,
        boost::mpl::push_back< boost::mpl::placeholders::_1, get_alternative_type< boost::mpl::placeholders::_2 > >
    >::type alternative_vector;

    typename boost::make_variant_over< typename dtl::append_other< alternative_vector, OTHER >::type >::type value;

    typedef D_TYPE discriminant_type;

    /**
     * Set this value to select an alternative.
     *
     * Example:
     *
     * \code
     *  var_rec_type vr;
     *
     *  // Select the Fri alternative
     *  vr.discriminant = Fri::value();
     *
     * \endcode
     */
    discriminant_type discriminant;

    template< typename OTHER_T, typename NA > struct compare_other;

    template<typename NA>
    struct compare_other< protox::dtl::discriminant_other_none, NA > {
        template< typename R >
        inline static bool is_equal(const R &lhs, const R &rhs) { return false; }
    };

    template< typename OTHER_T, typename NA >
    struct compare_other {
        template< typename R >
        inline static bool is_equal(const R &lhs, const R &rhs) {
            // This is the "other" case, so testing for discriminant equality is not necessary.
            typename OTHER_T::value_type const *lhs_value = lhs.other_();
            typename OTHER_T::value_type const *rhs_value = rhs.other_();

            if (!lhs_value) {
                return false;
            }

            if (!rhs_value) {
                return false;
            }

            return ((*lhs_value) == (*rhs_value));
        }
    };

    template< typename D, typename BASE >
    struct discriminant_compare {
        typedef typename protox::dtl::discriminator_test< D >::type discriminator_test;

        template< typename R >
        inline static bool is_equal(const R &lhs, const R &rhs) {
            if (discriminator_test::is_equal(lhs.discriminant)) {
                // Same object?
                if (&lhs == &rhs) {
                    return true;
                }

                if (!(lhs.discriminant == rhs.discriminant)) {
                    return false;
                }

                typename D::alternative::value_type const *lhs_value = lhs.template alt_< D >();
                typename D::alternative::value_type const *rhs_value = rhs.template alt_< D >();

                // No alternative values?
                if ((!lhs_value) && (!rhs_value)) {
                    return true;
                }

                if (!lhs_value) {
                    return false;
                }

                if (!rhs_value) {
                    return false;
                }

                return ((*lhs_value) == (*rhs_value));
            }

            return BASE::is_equal(lhs, rhs);
        }
    };

    /**
     * Equality operator
     */
    inline bool operator == (const variant_record &rhs) const {
        typedef typename boost::mpl::fold<
            D_VECTOR,
            compare_other< OTHER, void >,
            discriminant_compare< boost::mpl::placeholders::_2, boost::mpl::placeholders::_1 >
        >::type type;

        return type::is_equal(*this, rhs);
    }

    /**
     * Inequality operator
     */
    inline bool operator != (const variant_record &rhs) const { return !(*this == rhs); }

    // Alternative getters and setters.

    /**
     * Sets the value of the alternative identified by \a T.
     * \tparam T The alternative type value to be set.
     * \param v The alternative's new value.
     *
     * Example:
     *
     * \code
     *
     * var_rec_type vr;
     *
     * vr.alt_< alt_1 >( 345 );
     * vr.alt_< alt_2 >( 'b' );
     *
     * \endcode
     */
    template< typename T >
    inline void alt_(typename get_alternative_type<T>::type::value_type const &v) {
        value = static_cast< typename get_alternative_type< T >::type >(v);
    }

    // Gets a read/write pointer to an alternative's value

    /**
     * \tparam T The alternative type value to be set.
     * \return A read/write pointer to the alternative's value, or 0 if the alternative has not been set.
     *
     * Example:
     * \code
     *
     * var_rec_type vr;
     * vr.alt_< alt_1 >( 345 );
     *
     * assert( *vr.alt_< alt_1 >() == 345 ); // true
     *
     * \endcode
     */
    template< typename T >
    inline typename get_alternative_type< T >::type::value_type *alt_() {
        typedef typename get_alternative_type< T >::type alternative_type;
        alternative_type *alt_ptr = boost::get< alternative_type >(&value);

        if (alt_ptr == 0) {
            return 0;
        }

        return (&(alt_ptr->value));
    }

    /**
     * \tparam T The alternative type value to be set.
     * \return A read-only pointer to the alternative's value, or 0 if the alternative has not been set.
     *
     * Example:
     * \code
     *
     * var_rec_type vr;
     * vr.alt_< alt_1 >( 345 );
     *
     * assert( *vr.alt_< alt_1 >() == 345 ); // true
     *
     * \endcode
     */
    template< typename T >
    inline typename get_alternative_type< T >::type::value_type const *alt_() const {
        typedef typename get_alternative_type< T >::type alternative_type;
        alternative_type const *alt_ptr = boost::get< alternative_type >(&value);

        if (alt_ptr == 0) {
            return 0;
        }

        return (&(alt_ptr->value));
    }

    /**
     * Sets the value of the other alternative.
     * \param v The other alternative's new value.
     *
     * Example:
     *
     * \code
     *
     * var_rec_type vr;
     *
     * vr.other_( 3.1456f );
     *
     * \endcode
     */
    inline void other_(typename OTHER::value_type const &v) {

        typedef dtl::other_access< OTHER, variant_record< D_TYPE, D_VECTOR, OTHER, CODEC_TAG > > other;
        other::set_value(*this, v);
    }

    /**
     * \return A read-only pointer to the other alternative's value, or 0 if the alternative has not been set.
     *
     * Example:
     * \code
     *
     * var_rec_type vr;
     * vr.other_( 3.1456f );
     *
     * assert( *vr.other_() == 3.1456f ); // true
     *
     * \endcode
     */
    inline typename OTHER::value_type const *other_() const {

        typedef dtl::other_access< OTHER, variant_record< D_TYPE, D_VECTOR, OTHER, CODEC_TAG > > other;
        return other::get_value(*this);
    }
};

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
