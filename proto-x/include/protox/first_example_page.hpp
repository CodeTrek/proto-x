/*
    Copyright 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

/** \page first_example First Example
 * In this example we use \c proto-x to code a simple federate that sends a \c Greeting interaction
 * that consists of a single parameter called \c Message that is a fixed array of ASCII characters.
 * To do this, we need to define the following SOM components (assume we are building a federate to
 * the HLA 1516 standard):
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
 *
 */
