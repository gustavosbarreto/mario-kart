CC		= g++
CFLAGS	= -c -Wall -pipe -g -W -O2
INC	= $(shell pkg-config --cflags sdl2 SDL2_ttf)
LIB	= $(shell pkg-config --libs sdl2 SDL2_ttf)

all: 
	$(CC) $(CFLAGS) *.cpp $(INC) $(LIB)

clean:
	rm -f *.o