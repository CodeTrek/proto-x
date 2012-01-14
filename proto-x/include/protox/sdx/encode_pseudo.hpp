
// if T's endianess is the same as the platform's (where T is SDXUnsignedShort) then...
 static void encode( S &s, const T &value)
{
  const byte *bytes = &value;
  s.push_back( bytes[0] ); // low memory
  s.push_back( bytes[1] ); // high memory
}

// else if T's endianess is the _not_ the same as the platform's...
static void encode( S &s, const T &value)
{
  const byte *bytes = &value;
  s.push_back( bytes[1] ); // high memory
  s.push_back( bytes[0] ); // low memory
}
