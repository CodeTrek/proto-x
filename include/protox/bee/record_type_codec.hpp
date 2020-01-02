/******************************************************************************************************************************************/
// (c) 2009 - 2019 Jay Graham
//
// Distributed under the MIT License
// (see accompanying file LICENSE_1_0_0.txt or http://www.opensource.org/licenses/mit-license.php)
/******************************************************************************************************************************************/

#ifndef PROTOX_BEE_RECORD_TYPE_CODEC_HPP
#define PROTOX_BEE_RECORD_TYPE_CODEC_HPP

/******************************************************************************************************************************************/

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/min_max.hpp>
#include <boost/mpl/plus.hpp>

#include <protox/platform.hpp>

#include <protox/dtl/codec_interface.hpp>
#include <protox/dtl/compute_octet_boundary.hpp>

#include <protox/bee/codec_tags.hpp>

#include <protox/binary/bytes.hpp>
#include <protox/binary/endian.hpp>

/******************************************************************************************************************************************/

namespace protox {
namespace dtl {

/******************************************************************************************************************************************/

namespace bee_record_type_codec {

/******************************************************************************************************************************************/

// struct null_impllayout_ { typedef boost::mpl::int_<0> static_offset; };

/******************************************************************************************************************************************/

struct null_impl {
    typedef boost::mpl::int_<0> static_offset;
    typedef boost::mpl::int_<0> static_size;
    typedef boost::mpl::int_<0> octet_boundary;

    template<typename S, typename R>
    inline static void encode(S&, R const&) {
    }

    template<typename S, typename R>
    inline static void decode(R&, S const&, std::size_t&) {
    }

    template<typename R>
    inline static bool is_equal(R const&, R const&) {
        return true;
    }
};

/******************************************************************************************************************************************/

// Create the compile time interface for the given type pair, T and Base, where T derives directly
// from Base.
//
// T represents a single data element.
// Base represents the partial word formed by T's predecessor data elements.
template<typename T, typename Base>
struct impl_ {
    typedef boost::mpl::int_<Base::static_offset::value + Base::static_size::value> static_offset;
    typedef typename dtl::codec::static_size_in_bytes<typename T::value_type>::type static_size;
    typedef typename boost::mpl::max<typename dtl::codec::octet_boundary<typename T::value_type>::type, typename Base::octet_boundary>::type octet_boundary;

    template<typename R>
    inline static std::size_t dynamic_size(R const&) {
        return (static_offset::value + dtl::codec::static_size_in_bytes<typename T::value_type>::value);
    }

    template<typename S, typename R>
    static void encode(S &s, R const &obj) {
        typename T::value_type const &value = obj.template f_<T>();
        dtl::codec::encode(s, value);

        Base::encode(s, obj);
    }

    template<typename S, typename R>
    static void decode(R &obj, S const &s, std::size_t &offset) {
        Base::decode(obj, s, offset);

        typename T::value_type &value = obj.template f_<T>();
        dtl::codec::decode(value, s, offset);
    }
};

/******************************************************************************************************************************************/

template<typename T>
struct impl {
    // Compute the fixed record's required compile-time impl interface.
    //
    // A fold meta-function is used to construct encode/decode functions that makes recursive calls
    // down record's a field structure, computing alignment requirements along the way.
    typedef typename boost::mpl::fold<typename T::field_vector, null_impl, impl_<boost::mpl::placeholders::_2, boost::mpl::placeholders::_1> >::type type;
};

/******************************************************************************************************************************************/

}

/******************************************************************************************************************************************/

template<> struct codec_impl<protox::bee::record> {
    template<typename T>
    struct octet_boundary {
        typedef typename bee_record_type_codec::impl<T>::type::octet_boundary type;
    };

    template<typename T>
    struct static_size_in_bytes {
        typedef typename bee_record_type_codec::impl<T>::type impl;
        typedef typename boost::mpl::plus<typename impl::static_offset, typename impl::static_size >::type type;
    };

    template<typename T>
    inline static std::size_t dynamic_size(T const &obj) {
        typedef typename bee_record_type_codec::impl<T>::type impl;
        return impl::dynamic_size(obj);
    }
    ;

    template<typename S, typename T>
    inline static void encode(S &s, T const &obj) {
        typedef typename bee_record_type_codec::impl<T>::type impl;
        impl::encode(s, obj);
    }

    template<typename S, typename T>
    inline static void decode(T &v, S const &s, std::size_t &offset) {
        typedef typename bee_record_type_codec::impl<T>::type impl;
        impl::decode(v, s, offset);
    }
};

/******************************************************************************************************************************************/

}
}

/******************************************************************************************************************************************/

#endif

/******************************************************************************************************************************************/
