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
 * data item (N bytes)  is not a multiple of 4, then the N Bytes are followed by 1, 2, or 3 zero
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
 * An SDX unsigned integer short is a 16 bit datum that encodes a non-negative integer in the range
 * [0, 65536], represented by a binary number whose most significant Byte is 0. An SDX Unsigned
 * Integer Short is represented in tabular format as follows:
 *
 * \code
 * +------------------+--------------+------------+-------------------------+
 * | Name             | Size in Bits | Byte Order | Encoding                |
 * +------------------+--------------+------------+-------------------------+
 * | SDXUnsignedShort | 16           | big-endian | 16 bit unsigned integer |
 * +------------------+--------------+------------+-------------------------+
 * \endcode
 *
 * and is encoded as follows:
 *
 * \code
 *   (MSB)    (LSB)
 * +--------+--------+
 * | Byte 0 | Byte 1 |
 * +--------+--------+
 * <---- 16 bits ---->
 * \endcode
 *
 * \subsubsection sdx_record Record
 *
 * An SDX Record is a vector of components called Fields. A Field has a name and a data type. Fields
 * are encoded in the order they are listed in a Record definition. Each Field's size in Bytes is a
 * multiple of 4.
 *
 * An SDX Record is represented in tabular format as follows:
 *
 * \code
 * +----------+-------------------------------+
 * | Name     | Field                         |
 * |          +-------------------------------+
 * |          | Name       | Type             |
 * +----------+------------+------------------+
 * | MyRecord | CountShort | SDXUnsignedShort |
 * |          +------------+------------------+
 * |          | CountLong  | SDXUnsignedLong  |
 * +----------+------------+------------------+
 * \endcode
 *
 * And here is how the above Record is encoded:
 *
 * \code
 * +-------------------------------------------------------------+
 * | MyRecord                                                    |
 * +-------------------------+-----------------------------------+
 * | CountShort Field        | CoungLong Field                   |
 * +--------+--------+---+---+--------+--------+--------+--------+
 * | Byte 0 | Byte 1 | 0 | 0 | Byte 0 | Byte 1 | Byte 2 | Byte 3 |
 * +--------+--------+---+---+--------+--------+--------+--------+
 * \endcode
 *
 * Notice how two pading Bytes are added to make the length of the CountShort Field a multiple of
 * four.
 *
 * \section step_2_specify_codec_tags Step 2 - Specify the codec tags
 *
 * Codec tags are C++ types used as tags to perform the compile-time dispatch that directs the
 * compiler to select the correct codec implementation when encoding/decoding a value of a
 * particular type. You must specify a tag for each type of encoding. For the SDX protocol the types
 * of encoding are:
 *
 * - portable byte
 * - unsigned integer long
 * - unsigned integer short
 * - record
 *
 * Create these tag specification in the <tt>protox::sdx</tt> namespace, like this:
 *
 * \code
 * namespace protox {
 * namespace sdx {
 *
 * // A portable Byte.
 * struct sdx_portable {};
 *
 * // 32 bit unsigned integer
 * struct sdx_unsigned_long {};
 *
 * // 16 bit unsigned integer
 * struct sdx_unsigned_short {};
 *
 * // A vector of types
 * struct sdx_record {};
 *
 * }} // protox::sdx
 *
 * \endcode
 *
 * It's important to remember that these tags represent encoding types and not data types. As you
 * will see in a moment, Poroto-x data type definitions reference these tags in their definition.
 * That’s how data type definitions and encoding type implementations are associated at compile
 * time, allowing the compiler to generate the correct encode/decode code based on a value's
 * encoding type and not its data type.
 *
 * \section step_3_define_sdx_basic_data_types Step 3 - Define SDX Basic Data Types
 *
 * Most data coding standards start with a definition of basic or fundamental types and then build
 * more complex types from there. SDX is no exception. SDX defines a set of basic integer types that
 * can be used to define more complex Record data types. proto-x provides the
 * <tt>protox::dtl::basic</tt> template for defining basic types that can be used in the definition
 * of structured types, like Record. The following code snippet uses the <tt>protox::dtl::basic</tt>
 * template * to define the SDX basic data types. This code sample assumes that the codec tags
 * defined above are included in the compilation unit where these definitions appear. Also note how
 * the commenting style here is used to represent the basic type definition in a tabular format to
 * improve readability.
 *
 *
 */
