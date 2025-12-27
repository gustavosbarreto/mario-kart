CC		= g++
CFLAGS	= -c -Wall -pipe -g -W -O2
LDFLAGS	= $(shell pkg-config --libs sdl2 SDL2_ttf SDL2_image)

SOURCES	= \
	../Common/allegro.cpp			\
	../Common/AllegroSystem.cpp		\
	../Common/AllegroScreen.cpp		\
	../Common/AllegroKeyboard.cpp	\
	../Common/SuperMode7.cpp		\
	../Common/ObjectSize.cpp		\
	../Common/Vector.cpp			\
	Camera.cpp						\
	../Common/Track.cpp				\
	main.cpp 						\
	Game.cpp						\
	Opponent.cpp					\
	Player.cpp

OBJECTS		= $(SOURCES:.cpp=.o)
EXECUTABLE	= game

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@ -I../Common/ $(shell pkg-config --cflags sdl2 SDL2_ttf SDL2_image)

clean:
	rm -f *.o ../Common/*.o
	rm -f $(EXECUTABLE)
