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

class RTI
{
public:

#include "baseTypes.hh"
#include "RTItypes.hh"

#if 0
  typedef int ObjectClassHandle;
  typedef int AttributeHandle;

  typedef int InteractionClassHandle;
  typedef int ParameterHandle;
#endif

  class RTIambassador
  {
  public:

#include "RTIambServices.hh"

#if 0
    ObjectClassHandle getObjectClassHandle (const char *theName)
    {
      static int next_handle = 0;

      typedef std::map<std::string, ObjectClassHandle> name_to_handle_map_type;
      static name_to_handle_map_type map;

      name_to_handle_map_type::iterator it = map.find(theName);

      if (it == map.end())
      {
        return ++next_handle;
      }

      return ((*it).second);
    }

    AttributeHandle getAttributeHandle (const char *theName, ObjectClassHandle whichClass)
    {
      static int next_handle = 0;

      typedef std::map<std::string, AttributeHandle> attr_to_handle_map_type;
      typedef std::map<ObjectClassHandle, attr_to_handle_map_type> class_to_attr_map_type;

      static class_to_attr_map_type map;

      class_to_attr_map_type::iterator it1 = map.find(whichClass);

      if (it1 == map.end())
      {
        map[whichClass] = attr_to_handle_map_type();
        map[whichClass][theName] = (++next_handle);
        return map[whichClass][theName];
      }

      attr_to_handle_map_type::iterator it2 = (*it1).second.find(theName);

      if (it2 == (*it1).second.end())
      {
        map[whichClass][theName] = (++next_handle);
      }

      return map[whichClass][theName];
    }

    InteractionClassHandle getInteractionClassHandle (const char *theName)
    {
      static int next_handle = 0;

      typedef std::map<std::string, InteractionClassHandle> name_to_handle_map_type;
      static name_to_handle_map_type map;

      name_to_handle_map_type::iterator it = map.find(theName);

      if (it == map.end())
      {
        return ++next_handle;
      }

      return ((*it).second);
    }

    AttributeHandle getParameterHandle (const char *theName, InteractionClassHandle whichClass)
    {
      static int next_handle = 0;

      typedef std::map<std::string, ParameterHandle> param_to_handle_map_type;
      typedef std::map<InteractionClassHandle, param_to_handle_map_type> class_to_param_map_type;

      static class_to_param_map_type map;

      class_to_param_map_type::iterator it1 = map.find(whichClass);

      if (it1 == map.end())
      {
        map[whichClass] = param_to_handle_map_type();
        map[whichClass][theName] = (++next_handle);
        return map[whichClass][theName];
      }

      param_to_handle_map_type::iterator it2 = (*it1).second.find(theName);

      if (it2 == (*it1).second.end())
      {
        map[whichClass][theName] = (++next_handle);
      }

      return map[whichClass][theName];
    }

    void publishInteractionClass(InteractionClassHandle theInteraction) {}
    void unpublishInteractionClass(InteractionClassHandle theInteraction) {}
#endif
  };

#if 0
  class ParameterHandleValuePairSet
  {
  public:
    ParameterHandleValuePairSet() {}

    void add(RTI::ParameterHandle h, const char* buff, unsigned long length) {}
  };

  class ParameterSetFactory
  {
  public:
    static ParameterHandleValuePairSet* create(unsigned long count)
    {
      return new ParameterHandleValuePairSet();
    }
  };
#endif
};

#endif
