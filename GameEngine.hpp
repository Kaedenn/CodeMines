// GameEngine.hpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef CODEMINES_GAMEENGINE_HEADER_INCLUDED_
#define CODEMINES_GAMEENGINE_HEADER_INCLUDED_ 1

#include <vector>
#include "GameTiles.hpp"

namespace CM {
  
  bool IsConvexTile(Tile::Character tile);
  
  class GameEngine {
    
    std::vector<std::vector<Tile> > tileMatrix;
    
    mine_t num_mines;
    
    bool timerActive;
    std::time_t startTime;
    std::time_t endTime;
    
    GameEngine(const GameEngine& obj);
    
    public:
      enum Mode {
        Unloaded,
        Playing,
        Completed,
        Dead
      };
      
    private:
      Mode currentMode;
      
    public:
      explicit GameEngine()
       : tileMatrix(), num_mines(0), timerActive(false), startTime(0),
         endTime(0), currentMode(Unloaded) {
        std::srand(std::time(0));
      }
      ~GameEngine() { }
      
      void ResetGame(mine_t mines = DEF_NUMBER_OF_MINES);
      void Activate(row_t row, col_t col);
      Tile::Character Mark(row_t row, col_t col);
      
      void StartTimer() {
        if (timerActive) return;
        timerActive = true;
        startTime = std::time(0);
      }
      
      std::time_t StopTimer() {
        if (!timerActive) return endTime - startTime;
        timerActive = false;
        endTime = std::time(0);
        return endTime - startTime;
      }
      
      std::time_t GetElapsedTime() const {
        return endTime - startTime;
      }
      
      void SetMode(Mode mode) {
        currentMode = mode;
      }
      
      operator Mode() const {
        return currentMode;
      }
      
      const std::vector<std::vector<Tile> >& GetTileMatrix() const {
        return tileMatrix;
      }
      
      mine_t Mines() const { return num_mines; }
      
    public: // Error-handling
      struct Bounds : std::exception {
        const char* what() {
          return "Please select a tile ON the field.";
        }
      };
      struct Dimension : std::exception {
        const char* what() {
          return "Invalid dimension for new board size.";
        }
      };
      struct NumMines : std::exception {
        const char* what() {
          return "Invalid number of mines.";
        }
      };
      
  };
  
} // namespace CM

#endif // CODEMINES_GAMEENGINE_HEADER_INCLUDED_
