/*
    Copyright 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

/** \page first_example First Example
 * In this example we use \c proto-x to code a simple federate that sends an interaction called
 * \c Greeting that consists of a single parameter called \c Message that is a fixed array of ASCII
 * characters. To do this, we need to define the following SOM components in C++ code using
 * \c proto-x:
 *
 * -
 * A <b><i>basic data representation table</i></b> to define a basic data type that can be the bases
 * for the definition of an ASCII character type.
 *
 * -
 * A <b><i>simple datatype table</i></b> to define an ASCII character type.
 *
 * -
 * An <b><i>array datatype table</i></b> to define the type used to hold a \c Message parameter
 * value.
 *
 * -
 * A <b><i>parameter table</i></b> to define the \c Message parameter.
 *
 * -
 * And finally, an <b><i>interaction class structure table</i></b> to define the \c Greeting
 * interaction class.
 *
 * <hr width=100>
 * We start with a \c proto-x definition of a <b><i>basic data representation table</i></b>
 * containing a single basic data type called \c HLAoctet. Note that \c include directives and other
 * non-essential code are not shown to keep the code samples small and easier to read.
 * \code
 * //   +--------------------------------+--------------+-------------+-------------+
 * //   | Name                           | Size in bits | Endian      | Encoding    |
 * //   +--------------------------------+--------------+-------------+-------------+
 * struct HLAoctet : basic< unsigned char, 8,             endian::big,  HLAPortable > {PROTOX_BASIC(HLAoctet)};
 * //   +--------------------------------+--------------+-------------+-------------+
 * \endcode
 *
 * The \c struct template <tt><b>basic</b></tt> associates various attributes with the basic
 * data type being defined. In this case, \c HLAoctet is represented by the \c C++ native
 * type <tt>unsigned char</tt>, has a size of 8 bits, uses big endian representation, and uses
 * the HLA portable encoding policy for serialization. The macro \c PROTO_BASIC tacked onto the
 * end generates required boilerplate code.
 *
 * The commenting style and use of white space emphasizes how you can structure your \c proto-x code
 * so that its format resembles the HLA Object Model Template (OMT) tabular format. Using a
 * commenting style like this one is a good way to document your SOM as you implement your
 * \c proto-x based API. The advantage is that your code and SOM are always in sync so you can be
 * confident that the SOM you publish as your public HLA contract is accurate.
 *
 * <hr width=100>
 * Next, we define a <b><i>simple datatype table</i></b> with a simple datatype definition used to
 * represent ASCII characters called \c HLASCIIchar.
 *
 * \code
 * //   +--------------+------------------+----------+
 * //   | Name         | Representation   | Units    |
 * //   +--------------+------------------+----------+
 * struct HLAASCIIchar : simple< HLAoctet,  unitless > {PROTOX_SIMPLE(HLAASCIIchar)};
 * //   +--------------+------------------+----------+
 * \endcode
 *
 * Note how we used the basic data type \c HLAoctet in the definition of \c HLAASCIIchar.
 * Here we use the \c struct template \c simple to define our simple datatype, and the
 * \c PROTOX_SIMPLE macro to generate require boilerplate code.
 *
 * <hr width=100>
 * Here is an <b><i>array datatype table</i></b> that defines an array type for holding \c Message
 * parameter values.
 *
 * \code
 * //   +----------+----------------------+---------------+-------------+
 * //   | Name     | Encoding             | Element type  | Cardinality |
 * //   +----------+----------------------+---------------+-------------+
 * struct FixedMsg : hla_1516::fixed_array< HLAASCIIchar,   5 > {};
 * //   +----------+----------------------+---------------+-------------+
 * \endcode
 *
 * <hr width=100>
 *
 * We now have all the components necessary to define our <b><i>parameter table</i></b>:
 *
 * \code
 * //   +-----------------------------------+-----------+-----------------+----------------------+
 * //   | Name                              | Parameter | Datatype        | String Name          |
 * //   +-----------------------------------+-----------+-----------------+----------------------+
 * struct Greeting {PROTOX_NAME("Greeting")};
 * //                                       +-----------+-----------------+----------------------+
 *                                   struct Message     : param< FixedMsg > {HLA_NAME("Message")};
 * //                                       +-----------+-----------------+----------------------+
 * \endcode
 *
 * We define a single parameter called \c Message of type \c FixedMsg. Note also how we use the
 * paramter table to define the interaction class names. In this case, we define a single
 * interaction class named \c Greeting.
 *
 * <hr width=100>
 *
 * Here is our <b><i>interaction class table</i></b>:
 *
 * \code
 * struct inter_class_table : i_class< HLAinteractionRoot, none, child<
 * // +-----------------+
 * // | Class 1         |
 * // +-----------------+
 *   i_class< Greeting,   params< Message > > > > {};
 * // +-----------------+
 * \endcode
 *
 * This is where we establish the <i>'is-a'</i> relationsips between interaction classes. This is
 * a very simple interaction class table with a single interaction class called \c Greeting
 * derived from the root interaction class called \c HLAinteractionRoot.
 *
 * Now lets use our SOM components to constrcut two federates, one that sends \c Greeting
 * interactions and one that receives them.
 *
 * To make life simpler, we are going to use a very lightweight implementation of the RTI
 * API specifically designed to implement example code that demonstrates \c proto-x concepts and
 * functionality. This implementation of the RTI provides just enough functionality to satisfy the
 * needs of a \proto-x derived API without the additional overhead of using a real RTI e.g.,
 * configuration files, running federates and RTI executives in seperate processes, etc...
 *
 * You can find this lightweight RTI implementation in the code base in a folder called \c rtilite.
 *
 * Before we can implement our federates, we need to define a few more types that will complete our
 * SOM specific HLA API. Here they are:
 *
 *
 *
 */
