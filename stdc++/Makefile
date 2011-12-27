# Project: CodeMines
# Version: 2.0.2 Standard C++
# Makefile created by Peter Schultz

PROJECT = codemines

SOURCES = Makefile Main.cpp InputOutput.hpp InputOutput.cpp GameEngine.hpp GameEngine.cpp GameTiles.hpp GameTiles.cpp Types.hpp Types.cpp
OBJECTS = GameEngine.o GameTiles.o InputOutput.o Main.o Types.o 

BIN = CodeMines.x86.app

CXXWARNINGS = -Wall -Wextra -Wfloat-equal -Wundef -Wshadow
CXXFLAGS = $(CXXWARNINGS) -ansi -pedantic -fexceptions -fexpensive-optimizations -O3

all: $(PROJECT)

rebuild: distclean $(PROJECT)

clean:
	rm -f $(OBJECTS)

distclean: clean
	rm -f $(BIN)

codemines: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(BIN)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# custom stuff I find handy (but you may not)
open:
	gedit $(SOURCES) &

