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
#include <protox/hla/o_class_type.hpp>

#include <protox/om/rpr/obj_class_table.hpp>
#include <protox/om/rpr/inter_class_table.hpp>

/**********************************************************************************************************************/

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

    typedef i_class_type< som, q_name< CreateObjectResult > >::type create_object_result_type;
    BOOST_CHECK(create_object_result_type::get_name() == "HLAinteractionRoot.CreateObjectResult");
    BOOST_CHECK(create_object_result_type::get_num_params() == 2);

    typedef i_class_type< som, q_name< CreateEntity > >::type create_entity_type;
    BOOST_CHECK(create_entity_type::get_name() == "HLAinteractionRoot.CreateEntity");
    BOOST_CHECK(create_entity_type::get_num_params() == 3);

    typedef i_class_type< som, q_name< Data > >::type data_type;
    BOOST_CHECK(data_type::get_name() == "HLAinteractionRoot.Data");
    BOOST_CHECK(data_type::get_num_params() == 5);

    typedef i_class_type< som, q_name< DataQuery > >::type data_query_type;
    BOOST_CHECK(data_query_type::get_name() == "HLAinteractionRoot.DataQuery");
    BOOST_CHECK(data_query_type::get_num_params() == 6);

    typedef i_class_type< som, q_name< EventReport > >::type event_report_type;
    BOOST_CHECK(event_report_type::get_name() == "HLAinteractionRoot.EventReport");
    BOOST_CHECK(event_report_type::get_num_params() == 5);

    typedef i_class_type< som, q_name< MunitionDetonation > >::type munition_detonation_type;
    BOOST_CHECK(munition_detonation_type::get_name() == "HLAinteractionRoot.MunitionDetonation");
    BOOST_CHECK(munition_detonation_type::get_num_params() == 14);

    typedef i_class_type< som, q_name< RadioSignal > >::type radio_signal_type;
    BOOST_CHECK(radio_signal_type::get_name() == "HLAinteractionRoot.RadioSignal");
    BOOST_CHECK(radio_signal_type::get_num_params() == 0);

    typedef i_class_type< som, q_name< RadioSignal, ApplicationSpecificRadioSignal > >::type application_specific_radio_signal_type;
    BOOST_CHECK(application_specific_radio_signal_type::get_name() == "HLAinteractionRoot.RadioSignal.ApplicationSpecificRadioSignal");
    BOOST_CHECK(application_specific_radio_signal_type::get_num_params() == 7);
    BOOST_CHECK((boost::is_base_of< radio_signal_type, application_specific_radio_signal_type >::value) == true);

    typedef i_class_type< som, q_name< RadioSignal, DatabaseIndexRadioSignal > >::type database_index_radio_signal_type;
    BOOST_CHECK(database_index_radio_signal_type::get_name() == "HLAinteractionRoot.RadioSignal.DatabaseIndexRadioSignal");
    BOOST_CHECK(database_index_radio_signal_type::get_num_params() == 6);
    BOOST_CHECK((boost::is_base_of< radio_signal_type, database_index_radio_signal_type >::value) == true);

    typedef i_class_type< som, q_name< RadioSignal, EncodedAudioRadioSignal > >::type encoded_audio_radio_signal_type;
    BOOST_CHECK(encoded_audio_radio_signal_type::get_name() == "HLAinteractionRoot.RadioSignal.EncodedAudioRadioSignal");
    BOOST_CHECK(encoded_audio_radio_signal_type::get_num_params() == 6);
    BOOST_CHECK((boost::is_base_of< radio_signal_type, encoded_audio_radio_signal_type >::value) == true);

    typedef i_class_type< som, q_name< RadioSignal, RawBinaryRadioSignal > >::type raw_binary_radio_signal_type;
    BOOST_CHECK(raw_binary_radio_signal_type::get_name() == "HLAinteractionRoot.RadioSignal.RawBinaryRadioSignal");
    BOOST_CHECK(raw_binary_radio_signal_type::get_num_params() == 6);
    BOOST_CHECK((boost::is_base_of< radio_signal_type, raw_binary_radio_signal_type >::value) == true);

    typedef i_class_type< som, q_name< RemoveObjectRequest > >::type remove_object_request_type;
    BOOST_CHECK(remove_object_request_type::get_name() == "HLAinteractionRoot.RemoveObjectRequest");
    BOOST_CHECK(remove_object_request_type::get_num_params() == 2);

    typedef i_class_type< som, q_name< RemoveObjectResult > >::type remove_object_result_type;
    BOOST_CHECK(remove_object_result_type::get_name() == "HLAinteractionRoot.RemoveObjectResult");
    BOOST_CHECK(remove_object_result_type::get_num_params() == 2);

    typedef i_class_type< som, q_name< RemoveEntity > >::type remove_entity_type;
    BOOST_CHECK(remove_entity_type::get_name() == "HLAinteractionRoot.RemoveEntity");
    BOOST_CHECK(remove_entity_type::get_num_params() == 3);

    typedef i_class_type< som, q_name< RepairComplete > >::type repair_complete_type;
    BOOST_CHECK(repair_complete_type::get_name() == "HLAinteractionRoot.RepairComplete");
    BOOST_CHECK(repair_complete_type::get_num_params() == 3);

    typedef i_class_type< som, q_name< RepairResponse > >::type repair_response_type;
    BOOST_CHECK(repair_response_type::get_name() == "HLAinteractionRoot.RepairResponse");
    BOOST_CHECK(repair_response_type::get_num_params() == 3);

    typedef i_class_type< som, q_name< ResupplyCancel > >::type resupply_cancel_type;
    BOOST_CHECK(resupply_cancel_type::get_name() == "HLAinteractionRoot.ResupplyCancel");
    BOOST_CHECK(resupply_cancel_type::get_num_params() == 2);

    typedef i_class_type< som, q_name< ResupplyOffer > >::type resupply_offer_type;
    BOOST_CHECK(resupply_offer_type::get_name() == "HLAinteractionRoot.ResupplyOffer");
    BOOST_CHECK(resupply_offer_type::get_num_params() == 3);

    typedef i_class_type< som, q_name< ResupplyReceived > >::type resupply_received_type;
    BOOST_CHECK(resupply_received_type::get_name() == "HLAinteractionRoot.ResupplyReceived");
    BOOST_CHECK(resupply_received_type::get_num_params() == 3);

    typedef i_class_type< som, q_name< ServiceRequest > >::type service_request_type;
    BOOST_CHECK(service_request_type::get_name() == "HLAinteractionRoot.ServiceRequest");
    BOOST_CHECK(service_request_type::get_num_params() == 4);

    typedef i_class_type< som, q_name< SetData > >::type set_data_type;
    BOOST_CHECK(set_data_type::get_name() == "HLAinteractionRoot.SetData");
    BOOST_CHECK(set_data_type::get_num_params() == 5);

    typedef i_class_type< som, q_name< StartResume > >::type start_resume_type;
    BOOST_CHECK(start_resume_type::get_name() == "HLAinteractionRoot.StartResume");
    BOOST_CHECK(start_resume_type::get_num_params() == 5);

    typedef i_class_type< som, q_name< StopFreeze > >::type stop_freeze_type;
    BOOST_CHECK(stop_freeze_type::get_name() == "HLAinteractionRoot.StopFreeze");
    BOOST_CHECK(stop_freeze_type::get_num_params() == 8);

    typedef i_class_type< som, q_name< WeaponFire > >::type weapon_fire_type;
    BOOST_CHECK(weapon_fire_type::get_name() == "HLAinteractionRoot.WeaponFire");
    BOOST_CHECK(weapon_fire_type::get_num_params() == 14);

    // Some object class types...
    typedef o_class_type< som, q_name< BaseEntity > >::type base_entity_type;
    BOOST_CHECK(base_entity_type::get_name() == "HLAobjectRoot.BaseEntity");
    BOOST_CHECK(base_entity_type::get_num_attrs() == 9);

    typedef o_class_type< som, q_name< BaseEntity, EnvironmentalEntity > >::type environmental_entity_type;
    BOOST_CHECK(environmental_entity_type::get_name() == "HLAobjectRoot.BaseEntity.EnvironmentalEntity");
    BOOST_CHECK(environmental_entity_type::get_num_attrs() == 10);
    BOOST_CHECK((boost::is_base_of< base_entity_type, environmental_entity_type >::value) == true);

    typedef o_class_type< som, q_name< BaseEntity, PhysicalEntity > >::type physical_entity_type;
    BOOST_CHECK(physical_entity_type::get_name() == "HLAobjectRoot.BaseEntity.PhysicalEntity");
    BOOST_CHECK(physical_entity_type::get_num_attrs() == 28);
    BOOST_CHECK((boost::is_base_of< base_entity_type, physical_entity_type >::value) == true);

    typedef o_class_type< som, q_name< BaseEntity, PhysicalEntity, Platform > >::type platform_type;
    BOOST_CHECK(platform_type::get_name() == "HLAobjectRoot.BaseEntity.PhysicalEntity.Platform");
    BOOST_CHECK(platform_type::get_num_attrs() == 44);
    BOOST_CHECK((boost::is_base_of< physical_entity_type, platform_type >::value) == true);
    BOOST_CHECK((boost::is_base_of< base_entity_type, platform_type >::value) == true);
}
