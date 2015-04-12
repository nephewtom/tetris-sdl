CC=g++
CFLAGS=-c -DLINUX -I.
LDFLAGS=-lSDL -lSDL_gfx -lSDL_ttf
SOURCES=Main.cpp Game.cpp Board.cpp IO.cpp Pieces.cpp
OBJECTS=$(SOURCES:%.cpp=obj/%.o)
EXECUTABLE=tetris

all:	$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJECTS): | obj

obj:
	@mkdir -p $@

obj/%.o : %.cpp
	$(CC) $(CFLAGS) $< -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -rf obj $(EXECUTABLE)
