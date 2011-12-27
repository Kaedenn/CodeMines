// Extreme C++ Stream Colors

/* Color attributes for Win32 are specified by TWO hex digits -- the first
  corresponds to the background; the second the foreground. Each digit can be
  any of the following values:
    0 = Black       8 = Gray
    1 = Blue        9 = Light Blue
    2 = Green       A = Light Green
    3 = Aqua        B = Light Aqua
    4 = Red         C = Light Red
    5 = Purple      D = Light Purple
    6 = Yellow      E = Light Yellow
    7 = White       F = Bright White
  *
  * Color attributes for the POSIX console are specified by a string of
   attributes, separated by a semicolon. ECMA-48 SGR in `man console_codes`
   lists a number of attributes, some of which are listed here:
    0	reset all attributes to their defaults
    1	set bold
    2	set half-bright
    4	set underscore
    5	set blink
    21	set normal intensity (ECMA-48 says "doubly underlined")
    22	set normal intensity
    24	underline off
    25	blink off
    30	set black foreground
    31	set red foreground
    32	set green foreground
    33	set brown foreground
    34	set blue foreground
    35	set magenta foreground
    36	set cyan foreground
    37	set white foreground
    38	set underscore on, set default foreground color
    39	set underscore off, set default foreground color
    40	set black background
    41	set red background
    42	set green background
    43	set brown background
    44	set blue background
    45	set magenta background
    46	set cyan background
    47	set white background
    49	set default background color
  *
  * Also, do know that control characters (\r, \n, \t, etc) will not work with
   the Win32 half of this utility. This is due to the limitations of the
   functions I'm using.
  */

#ifndef EXTREME_CPP_STREAM_COLORS_HEADER_INCLUDED_
#define EXTREME_CPP_STREAM_COLORS_HEADER_INCLUDED_ 1

#include <ostream>

namespace eX {
  
  namespace IO {
    
    struct ColorField {
      ColorField(std::string code, std::string message)
       : code(code), message(message) { }
      std::string code;
      std::string message;
    };
    
    std::ostream& operator << (std::ostream& os, const ColorField& field) {
      return os << ("\033[" + field.code + 'm' + field.message + "\033[0m");
    }
    
  }
  
}

namespace std {
  using eX::IO::operator<<;
}

#endif // EXTREME_CPP_STREAM_COLORS_HEADER_INCLUDED_
