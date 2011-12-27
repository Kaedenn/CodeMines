// InputOutputColor.hpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef CODEMINES_INPUTOUTPUTCOLOR_HEADER_INCLUDED_
#define CODEMINES_INPUTOUTPUTCOLOR_HEADER_INCLUDED_ 1

#include "InputOutput.hpp"

namespace CM {
  
  class InputOutputColor : public InputOutput {
    
    public:
      explicit InputOutputColor(std::istream* input, std::ostream& output);
      virtual ~InputOutputColor() { }
      
      virtual void InitializeGame();
      
    protected:
      virtual void Redraw();
      
  };
  
}

#endif // CODEMINES_INPUTOUTPUTCOLOR_HEADER_INCLUDED_
