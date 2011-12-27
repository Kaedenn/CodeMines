// GameEngine.cpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#include <cstdlib>
#include <ctime>
#include "GameEngine.hpp"

namespace CM {
  
  bool IsConvexTile(Tile::Character tile) {
    switch (tile) {
      case Tile::Convex:
      case Tile::Flag:
      case Tile::Unknown: return true;
      default: return false;
    }
  }
  
  void GameEngine::ResetGame(mine_t mines) {
    if (mines > 0 && mines < NUMBER_OF_ROWS * NUMBER_OF_COLS) {
      num_mines = mines;
      tileMatrix = std::vector<std::vector<Tile> >(NUMBER_OF_ROWS,
                                                   std::vector<Tile>(
                                                     NUMBER_OF_COLS, Tile()));
      int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};
      int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
      for (int i = 0; i < NUMBER_OF_ROWS; ++i) {
        for (int j = 0; j < NUMBER_OF_COLS; ++j) {
          tileMatrix[i][j].Reset();
          for (Direction dir = Direction(0); dir < 8; dir = Direction(dir + 1)) {
            // If the tile is off the board, continue
            if (i + dr[dir] < 0 || i + dr[dir] == NUMBER_OF_ROWS) {
              continue;
            }
            if (j + dc[dir] < 0 || j + dc[dir] == NUMBER_OF_COLS) {
              continue;
            }
            // Otherwise, link up the tiles
            tileMatrix[i][j].Link(&tileMatrix[i + dr[dir]][j + dc[dir]], dir);
          }
        }
      }
      for (int i = 0; i < num_mines; ) {
        int row = int((double(std::rand()) / RAND_MAX) * NUMBER_OF_ROWS); // I know what I'm doing.
        int col = int((double(std::rand()) / RAND_MAX) * NUMBER_OF_COLS); // Do you?
        if (tileMatrix[row][col] == Tile::Volatile) {
          continue;
        }
        tileMatrix[row][col] = Tile::Volatile;
        ++i;
      }
    } else {
      throw NumMines();
    }
    SetMode(Playing);
  }
  
  void GameEngine::Activate(row_t row, col_t col) {
    if (row >= 0 && row < NUMBER_OF_ROWS && col >= 0 && col < NUMBER_OF_COLS) {
      if (tileMatrix[row][col].Activate() == Tile::TrippedMine) {
        SetMode(Dead);
        for (int i = 0; i < NUMBER_OF_ROWS; ++i) {
          for (int j = 0; j < NUMBER_OF_COLS; ++j) {
            if (tileMatrix[i][j] == Tile::Volatile) {
              switch (Tile::Character(tileMatrix[i][j])) {
                case Tile::Convex:
                case Tile::Unknown: {
                  tileMatrix[i][j] = Tile::Mine;
                } break;
                default: { } break; // C++-style "noop"
              }
            } else if (tileMatrix[i][j] == Tile::Inert) {
              switch (Tile::Character(tileMatrix[i][j])) {
                case Tile::Flag: {
                  tileMatrix[i][j] = Tile::Unknown;
                } break;
                default: { } break;
              }
            }
          }
        }
      } else {
        for (int i = 0; i < NUMBER_OF_ROWS; ++i) {
          for (int j = 0; j < NUMBER_OF_COLS; ++j) {
            if (tileMatrix[i][j] != Tile::Volatile) {
              if (IsConvexTile(tileMatrix[i][j])) {
                return;
              }
            }
          }
        }
        // Should only get here if the game is completed
        SetMode(Completed);
        for (int i = 0; i < NUMBER_OF_ROWS; ++i) {
          for (int j = 0; j < NUMBER_OF_COLS; ++j) {
            if (tileMatrix[i][j] == Tile::Volatile) {
              tileMatrix[i][j] = Tile::Flag;
            }
          }
        }
      }
    } else {
      throw Bounds();
    }
  }
  
  Tile::Character GameEngine::Mark(row_t row, col_t col) {
    if (row >= 0 && row < NUMBER_OF_ROWS && col >= 0 && col < NUMBER_OF_COLS) {
      return tileMatrix[row][col].Mark();
    } else {
      throw Bounds();
    }
  }
  
}
