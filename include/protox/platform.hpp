/*
 * Copyright 2009 - 2019 Jay Graham
 *
 * Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
 * or http://www.opensource.org/licenses/mit-license.php)
 *
 */

/**********************************************************************************************************************/

/**
 * \file platform.hpp
 * Platform specific configuration settings and library option flags are defined here.
 */

#ifndef PROTOX_PLATFORM_HPP
#define PROTOX_PLATFORM_HPP

/**********************************************************************************************************************/

#include <boost/static_assert.hpp>

/**********************************************************************************************************************/

/// \cond

#if defined(_PROTOX_DTL_DEBUG)
#define PROTOX_DTL_DEBUG(x) (x)
#else
#define PROTOX_DTL_DEBUG(x)
#endif

/// \endcond

/**
 * The value of a pad byte.
 */
#define PROTOX_DTL_PAD_CHARACTER 0x00

/**
 * Power of 2 maximum size of a basic data type in bits i.e., 2 raised to this power determines
 * maximum bit size. For example, 2^7 = 128 bits.
 */
#define PROTOX_DTL_POW_2_MAX_BIT_SIZE 7  // 2^7 or 128 bits.

/**
 * Indicates unknown platform endianess.
 */
#define PROTOX_DTL_NA_ENDIAN     0

/**
 * Set PROTOX_DTL_PLATFORM_ENDIANESS to this value to specify a little endian architecture.
 */
#define PROTOX_DTL_LITTLE_ENDIAN 1

/**
 * Set PROTOX_DTL_PLATFORM_ENDIANESS to this value to specify a big endian architecture.
 */
#define PROTOX_DTL_BIG_ENDIAN    2

// Default to little endian
#ifndef PROTOX_DTL_PLATFORM_ENDIANESS
/**
 * Use this macro to configure protox::dtl for a big or little endian architecture.
 * Default is: PROTOX_DTL_LITTLE_ENDIAN
 */
#define PROTOX_DTL_PLATFORM_ENDIANESS PROTOX_DTL_LITTLE_ENDIAN
#endif

/// \cond
BOOST_STATIC_ASSERT((
  ( PROTOX_DTL_PLATFORM_ENDIANESS == PROTOX_DTL_LITTLE_ENDIAN ) ||
  ( PROTOX_DTL_PLATFORM_ENDIANESS == PROTOX_DTL_BIG_ENDIAN )
)); // Undefined endianess!

#ifdef WIN32
#define SYS_NTOHL ::ntohl
#else
#include <netinet/in.h>
#define SYS_NTOHL ntohl
#endif

/// \endcond

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
