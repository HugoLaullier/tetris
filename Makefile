CC=g++
CFLAGS= $(shell sdl2-config --cflags)
LDFLAGS=  $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_mixer

INCLUDE_PATH = ./include

TARGET   = tetris

SRCDIR   = src
OBJDIR   = obj

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.hpp)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(TARGET): $(OBJECTS)
	$(CC) -o tetris $^ $(CFLAGS) $(LDFLAGS)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)

.PHONY : clean
clean:
	rm -f tetris
	rm -rf *.o
	rm -r obj
