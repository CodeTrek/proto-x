/******************************************************************************************************************************************/
// (c) 2009 - 2019 Jay Graham
//
// Distributed under the MIT License
// (see accompanying file LICENSE_1_0_0.txt or http://www.opensource.org/licenses/mit-license.php)
/******************************************************************************************************************************************/

#ifndef PROTOX_DTL_VARIABLE_ARRAY_HPP
#define PROTOX_DTL_VARIABLE_ARRAY_HPP

/******************************************************************************************************************************************/

#include <initializer_list>

/******************************************************************************************************************************************/

namespace protox {
namespace dtl {

/******************************************************************************************************************************************/

/**
 * Constructs a variable size array with \a T as the container type.
 *
 * \tparam T The container type used to store the elements of the array.
 * \tparam CODEC_TAG The encode/decode policy.
 *
 * Example:
 *
 * \code
 *  // Define a simple type
 *  struct SimpleHLAoctet : simple< HLAoctet > {};
 *
 *  // Define a array using 1516 variable array encoding using std::vector as the container type
 *  typedef variable_array< std::vector< SimpleHLAoctet >, HLAvariableArray > variable_array_type;
 *
 * \endcode
 *
 */

/******************************************************************************************************************************************/

template<typename T, typename CODEC_TAG>
struct variable_array : public T {
    typedef T array_type;
    typedef typename T::value_type value_type;
    typedef CODEC_TAG codec_tag;

    variable_array() {
    }

    variable_array(std::initializer_list<value_type> l) :
            T(l) {
    }
};

/******************************************************************************************************************************************/

#define PROTOX_VARIABLE_ARRAY(variable_array_name)                                                                            \
    /* Default constructor. */                                                                                                \
  variable_array_name() {}                                                                                                    \
                                                                                                                              \
  /* simple_name derives from simple_type. */                                                                                 \
  typedef protox::dtl::variable_array< variable_array_name::array_type, variable_array_name::codec_tag > variable_array_type; \
                                                                                                                              \
  /* Initialization constructor. */                                                                                           \
  variable_array_name(std::initializer_list<variable_array_name::value_type> l) : variable_array_type(l) {}

/******************************************************************************************************************************************/

}
}

/******************************************************************************************************************************************/

#endif

/******************************************************************************************************************************************/
