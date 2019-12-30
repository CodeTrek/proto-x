/******************************************************************************************************************************************/
// (c) 2009 - 2019 Jay Graham
//
// Distributed under the MIT License
// (see accompanying file LICENSE_1_0_0.txt or http://www.opensource.org/licenses/mit-license.php)
/******************************************************************************************************************************************/

#ifndef PROTOX_BEE_BASIC_DATA_CODEC_HPP
#define PROTOX_BEE_BASIC_DATA_CODEC_HPP

/******************************************************************************************************************************************/

#include <boost/mpl/int.hpp>
#include <boost/mpl/sizeof.hpp>

#include <boost/static_assert.hpp>

#include <protox/platform.hpp>

#include <protox/dtl/codec_interface.hpp>
#include <protox/dtl/compute_octet_boundary.hpp>

#include <protox/bee/codec_tags.hpp>

// #include <protox/bee/basic_data_encoders.hpp>
// #include <protox/bee/basic_data_decoders.hpp>

#include <protox/binary/bytes.hpp>
#include <protox/binary/endian.hpp>

/******************************************************************************************************************************************/

namespace protox {
namespace dtl {

/******************************************************************************************************************************************/

struct bee_basic_codec_impl {
    template<typename T>
    struct octet_boundary {
        typedef typename compute_octet_boundary<T::size_in_bits>::type type;

        BOOST_STATIC_ASSERT(( type::value != UNKNOWN_OCTET_BOUNDARY::value ));
    };

    // Compute the data type's size in bytes from size in bits. If the size in bits is not a multiple
    // of 8, add a padding byte.
    template<typename T>
    struct static_size_in_bytes {
        typedef typename boost::mpl::int_<(T::size_in_bits / 8) + (((T::size_in_bits % 8) == 0) ? 0 : 1)>::type type;
    };

    template<typename T>
    inline static std::size_t dynamic_size(T) {
        return static_size_in_bytes<T>::type::value;
    }

    template<typename S, typename T>
    inline static void encode(S &s, const T &obj) {
        BOOST_STATIC_ASSERT((boost::mpl::sizeof_<unsigned char>::value == 1));
        const protox::binary::BitEndian bitEndian = (T::endianess::value == PROTOX_DTL_LITTLE_ENDIAN ? protox::binary::BIT_LITTLE_ENDIAN : protox::binary::BIT_BIG_ENDIAN);

        const unsigned char *bytes = (unsigned char const*) (&obj.value);

        protox::binary::bytes<
            T::size_in_bits,
            codec::static_size_in_bytes<T>::value,
            (protox::binary::ByteEndian) PROTOX_DTL_PLATFORM_ENDIANESS,
            bitEndian
        >::encode(s, bytes);
    }

    template<typename S, typename T>
    inline static void decode(T &v, const S &s, std::size_t &offset) {
        BOOST_STATIC_ASSERT((boost::mpl::sizeof_<unsigned char>::value == 1));
        const protox::binary::BitEndian bitEndian = (T::endianess::value == PROTOX_DTL_LITTLE_ENDIAN ? protox::binary::BIT_LITTLE_ENDIAN : protox::binary::BIT_BIG_ENDIAN);

        unsigned char *bytes = (unsigned char*) (&v.value);

        protox::binary::bytes<
            T::size_in_bits,
            codec::static_size_in_bytes<T>::value,
            (protox::binary::ByteEndian) PROTOX_DTL_PLATFORM_ENDIANESS,
            bitEndian
        >::decode(s, bytes, offset);
    }
};

/******************************************************************************************************************************************/

template<> struct codec_impl<protox::bee::boolean> : bee_basic_codec_impl {
};

/******************************************************************************************************************************************/

template<> struct codec_impl<protox::bee::number> : bee_basic_codec_impl {
};

/******************************************************************************************************************************************/

}
}

/******************************************************************************************************************************************/

#endif

/******************************************************************************************************************************************/
