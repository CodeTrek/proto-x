#ifndef MOCK_RTI_HH
#define MOCK_RTI_HH

#if defined(WIN32)
// disable warning about exceptions not being part of a method's signature
#pragma warning(disable: 4290)
// disable warnings about deriving a "dllexport" class from a regular class
#pragma warning(disable: 4275)
#pragma warning(disable: 4251)
#endif

#define RTI_EXPORT
#define RTI_EXPORT_FEDTIME

#include <map>
#include <string>

class RTI
{
public:

#include "baseTypes.hh"
#include "RTItypes.hh"

  typedef std::map<std::string, ObjectClassHandle> o_class_to_handle_map_type;
  typedef std::map<std::string, InteractionClassHandle> i_class_to_handle_map_type;


  class RTIambassador
  {
  public:
    RTI::o_class_to_handle_map_type o_class_to_handle_map;
    RTI::i_class_to_handle_map_type i_class_to_handle_map;

#include "RTIambServices.hh"
  };
};

#endif
