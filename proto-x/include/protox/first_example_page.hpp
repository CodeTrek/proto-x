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
 *                                     struct Message   : param< FixedMsg > {HLA_NAME("Message")};
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
 * needs of a \c proto-x derived API without the additional overhead of using a real RTI e.g.,
 * configuration files, running federates and RTI executives in seperate processes, etc...
 *
 * You can find this lightweight RTI implementation in the code base in a folder called \c rtilite.
 *
 * Before we can implement our federates, we need to define a few more types that will complete our
 * SOM specific HLA API.
 *
 * First we need a type that represents our simulation object model (SOM). We define it like this:
 *
 * \code
 * // Hello world SOM type
 * typedef protox::hla::som< null_o_class, inter_class_table > hw_som;
 * \endcode
 *
 * A SOM is defined by an object class table type and an interaction class table type. In this
 * example we don't have an object class table, so the first template argument is
 * <tt>null_o_class</tt>. The second template argument is our interaction class table type
 * <tt>inter_class_table</tt>.
 *
 * We use our SOM type <tt>hw_som</tt> to define a \c Greeting interaction type like this:
 *
 * \code
 * typedef i_class_type< hw_som, q_name< Greeting > >::type greeting_type;
 * \endcode
 *
 * <tt>hw_som</tt> is our SOM. The template argument <tt>q_name< Greeting ></tt> is the fully
 * qualified name of our interaction. The type <tt>greeting_type</tt> can now be used to
 * declare instances of a \c Greeting interaction.
 *
 * Next, we need an interaction ambassador that is capable of receiving \c greeting_type
 * interactions. Here it is:
 *
 * \code
 * // An interaction ambassador used to register callbacks that are invoked by interaction class
 * // type.
 * typedef hla::interaction_amb< mpl::vector< greeting_type > >::type inter_amb_type;
 * \endcode
 *
 *
 * We now have all of the \c proto-x types we need to complete our sample federates.
 *
 * Our receiving federate will need an HLA federate ambassador that forwards interactions to our
 * \c proto-x ambassador. Here is an HLA federate ambassador that gets a reference to our
 * interaction ambassador. Note how all received interactions our forwarded to the interaction
 * ambassador.
 *
 * \code
 * class fed_amb : public RTI::FederateAmbassador
 * {
 * private:
 *   inter_amb_type &inter_amb;
 *
 * public:
 *   fed_amb( inter_amb_type &inter_amb ) : inter_amb(inter_amb) {}
 *
 *   virtual void receiveInteraction( RTI::InteractionClassHandle             theInteraction,
 *                                    const RTI::ParameterHandleValuePairSet &theParameters,
 *                                    const char                             *theTag )
 *   {
 *     inter_amb.recv_interaction( theInteraction, theParameters, 0, theTag );
 *   }
 * };
 * \endcode
 *
 * Our interaction ambassador lets us register a callback function that gets invoked when we
 * receive a \c Greeting interaction. Here is our handler. It simply writes the value of the
 * \c message parameter to standard out.
 *
 * \code
 * static void greeting_handler( const greeting_type &greeting, const RTI::FedTime *, const char * )
 * {
 *   std::string str( greeting.p_< message >().begin(), greeting.p_< message >().end() );
 *   std::cout << "greeting : " << str.c_str() << " ";
 * }
 * \endcode
 *
 * Finally, here is our \c main that ties everything together.
 *
 * \code
 * int main( int argc, char *argv[] )
 * {
 *   // The "fake" RTI exec used to mimic HLA data exchanges
 *   RTI::RTIexec rti_exec;
 *
 *   // Create an interaction ambassador and register our interaction callback.
 *   inter_amb_type inter_amb;
 *   inter_amb.set_handler( greeting_handler );
 *
 *   //
 *   // Sender Federate
 *   //
 *   RTI::RTIambassador send_rti_amb( rti_exec );
 *   fed_amb send_fed_amb( inter_amb );
 *
 *   //
 *   // Initialize handles
 *   //
 *   hw_som::init_handles( send_rti_amb );
 *
 *   //
 *   // Join federation
 *   //
 *   send_rti_amb.joinFederationExecution( "", "hw_sender", &send_fed_amb );
 *
 *   //
 *   // Publish interaction
 *   //
 *   greeting_type::publish( send_rti_amb );
 *
 *
 *
 *
 *   //
 *   // Receiver Federate
 *   //
 *   RTI::RTIambassador recv_rti_amb( rti_exec );
 *   fed_amb recv_fed_amb( inter_amb );
 *
 *   //
 *   // Join federation
 *   //
 *   recv_rti_amb.joinFederationExecution( "", "hw_receiver", &recv_fed_amb );
 *
 *   //
 *   // Subscribe interaction
 *   //
 *   greeting_type::subscribe( recv_rti_amb );


 *
 *   //
 *   // Run...
 *   //
 *   greeting_type send_msg;
 *
 *   const std::string what_up = "What up?";
 *
 *   send_msg.p_< Message >() = ASCIIString::array_type( what_up.begin(), what_up.end() );
 *
 *   send_msg.send( send_rti_amb );
 *
 *   rti_exec.tick();
 * }
 * \endcode
 *
 */
