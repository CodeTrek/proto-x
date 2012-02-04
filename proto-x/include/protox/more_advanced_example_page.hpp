/*
    Copyright 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

/**
 * \page more_advanced_example A More Advanced Example
 *
 * This example is a little more involved than the \ref first_example "first example". This example
 * creates two federates called <tt>platform_pub</tt> and <tt>platform_sub</tt>.
 * <tt>platform_sub</tt> sends an interaction requesting that <tt>platform_pub</tt> create some
 * number of objects of type <tt>Platform</tt>. These objects have two attributes <tt>Position</tt>
 * and <tt>Color</tt>. <tt>platform_pub</tt> initializes each <tt>Platform</tt> object's  color to
 * <tt>Green</tt>, and then proceeds to update each object's <tt>Position</tt> attribute for some
 * number of ticks. After which, each objects's <tt>Color</tt> is set to <tt>Red</tt>,
 * indicating that the object has stopped. <tt>platform_sub</tt> subscribes the <tt>Platform</tt>
 * class attributes and prints updates to thier values to standard out.
 *
 * Like the \ref first_example "first example", this example uses a bare-bones version of the RTI
 * (found in the directory called <tt>/rtilite</tt>) to keep the implementation as simple as
 * possible.
 *
 * Here is the complete code to this example:
 *
 * \include platform/main.cpp
 */
