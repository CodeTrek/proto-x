/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/******************************************************************************/

#ifndef PROTOX_HLA_HAS_DUPICATE_PARAM_NAMES_HPP
#define PROTOX_HLA_HAS_DUPICATE_PARAM_NAMES_HPP

/******************************************************************************/

#include <boost/mpl/count.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/max_element.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/equal_to.hpp>

#include <protox/hla/element_counter.hpp>

/******************************************************************************/

namespace protox { namespace hla {

/******************************************************************************/

template< bool EMPTY_SET, typename SET > struct has_duplicate_param_names_impl;

/******************************************************************************/

template< typename SET >
struct has_duplicate_param_names_impl< true, SET >
{
  // Empty sets do not have duplicate names.
  typedef typename boost::mpl::bool_< false >::type type;
};

/******************************************************************************/

template< typename SET >
struct has_duplicate_param_names_impl< false, SET >
{
  // Count each unique attr name.
  typedef typename boost::mpl::transform_view<
    SET,
    typename element_counter< SET >::template op< boost::mpl::placeholders::_1 >
  >::type name_counts;

  // Get the max number of occurances of any name in SET.
  typedef typename
    boost::mpl::deref<
      typename boost::mpl::max_element< name_counts >::type
    >::type max_count;

  // No duplicate names (i.e., max_count is 1)?
  typedef typename
    boost::mpl::equal_to< max_count,
                          boost::mpl::int_< 1 > >::type no_duplicates;

  // Has duplicates = !no_duplicates.
  typedef typename boost::mpl::bool_< !no_duplicates::value >::type type;
};

/******************************************************************************/

template< typename SET >
struct has_duplicate_param_names
{
  typedef typename has_duplicate_param_names_impl<
      boost::mpl::empty<SET>::value, SET
    >::type type;
};

/******************************************************************************/

}} // protox.hla

/******************************************************************************/

#endif

/******************************************************************************/
