// InputOutput.hpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef CODEMINES_INPUTOUTPUT_HEADER_INCLUDED_
#define CODEMINES_INPUTOUTPUT_HEADER_INCLUDED_ 1

#include "GameEngine.hpp"
#include <iostream>

namespace CM {
  
  class InputOutput {
    
    InputOutput(const InputOutput& object);
    
    protected:
      std::istream* input;
      std::ostream& output;
      
    protected:
      GameEngine engine;
      std::string lastMessage;
      
    public:
      explicit InputOutput(std::ostream& output);
      explicit InputOutput(std::istream* input, std::ostream& output);
      virtual ~InputOutput();
      
      virtual void InitializeGame();
      virtual void RunGameLoop();
      
    protected: // Internal functions
      /* Technically, to add a new interface all you'd need to do would be to
         override these next two functions in a derived class, and pass some
         ostream to this class's constructor. */
      virtual void PauseForInput();
      virtual std::string GetCommand();
      
      virtual void Redraw(); // Calls Redraw(output)
      virtual void Redraw(std::ostream& out);
      virtual void GetTile(std::string& command, int& row, char& col,
                           std::size_t start);
    
  };
  
} // namespace CM

#endif // CODEMINES_INPUTOUTPUT_HEADER_INCLUDED_
