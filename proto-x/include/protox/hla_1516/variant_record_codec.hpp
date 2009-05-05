/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_1516_VARIANT_RECORD_CODEC_HPP
#define PROTOX_HLA_1516_VARIANT_RECORD_CODEC_HPP

/**************************************************************************************************/

#include <cstddef>

#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/not_equal_to.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/multiplies.hpp>
#include <boost/call_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform_view.hpp>

#include <protox/dtl/codec_interface.hpp>
#include <protox/dtl/unknown_static_size.hpp>
#include <protox/dtl/discriminant.hpp>
#include <protox/dtl/discriminator_test.hpp>
#include <protox/dtl/alternative.hpp>

#include <protox/hla_1516/codec_tags.hpp>
#include <protox/hla_1516/static_pad.hpp>
#include <protox/hla_1516/dynamic_pad.hpp>
#include <protox/hla_1516/size_type.hpp>

/**************************************************************************************************/

using namespace boost;

/**************************************************************************************************/

namespace protox { namespace dtl {

/**************************************************************************************************/

namespace variant_record_codec_1516 {

/**************************************************************************************************/

    // Compute the padding (in bytes) between the discriminant value and
    // the variant record's value, where R is a discriminant record type
    template< typename R >
    struct compute_static_pad {
      typedef typename protox::hla_1516::static_pad_<
        mpl::int_<0>,
        typename protox::dtl::codec::static_size_in_bytes< typename R::discriminant_type >::type,
        typename protox::dtl::codec::octet_boundary< R >::type
      >::type type;
    };

    // Forward reference.
    template< typename Other > struct _layout_other;

    template<>
    struct _layout_other< protox::dtl::discriminant_other_none >
    {
      template< typename S, typename R >
      inline static void encode(S &s, R const &obj)
      {
        typedef typename compute_static_pad< R >::type static_pad;

        protox::dtl::codec::encode(s, obj.discriminant);
        protox::hla_1516::pad< S, static_pad::value >::encode(s);
      }

      template< typename S, typename R >
      inline static void decode( R &, S const &s, std::size_t &offset )
      {
        typedef typename compute_static_pad< R >::type static_pad;
        protox::hla_1516::pad< S, static_pad::value >::decode( s, offset );
      }

      template< typename R >
      inline static std::size_t dynamic_size( R const & )
      {
        typedef typename compute_static_pad< R >::type static_pad;
        return(protox::dtl::codec::static_size_in_bytes< typename R::discriminant_type >::value + static_pad::value);
      }
    };

    template< typename Other  >
    struct _layout_other
    {
      template< typename S, typename R >
      inline static void encode( S &s, R const &obj )
      {
        typename Other::value_type const *value = obj.other_();

        assert( value != 0 ); // Don't allow null 'other' value.
#if 0
        if (value == 0) {
          typedef null_dtx< discriminant_other_none > null_value;
          null_value::encode( s, obj );

          return;
        }
#endif

        typedef typename compute_static_pad< R >::type static_pad;

        protox::dtl::codec::encode( s, obj.discriminant );
        protox::hla_1516::pad< S, static_pad::value >::encode( s );
        protox::dtl::codec::encode( s, *value );
      }

      template< typename S, typename R >
      inline static void decode(
        R &obj,
        S const &s,
        std::size_t &offset )
      {
        typedef typename compute_static_pad< R >::type static_pad;
        protox::hla_1516::pad< S, static_pad::value >::decode( s, offset );

        typename Other::value_type value;
        protox::dtl::codec::decode( value, s, offset );

        obj.other_(value);
      }

      template< typename R >
      inline static std::size_t dynamic_size( R const &obj )
      {
        typename Other::value_type const *value = obj.other_();

        if (value == 0) {
          typedef _layout_other< discriminant_other_none > null_value;
          return( null_value::dynamic_size( obj ) );
        }

        std::size_t const alt_size = protox::dtl::codec::dynamic_size( *value );
        typedef typename compute_static_pad< R >::type static_pad;

        return(
          protox::dtl::codec::static_size_in_bytes< typename R::discriminant_type >::value +
          static_pad::value                                     +
          alt_size
        );
      }
    };

    template< typename D, typename Base >
    struct _layout
    {
      typedef typename protox::dtl::discriminator_test< D >::type discriminator_test;

      template< typename S, typename R >
      static void encode( S &s, R const &obj )
      {
        if ( discriminator_test::is_equal( obj.discriminant ) ) {
          typename D::alternative::value_type const *value = obj.template alt_< D >();

          assert( value != 0 ); // Don't allow null alternative values.
#if 0
          if (value == 0) {
            typedef null_dtx< discriminant_other_none > null_value;
            null_value::encode( s, obj );
            return;
          }
#endif

          typedef typename compute_static_pad< R >::type static_pad;

          protox::dtl::codec::encode( s, obj.discriminant );
          protox::hla_1516::pad< S, static_pad::value >::encode( s );
          protox::dtl::codec::encode( s, *value );

          return;
        }

        Base::encode( s, obj );
      }

      template< typename S, typename R >
      static void decode( R &obj, S const &s, std::size_t &offset )
      {
        if ( discriminator_test::is_equal( obj.discriminant ) ) {

          typedef typename compute_static_pad< R >::type static_pad;
          protox::hla_1516::pad< S, static_pad::value >::decode( s, offset );

          typename D::alternative::value_type value;
          protox::dtl::codec::decode( value, s, offset );

          obj.template alt_< D >( value );

          return;
        }

        Base::decode( obj, s, offset );
      }

      template< typename R >
      static std::size_t dynamic_size( R const &obj )
      {
        if ( discriminator_test::is_equal( obj.discriminant ) ) {
          typename D::alternative::value_type const *value = obj.template alt_< D >();

          if (value == 0) {
            typedef _layout_other< discriminant_other_none > null_value;
            return( null_value::dynamic_size( obj ) );
          }

          std::size_t const alt_size = protox::dtl::codec::dynamic_size( *value );

          typedef typename compute_static_pad< R >::type static_pad;

          return( protox::dtl::codec::static_size_in_bytes< typename R::discriminant_type >::value + static_pad::value + alt_size );
        }

        return( Base::dynamic_size( obj ) );
      }
    };

    template< typename T >
    struct impl
    {
      // Compute the layout compile-time interface.
      typedef typename mpl::fold<
        typename T::d_vector,
        _layout_other< typename T::other_type >,
        _layout< boost::mpl::placeholders::_2, boost::mpl::placeholders::_1 >
      >::type type;
    };

/**************************************************************************************************/

}

/**************************************************************************************************/

  template<> struct codec_impl< protox::hla_1516::HLAvariantRecord >
  {
    // C++ does not allow full template specialiation within a non-namespace container. Add
    // an extra template parameter to prevent the need for full specialization. The extra
    // paramater is ignored.
    template< typename T, typename I >
    struct other_octet_boundary {
      typedef typename protox::dtl::codec::octet_boundary< typename T::value_type >::type type;
    };

    // This would be a fully specialized template outside of the struct scope.
    template<typename I>
    struct other_octet_boundary< protox::dtl::discriminant_other_none, I > {
      typedef mpl::int_<0> type;
    };

    template< typename T >
    struct alternative_octet_boundary {
      typedef typename protox::dtl::codec::octet_boundary< typename T::value_type >::type type;
    };

    template< typename T >
    struct octet_boundary {
      // Compute the octet boundary of the alternative values.
      typedef typename mpl::max<
        typename other_octet_boundary< typename T::other_type, void >::type,
        typename mpl::deref<
          typename mpl::max_element<
            mpl::transform_view< typename T::alternative_vector, alternative_octet_boundary< boost::mpl::placeholders::_1 > >
          >::type
        >::type
      >::type alt_octet_boundary;

      // Compute the octet boundary of the variant record.
      typedef typename mpl::max<
        typename protox::dtl::codec::octet_boundary< typename T::discriminant_type >::type,
        alt_octet_boundary
      >::type type;
    };

    template< typename T >
    struct static_size_in_bytes
    {
      typedef protox::dtl::UNKNOWN_STATIC_SIZE::type type;
    };

    template< typename T >
    inline static std::size_t dynamic_size( T const &obj )
    {
      return variant_record_codec_1516::impl<T>::type::dynamic_size( obj );
    };

    template< typename S, typename T >
    inline static void encode( S &s, T const &obj )
    {
      s.start_variant_record();
      variant_record_codec_1516::impl<T>::type::encode( s, obj );
      s.end_variant_record();
    }

    template< typename S, typename T >
    inline static void decode( T &obj, S const &s, std::size_t &offset )
    {
      s.start_variant_record();
      protox::dtl::codec::decode( obj.discriminant, s, offset );
      variant_record_codec_1516::impl<T>::type::decode( obj, s, offset );
      s.end_variant_record();
    }
  };

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
