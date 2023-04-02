#include <array>
#include <map>
#include <string>
#include "G4Color.hh"

extern const G4Color DEFAULT_COLORS[];

#ifndef MYB1PHANTOM_HH
#define MYB1PHANTOM_HH 1

class G4LogicalVolume;

namespace myb1
{
  class MyB1Phantom{
    public:
      MyB1Phantom() = default;
      MyB1Phantom(std::string);
      ~MyB1Phantom();

      G4LogicalVolume** logPhantoms;

      bool* isInUses;
      std::map<std::string, bool> phantomMap;
      void* memPhantom;

    private:
      bool hasColors; 
      
  }; 
} // namespace myb1


#endif