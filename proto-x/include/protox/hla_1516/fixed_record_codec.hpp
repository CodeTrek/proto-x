/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_1516_FIXED_RECORD_CODEC_HPP
#define PROTOX_HLA_1516_FIXED_RECORD_CODEC_HPP

/**************************************************************************************************/

#include <cstddef>

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/min_max.hpp>

#include <protox/dtl/unknown_static_size.hpp>
#include <protox/dtl/codec_interface.hpp>

#include <protox/hla_1516/codec_tags.hpp>
#include <protox/hla_1516/static_pad.hpp>
#include <protox/hla_1516/dynamic_pad.hpp>

/**************************************************************************************************/

using namespace boost;

/**************************************************************************************************/

namespace protox { namespace dtl {

/**************************************************************************************************/

namespace fixed_record_codec_1516 {

/**************************************************************************************************/

struct null_impl_layout
{
  typedef mpl::int_< 0 > static_pad;
  typedef mpl::int_< 0 > static_offset;
};

struct null_impl
{
  typedef null_impl_layout layout;
  typedef mpl::int_< 0 > static_size;
  typedef mpl::int_< 0 > octet_boundary;
  typedef mpl::bool_< true > has_static_size;

  template< typename S, typename R >
  inline static void encode(S &, R const &) {}

  template< typename S, typename R >
  inline static void decode(R &, S const &, std::size_t &) {}

  template< typename R >
  inline static bool is_equal(R const &, R const &) { return true; }
};

// This template is used to compute layout values i.e., padding and
// offset sizes in bytes.
template<
  typename T,               // The field of focus.
  typename Base,            // T's immediate predecessor.
  bool T_Has_Static_Size,   // true, if T's size is fixed and Base's size
                                // is fixed.
  bool Base_Has_Static_Size // true, if Base's size is fixed.
> struct _layout;

// The static size of field T and its Base determine if T's offset and
// padding can be computed at compile time. The table below list all
// possible combinations of T_Has_Static_Size and Base_Has_Static_Size
// and each combinations's implication for calulating padding and offset
// values at compile time.

//   +------------------+------------------------------------------+
//   | Has Static Size? |       Computed at Compile-time?          |
//   +-------+----------+----------------------------+-------------+
//   |   T   |   Base   | Padding between Base and T |  T's Offset |
//   +-------+----------+----------------------------+-------------+
//   | true  |   true   |          true              |  true       |
//   | false |   true   |          true              |  true       |
//   | false |   false  |          false             |  false      |
//   | true  |   false  |          undefined         |  undefined  |
//   +-------+----------+----------------------------+-------------+

template< typename T, typename Base >
struct _layout< T, Base, true, true >
{
  typedef typename protox::hla_1516::static_pad_<
    typename Base::layout::static_offset,
    typename Base::static_size,
    typename protox::dtl::codec::octet_boundary< typename T::value_type >::type
  >::type static_pad;

  typedef mpl::int_<
    Base::layout::static_offset::value +
    Base::static_size::value        +
    static_pad::value
  > static_offset;

  template< typename S, typename R >
  inline static void encode_pad(S &s, R const &, std::size_t const)
  {
    protox::hla_1516::pad< S, static_pad::value >::encode(s);
  }

  template< typename S, typename R >
  inline static void decode_pad(
    R &,
    S const &s,
    std::size_t const base_size,
    std::size_t &offset )
  {
    protox::hla_1516::pad< S, static_pad::value >::decode(s, offset);
  }

  template< typename R >
  inline static std::size_t dynamic_size(R const &)
  {
    return (static_offset::value + protox::dtl::codec::static_size_in_bytes<typename T::value_type>::value);
  }
};

template< typename T, typename Base >
struct _layout< T, Base, false, true >
{
  typedef typename protox::hla_1516::static_pad_<
    typename Base::layout::static_offset,
    typename Base::static_size,
    typename protox::dtl::codec::octet_boundary< typename T::value_type >::type
  >::type static_pad;

  typedef mpl::int_<
    Base::layout::static_offset::value +
    Base::static_size::value           +
    static_pad::value
  > static_offset;

  template< typename S, typename R >
  inline static void encode_pad(S &s, R const &, std::size_t const)
  {
    protox::hla_1516::pad< S, static_pad::value >::encode(s);
  }

  template< typename S, typename R >
  inline static void decode_pad(
    R &,
    S const &s,
    std::size_t const base_size,
    std::size_t &offset)
  {
    protox::hla_1516::pad< S, static_pad::value >::decode(s, offset);
  }

  template< typename R >
  inline static std::size_t dynamic_size(R const &obj)
  {
    typename T::value_type const &value = obj.template f_ < T > ();
    typedef typename T::impl::layout T_layout;
    return (static_offset::value + T_layout::dynamic_size(value));
  }
};

template< typename T, typename Base >
struct _layout< T, Base, false, false >
{
  typedef protox::dtl::UNKNOWN_STATIC_SIZE static_offset;

  template< typename S, typename R >
  inline static void encode_pad(
    S &s,
    R const &obj,
    std::size_t const base_size)
  {
    std::size_t const pad_bytes
      = sizeof_pad(
          base_size,
          protox::dtl::codec::octet_boundary< typename T::value_type >::value);

    encode_pad(s, pad_bytes);
  }

  template< typename S, typename R >
  inline static void decode_pad(
    R &,
    S const &s,
    std::size_t const base_size,
    std::size_t &offset)
  {
    std::size_t const pad_bytes
      = sizeof_pad(
          base_size,
          protox::dtl::codec::octet_boundary< typename T::value_type >::value);

    decode_pad(s, pad_bytes, offset);
  }

  template< typename R >
  inline static std::size_t dynamic_size(R const &obj)
  {
    typedef typename Base::layout base_layout;
    std::size_t const base_size = base_layout::dynamic_size(obj);
    std::size_t const pad_bytes
      = sizeof_pad(
        base_size, protox::dtl::codec::octet_boundary< typename T::value_type >::value);

    typename T::value_type const &value = obj.template f_< T > ();
    typedef typename T::impl::layout T_layout;
    return (base_size + pad_bytes + T_layout::dynamic_size(value));
  }
};

// _The following case should never happen_
// Once a dynamic Base field in record R is
// encounterd (i.e., Base::static_size is dtel::UNKNOWN_STATIC_SIZE),
// then all subsequent fields T have unknown static sizes.
template< typename T, typename Base > struct _layout< T, Base, true, false >;

// Create the compile time interface for the given type pair, T and Base,
// where T derives directly from Base.
//
// T represents a single field.
// Base represents the partial record formed by T's predeccsor fields.
template< typename T, typename Base >
struct _impl
{
  typedef typename protox::dtl::codec::static_size_in_bytes< typename T::value_type >::type static_size;

  typedef typename mpl::max<
    typename protox::dtl::codec::octet_boundary< typename T::value_type >::type,
    typename Base::octet_boundary
  >::type octet_boundary;

  // Both Base and T have a static size?
  typedef mpl::bool_<
    Base::has_static_size::value &&
    (static_size::value != protox::dtl::UNKNOWN_STATIC_SIZE::value)
  > has_static_size;

  typedef _layout<
    T,
    Base,
    has_static_size::value,
    Base::has_static_size::value
  > layout;

  template< typename S, typename R >
  static void encode( S &s, R const &obj )
  {
    std::size_t const base_offset = s.size();
    Base::encode( s, obj );
    std::size_t const base_size = s.size() - base_offset;

    layout::template encode_pad<S, R>( s, obj, base_size );

    s.start_field();

    typename T::value_type const &value = obj.template f_< T > ();
    protox::dtl::codec::encode(s, value);

    s.end_field();
  }

  template< typename S, typename R >
  static void decode( R &obj, S const &s, std::size_t &offset )
  {
    std::size_t const base_offset = offset;
    Base::decode( obj, s, offset );
    std::size_t const base_size = offset - base_offset;

    layout::template decode_pad<S, R>( obj, s, base_size, offset );

    s.start_field();
    typename T::value_type &value = obj.template f_< T >();
    protox::dtl::codec::decode( value, s, offset );
    s.end_field();
  }
};

template< typename T >
struct impl
{
  // Compute the fixed record's required compile-time impl interface.
  //
  // A fold meta-function is used to construct encode/decode functions
  // that makes recursive calls down record's a field structure, computing
  // alignment requirements along the way.
  typedef typename mpl::fold<
    typename T::field_vector,
    null_impl,
    _impl< mpl::placeholders::_2, mpl::placeholders::_1 >
  >::type type;
  };

/**************************************************************************************************/

} // protox::dtl::fixed_record_codec

/**************************************************************************************************/

template<> struct codec_impl< protox::hla_1516::HLAfixedRecord >
{
  template< typename T >
  struct octet_boundary
  {
    typedef typename fixed_record_codec_1516::impl< T >::type::octet_boundary type;
  };

  template< typename T >
  struct static_size_in_bytes
  {
    typedef typename fixed_record_codec_1516::impl< T >::type impl;

    typedef typename mpl::if_ <
      // Size is not fixed?
      mpl::equal_to< typename impl::static_size, protox::dtl::UNKNOWN_STATIC_SIZE >,

      // true : unknown static size.
      protox::dtl::UNKNOWN_STATIC_SIZE,

      // false : compute this record's static size.
      mpl::plus<
        typename impl::layout::static_offset,
        typename impl::static_size
      >
    >::type type;
  };

  template< typename T >
  inline static std::size_t dynamic_size(T const &obj)
  {
    typedef typename fixed_record_codec_1516::impl< T >::type impl;
    return impl::layout::dynamic_size(obj);
  };

  template< typename S, typename T >
  inline static void encode(S &s, T const &obj)
  {
    typedef typename fixed_record_codec_1516::impl< T >::type impl;
    s.start_fixed_record();
    impl::encode(s, obj);
    s.end_fixed_record();
  }

  template< typename S, typename T >
  inline static void decode(T &v, S const &s, std::size_t &offset)
  {
    typedef typename fixed_record_codec_1516::impl< T >::type impl;
    s.start_fixed_record();
    impl::decode(v, s, offset);
    s.end_fixed_record();
  }
};

/**************************************************************************************************/

}} // protox::dtl

/**************************************************************************************************/

#endif

/**************************************************************************************************/
