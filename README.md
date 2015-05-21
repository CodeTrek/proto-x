# proto-x

**proto-x**  is a cross-platform, open source C++ library for developing high level architecture [HLA] (http://en.wikipedia.org/wiki/IEEE_1516) compliant simulations, tools, and utilities. proto-x places an emphasis on letting you represent SOM component definitions as C++ type definitions. As a result, you can define a proto-x based HLA C++ API that is tailored to match your federate’s SOM. This has several advantages, including:

  * _Code at the same level of abstraction as your SOM_ - You don’t have to deal with attribute and parameter values as opaque byte arrays. Attribute and parameter value representations are accessed via an interface that matches your SOM specification. The interface uses the same names, data type definitions, and class structures defined in your SOM, so when you program to a proto-x defined interface you are working at the same level of abstraction as your SOM.

  * _Correct encoding/decoding of all your SOM data types_ - proto-x enforces correct default encoding and decoding rules,  with support for both HLA 13 and 1516 "out of the box". You can also define custom encoding/decoding rules when your SOM deviates from the standard.

  * _SOM and source code are never out of sync_ - proto-x lets you define your SOM in C++ source code, so there is no way for your code and SOM to be in conflict.

  * _Simpler build process_ - protox leverages the C++ template compiler to perform the translation from your SOM component definitions to equivalent C++ types, eliminating the need for a separate code generation step in your build process.

  * _Code that is easier to maintain and modify_ – A proto-x based API hides many of the messy coding details associated with programming to the [RTI] (http://en.wikipedia.org/wiki/Run-Time_Infrastructure_(simulation)) API that can make your code difficult to read and understand (and therefore difficult to maintain and modify). In particular, error prone bookkeeping details such as handle management are completely hidden with proto-x.
  
  # Example
  
