/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

#define BOOST_AUTO_TEST_MAIN

#include <boost/test/included/unit_test_framework.hpp>
#include <boost/test/auto_unit_test.hpp>

// Data type language (DTL) tests
#include "test/protox/dtl/compute_octet_boundary.hpp"
#include "test/protox/dtl/basic.hpp"
#include "test/protox/dtl/simple.hpp"

// HLA 1516 tests
#include "test/protox/hla_1516/policy_basic_data.hpp"
#include "test/protox/hla_1516/policy_simple_data.hpp"
#include "test/protox/hla_1516/policy_fixed_record.hpp"
#include "test/protox/hla_1516/policy_fixed_array.hpp"
#include "test/protox/hla_1516/policy_variable_array.hpp"
#include "test/protox/hla_1516/policy_enumerated.hpp"
#include "test/protox/hla_1516/policy_variant_record.hpp"

// HLA tests
#include "test/protox/hla/test_keywords.hpp"
#include "test/protox/hla/test_o_class.hpp"
#include "test/protox/hla/test_i_class.hpp"

#include "test/protox/hla/test_som.hpp"

#include "test/protox/hla/test_o_class_type.hpp"
#include "test/protox/hla/test_i_class_type.hpp"

#include "test/protox/hla/test_object_amb.hpp"
#include "test/protox/hla/test_interaction_amb.hpp"
