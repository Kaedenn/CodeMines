// GameTiles.cpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#include "GameTiles.hpp"

namespace CM {
  
  void Tile::Link(Tile* tile, Direction dir) {
    siblings[dir] = tile;
  }
  
  Tile::Character Tile::Activate() {
    if (currentCharacter == Convex) {
      if (currentState == Volatile) {
        return currentCharacter = TrippedMine;
      }
      int numSiblingMines = 0;
      for (int i = 0; i < 8; ++i) {
        if (siblings[i] == 0) continue;
        if (siblings[i]->currentState == Volatile) {
          ++numSiblingMines;
        }
      }
      if (numSiblingMines > 0) {
        return currentCharacter = Character(Numeral_1 + numSiblingMines - 1);
      } else {
        currentCharacter = Blank;
        for (int i = 0; i < 8; ++i) {
          if (siblings[i] == 0 || Character(*siblings[i]) != Convex) continue;
          siblings[i]->Activate();
        }
      }
    } else switch (currentCharacter) {
      case Blank:
      case Numeral_1:
      case Numeral_2:
      case Numeral_3:
      case Numeral_4:
      case Numeral_5:
      case Numeral_6:
      case Numeral_7:
      case Numeral_8:
      case Numeral_9: {
        throw AlreadyActivated;
      } break;
      default: {
        throw AlreadyFlagged;
      } break;
    }
    return currentCharacter;
  }
  
  Tile::Character Tile::Mark() {
    if (currentCharacter == Convex) {
      if (userIsCheating == true && currentState != Volatile) {
        return currentCharacter = Unknown;
      }
      return currentCharacter = Flag;
    } else if (currentCharacter == Flag) {
      return currentCharacter = Unknown;
    } else if (currentCharacter == Unknown) {
      return currentCharacter = Convex;
    } else {
      return currentCharacter;
    }
  }
  
}
