# Project: CodeMines
# Version: 2.0.1 Linux
# Makefile created by Peter Schultz

SOURCES = Makefile Main.cpp InputOutput.hpp InputOutput.cpp InputOutputColor.hpp InputOutputColor.cpp StreamColors.hpp GameEngine.hpp GameEngine.cpp GameTiles.hpp GameTiles.cpp Types.hpp Types.cpp
OBJECTS = GameEngine.o GameTiles.o InputOutput.o Main.o Types.o InputOutputColor.o

PROJECT = codemines
BIN = CodeMines.x86.app

PPLINUX = -DCODEMINES_GAME_USE_COLOR_VERSION_
CXXWARNINGS = -Wall -Wextra -Wfloat-equal -Wundef -Wshadow
CXXFLAGS = $(PPLINUX) $(CXXWARNINGS) -ansi -pedantic -fexceptions -fexpensive-optimizations -O3

all: $(PROJECT)

rebuild: distclean $(PROJECT)

clean:
	rm -f $(OBJECTS)

distclean: clean
	rm -f $(BIN)

$(PROJECT): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(BIN)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# custom stuff I find handy (but you may not)
open:
	gedit $(SOURCES) &

