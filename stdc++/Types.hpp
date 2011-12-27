// Types.hpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef CODESWEEPER_TYPES_HEADER_INCLUDED_
#define CODESWEEPER_TYPES_HEADER_INCLUDED_ 1

#include <cstddef>
#include <sstream>
#include <typeinfo>

namespace CM {
  
  typedef int row_t;
  typedef int col_t;
  typedef int tile_t;
  typedef int mine_t;
  
  extern const tile_t NUMBER_OF_ROWS;
  extern const tile_t NUMBER_OF_COLS;
  extern const mine_t DEF_NUMBER_OF_MINES;
  
  extern short userIsCheating;
  
  enum Direction {
    Up, UpRight, Right, DownRight,
    Down, DownLeft, Left, UpLeft
  };
  
  std::string toLower(std::string array);
  
  template <typename To, typename From>
  To logical_cast(const From& from) {
    std::stringstream ss;
    To to;
    if (ss << from && ss >> to) {
      return to;
    } else {
      throw std::bad_cast();
    }
  }
  
}

#endif // CODESWEEPER_TYPES_HEADER_INCLUDED_
