# Project: CodeMines
# Makefile created by Peter Schultz

CXX = g++
OBJ = GameEngine.o GameTiles.o InputOutput.o Main.o Types.o
AUXOBJ = InputOutputColor.o
BIN = CodeMines.x86.bin
PPCOLOR = -DCODEMINES_GAME_USE_COLOR_VERSION_
PPWIN32 = -DEXTREME_CPP_STREAM_COLORS_USE_WINDOWS_FUNCTIONS_
PPLINUX = -DEXTREME_CPP_STREAM_COLORS_USE_EMCA_ESCAPE_SEQUENCES_
CXXFLAGS = -Wall -Wextra -ansi -pedantic -fexceptions -fexpensive-optimizations -O3

%.o: %.cpp

all: codemines

clean:
	rm -f $(OBJECTS)

distclean: clean
	rm -f codemines

codemines: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o codemines $(OBJECTS)
