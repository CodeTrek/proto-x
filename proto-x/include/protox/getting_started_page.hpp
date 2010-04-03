/*
    Copyright 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

/**
 * \page getting_started Getting Started
 *
 * \section steps Steps
 *
 * -# <b>Get Proto-x </b>
 * -# <b>Get boost libraries</b>
 * -# <b>Build and run the first example</b>
 * -# <b>Install an HLA 1.3 compliant RTI</b>
 *
 * \section get_proto_x Get Proto-x
 *
 * Proto-x is a headers-only library. There are no separate libraries to build. To install Proto-x
 * simply unpack the distribution. Here is the Proto-x directory structure after unpacking:
 *
 * \code
 * protox
 *   examples/          // Examples requiring an HLA 1.3 RTI (1516 support soon).
 *   include/           // The Proto-x headers-only library.
 *   rtilite/           // A simple RTI designed to make implementing example code easier.
 *   rtilite_examples/  // Examples built using the rtilite RTI.
 *   test/              // Proto-x unit tests (requires Boost test header only version).
 *   LICENSE_1_0.txt    // Proto-x is released under MIT software license.
 * \endcode
 *
 * \section get_boost Get boost libraries
 *
 * Proto-x depends on the following <a href="http://www.boost.org">boost</a> libraries
 * (boost version 1.42.0 or later):
 *
 * - Foreach
 * - MPL
 * - Smart Ptr
 * - Static Assert
 * - Test (unit tests only)
 * - Type Traits
 * - Variant
 *
 * Proto-x uses the header-only version of these libraries. Therefore, all you have to do is unpack
 * the boost distribution and you are ready to start building with Proto-x.
 *
 * \section build_first_example Build and run the first example
 *
 * Build and run the example found \ref first_example "here".
 *
 * See <a href = "http://www.boost.org/doc/tools/build/index.html">here</a> if you want to use the
 * boost build system to build the Proto-x examples and unit tests. Here is another good source
 * of information on the boost build system:
 * <a href="http://www.highscore.de/cpp/boostbuild/index.html">boost build help</a>.
 *
 * \section install_rti Install an HLA 1.3 compliant RTI
 *
 * Install an HLA 1.3 RTI when you are ready to start building applications using a real RTI.
 * See <a href="http://en.wikipedia.org/wiki/Run-Time_Infrastructure_(simulation)">here</a> for a
 * list of RTI implementations.
 *
 * <a href="http://porticoproject.org/index.php?title=Main_Page">Portico</a> is a good open source
 * solution.
 */
