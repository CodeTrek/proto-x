/*
    Copyright 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#define BOOST_AUTO_TEST_MAIN

#include <boost/test/included/unit_test_framework.hpp>
#include <boost/test/auto_unit_test.hpp>

/**********************************************************************************************************************/

#include <boost/mpl/sizeof.hpp>

#include "protox/codec/codecs.hpp"

#include "protox/io/byte_data_sink.hpp"
#include "protox/io/byte_data_source.hpp"

#include "protox/hla_1516/enumerated.hpp"
#include "protox/hla_1516/basic_data_representation_table.hpp"
#include "protox/hla_1516/hla_boolean.hpp"

#include "./test_days_of_week_enum.hpp"

/**********************************************************************************************************************/

using namespace boost;
using namespace protox::hla_1516;

/**********************************************************************************************************************/

/**
 * Define an enumeration with enumerators that can be represented by multiple values.
 */

typedef HLAinteger32BE Color_value_type;

typedef protox::hla_1516::enumerated< class ColorEnum, Color_value_type > Color_enumerated;

/**********************************************************************************************************************/

class ColorEnum : public Color_enumerated {
    private:
        friend struct ColorEnum_Red;
        friend struct ColorEnum_Green;
        friend struct ColorEnum_Blue;
        friend struct ColorEnum_Yellow;

        ColorEnum(Color_value_type v) : Color_enumerated(v) {}

    public:
        ColorEnum() : Color_enumerated(1) {}
        ColorEnum(ColorEnum const &v) : Color_enumerated(v) {}

        /**
         * @return true If the two values are equal.
         */
        static bool is_equal(Color_value_type lhs, Color_value_type rhs);
};

/**********************************************************************************************************************/

struct ColorEnum_Red {
    static ColorEnum const &value() { static ColorEnum const e(1); return (e); }

    static bool is_equal(Color_value_type v) {
        return ((v == 1) || (v == 11) || (v == 23));
    }
};

/**********************************************************************************************************************/

struct ColorEnum_Green {
    static ColorEnum const &value() { static ColorEnum const e(2); return (e); }

    static bool is_equal(Color_value_type v) {
      return ((v == 2) || (v == 12) || (v == 24));
    }
};

/**********************************************************************************************************************/

struct ColorEnum_Blue {
    static ColorEnum const &value() { static ColorEnum const e(3); return (e); }

    static bool is_equal (Color_value_type v) {
      return ((v == 3) || (v == 13) || (v == 25) || (v == 201));
    }
};

/**********************************************************************************************************************/

struct ColorEnum_Yellow {
    static ColorEnum const &value() { static ColorEnum const e(4); return (e); }

    static bool is_equal(Color_value_type v) {
        return ((v == 4) || (v == 14) || (v == 26));
    }
};

/**********************************************************************************************************************/

/**
 * Compare values to equivalence sets, where each equivalence set represents the range of valid values for a particular
 * enumerated value.
 */
bool ColorEnum::is_equal(Color_value_type lhs, Color_value_type rhs) {
    if ((ColorEnum_Red::is_equal(lhs)) && (ColorEnum_Red::is_equal(rhs))) {
        return (true);
    }

    if ((ColorEnum_Green::is_equal(lhs)) && (ColorEnum_Green::is_equal(rhs))) {
        return (true);
    }

    if ((ColorEnum_Blue::is_equal(lhs)) && (ColorEnum_Blue::is_equal(rhs))) {
        return (true);
    }

    if ((ColorEnum_Yellow::is_equal(lhs)) && (ColorEnum_Yellow::is_equal(rhs))) {
        return (true);
    }

    return (false);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_enumerated) {
    BOOST_CHECK(protox::dtl::codec::octet_boundary< HLAboolean::type       >::value == 4);
    BOOST_CHECK(protox::dtl::codec::static_size_in_bytes< HLAboolean::type >::value == 4);

    using namespace HLAboolean;

    BOOST_CHECK(protox::dtl::codec::dynamic_size(HLAtrue::value()) == 4);

    protox::io::byte_data_sink sink;

    HLAboolean::type b = HLAtrue::value();
    sink.encode(b);

    BOOST_CHECK(sink.size() == 4);
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE( test_enum_equality ) {
    ColorEnum red1;
    ColorEnum red2;

    red1 = ColorEnum_Red::value();
    red2 = ColorEnum_Red::value();

    BOOST_CHECK(red1 == red2);

    ColorEnum green1 = ColorEnum_Green::value();
    ColorEnum green2 = ColorEnum_Green::value();

    BOOST_CHECK(green1 == green2);

    ColorEnum blue1 = ColorEnum_Blue::value();
    ColorEnum blue2 = ColorEnum_Blue::value();

    BOOST_CHECK(blue1 == blue2);

    ColorEnum yellow1 = ColorEnum_Yellow::value();
    ColorEnum yellow2 = ColorEnum_Yellow::value();

    BOOST_CHECK(yellow1 == yellow2);
}

/**********************************************************************************************************************/

/**
 * Perform simple inequality tests.
 */
BOOST_AUTO_TEST_CASE(test_enum_inequality) {
    ColorEnum red    = ColorEnum_Red::value();
    ColorEnum green  = ColorEnum_Green::value();
    ColorEnum blue   = ColorEnum_Blue::value();
    ColorEnum yellow = ColorEnum_Yellow::value();

    BOOST_CHECK(red   != yellow);
    BOOST_CHECK(green != blue  );
    BOOST_CHECK(red   != green );
}

/**********************************************************************************************************************/

/**
 * Test the use of equivalence sets to test for enumerator equality.
 */
BOOST_AUTO_TEST_CASE(test_enum_equivalence_set) {
    protox::io::byte_data_sink sink;

    // Encode a 'raw' enumerator value representation.
    sink.encode((Color_value_type) 23);

    // Decode the raw enumerator value representation as a ColorEnum.
    ColorEnum red;
    protox::io::byte_data_source red_source(sink);
    red_source.decode(red);

    // The decoded value should represent ColorEnum_Red enumerator.
    BOOST_CHECK(red == ColorEnum_Red::value()  );
    BOOST_CHECK(red != ColorEnum_Green::value());

    // Repeat the above for a raw yellow value.
    sink.clear();
    sink.encode((Color_value_type) 14);

    ColorEnum yellow;

    protox::io::byte_data_source yellow_source(sink);
    yellow_source.decode(yellow);

    BOOST_CHECK(yellow == ColorEnum_Yellow::value());
    BOOST_CHECK(yellow != ColorEnum_Blue::value()  );

    // Encode a value that does _not_ represent a valid ColorEnum enumerator.
    sink.clear();
    sink.encode((Color_value_type) 100);

    // Decode the value as a ColorEnum value.
    ColorEnum purple;

    protox::io::byte_data_source purple_source(sink);
    purple_source.decode(purple);

    // Verify that the decoded ColorEnum does not match any of the legal ColorEnum enumerators.
    BOOST_CHECK(purple != ColorEnum_Red::value()   );
    BOOST_CHECK(purple != ColorEnum_Green::value() );
    BOOST_CHECK(purple != ColorEnum_Blue::value()  );
    BOOST_CHECK(purple != ColorEnum_Yellow::value());

    // Encode two different value representations for the colorEnum_Blue enumerator.
    sink.clear();
    sink.encode((Color_value_type)  13);
    sink.encode((Color_value_type) 201);

    protox::io::byte_data_source blue_source(sink);

    ColorEnum blue1;
    ColorEnum blue2;

    blue_source.decode(blue1);
    blue_source.decode(blue2);

    // Verify that the decoded representations are valid ColorEnum_Blue enumerators.
    BOOST_CHECK(blue1                   == blue2                    );
    BOOST_CHECK(blue1                   == ColorEnum_Blue::value()  );
    BOOST_CHECK(ColorEnum_Blue::value() == blue2                    );
    BOOST_CHECK(blue1                   != ColorEnum_Yellow::value());
}

/**********************************************************************************************************************/

BOOST_AUTO_TEST_CASE(test_enum_pre_processor) {
    test_hla1516::DaysOfWeekEnum16::type sun = test_hla1516::DaysOfWeekEnum16::Sun::value();
    test_hla1516::DaysOfWeekEnum16::type mon = test_hla1516::DaysOfWeekEnum16::Mon::value();
    test_hla1516::DaysOfWeekEnum16::type tue = test_hla1516::DaysOfWeekEnum16::Tue::value();
    test_hla1516::DaysOfWeekEnum16::type wed = test_hla1516::DaysOfWeekEnum16::Wed::value();
    test_hla1516::DaysOfWeekEnum16::type thr = test_hla1516::DaysOfWeekEnum16::Thr::value();
    test_hla1516::DaysOfWeekEnum16::type fri = test_hla1516::DaysOfWeekEnum16::Fri::value();
    test_hla1516::DaysOfWeekEnum16::type sat = test_hla1516::DaysOfWeekEnum16::Sat::value();

    test_hla1516::DaysOfWeekEnum16::type day01 = test_hla1516::DaysOfWeekEnum16::Thr::value();

    BOOST_CHECK(sun == sun);
    BOOST_CHECK(tue == tue);

    BOOST_CHECK(sun != mon);
    BOOST_CHECK(fri != wed);

    BOOST_CHECK(day01 == thr);
    BOOST_CHECK(day01 != wed);
}
