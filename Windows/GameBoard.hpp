/* GameBoard.hpp (now obsolete)

#ifndef CODEMINES_GAMEBOARD_HEADER_INCLUDED_
#define CODEMINES_GAMEBOARD_HEADER_INCLUDED_ 1

#include <exception>
#include <vector>
#include "GameTiles.hpp"

namespace CM {
  
  class GameBoard {
    
    
    GameBoard(const GameBoard& other);
    
    public:
      explicit GameBoard();
      ~GameBoard();
      
    public: // Error handling
      
      
    public:
      
      
      void Reset(const row_t& rows, const col_t& cols, const ushort& num_mines);
    
  };
  
} // namespace CM

#endif // CODEMINES_GAMEBOARD_HEADER_INCLUDED_*/
