/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_HLA_BUILD_FULL_NAME_HPP
#define PROTOX_HLA_BUILD_FULL_NAME_HPP

/**********************************************************************************************************************/

/**************************************************************************************************/

#include <string>

/**********************************************************************************************************************/

namespace protox {
namespace hla {

/**********************************************************************************************************************/

enum reverse_flag {REVERSED = 1, NOT_REVERSED};

/**********************************************************************************************************************/

struct build_full_name {
    std::string &full_name;
    reverse_flag reverse;
  
    build_full_name(std::string &fn, reverse_flag f = NOT_REVERSED) : full_name(fn), reverse(f) {}

    template< typename N >
    void operator()(N) {

        if (full_name.empty()) {
            full_name = std::string(N::name_type::name());
        } else {
            if (reverse == REVERSED) {
                full_name = std::string(N::name_type::name()) + "." + full_name;
            } else {
                full_name = full_name + "." + std::string(N::name_type::name());
            }
        }
    }
};

/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
