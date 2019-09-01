/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_DTL_ALTERNATIVE_HPP
#define PROTOX_DTL_ALTERNATIVE_HPP

/**********************************************************************************************************************/

namespace protox {
namespace dtl {

/**********************************************************************************************************************/

// Represents a variant record alternative value of type T.
template< typename T > // The variant's type
struct alternative {
    typedef T value_type;

    value_type value;

    alternative() {}
    alternative(const T &v) : value(v) {}
};

/**********************************************************************************************************************/


// Returns the data type associated with the alternative for the given discriminant D.
template< typename D > // The discriminant
struct get_alternative_type {
    typedef typename D::alternative type;
};

/**********************************************************************************************************************/


}}

/**********************************************************************************************************************/


#endif

/**********************************************************************************************************************/
