/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/
 
#ifndef PROTOX_HLA_KEYWORDS_HPP
#define PROTOX_HLA_KEYWORDS_HPP

#include <boost/preprocessor/repetition.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/iteration/local.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/set.hpp>

/**************************************************************************************************/

namespace protox {
namespace hla {

/**************************************************************************************************/

struct empty {};

/**************************************************************************************************/

// keyword: attrs

/**************************************************************************************************/

#ifndef HLA_MAX_NUM_ATTRS
#define HLA_MAX_NUM_ATTRS 20
#endif

#define HLA_ATTRS_DEFAULT_PARAMS(z, n, text) text##n=empty

// Forward reference
template< BOOST_PP_ENUM(HLA_MAX_NUM_ATTRS, HLA_ATTRS_DEFAULT_PARAMS, typename T) > struct attrs;

// Used to yield the 'text' argument
#define HLA_ATTRS_TEXT(z, n, text) text

// struct attrs specializations
#define HLA_ATTRS(z, n, unused)                               \
  template< BOOST_PP_ENUM_PARAMS(n, typename T) >             \
  struct attrs<                                               \
    BOOST_PP_ENUM_PARAMS(n, T)                                \
    BOOST_PP_COMMA_IF(n)                                      \
    BOOST_PP_ENUM(                                            \
    BOOST_PP_SUB(HLA_MAX_NUM_ATTRS,n), HLA_ATTRS_TEXT, empty) \
  > : boost::mpl::set< BOOST_PP_ENUM_PARAMS(n, T) > {};

// Non-specialized structa attrs
template< BOOST_PP_ENUM_PARAMS(HLA_MAX_NUM_ATTRS, typename T) >
struct attrs : boost::mpl::set< BOOST_PP_ENUM_PARAMS(HLA_MAX_NUM_ATTRS, T) > {};

// Vertical repetition
#define BOOST_PP_LOCAL_MACRO(n) HLA_ATTRS(~, n, ~)
#define BOOST_PP_LOCAL_LIMITS (0, HLA_MAX_NUM_ATTRS - 1)
#include BOOST_PP_LOCAL_ITERATE()

// Clean up definitions
#undef HLA_ATTRS_DEFAULT_PARAMS
#undef HLA_ATTRS_TEXT
#undef HLA_ATTRS

/**************************************************************************************************/

// keyword: params

/**************************************************************************************************/

#ifndef HLA_MAX_NUM_PARAMS
#define HLA_MAX_NUM_PARAMS 20
#endif

#define HLA_PARAMS_DEFAULT_PARAMS(z, n, text) text##n=empty

// Forward reference
template< BOOST_PP_ENUM(HLA_MAX_NUM_PARAMS, HLA_PARAMS_DEFAULT_PARAMS, typename T) > struct params;

// Used to yield the 'text' argument
#define HLA_PARAMS_TEXT(z, n, text) text

// struct attrs specializations
#define HLA_PARAMS(z, n, unused)                                \
  template< BOOST_PP_ENUM_PARAMS(n, typename T) >               \
  struct params<                                                \
    BOOST_PP_ENUM_PARAMS(n, T)                                  \
    BOOST_PP_COMMA_IF(n)                                        \
    BOOST_PP_ENUM(                                              \
    BOOST_PP_SUB(HLA_MAX_NUM_PARAMS,n), HLA_PARAMS_TEXT, empty) \
  > : boost::mpl::set< BOOST_PP_ENUM_PARAMS(n, T) > {};

// Non-specialized structa attrs
template< BOOST_PP_ENUM_PARAMS(HLA_MAX_NUM_PARAMS, typename T) >
struct params : boost::mpl::set< BOOST_PP_ENUM_PARAMS(HLA_MAX_NUM_PARAMS, T) > {};

// Vertical repetition
#define BOOST_PP_LOCAL_MACRO(n) HLA_PARAMS(~, n, ~)
#define BOOST_PP_LOCAL_LIMITS (0, HLA_MAX_NUM_PARAMS - 1)
#include BOOST_PP_LOCAL_ITERATE()

// Clean up definitions
#undef HLA_PARAMS_DEFAULT_PARAMS
#undef HLA_PARAMS_TEXT
#undef HLA_PARAMS

/**************************************************************************************************/

// keyword: child

/**************************************************************************************************/

#ifndef HLA_MAX_NUM_CHILDREN
#define HLA_MAX_NUM_CHILDREN 20
#endif

#define HLA_CHILDREN_DEFAULT_PARAMS(z, n, text) text##n=empty

// Forward reference
template< BOOST_PP_ENUM(HLA_MAX_NUM_CHILDREN, HLA_CHILDREN_DEFAULT_PARAMS, typename T) >
struct child;

// Used to yield the 'text' argument
#define HLA_CHILDREN_TEXT(z, n, text) text

// struct child specializations
#define HLA_CHILDREN(z, n, unused)                                  \
  template< BOOST_PP_ENUM_PARAMS(n, typename T) >                   \
  struct child<                                                     \
    BOOST_PP_ENUM_PARAMS(n, T)                                      \
    BOOST_PP_COMMA_IF(n)                                            \
    BOOST_PP_ENUM(                                                  \
    BOOST_PP_SUB(HLA_MAX_NUM_CHILDREN,n), HLA_CHILDREN_TEXT, empty) \
  > : boost::mpl::set< BOOST_PP_ENUM_PARAMS(n, T) > {};

// Non-specialized structa attrs
template< BOOST_PP_ENUM_PARAMS(HLA_MAX_NUM_CHILDREN, typename T) >
struct child : boost::mpl::set< BOOST_PP_ENUM_PARAMS(HLA_MAX_NUM_CHILDREN, T) > {};

// Vertical repetition
#define BOOST_PP_LOCAL_MACRO(n) HLA_CHILDREN(~, n, ~)
#define BOOST_PP_LOCAL_LIMITS (0, HLA_MAX_NUM_CHILDREN - 1)
#include BOOST_PP_LOCAL_ITERATE()

// Clean up definitions
#undef HLA_CHILDREN_DEFAULT_PARAMS
#undef HLA_CHILDREN_TEXT
#undef HLA_CHILDREN

/**************************************************************************************************/

// keyword: q_name

/**************************************************************************************************/

#ifndef HLA_MAX_NUM_QNAME
#define HLA_MAX_NUM_QNAME 20
#endif

#define HLA_QNAME_DEFAULT_PARAMS(z, n, text) text##n=empty

// Forward reference
template< BOOST_PP_ENUM(HLA_MAX_NUM_QNAME, HLA_QNAME_DEFAULT_PARAMS, typename T) > struct q_name;

// Used to yield the 'text' argument
#define HLA_QNAME_TEXT(z, n, text) text

// struct child specializations
#define HLA_QNAME(z, n, unused)                               \
  template< BOOST_PP_ENUM_PARAMS(n, typename T) >             \
  struct q_name<                                              \
    BOOST_PP_ENUM_PARAMS(n, T)                                \
    BOOST_PP_COMMA_IF(n)                                      \
    BOOST_PP_ENUM(                                            \
    BOOST_PP_SUB(HLA_MAX_NUM_QNAME,n), HLA_QNAME_TEXT, empty) \
  > : boost::mpl::vector< BOOST_PP_ENUM_PARAMS(n, T) > {};

// Non-specialized structa attrs
template< BOOST_PP_ENUM_PARAMS(HLA_MAX_NUM_QNAME, typename T) >
struct q_name : boost::mpl::vector< BOOST_PP_ENUM_PARAMS(HLA_MAX_NUM_QNAME, T) > {};

// Vertical repetition
#define BOOST_PP_LOCAL_MACRO(n) HLA_QNAME(~, n, ~)
#define BOOST_PP_LOCAL_LIMITS (0, HLA_MAX_NUM_QNAME - 1)
#include BOOST_PP_LOCAL_ITERATE()

// Clean up definitions
#undef HLA_QNAME_DEFAULT_PARAMS
#undef HLA_QNAME_TEXT
#undef HLA_QNAME

/**************************************************************************************************/

// keyword: none

/**************************************************************************************************/

struct none : boost::mpl::vector<> {};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
