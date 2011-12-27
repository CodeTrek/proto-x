/*
    Copyright 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

/**
 * \page implementing_a_custom_codec Implementing a Custom codec
 *
 * \section Introduction
 *
 * This tutorial takes you through the steps required to develop a custom proto-x codec. We start by
 * defining a new codec for a fictitious binary encoding standard called Simple Data eXchange (SDX).
 * The SDX encoding standard is (very) loosely based on the Extenernal Data Representation Standard
 * (XDR), but simplified so that this tutorial can focus on presenting proto-x concepts without the
 * distracting details of a full-blown binary standard.
 *
 * Here is a quick overview of the steps we'll take to implement a proto-x based SDX codec:
 *
 * -# Define the SDX standard
 * -# Specify SDX codec tags
 * -# Define SDX basic data types
 * -# Implement the codec for each basic type codec tag
 * -# Define SDX structured types e.g., Record
 * -# Implement the codec for each new SDX structured type
 * -# Implement unit tests
 *
 * \section step_1_define_sdx_standard Step 1 - Define the SDX Standard
 *
 * SDX is our extremely simple and fictitious "standard" data format description language. It's used
 * to describe binary data formats that are useful for exchanging data between computer
 * architectures.
 *
 * \subsection sdx_portable_byte_assumption SDX Portable Byte Assumption
 *
 * SDX defines a Byte as 8 bits of data. SDX assumes that Bytes are portable across all computer
 * architectures. In other words, SDX describes the encoding of data at the Byte level and not the
 * Bit level of detail.
 *
 * \subsection sdx_padding_rule SDX Padding Rule
 *
 * SDX requires that the size of all data item representations be a multiple of four bytes. Bytes
 * are numbered 0 through N-1. Bytes read or written to a stream are ordered in such a way that Byte
 * M always precedes byte M+1. If the number of bytes required to hold the data contained in an SDX
 * data item (N bytes)  is not a multiple of 4, then the n Bytes are followed by 1, 2, or 3 zero
 * padding Bytes to make the byte count a multiple of 4.
 *
 * For example:
 *
 * \code
 * +-----------------+---------------+
 * | Data Bytes      | Padding Bytes |
 * |--------+--------+-------+-------|
 * | Byte 0 | Byte 1 |   0   |  0    |
 * +--------+--------+-------+-------+
 * \endcode
 *
 *
 * \subsection sdx_basic_data_types SDX Basic Data Types
 *
 * The following sections describe the data types you can define using SDX. SDX defines 2 basic
 * types - Unsigned Integer Long and Unsigned Integer Short. SDX also defines one structured type
 * called Record.
 *
 * \subsubsection sdx_unsigned_int_long Unsigned Integer Long
 *
 * An SDX unsigned integer long is a 32 bit datum that encodes a non-negative integer in the range
 * [0, 4294967296], represented by a binary number whose most significant Byte is 0. An SDX Unsigned
 * Integer Long is represented in tabular format as follows:
 *
 * \code
 * +-----------------+--------------+------------+-------------------------+
 * | Name            | Size in Bits | Byte Order | Encoding                |
 * +-----------------+--------------+------------+-------------------------+
 * | SDXUnsignedLong | 32           | big-endian | 32 bit unsigned integer |
 * +-----------------+--------------+------------+-------------------------+
 * \endcode
 *
 * and is encoded as follows:
 *
 * \code
 *   (MSB)                      (LSB)
 * +--------+--------+--------+--------+
 * | Byte 0 | Byte 1 | Byte 2 | Byte 3 |
 * +--------+--------+--------+--------+
 * <------------ 32 bits -------------->
 * \endcode
 *
 * \subsubsection sdx_unsigned_int_short Unsigned Integer Short
 *
 */
