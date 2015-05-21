# proto-x

**proto-x**  is a cross-platform, open source C++ library for developing high level architecture [HLA] (http://en.wikipedia.org/wiki/IEEE_1516) compliant simulations, tools, and utilities. proto-x places an emphasis on letting you represent SOM component definitions as C++ type definitions. As a result, you can define a proto-x based HLA C++ API that is tailored to match your federate’s SOM. This has several advantages, including:

  * _Code at the same level of abstraction as your SOM_ - You don’t have to deal with attribute and parameter values as opaque byte arrays. Attribute and parameter value representations are accessed via an interface that matches your SOM specification. The interface uses the same names, data type definitions, and class structures defined in your SOM, so when you program to a proto-x defined interface you are working at the same level of abstraction as your SOM.

  * _Correct encoding/decoding of all your SOM data types_ - proto-x enforces correct default encoding and decoding rules,  with support for both HLA 13 and 1516 "out of the box". You can also define custom encoding/decoding rules when your SOM deviates from the standard.

  * _SOM and source code are never out of sync_ - proto-x lets you define your SOM in C++ source code, so there is no way for your code and SOM to be in conflict.

  * _Simpler build process_ - protox leverages the C++ template compiler to perform the translation from your SOM component definitions to equivalent C++ types, eliminating the need for a separate code generation step in your build process.

  * _Code that is easier to maintain and modify_ – A proto-x based API hides many of the messy coding details associated with programming to the [RTI] (http://en.wikipedia.org/wiki/Run-Time_Infrastructure_(simulation)) API that can make your code difficult to read and understand (and therefore difficult to maintain and modify). In particular, error prone bookkeeping details such as handle management are completely hidden with proto-x.
 
# Example
  Let’s use proto-x to code a simple federate that sends a _Greeting_ interaction that consists of a single parameter called _message_ that is a fixed array of ASCII characters. To do this, we need to define the following SOM components (assume we are building a federate to the HLA 1516 standard):

  * A _*basic data representation table*_ to define a basic data type that can be the bases for the definition of an ASCII character type.

  * A _*simple datatype table*_ to define an ASCII character type.

  * An _*array datatype table*_ to define the type used to hold messages.

  * A _*parameter table*_ to define the _Message_ parameter.

  * And finally, an _*interaction class structure table*_ to define the _Greeting_ interaction.

We’ll define our SOM components in the order listed above.

We start with a proto-x definition of _*basic data representation table*_ with a single basic data representation definition called HLAoctet. Note that `#include` directives and other non-essential code are not shown to keep the code samples small and easier to read.

```C++
//   +--------------------------------+--------------+-------------+------------+
//   | Name                           | Size in bits | Endian      | Encoding   | 
//   +--------------------------------+--------------+-------------+------------+
struct HLAoctet : basic< unsigned char, 8,             endian::big,  HLAPortable> {};
```
The proto-x keywords in this defintion are: *basic_data_representation* and *endian::big*. The commenting style and use of white space emphasizes how you can structure your proto-x code so that its format is similar to the OMT tabular format. Using a commenting style like this one is a good way to document your SOM as you implement your federate. Although it is not covered in this example, you can actually use proto-x as your primary means of documenting your federate’s SOM. The advantage is that your code and SOM are always in sync so you can be confident that the SOM you publish as your public HLA contract is accurate.

Next, let’s define a _*simple datatype table*_ with a simple datatype definition used to represent ASCII characters.
```C++
//   +----------------------+------------------+----------+
//   | Name                 | Representation   | Units    |
//   +----------------------+------------------+----------+
struct HLAASCIIchar : simple< HLAoctet,          unitless > {};
```

Note how we used the basic data representation *HLAoctet* in the definition of *HLAASCIIchar*.

Here is the entry in our _*array datatype table*_ that defines an array type for holding _Message_ parameter values.
```C++
//   +----------+----------------------+---------------+-------------+
//   | Name     | Encoding             | Element type  | Cardinality |
//   +----------+----------------------+---------------+-------------+
struct FixedMsg : hla_1516::fixed_array< HLAASCIIchar,   5 > {};
```
Note that the proto-x keyword *hla_1516::fixed_array* specifies the standard HLA 1516 encoding for fixed arrays.

We now have all the definitions we need to define our _*parameter table*_ and our _*interaction class structure table*_:

```C++
//   +------------------------------+-----------+-----------------+----------------------+
//   | Name                         | Parameter | Datatype        | String Name          |
//   +------------------------------+-----------+-----------------+----------------------+
struct Greeter {HLA_NAME("Greeter")};
//                                  +-----------+-----------------+----------------------+
                               struct Message   : param< FixedMsg > {HLA_NAME("Message")};
//                                  +-----------+-----------------+----------------------+

struct InteractionClassTable : i_class< Greeter, params< Message > > {};
```
With all of our SOM components defined, we can now implement our federate as follows:
```C++
// Define a SOM
typedef som< InteractionClassTable > GreeterSom;

main()
{
  RTI::RTIambassador rti;

  // Initialize class, attribute, interaction, and parameter handles
  GreeterSom::init_handles(rti);

  // Join a federation (code not shown for brevity)…

  // Generate the Greeter interaction class type 
  typedef interaction_class< GreeterSom , name< Greeter > >::type GreeterType;

  // Publish the Greeter interaction class
  GreeterType::publish(rti);

  // Create a Greeter interaction
  GreeterType greeter;

  // Initialize a null terminated Message parameter
  greeter.param< Message >()[0] = ‘h’;
  greeter.param< Message >()[1] = ‘i’;
  greeter.param< Message >()[2] =  0;

  // Send the interaction
  greeter.send(rti);
}
```
# Conclusion

Proto-x is an effort to make developing C++ HLA federates easier by providing the following:

  * An HLA interface description language (IDL) for the C++ language, and
  * A middleware component similar to object-relational mapping middleware solutions found in the relational database domain.

The goal is to provide these solutions using a "pure" C++ implementation with minimal reliance on third-party libraries, and when third-party libraries are needed, they must be open source and cross-platform. Hopefully, proto-x along with a good open source RTI (e.g., [http://www.porticoproject.org/index.php?title=Main_Page portico]) will remove some of the pain associated with HLA experimentation and development on a limited budget, while at the same time providing a solid foundation upon which to build high quality HLA federates.

# References
The original concept for proto-x is described in the paper "Creating an HLA 1516 Data Encoding Library using C++ Template Metaprogramming Techniques". See 07S-SIW-035.pdf in Featured Downloads for a link to this paper.

See the paper "CERTI, an Open Source RTI, why and how" for a description of an [http://savannah.nongnu.org/projects/certi/ open source RTI] that uses techniques similar to those described here for its implementation of an HLA compliant encoding library. See 09S-SIW-015.pdf in Featured Downloads for a link to this paper.
