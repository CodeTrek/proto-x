/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_DTL_ENUM_PP_HPP
#define PROTOX_DTL_ENUM_PP_HPP

/**************************************************************************************************/

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
 * namespace skill_level_enum
 * {
 *   PROTOX_ENUM_TYPE( HLAinteger16BE, enumerated );
 *
 *   PROTOX_ENUM_VALUE( POOR,      1 );
 *   PROTOX_ENUM_VALUE( GOOD,      2 );
 *   PROTOX_ENUM_VALUE( EXCELLENT, 3 );
 *
 *   PROTOX_ENUM_EQUALITY_OPERATOR;
 *   PROTOX_ENUM_DEFAULT( GOOD );
 * }
 *
 * skill_level_enum::Type skill_level;            // defaults to GOOD
 * skill_level = skill_level_enum::POOR::value(); // Set to POOR
 *
 * \endcode
 *
 * \def PROTOX_ENUM_TYPE(T, ENUMERATED_TYPE)
 *
 * This macro generates boilerplate code used to define a protox enumerated type. The output from
 * this macro is a class named \c Type. \a T is the basic type used to represent enumerated values,
 * and \c Type derives from \a ENUMERATED_TYPE.
 *
 * \def PROTOX_ENUM_EQUALITY_OPERATOR
 *
 * Declares and implements a default equality operator for \c Type.
 *
 * \def PROTOX_ENUM_VALUE(NAME, VALUE)
 *
 * Defines an enumerator with the given \a NAME and \a VALUE.
 *
 * \def PROTOX_ENUM_DEFAULT(NAME)
 *
 * Defines the default enumerator.
 */

#define PROTOX_ENUM_TYPE(T, ENUMERATED_TYPE)                                  \
  typedef T enum_rep_type;                                                    \
  typedef ENUMERATED_TYPE< class Type, enum_rep_type > Type_enumerated;       \
                                                                              \
  class Type : public Type_enumerated                                         \
  {                                                                           \
  private:                                                                    \
    friend class Enum;                                                        \
                                                                              \
    Type(enum_rep_type v) : Type_enumerated(v) {}                             \
                                                                              \
  public:                                                                     \
    Type();                                                                   \
    Type(const Type & v) : Type_enumerated(v) {}                              \
    ~Type() {}                                                                \
                                                                              \
    static bool is_equal(enum_rep_type lhs, enum_rep_type rhs);               \
  };                                                                          \
                                                                              \
  class Enum                                                                  \
  {                                                                           \
    protected: static Type value(enum_rep_type v) { return Type(v); }         \
  }

/**************************************************************************************************/

#define PROTOX_ENUM_EQUALITY_OPERATOR             \
  bool Type::is_equal(                            \
    enum_rep_type lhs,                            \
    enum_rep_type rhs ) { return (lhs == rhs); }

/**************************************************************************************************/

#define PROTOX_ENUM_VALUE(NAME, VALUE)                     \
  struct NAME : private Enum                               \
  {                                                        \
    static Type value() { return( Enum::value(VALUE) ); }  \
  }

/**************************************************************************************************/

#define PROTOX_ENUM_DEFAULT(NAME) Type::Type() : Type_enumerated( NAME::value() ) {}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
