// Main.cpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef CODEMINES_GAME_USE_COLOR_VERSION_
# include "InputOutput.hpp"
#else
# include "InputOutputColor.hpp"
#endif // CODEMINES_GAME_USE_COLOR_VERSION_

int main(int argc, char* argv[]) {
  
  if (argc > 1) {
    if (std::string(argv[1]) == "-listcommands") {
      std::cout << "quit        -quits the game" << '\n'
                << "restart     -restarts the current game" << '\n'
                << "setmines #  -replace # with a number of mines between 1 and" << '\n'
                << "             519 to change the number of mines. This also" << '\n'
                << "             restarts the level." << '\n'
                << "mark $      -replace $ with the desired tile to 'mark' or" << '\n'
                << "             'flag' the selected tile." << '\n'
                << "flag $      -exactly the same as 'mark $'" << '\n'
                << "log $-      -Takes a snapshot of the current output and" << '\n'
                << "             it in 'codesmineslog.txt'" << '\n'
                << "longcat, desu, dontpanic, cassie, dragon, tigger, mario," << '\n'
                << "sexysexy, :v:, xyzzy, yzzyx" << std::endl;
    }
  }
  
#ifndef CODEMINES_GAME_USE_COLOR_VERSION_
  try {
    CM::InputOutput game(&std::cin, std::cout);
    game.InitializeGame();
    game.RunGameLoop();
  } catch (...) {
    std::cout << "Fatal error detected. The program will close now.";
  }
#else
  try {
    CM::InputOutputColor game(&std::cin, std::cout);
    game.InitializeGame();
    game.RunGameLoop();
  } catch (...) {
    std::cout << "Fatal error detected. The program will close now.";
    return 1;
  }
#endif // CODEMINES_GAME_USE_COLOR_VERSION_
  
  return 0;
}
