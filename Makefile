#
# Makefile for game using Dragonfly
#
# Copyright Mark Claypool and WPI, 2016-2025
#
# 'make' to build executable
# 'make depend' to generate new dependency list
# 'make clean' to remove all constructed files
#
# Variables of interest:
#   GAMESRC is the source code files for the game
#   GAME is the game main() source
#   EXECUTABLE is the name of the runnable game
#   ENG is the name of the Dragonfly engine
#

# Compiler and SFML settings.
CC= g++ 
SFML_VERSION= 3.1.0


# Update libraries and includes to location of engine.
LINKDIR= -L/home/williamr/'WPI Folder'/'IMGD 3000'/Project1/lib # path to dragonfly library
INCDIR= -I/home/williamr/'WPI Folder'/'IMGD 3000'/Project1/include # path to dragonfly includes

### Update below if using local SFML installation.
LOCALSFML= $(HOME)/src/SFML-$(SFML_VERSION)
LINKDIR:= $(LINKDIR) -L/usr/local/lib
INCDIR:= $(INCDIR) -I/usr/local/include

CFLAGS= -std=c++17

## 1) For Linux:
ENG= dragonfly-x64-linux
CFLAGS:= $(CFLAGS) -Wall
LINKLIB= -l$(ENG) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lrt

######

GAMESRC= \

GAME= game.cpp 
EXECUTABLE= game
OBJECTS= $(GAMESRC:.cpp=.o)

.PHONY: all clean

all: $(EXECUTABLE) Makefile

$(EXECUTABLE): $(OBJECTS) $(GAME) $(GAMESRC) 
	$(CC) $(CFLAGS) $(GAME) $(OBJECTS) -o $@ $(INCDIR) $(LINKDIR) $(LINKLIB) 

.cpp.o: 
	$(CC) $(CFLAGS) -c $< -o $@ $(INCDIR)

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) core dragonfly.log Makefile.bak *~
