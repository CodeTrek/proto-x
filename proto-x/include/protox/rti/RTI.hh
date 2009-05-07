#ifndef RTI_hh
#define RTI_hh

#include <map>

class RTI
{
public:
  typedef int ObjectClassHandle;
  typedef int AttributeHandle;

  class RTIambassador
  {
  public:
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
  };
};

#endif
