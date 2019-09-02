/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_DTL_ENUM_PP_HPP
#define PROTOX_DTL_ENUM_PP_HPP

/**********************************************************************************************************************/

/**
 * \file enum_pp.hpp
 *
 * A collection of macros that make defining protox compliant easier. Use these macros inside a
 * namespace to ensure that the various \c class and \c struct definitions they produce do not
 * conflict.
 *
 * Example:
 *
 * \code
 *
 * //      +------------------------------------+-------------------------------+------------+--------+
 * //      | Name                               | Representation                | Enumerator | Values |
 * //      +------------------------------------+-------------------------------+------------+--------+
 * namespace skill_level_enum { PROTOX_ENUM_TYPE( HLAinteger16BE, enumerated   );
 * //      +------------------------------------+-------------------------------+------------+--------+
 *                                                             PROTOX_ENUM_VALUE( POOR,        1     );
 * //                                                                           +------------+--------+
 *                                                             PROTOX_ENUM_VALUE( GOOD,        2     );
 * //                                                                           +------------+--------+
 *                                                             PROTOX_ENUM_VALUE( EXCELLENT,   3     );
 * //                                                                           +------------+--------+
 *        PROTOX_ENUM_EQUALITY_OPERATOR;
 *        PROTOX_ENUM_DEFAULT( GOOD );
 *
 * } // skill_level_enum
 *
 * skill_level_enum::type skill_level;            // defaults to GOOD
 * skill_level = skill_level_enum::POOR::value(); // Set to POOR
 *
 * \endcode
 *
 * \def PROTOX_ENUM_TYPE(T, ENUMERATED_TYPE)
 *
 * This macro generates boilerplate code used to define a protox enumerated type. The output from
 * this macro is a class named \c type. \a T is the basic type used to represent enumerated values,
 * and \c type derives from \a ENUMERATED_TYPE.
 *
 * \def PROTOX_ENUM_EQUALITY_OPERATOR
 *
 * Declares and implements a default equality operator for \c type.
 *
 * \def PROTOX_ENUM_VALUE(NAME, VALUE)
 *
 * Defines an enumerator with the given \a NAME and \a VALUE.
 *
 * \def PROTOX_ENUM_DEFAULT(NAME)
 *
 * Defines the default enumerator.
 */

#define PROTOX_ENUM_TYPE(T, ENUMERATED_TYPE, DEFAULT_VALUE)                                     \
    typedef T enum_rep_type;                                                                    \
                                                                                                \
    class type : public ENUMERATED_TYPE< type, enum_rep_type > {                                \
        private:                                                                                \
            friend class private_enum;                                                          \
                                                                                                \
            type(enum_rep_type v) : ENUMERATED_TYPE< type, enum_rep_type >(v) {}                \
                                                                                                \
        public:                                                                                 \
            type() : ENUMERATED_TYPE< type, enum_rep_type >( DEFAULT_VALUE ) {}                 \
            type(const type & v) : ENUMERATED_TYPE< type, enum_rep_type >(v) {}                 \
            ~type() {}                                                                          \
                                                                                                \
            static bool is_equal(enum_rep_type lhs, enum_rep_type rhs) { return (lhs == rhs); } \
    };                                                                                          \
                                                                                                \
    class private_enum {                                                                        \
        protected: static const type value(enum_rep_type v) { return type(v); }                 \
    };                                                                                          \
                                                                                                \
    typedef ENUMERATED_TYPE< type, enum_rep_type > type_enumerated

/**********************************************************************************************************************/

#define PROTOX_ENUM_VALUE(NAME, VALUE)                                    \
    struct NAME : private private_enum {                                  \
        static type value() { return( private_enum::value(VALUE) ); }     \
    }

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
