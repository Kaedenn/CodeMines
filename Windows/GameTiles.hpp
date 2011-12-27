// GameTiles.hpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef CODEMINES_GAMETILES_HEADER_INCLUDED_
#define CODEMINES_GAMETILES_HEADER_INCLUDED_ 1

#include "Types.hpp"

namespace CM {
  
  class Tile {
    Tile* siblings[8]; // One for each direction
    
    public:
      Tile()
       : currentState(Inert), currentCharacter(Convex) {
        for (int i = 0; i < 8; ++i)
          siblings[i] = 0;
      }
      //Tile(const Tile& otherTile); Use default copy-ctor
      ~Tile() {}
      
    public:
      enum State {
        Inert, Volatile
      };
      enum Character {
        Convex = 'O',
        Blank = ' ',
        Numeral_1 = '1',
        Numeral_2 = '2',
        Numeral_3 = '3',
        Numeral_4 = '4',
        Numeral_5 = '5',
        Numeral_6 = '6',
        Numeral_7 = '7',
        Numeral_8 = '8',
        Numeral_9 = '9',
        Flag = '!',
        Unknown = '?',
        TrippedMine = 'X',
        Mine = '*'
      };
      enum Error {
        AlreadyActivated,
        AlreadyFlagged
      };
      
    public:
      void Reset() {
        currentState = Inert;
        currentCharacter = Convex;
        for (int i = 0; i < 8; ++i)
          siblings[i] = 0;
      }
      
      void Link(Tile* tile, Direction dir);
      Character Activate();
      Character Mark();
      
      operator State() const {
        return currentState;
      }
      
      operator Character() const {
        return currentCharacter;
      }
      
      Tile& operator = (State state) {
        currentState = state;
        return *this;
      }
      
      Tile& operator = (Character character) {
        currentCharacter = character;
        return *this;
      }
      
    private:
      State currentState;
      Character currentCharacter;
    
  };
  
} // namespace CM

#endif // CODEMINES_GAMETILES_HEADER_INCLUDED_
