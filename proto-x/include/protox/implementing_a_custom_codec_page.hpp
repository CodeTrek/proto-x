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
 * This tutorial takes you through the steps required to develop a custom <tt>proto-x</tt> codec. We start by
 * defining a new codec for a fictitious binary encoding standard called Simple Data eXchange (SDX).
 * The SDX encoding standard is (very) loosely based on the Extenernal Data Representation Standard
 * (XDR), but simplified so that this tutorial can focus on presenting <tt>proto-x</tt> concepts without the
 * distracting details of a full-blown binary standard.
 *
 * Here is a quick overview of the steps we'll take to implement a <tt>proto-x</tt> based SDX codec:
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
 * That's how data type definitions and encoding type implementations are associated at compile
 * time, allowing the compiler to generate the correct encode/decode code based on a value's
 * encoding type and not its data type.
 *
 * \section step_3_define_sdx_basic_data_types Step 3 - Define SDX Basic Data Types
 *
 * Most data coding standards start with a definition of basic or fundamental types and then build
 * more complex types from there. SDX is no exception. SDX defines a set of basic integer types that
 * can be used to define more complex Record data types. <tt>proto-x</tt> provides the
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
 * The macro <tt>PROTOX_BASIC</tt> generates bolerplate code required by each <tt>proto-x</tt> basic data
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
 * Let's start by creating an empty <tt>codec_impl</tt> template specialization for each basic data
 * type SDX protocol tag:
 *
 * \include protox/sdx/basic_data_codec_empty.hpp
 *
 * The first thing to note is that <b>all</b> <tt>codec_impl</tt> specializations must belong to the
 * <tt>protox::dtl</tt> namespace.
 *
 * Looking at the the definition of <tt>protox::dtl::codec_interface</tt>, we see each template
 * specializaton must provide two <tt>struct</tt> templates:
 *
 * - <tt>template< typename T > struct octet_bounddary {};</tt>
 * - <tt>template< typename T > struct static_size_in_bytes {};</tt>
 *
 * and three <tt>static</tt> function templates:
 *
 * - <tt>template< typename T > static std::size_t dynamic_size( T );</tt>
 * - <tt>template< typename S, typename T > static void encode( S &, const T &obj );</tt>
 * - <tt>template< typename S, typename T > static void decode( T &obj, const S &, std::size_t &offset );</tt>
 *
 * Let's add these <tt>struct</tt> and function specifications to our SDX specializations, like
 * this:
 *
 * \include protox/sdx/basic_data_codec_stubs.hpp
 *
 * We are now ready to provide SDX protocol specific implementations of these compile-time and
 * run-time functions.
 *
 * Let's start with <tt>sdx::sdx_portable</tt>.
 *
 * \include protox/sdx/basic_data_codec_portable.hpp
 *
 * As you can see, it's very straightforward. The compile-time constants <tt>octet_boundary</tt> and
 * <tt> static_size_in_bytes</tt> can be hardcoded to return a value of 1. And because we are
 * dealing with a type with a fixed size, <tt>dynamic_size</tt> simply returns the constant static
 * size.
 *
 * The <tt>encode</tt> and <tt>decode</tt> functions are simple too. They write and read a single
 * 8 bit value from the given stream of type <tt>S</tt>, respectively.
 *
 * Next we create a <tt>codec_impl</tt> template specialization for <tt>sdx::sdx_unsigned_short</tt>,
 * starting with the implementation <tt>octet_boundary</tt>. Here's the code:
 *
 * \include protox/sdx/basic_data_codec_unsigned_short_octet.hpp
 *
 * Here we've cheated a little by forwarding the work to be done to a function supplied by
 * <tt>proto-x</tt>, called <tt>compute_octet_boundary</tt>. If you look at the implementation of
 * <tt>compute_octet_boundary</tt>, you'll see that it computes the smallest value <tt>2^N</tt>,
 * where <tt>N</tt> is a non-negative integer for which <tt>(8 * 2^N) >=</tt>  the size of the data
 * type <tt>T</tt> in bits.
 *
 * Next, here is the code for <tt>static_size_in_bytes</tt> and <tt>dynamic_size</tt>:
 *
 * \include protox/sdx/basic_data_codec_unsigned_short_size.hpp
 *
 * <tt>static_size_in_bytes</tt> is a simple compile time computation that computes the size of
 * <tt>T</tt> in bytes from its size in bits and pads the value with 1 if <tt>T</tt>'s size in bits
 * is not a multiple of 8. And again, since we are dealing with a basic type with a fixed size,
 * <tt>dynamic_size</tt> simply returns the value computed by <tt>static_size_in_bytes</tt>.
 *
 * Finally, we are ready to implement the <tt>encode</tt> and <tt>decode</tt> functions. For this
 * example we'll just implement the <tt>encode</tt> function, since the <tt>decode</tt> function is
 * just its inverse.
 *
 * The only issue we really need to consider here is byte ordering - does the endianess of an
 * <tt>sdx_unsigned_short</tt> value match the platform's endianess? If the answer is "yes", we
 * stream the 2 bytes that makeup an <tt>sdx_unsigned_short</tt> value from low to high memory,
 * otherwise we reverse the order.
 *
 * Here is some pseudo code to illustrate this point:
 *
 * \code
 *
 * // if T's endianess is the same as the platform's (where T is SDXUnsignedShort) then...
 * static void encode( S &s, const T &value)
 * {
 *   const byte *bytes = &value;
 *   s.push_back( bytes[0] ); // low memory
 *   s.push_back( bytes[1] ); // high memory
 * }
 *
 * // else if T's endianess is the _not_ the same as the platform's...
 * static void encode( S &s, const T &value)
 * {
 *   const byte *bytes = &value;
 *   s.push_back( bytes[1] ); // high memory
 *   s.push_back( bytes[0] ); // low memory
 * }
 *
 * \endcode
 *
 * We want to generate the correct <tt>encode</tt>function at compile time. Do this this we declare
 * a <tt>struct template</tt> with a <tt>bool</tt> argument like this:
 *
 * \code
 * template<
 *   typename S,         // The destination byte buffer
 *   bool CONVERT_ENDIAN // true, if endian conversion is required
 * > struct encode_basic;
 * \endcode
 *
 * Now we create a specialization for the <tt>true</tt> case i.e., when we need to perform endian
 * conversion, and for the <tt>false</tt> case i.e., when no byte reordering is requried. Here are
 * the specializations:
 *
 * \code
 *
 * template<
 *   typename S,         // The destination byte buffer
 *   bool CONVERT_ENDIAN // true, if endian conversion is required
 * > struct encode_basic;
 *
 * // Byte reordering is required specialization...
 * template< typename S >
 * struct encode_basic< S, true >
 * {
 *   static inline void pack( S &s, SDXByte::value_type const *value )
 *   {
 *     s.push_back( value[1] );
 *     s.push_back( value[0] );
 *   }
 * };
 *
 * // Byte reordering is _not_ required specialization...
 * template< typename S >
 * struct encode_basic< S, false >
 * {
 *   static inline void pack( S &s, SDXByte::value_type const *value )
 *   {
 *     s.push_back( value[0] );
 *     s.push_back( value[1] );
 *   }
 * };
 *
 * \endcode
 *
 * Here is how we use the <tt>encode_basic</tt> template to implement the <tt>encode</tt> function
 * for <tt>sdx_unsigned_short</tt>:
 *
 * \include protox/sdx/basic_data_codec_unsigned_short_encode.hpp
 *
 * The <tt>encode_basic</tt> template can be generalized to support encoding and decoding of all of
 * the <tt>sdx</tt> basic types.
 *
 * See \link protox/sdx/basic_data_encoders.hpp\endlink for a complete implementation of the encoder
 * functions.
 *
 * See \link protox/sdx/basic_data_decoders.hpp\endlink for a complete implementation of the decoder
 * functions.
 *
 * See \link protox/sdx/basic_data_codec.hpp\endlink for a complete implementation basic data
 * codec for this example.
 *
 * \section step_4_define_sdx_structured_types Step 5 - Define SDX Structured Types
 *
 * Now that we have codec functions implemented for the basic types, we are ready to build more
 * structured types out of the basic types. In this section we implement the codec functions for a
 * record type. A record type is a vector of fields, where each field has a name that is unique to
 * the record and type. An example of a record type in C++ is a <tt>struct</tt> type.
 *
 * In this section we'll work backwards, in a sense, from 'form' to 'function'. We'll do this by
 * presenting the syntax of a <tt>proto-x</tt> based record type, and then show how that syntax
 * supports the auto-generation of correct codec functions at compile time.
 *
 * We start with the syntax for the definition of a plain old C++ <tt>struct</tt> type, and then
 * look at how we have to augment it to support compiler generated codec functions for types like
 * those represetned by C++ <tt>struct</tt>s.
 *
 * So to start, here is an example of a plain old <tt>struct</tt> type in C++:
 *
 * \code
 * struct Foo
 * {
 *   SDXUnsignedShort f1:
 *   SDXUnsignedLong f2;
 * }
 * \endcode
 *
 * The fundamental idea behind <tt>proto-x</tt> is to use the C++ compiler to generate correct encode/decode
 * functions conforming to some standard. In order for this to work for structured types like
 * records, the C++ compiler needs to have enough information to interrogate the structured type at
 * compile time.
 *
 * \code
 * //      +--------+------------------------------------+-------------+
 * //      | Record | Field                              | Encoding    |
 * //      | Name   +------+-----------------------------+             |
 * //      |        | Name | Type                        |             |
 * //      +--------+------+-----------------------------+-------------+
 * namespace Foo    {
 * //      +---------------+-----------------------------+
 *             struct f1   : field< SDXUnsignedShort > {};
 *             struct f2   : field< SDXUnsignedLong  > {};
 * //      +---------------+-----------------------------+-------------+
 *                                           struct type : sdx::record < boost::mpl::vector< f1, f2 > > {}; }
 * \endcode
 *
 * The first thing to note is that this is not the only way to organize the code used to define a
 * <tt>proto-x</tt> based record structure. This particular code organization is used because it
 * supports a tabular commenting style that highlights the components of the definition nicely. The
 * need for such a disciplined coding and commenting style is because <tt>proto-x</tt> definitions
 * are (unfortunately) considerably more verbose then their 'plain-old' counterparts. The additional
 * syntax is necessary to give the compiler enough information to generate correct codec functions.
 *
 * Let's breakdown this definition component by component.
 *
 * First, we use a <tt>namespace</tt> to name our structure <tt>Foo</tt> and we bury the record's
 * actual type definition inside. So declaring a record of type <tt>Foo</tt> looks like this:
 *
 * <tt>Foo::type myFooRecord;</tt>
 *
 * We also place the field type definitions inside the <tt>Foo namespace</tt>. This helps with name
 * deconfliction between records with matching field names. Fields are defined as <tt>struct</tt>s
 * that extend the <tt>protox::dtl::field</tt> template, which wraps the field's type. The name of
 * the <tt>struct</tt> is the name of the field. The <tt>protox:dtl:field</tt> template is part of
 * <tt>proto-x</tt>'s data type language (dtl), which provides basic data type definition
 * mechanisms (like the field template) for the most common <tt>proto-x</tt> use cases.
 *
 * Finally, we define the actual record type as a <tt>struct</tt> (named <tt>type</tt>) as an
 * extension of an <tt>sdx</tt> defined record template. The record template takes a
 * <tt>boost::mpl::vector</tt> of our field definitions.
 *
 * Now let's look at how we define the <tt>sdx</tt> record template. The definition is actually
 * quite simple. Here it is:
 *
 * \code
 * template< typename FIELD_VECTOR >
 * struct record : protox::dtl::fixed_record< FIELD_VECTOR, sdx_record > {};
 * \endcode
 *
 * We forward our definition to a <tt>protox::dtl::fixed_record</tt> template. We pass the field
 * vector and the codec tag for sdx records - <tt>sdx_record</tt>. Here again we rely on the
 * <tt>dtl</tt> substrate of <tt>proto-x</tt> to provide us with common functionality. Look at
 * the documentation for <tt>protox::dtl::fixed_record</tt> for details on its implementation.
 *
 * One of the most important bits of functionality we get with <tt>dtl::fixed_record</tt> is a field
 * access operator. As you might expect, accessing a field to set/get its value is not as simple as
 * using the normal access operators like <tt>.</tt> and <tt>-></tt>. <tt>protox::dtl::fixed_record</tt>
 * provides us with a function template access operator that follows this pattern:
 *
 * <tt>instance_name.f_< field_name >()</tt>
 *
 * Here is an example using our Foo record:
 *
 * \code
 * Foo::type myFoo;
 * myFoo.f_< f1 >() = 5;
 * myFoo.f_< f2 >() = 6;
 * \endcode
 *
 * Now let's implement the codec functions for <tt>protox::sdx::record</tt>. Recall that we must
 * provide a specialization of the <tt>protox::dtl::codec_impl</tt> template for our record type.
 * Here is our specialization minus implementation details:
 *
 * \code
 *
 * namespace protox {
 * namespace dtl {
 *
 * template<> struct codec_impl< protox::sdx::sdx_record >
 * {
 *   template< typename T > struct octet_boundary {...};
 *   template< typename T > struct static_size_in_bytes {...};
 *
 *   template< typename T > inline static std::size_t dynamic_size( T const &obj ) {...}
 *
 *   template< typename S, typename T > inline static void encode( S &s, T const &obj ) {...}
 *
 *   template< typename S, typename T > inline static void decode( T &v,
 *                                                                 S const &s,
 *                                                                 std::size_t &offset )
 *   {...}
 * };
 *
 * }} // protox::dtl
 *
 * \endcode
 *
 * For example, a field in <tt>proto-x</tt> is a
 * <tt>struct</tt> template, like this:
 *
 * \code
 * template< typename T > struct field {...};
 * \endcode
 *
 * Here is how you define the field <tt>f1</tt> from the <tt>Foo struct</tt> above using
 * <tt>proto-x field</tt> template:
 *
 * \code
 * struct f1 : protox::dtl::field< SDXUnsignedShort > {};
 * \endcode
 *
 *
 */
