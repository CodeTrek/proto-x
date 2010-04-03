/*
    Copyright 2009 Jay Graham

    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or http://www.opensource.org/licenses/mit-license.php)
*/

/**************************************************************************************************/

/** \page first_example First Example
 * This example uses \c proto-x to create an API for two simple federates. One that sends an
 * interaction called \c Greeting that consists of a single parameter called \c Message, a fixed
 * array of ASCII characters. And another that receives \c Greeting interactions and prints the
 * value of the \c Message parameter to standard out.
 *
 * Start by defining the following these SOM components:
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
 * Here is a \c proto-x definition of the <b><i>basic data representation table</i></b>
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
 * The commenting style and use of white space emphasizes how \c proto-x code can be structured
 * so that its format resembles the HLA Object Model Template (OMT) tabular format. Using a
 * commenting style like this is a good way to document a SOM specification. The advantage is
 * that the resulting code and SOM specification are always in sync.
 *
 * <hr width=100>
 * Here is the <b><i>simple datatype table</i></b> with a simple datatype definition used to
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
 * Note how the basic datatype \c HLAoctet is used in the definition of \c HLAASCIIchar.
 * The \c struct template \c defines our simple datatype, and the \c PROTOX_SIMPLE macro generates
 * require boilerplate code.
 *
 * <hr width=100>
 * Here is the <b><i>array datatype table</i></b> that defines an array type for holding \c Message
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
 * Here is the <b><i>parameter table</i></b>:
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
 * This table contains a single parameter called \c Message of type \c FixedMsg. The
 * paramter table is also the place to define interaction class names. In this case, the table
 * defines a single interaction class named \c Greeting.
 *
 * <hr width=100>
 *
 * Here is the <b><i>interaction class table</i></b>:
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
 * This table establishes <i>'is-a'</i> relationsips between interaction classes. This is
 * a very simple interaction class table with a single interaction class called \c Greeting
 * derived from the root interaction class called \c HLAinteractionRoot.
 *
 * These SOM components are now ready to be used to constrcut the two federates.
 *
 * To make things easier, this example uses a very lightweight implementation of the RTI
 * API specifically designed to implement example code that demonstrates \c proto-x concepts and
 * functionality. This implementation of the RTI provides just enough functionality to satisfy the
 * needs of a \c proto-x derived API without the additional overhead of using a real RTI e.g.,
 * configuration files, running federates and RTI executives in seperate processes, etc...
 *
 * This lightweight RTI implementation is found in the code base in a folder called \c rtilite.
 *
 * The federates require a few more \c proto-x types.
 *
 * The first type represents a simulation object model (SOM). It is defined like this:
 *
 * \code
 * // Hello world SOM type
 * typedef protox::hla::som< null_o_class, inter_class_table > hw_som;
 * \endcode
 *
 * A SOM is defined by an object class table type and an interaction class table type. This
 * example does not require an object class table, so the first template argument is
 * <tt>null_o_class</tt>. The second template argument is the interaction class table type
 * <tt>inter_class_table</tt>.
 *
 * This SOM type <tt>hw_som</tt> is used to define a \c Greeting interaction type like this:
 *
 * \code
 * typedef i_class_type< hw_som, q_name< Greeting > >::type greeting_type;
 * \endcode
 *
 * <tt>hw_som</tt> is the SOM. The template argument <tt>q_name< Greeting ></tt> is the fully
 * qualified name of the \c Greeting interaction. The type <tt>greeting_type</tt> is used to
 * declare instances of a \c Greeting interaction.
 *
 * Next is the definition of an interaction ambassador that is capable of receiving
 * \c greeting_type interactions:
 *
 * \code
 * // An interaction ambassador used to register callbacks that are invoked by interaction class
 * // type.
 * typedef hla::interaction_amb< mpl::vector< greeting_type > >::type inter_amb_type;
 * \endcode
 *
 * The receiving federate needs an HLA federate ambassador that forwards interactions to the
 * \c proto-x ambassador. Here is an HLA federate ambassador that gets a reference to the
 * interaction ambassador. Note how all received interactions are forwarded to the \c proto-x
 * interaction ambassador.
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
 * Callback functions are registered with the interaction ambassador to handle received
 * \c Greeting interactions. Here is a simple handler that writes the value of the \c message
 * parameter to standard out.
 *
 * \code
 * static void greeting_handler( const greeting_type &greeting, const RTI::FedTime *, const char * )
 * {
 *   std::string str( greeting.p_< message >().begin(), greeting.p_< message >().end() );
 *   std::cout << "greeting : " << str.c_str() << " ";
 * }
 * \endcode
 *
 * Here is the \c main that ties everything together.
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
 *   // /////////////////////////////////////////////
 *   // SENDER FEDERATE
 *   // /////////////////////////////////////////////
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
 *   // /////////////////////////////////////////////
 *   // RECEIVER FEDERATE
 *   // /////////////////////////////////////////////
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
 *   // /////////////////////////////////////////////
 *   // RUN...
 *   // /////////////////////////////////////////////
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
