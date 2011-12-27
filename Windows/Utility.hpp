// Utility.hpp

#ifndef CODEMINES_UTILITY_HEADER_INCLUDED_
#define CODEMINES_UTILITY_HEADER_INCLUDED_

#include <sstream>

namespace CM {
  
  template <typename Source>
  std::string string_cast(const Source& source) {
    std::ostringstream oss;
    if (oss << source) {
      return oss.str();
    } else {
      throw std::bad_cast();
    }
  }
  
}

#endif // CODEMINES_UTILITY_HEADER_INCLUDED_
