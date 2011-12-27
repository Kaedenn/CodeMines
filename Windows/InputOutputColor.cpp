// InputOutputColor.cpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifdef CODEMINES_GAME_USE_COLOR_VERSION_

# include "InputOutputColor.hpp"
# include "StreamColors.hpp"
# include <iomanip>

namespace CM {
  
  InputOutputColor::InputOutputColor(std::istream* in, std::ostream& out)
   : InputOutput::InputOutput(in, out) { }
  
  void InputOutputColor::InitializeGame() {
    InputOutput::output <<
"+-----------------------------------------------------------------------------+" << '\n' <<
"| Welcome to CodeMines!                                                       |" << '\n' <<
"|    First came CodeMines in 100% standard C++, but now, after reading a few  |" << '\n' <<
"|  chapters of my Assembly Language Programming textbook, I decided to add    |" << '\n' <<
"|  some very interesting (and pleasing) features to this game, namely color   |" << '\n' <<
"|  support. Now, since all these functions are part of the Win32 API, I don't |" << '\n' <<
"|  have to use ASM! I can just use these functions directly, in my code.      |" << '\n' <<
"|   Maybe this is overkill, but I'm expanding this color support idea to      |" << '\n' <<
"|  Linux/Unix control codes. This'll allow me to output colors to the POSIX   |" << '\n' <<
"|  console, just like I do with the Win32 console! I'd love to make this work |" << '\n' <<
"|  natively on MacOSX as well, but I'm not sure if that's even possible.      |" << '\n' <<
"|    Questions? Comments? Find me on IRC at irc.freenode.net. I'll be in the  |" << '\n' <<
"|  channel \"##c++-social\" under the nickname \"Kaedenn\". Questions,            |" << '\n' <<
"|  comments, opinions, bugs, etc. are all welcome! I love to receive input    |" << '\n' <<
"|  about the programs I make.                                                 |" << '\n' <<
"|    Now, if you've played Minesweeper, then this game should come naturally. |" << '\n' <<
"|  To select a tile, enter the row number (from 1 to 20) followed by the      |" << '\n' <<
"|  column letter (from A to Z). Letters are not case-sensitive, so 'A' is the |" << '\n' <<
"|  same as 'a', and they both work. To \"mark\" or \"flag\" a tile, type the      |" << '\n' <<
"|  word \"MARK\" or \"FLAG\", followed by the tile. Ex: \"FLAG 10A\" will mark      |" << '\n' <<
"|  the tile 10 rows down and on the first column. Commas and spaces don't     |" << '\n' <<
"|  matter, so \"10A\" is the same as \"10 , a\". Furthermore, you can swap the    |" << '\n' <<
"|  row number and column letter, so \"A10\" is the same as \"10A\".               |" << '\n' <<
"|    Other commands: SETMINES #, RESTART, QUIT. With SETMINES, replace # with |" << '\n' <<
"|  a number between 1 and 520. Ex: \"SETMINES 200\" will restart the game with  |" << '\n' <<
"|  200 mines.                                                                 |" << '\n' <<
"|    There are a few \"Easter Eggs\" in this game, and two cheat codes... see   |" << '\n' <<
"|  if you can find them!                                                      |" << '\n' <<
"+-----------------------------------------------------------------------------+" << '\n' <<
"|  Press ENTER or RETURN to begin the game with 20 rows, 26 columns and 50    |" << '\n' <<
"|    mines. Good luck!                                                        |" << '\n' <<
"+-----------------------------------------------------------------------------+" << '\n';
    InputOutput::PauseForInput();
  }
  
  void InputOutputColor::Redraw() {
    using eX::IO::ColorField;
    std::ostream& out = InputOutput::output;
    const std::string& lastMessage = InputOutput::lastMessage;
    const GameEngine& engine = InputOutput::engine;
    const std::vector<std::vector<Tile> >& matrix = engine.GetTileMatrix();
    std::string lsmiley;
    std::string rsmiley;
    if (engine == GameEngine::Dead) {
      lsmiley = "x(";
      rsmiley = ")x";
    } else if (engine == GameEngine::Completed) {
      lsmiley = "8)";
      rsmiley = "(8";
    } else {
      lsmiley = "=)";
      rsmiley = "(=";
    }
    const char* rightSideBar[20] = {"                   ",
                                    " To select a tile, ",
                                    " enter the row     ",
                                    " number then the   ",
                                    " column letter.    ",
                                    "  >> 10A           ",
                                    "  >> 10 A          ",
                                    "  >> 10,A          ",
                                    " As always, case   ",
                                    " does not matter;  ",
                                    " both 'a' and 'A'  ",
                                    " work fine.        ",
                                    "                   ",
                                    "  Other Commands:  ",
                                    "                   ",
                                    " FLAG tile         ",
                                    " SETMINES #        ",
                                    " RESTART           ",
                                    " QUIT              ",
                                    "                   "};
    const char* numbers[20] = {" 1"," 2"," 3"," 4"," 5"," 6"," 7"," 8"," 9",
                               "10","11","12","13","14","15","16","17","18",
                               "19","20"};
    const char* horizBar = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    out << ColorField(0x02,"+-----------------------------------------------------------------------------+")
        << '\n' << ColorField(0x02,"|")
        << ColorField(0x0B,"                                   CodeMines                                 ")
        << ColorField(0x02,"|") << '\n' << ColorField(0x02,"|")
        << ColorField(0x09,"                                By Peter Schultz                             ")
        << ColorField(0x02,"|") << '\n'
        << ColorField(0x02,"+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-------------------+")
        << '\n' << ColorField(0x02,"|") << ColorField(0x0C,lsmiley);
    for (tile_t i = 0; i < NUMBER_OF_COLS; ++i) {
      char letter[2] = {horizBar[i], 0};
      out << ColorField(0x02,"|") << ColorField(0x09, letter);
    }
    out << ColorField(0x02,"|") << ColorField(0x0C,rsmiley)
        << ColorField(0x02,"|") << ColorField(0x0B,"     Commands:     ")
        << ColorField(0x02,"|") << '\n';
    for (std::size_t i = 0; i < matrix.size(); ++i) {
      out << ColorField(0x02,"|") << ColorField(0x09,numbers[i])
          << ColorField(0x02,"|");
      for (std::size_t j = 0; j < matrix[i].size(); ++j) {
        if (j == 0) {
          // noop
        } else if (!IsConvexTile(matrix[i][j]) || matrix[i][j] == Tile::Flag) {
          out << ' ';
        } else if (!IsConvexTile(matrix[i][j-1]) || matrix[i][j-1] == Tile::Flag) {
          out << ' ';
        } else {
          out << ColorField(0x02,"|");
        }
        if (userIsCheating == 2 && (Tile::State(matrix[i][j]) == Tile::Volatile)) {
          out << ColorField(0x04, "O");
        } else {
          unsigned char color = 0x07;
          char tile[2] = {char(Tile::Character(matrix[i][j])), 0};
          switch (tile[0]) {
            case Tile::Numeral_1: { color = 0x0B; } break;
            case Tile::Numeral_2: { color = 0x0C; } break;
            case Tile::Numeral_3: { color = 0x0A; } break;
            case Tile::Numeral_4: { color = 0x0D; } break;
            case Tile::Numeral_5: { color = 0x0E; } break;
            case Tile::Numeral_6: { color = 0x06; } break;
            case Tile::Numeral_7: { color = 0x05; } break;
            case Tile::Numeral_8: { color = 0x0F; } break;
            case Tile::Flag: { color = 0x09; } break;
            case Tile::Unknown: { color = 0x03; } break;
            case Tile::TrippedMine:
            case Tile::Mine: { color = 0xC0; } break;
            default: {  } break;
          }
          out << ColorField(color, tile);
        }
      }
      out << ColorField(0x02,"|") << ColorField(0x09,numbers[i])
          << ColorField(0x02,"|") << ColorField(0x09,rightSideBar[i])
          << ColorField(0x02,"|") << '\n';
    }
    out << ColorField(0x02,"|") << ColorField(0x0C,lsmiley);
    for (tile_t i = 0; i < NUMBER_OF_COLS; ++i) {
      char letter[2] = {horizBar[i], 0};
      out << ColorField(0x02,"|") << ColorField(0x09, letter);
    }
    out << ColorField(0x02,"|") << ColorField(0x0C,rsmiley)
        << ColorField(0x02,"|") << ColorField(0x0B,"    Mines: ")
        << std::setw(3) << std::left
        << ColorField(0x0B,logical_cast<std::string>(engine.Mines()))
        << std::right << std::setw(5) << ' ' << ColorField(0x02,"|") << '\n'
        << ColorField(0x02,"+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-------------------+")
        << '\n' << ColorField(0x02,"|") << ColorField(0x0C," {{ ")
        << lastMessage << ColorField(0x0C," }} ")
        << std::setw(69 - lastMessage.size()) << ' ' << ColorField(0x02,"|")
        << '\n' << ColorField(0x02,"+") << ColorField(0x0E," >> ")
        << std::flush;
  }
  
}

#endif // CODEMINES_GAME_USE_COLOR_VERSION_
