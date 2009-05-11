/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_DTL_ENUM_PP_HPP
#define PROTOX_DTL_ENUM_PP_HPP

/******************************************************************************/

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

/******************************************************************************/

#define PROTOX_ENUM_EQUALITY_OPERATOR             \
  bool Type::is_equal(                            \
    enum_rep_type lhs,                            \
    enum_rep_type rhs ) { return (lhs == rhs); }

/******************************************************************************/

#define PROTOX_ENUM_VALUE(NAME, VALUE)                     \
  struct NAME : private Enum                               \
  {                                                        \
    static Type value() { return( Enum::value(VALUE) ); }  \
  }

/******************************************************************************/

#define PROTOX_ENUM_DEFAULT(NAME)                         \
    Type::Type() : Type_enumerated( NAME::value() ) {}

/******************************************************************************/

#endif

/******************************************************************************/
