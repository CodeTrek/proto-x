/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#define BOOST_AUTO_TEST_MAIN

#include <boost/test/included/unit_test_framework.hpp>
#include <boost/test/auto_unit_test.hpp>

#include <boost/type_traits.hpp>

/**********************************************************************************************************************/

#include <protox/hla/som.hpp>
#include <protox/hla/i_class_type.hpp>

#include <protox/om/rpr/obj_class_table.hpp>
#include <protox/om/rpr/inter_class_table.hpp>

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_i_abc) {
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(test_i_class_static_attributes) {
    using namespace protox::om::rpr;

    typedef protox::hla::som< obj_class_table, inter_class_table > som;

    typedef i_class_type< som, q_name< Acknowledge > >::type acknowledge_type;
    BOOST_CHECK(acknowledge_type::get_name() == "HLAinteractionRoot.Acknowledge");
    BOOST_CHECK(acknowledge_type::get_num_params() == 5);

    typedef i_class_type< som, q_name< ActionRequest > >::type action_request_type;
    BOOST_CHECK(action_request_type::get_name() == "HLAinteractionRoot.ActionRequest");
    BOOST_CHECK(action_request_type::get_num_params() == 6);

    typedef i_class_type< som, q_name< ActionResponse > >::type action_response_type;
    BOOST_CHECK(action_response_type::get_name() == "HLAinteractionRoot.ActionResponse");
    BOOST_CHECK(action_response_type::get_num_params() == 6);

    typedef i_class_type< som, q_name< ActionRequestToObject > >::type action_request_to_object_type;
    BOOST_CHECK(action_request_to_object_type::get_name() == "HLAinteractionRoot.ActionRequestToObject");
    BOOST_CHECK(action_request_to_object_type::get_num_params() == 2);

    typedef i_class_type< som, q_name< ActionResponseFromObject > >::type action_response_from_object_type;
    BOOST_CHECK(action_response_from_object_type::get_name() == "HLAinteractionRoot.ActionResponseFromObject");
    BOOST_CHECK(action_response_from_object_type::get_num_params() == 1);

    typedef i_class_type< som, q_name< AttributeChangeRequest > >::type attribute_change_request_type;
    BOOST_CHECK(attribute_change_request_type::get_name() == "HLAinteractionRoot.AttributeChangeRequest");
    BOOST_CHECK(attribute_change_request_type::get_num_params() == 2);

    typedef i_class_type< som, q_name< AttributeChangeResult > >::type attribute_change_result_type;
    BOOST_CHECK(attribute_change_result_type::get_name() == "HLAinteractionRoot.AttributeChangeResult");
    BOOST_CHECK(attribute_change_result_type::get_num_params() == 3);

    typedef i_class_type< som, q_name< Collision > >::type collision_type;
    BOOST_CHECK(collision_type::get_name() == "HLAinteractionRoot.Collision");
    BOOST_CHECK(collision_type::get_num_params() == 7);

    typedef i_class_type< som, q_name< Comment > >::type comment_type;
    BOOST_CHECK(comment_type::get_name() == "HLAinteractionRoot.Comment");
    BOOST_CHECK(comment_type::get_num_params() == 3);

    typedef i_class_type< som, q_name< CreateObjectRequest > >::type create_object_request_type;
    BOOST_CHECK(create_object_request_type::get_name() == "HLAinteractionRoot.CreateObjectRequest");
    BOOST_CHECK(create_object_request_type::get_num_params() == 3);
}
