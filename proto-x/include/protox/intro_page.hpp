/*
    Copyright 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

/** \page intro Introduction
 *
 * \c proto-x is a cross-platform, open source C++ library for developing high level architecture
 * (HLA) compliant simulations, tools, and utilities. \c proto-x lets you represent simulation
 * object model (SOM) component definitions directly in C++ code. You can then use these definitions
 * to derive an application programming interface (API) to the HLA simulation services provided by
 * an implementation of the HLA run-time infrastructure (RTI).
 *
 * \c proto-x is not a framework. It is an alternative API to the standard RTI API that offers the
 * following advantages:
 *
 * -
 * <b>Code at the same level of abstraction as your SOM</b>. You do not have to deal with
 * attribute and parameter values as opaque byte arrays. With a \c proto-x derived API, attribute
 * and parameter value representations are accessed via an interface that matches your SOM
 * specification. The interface uses the same names, data type definitions, and class structures
 * defined in your SOM.
 *
 * -
 * <b>Correct encoding/decoding of all your SOM data types</b>. \c proto-x enforces correct default
 * encoding and decoding rules, with support for both HLA 13 and 1516 "out of the box". You can
 * also define custom encoding/decoding rules when your SOM deviates from the standard.
 *
 * -
 * <b>SOM and source code are never out of sync</b>. \c proto-x lets you represent your SOM in
 * directly in C++ source code, so there is no way for your code and SOM to be in conflict.
 *
 * -
 * <b>No special code generator required/easy build process</b>. \c proto-x leverages the C++
 * template compiler to perform the translation from your SOM component definitions to equivalent
 * C++ types, thus eliminating the  need for a separate code generation step in your build process.
 *
 * -
 * <b>Code that is easier to maintain and modify</b>. A \c proto-x based API hides many of the messy
 * coding details associated with programming to the RTI API that can make your code difficult to
 * read and understand (and therefore difficult to maintain and modify). Error prone coding tasks
 * such as handle management and data serialization are completely eliminated.
 *
 * Look \ref first_example "here" for an example that will give you a better feel for what
 * \c proto-x is and how it works.
 *
 */
