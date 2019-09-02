/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_DTL_BASIC_HPP
#define PROTOX_DTL_BASIC_HPP

/**********************************************************************************************************************/

#include <cstddef>

#include <boost/static_assert.hpp>
#include <boost/type_traits/has_trivial_constructor.hpp>

#include <protox/platform.hpp>
#include <protox/dtl/endian_enum.hpp>
#include <protox/dtl/basic_tag.hpp>

/**********************************************************************************************************************/

namespace protox {
namespace dtl {

/**********************************************************************************************************************/

/**
 * A type generator for basic data representations. basic data representations form the foundation of the
 * protox::dtl type system. Generally, simple, enumerated, and constructed types are built using basic data
 * representations.
 *
 * Use basic to associate C++ type \a T with a size in bits, endian representation, and encode/decode policy.
 *
 * \tparam T The native type used to represent the basic data representation being defined.
 *
 * \tparam SIZE_IN_BITS The size of the data representation in bits. This value does not have to equal size of \a T in
 *                      bits.
 *
 * \tparam ENDIAN Specifies either big, little, or na endianess.
 *
 * \tparam CODEC_TAG The encode/decode policy.
 *
 * \sa protox::dtl::endian
 *
 *
 * Example:
 *
 * \code
 *       +----------------------------------------------------------------------------------------------------+
 *       | Basic data representation table                                                                    |
 *       +---------------------------------------+--------------+--------------+------------------------------+
 *       | Name                                  | Size in bits | Endian       | Encoding                     |
 *       +---------------------------------------+--------------+--------------+------------------------------+
 *  struct HLAoctet       : basic< unsigned char,   8,            endian::na,    HLAportable                  > {PROTOX_BASIC( HLAoctet )      };
 *  struct HLAinteger16BE : basic< unsigned short, 16,            endian::big,   HLA16BitTwosComplementSigned > {PROTOX_BASIC( HLAinteger16BE )};
 *       +---------------------------------------+--------------+--------------+------------------------------+
 *
 * \endcode
 *
 */

template< typename T, int SIZE_IN_BITS, typename ENDIAN, typename CODEC_TAG >
struct basic : basic_tag {

/**********************************************************************************************************************/

    private:
        // Test for valid template arguments:

        // T is default constructable?
        BOOST_STATIC_ASSERT((boost::has_trivial_constructor< T >::value));

        // Valid size?
        BOOST_STATIC_ASSERT((SIZE_IN_BITS > 0));

        // Valid endian-ness?
        BOOST_STATIC_ASSERT((ENDIAN::value == endian::little::value) ||
                            (ENDIAN::value == endian::big::value) ||
                            (ENDIAN::value == endian::na::value));

/**********************************************************************************************************************/

    public:
        typedef CODEC_TAG codec_tag;
        typedef ENDIAN endianess;
        typedef T value_type;

/**********************************************************************************************************************/

        enum { size_in_bits = SIZE_IN_BITS };

/**********************************************************************************************************************/

        T value;

/**********************************************************************************************************************/

        basic() : value(T()) {}

        // Implicit conversion from T to basic
        basic(const T v) : value(v) {}

/**********************************************************************************************************************/

        /**
         * Implicit conversion from basic to \a T.
         */
        inline operator T() const { return value; }

        /**
         * Increment operator
         */
        inline basic &operator ++() {
            ++value;
            return (*this);
        }

        /**
         * Increment/assign operator
         */
        inline basic &operator +=(const basic &v) {
            value += v;
            return (*this);
        }

        /**
         * Enable numerical assignment. For example, assignment of float to int, assignment int to float, etc...
         */
        template< typename RHST >
        basic &operator =(const RHST rhs) {
            value = rhs;
            return (*this);
        }
};

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

/**
 * \file basic.hpp
 *
 * \def PROTOX_BASIC(basic_name)
 * Defines constructor methods for a basic type named \a basic_name.
 */
#define PROTOX_BASIC(basic_name)                      \
  basic_name() {}                                     \
  typedef protox::dtl::basic< basic_name::value_type, \
    basic_name::size_in_bits,                         \
    basic_name::endianess,                            \
    basic_name::codec_tag > base_type;                \
  basic_name(base_type::value_type v) : base_type(v) {}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
