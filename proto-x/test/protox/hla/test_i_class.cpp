/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#define BOOST_AUTO_TEST_MAIN

#include <boost/test/included/unit_test_framework.hpp>
#include <boost/test/auto_unit_test.hpp>

/**********************************************************************************************************************/

#include <boost/mpl/size.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>

#include <test/protox/hla/som/s005/inter_class_table.hpp>
#include <test/protox/hla/som/s006/inter_class_table.hpp>
#include <test/protox/hla/som/s007/inter_class_table.hpp>
#include <test/protox/hla/som/s008/inter_class_table.hpp>

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_i_class_empty) {
    using namespace som_s005;

    BOOST_CHECK(inter_class_table::name_type::name() == std::string("Class_A"));
    BOOST_CHECK(inter_class_table::name_type::name() != std::string("Class_B"));
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_i_class_children) {
    using namespace som_s006;
    using namespace boost;

    BOOST_CHECK(inter_class_table::name_type::name() == std::string("Class_A"));

    // No parameters?
    BOOST_CHECK(mpl::size<inter_class_table::param_list_type>::value == 0);

    // 3 child classes?
    BOOST_CHECK(mpl::size<inter_class_table::child_list_type>::value == 3);
}

/**********************************************************************************************************************/

template< typename T >
static void verify_class() {
    using namespace boost;

    if (T::name_type::name() == std::string("Class_B")) {
        BOOST_CHECK(mpl::size< typename T::param_list_type >::value == 0);
        BOOST_CHECK(mpl::size< typename T::child_list_type >::value == 3);
    }
    else if (T::name_type::name() == std::string( "Class_C")) {
        BOOST_CHECK(mpl::size< typename T::param_list_type >::value == 0);
        BOOST_CHECK(mpl::size< typename T::child_list_type >::value == 2);
    }
    else if (T::name_type::name() == std::string("Class_D")) {
        BOOST_CHECK(mpl::size< typename T::param_list_type >::value == 0);
        BOOST_CHECK(mpl::size< typename T::child_list_type >::value == 2);
    }
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_i_class_nested_children) {
    using namespace boost;
    using namespace som_s007;

    BOOST_CHECK(inter_class_table::name_type::name() == std::string("Class_A"));

    // No parameters?
    BOOST_CHECK(mpl::size< inter_class_table::param_list_type >::value == 0);

    // Class_A has 3 child classes?
    BOOST_CHECK(mpl::size< inter_class_table::child_list_type >::value == 3);

    typedef mpl::deref< mpl::begin< inter_class_table::child_list_type >::type >::type class_1_type;
    typedef mpl::deref< mpl::next< mpl::begin< inter_class_table::child_list_type >::type >::type >::type class_2_type;
    typedef mpl::deref< mpl::next< mpl::next< mpl::begin< inter_class_table::child_list_type >::type >::type >::type >::type class_3_type;

    verify_class< class_1_type >();
    verify_class< class_2_type >();
    verify_class< class_3_type >();
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_i_class_children_with_params) {
    using namespace som_s008;

    BOOST_CHECK(boost::mpl::size<inter_class_table::param_list_type>::value == 2);
}
