#ifndef RTI_hh
#define RTI_hh

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
      static int handle = 0;

      return ++handle;
    }

    AttributeHandle getAttributeHandle (const char *theName, ObjectClassHandle whichClass) { return 2; }
  };
};

#endif
