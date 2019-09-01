/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_DTL_DISCRIMINATOR_TEST_HPP
#define PROTOX_DTL_DISCRIMINATOR_TEST_HPP

/**********************************************************************************************************************/

#include <boost/mpl/fold.hpp>
#include <boost/mpl/placeholders.hpp>

/**********************************************************************************************************************/

namespace protox {
namespace dtl {

/**********************************************************************************************************************/

struct in_enumerator_set_false {
    template< typename T >
    static bool is_equal(const T &) { return false; };
};

/**********************************************************************************************************************/

template< typename E, typename Base >
struct in_enumerator_set {
    template< typename T >
    static bool is_equal(const T &d) {
        if (Base::is_equal(d)) {
            return true;
        }

        return (d == E::value());
    }
};

/**********************************************************************************************************************/

template< typename D >
struct discriminator_test {
    typedef typename boost::mpl::fold<
        typename D::enumerator_vector,
        in_enumerator_set_false,
        in_enumerator_set< boost::mpl::placeholders::_2, boost::mpl::placeholders::_1 >
    >::type type;
};

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
