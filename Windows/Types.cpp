// Types.cpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#include "Types.hpp"

namespace CM {
  
  const mine_t NUMBER_OF_ROWS = 20;
  const mine_t NUMBER_OF_COLS = 26;
  const mine_t DEF_NUMBER_OF_MINES = 50;
  
  // Little easter-egg/cheating thing, if you want.
  short userIsCheating = false;
  
  // I guess having toLower(string) was too much to ask.
  std::string toLower(std::string array) {
    return std::use_facet<std::ctype<char> >(
      std::locale()
    ).tolower(
      &array[0],
      &array[0] + array.length()
    ) - array.length();
  }
  
}

