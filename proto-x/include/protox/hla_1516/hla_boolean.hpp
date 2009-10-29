/*
    Copyright (c) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

#ifndef PROTOX_HLA_1516_BOOLEAN_HPP
#define PROTOX_HLA_1516_BOOLEAN_HPP

/**************************************************************************************************/

#include <protox/dtl/enumerated.hpp>
#include <protox/hla_1516/basic_data_representation_table.hpp>

/**************************************************************************************************/

namespace protox {
namespace hla_1516 {

/**************************************************************************************************/

typedef protox::hla_1516::enumerated<
  class HLAboolean,
  protox::hla_1516::HLAinteger32BE
> HLAboolean_enumerated;

/**************************************************************************************************/

class HLAboolean : public HLAboolean_enumerated
{
private:
  friend struct HLAtrue;
  friend struct HLAfalse;

  HLAboolean( protox::hla_1516::HLAinteger32BE v ) : HLAboolean_enumerated(v) {}

public:
  HLAboolean() : HLAboolean_enumerated(0) {}
  HLAboolean( HLAboolean const & v ) : HLAboolean_enumerated(v) {}

  static bool is_equal( protox::hla_1516::HLAinteger32BE lhs, protox::hla_1516::HLAinteger32BE rhs )
  {
    return( lhs == rhs );
  }
};

/**************************************************************************************************/

struct HLAtrue
{
  static HLAboolean const &value() { static HLAboolean const e( 1 ); return e; }
};

/**************************************************************************************************/

struct HLAfalse
{
  static HLAboolean const &value() { static HLAboolean const e( 0 ); return e; }
};

/**************************************************************************************************/

}}

/**************************************************************************************************/

#endif

/**************************************************************************************************/
