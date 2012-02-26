/*
    Copyright (C) 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**********************************************************************************************************************/

#ifndef PROTOX_HLA_INTERACTION_AMB_HPP
#define PROTOX_HLA_INTERACTION_AMB_HPP

/**********************************************************************************************************************/

#include <cstddef>

#include <boost/mpl/inherit_linearly.hpp>
#include <boost/mpl/placeholders.hpp>

#include <RTI.hh>

#include <protox/hla/recv_interaction.hpp>

/**********************************************************************************************************************/

namespace protox {
namespace hla {

/**********************************************************************************************************************/

/**
 * Generates an interaction ambassador that can be used to forward a received interaction to an interaction type safe
 * handler function.
 *
 * \tparam CLASS_TYPE_VECTOR A vector of interaction class types to be handled.
 *
 * \sa protox::hla::i_class_type
 * \sa protox::hla::recv_interaction_inherit
 *
 * Example:
 *
 * \code
 * // An interaction class types...
 * typedef i_class_type< hw_som, q_name< Greeting > >::type greeting_type;
 *
 * // An interaction ambassador used to register a callback function that is invoked whenever
 * // interaction of type greeting_type is received.
 *
 * typedef hla::interaction_amb< mpl::vector< greeting_type > >::type inter_amb_type;
 *
 * // Greeting interaction type handler. The handler can treat the receieved interaction in a type safe way.
 * static void greeting_handler(const greeting_type &greeting, const RTI::FedTime *, const char *) {
 *     std::string str(greeting.p_< message >().begin(), greeting.p_< message >().end());
 *     std::cout << "greeting : " << str.c_str() << " ";
 * }
 *
 * // An HLA federate ambassador used to forward interactions to a proto-x interaction ambassador.
 * class fed_amb : public RTI::FederateAmbassador
 * {
 * private:
 *   inter_amb_type &inter_amb;
 *
 * public:
 *   virtual void receiveInteraction( RTI::InteractionClassHandle             theInteraction,
 *                                    const RTI::ParameterHandleValuePairSet &theParameters,
 *                                    const RTI::FedTime                     &theTime,
 *                                    const char                             *theTag,
 *                                    RTI::EventRetractionHandle              theHandle )
 *   {
 *     inter_amb.recv_interaction( theInteraction, theParameters, &theTime, theTag );
 *   }
 * };
 *
 * // Create an interaction ambassador and register our interaction callbacks.
 * inter_amb_type inter_amb;
 * inter_amb.set_handler( greeting_handler );
 *
 * \endcode
 */

/**********************************************************************************************************************/

template< typename CLASS_TYPE_VECTOR >
struct interaction_amb {

    typedef typename boost::mpl::inherit_linearly<
        CLASS_TYPE_VECTOR,
        recv_interaction_inherit< recv_interaction_base< boost::mpl::placeholders::_2 >, boost::mpl::placeholders::_1 >
    >::type recv_interactions_type;

    struct type : recv_interactions_type {};
};
  
/**********************************************************************************************************************/

}}

/**********************************************************************************************************************/

#endif

/**********************************************************************************************************************/
