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
 * \include protox/sdx/codec_tags.hpp
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
 * \include protox/sdx/basic_data_representation_table.hpp
 *
 * The <tt>dtl::basic</tt> template associates four attributes with the defined data type:
 * -# The C++ built-in type used to represent the basic type
 * -# The size of the basic type in bits
 * -# The types byte ordering (<tt>dtl::endian:big</tt>, <tt>dtl::endian::little</tt>, or <tt>dtl::endian::na</tt>)
 * -# The codec type to use when encoding/decoding values of the type being defined
 *
 * The macro <tt>PROTOX_BASIC</tt> generates bolerplate code required by each proto-x basic data
 * type definition.
 *
 * \section step_4_implement_basic_type_codecs Step 4 - Implement Basic Type codecs
 *
 * In this step, we implement the algorithms that perform the encoding/decoding rules represented by
 * the codec tags given in step 2. We start with the encoding rules for the basic types.
 *
 * Implementing a codec starts with understanding the role of the <tt>protox::dtl::codec</tt>
 * interface. This interface is a compile time interface that uses its type argument <tt>T</tt> to
 * direct the compiler to generate the correct codec code for values of type <tt>T</tt>.
 *
 * Here is the codec interface.
 *
 * \include protox/dtl/codec_interface.hpp
 *
 * The most important details to focus on are
 * -# the template signatures
 * -# the fact that the primary purpose of this interface is to forward requests to another template called <tt>code_impl</tt>
 *
 * Notice how the implementation of this interface forwards compile time calls to another compile
 * time entity called <tt>codec_impl</tt>. The <tt>codec_impl</tt> template is where the real type
 * specific work is done. The purpose of <tt>protox::dtl::codec</tt> is simply to give
 * <tt>code_impl</tt> a uniform interface that can be used for any type <tt>T</tt> for which there
 * is a corresponding <tt>codec_impl</tt>.
 *
 * So our next step is to creae <tt>codec_impl</tt> implementations for our basic SDX types. We
 * create custom codec implementations by creating <tt>protox::dtl::codec_impl</tt> template
 * specializations that conform to the <tt>protox::dtl::codec</tt> interface. Here is the
 * <tt>codec_impl</tt> template. It's very simple:
 *
 * \include protox/dtl/codec_impl.hpp
 *
 * As you can see, it's only purpose in life is to be specialized.
 *
 */
