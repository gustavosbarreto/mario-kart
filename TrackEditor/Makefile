CC		= g++
CFLAGS	= -Wall -pipe -g -W -O2 
LDFLAGS	= $(shell pkg-config --libs sdl2 SDL2_ttf SDL2_image)
SOURCES	= \
	../Common/allegro.cpp			\
	../Common/AllegroSystem.cpp		\
	../Common/AllegroScreen.cpp		\
	../Common/AllegroKeyboard.cpp	\
	../Common/SuperMode7.cpp		\
	../Common/ObjectSize.cpp		\
	../Common/Track.cpp				\
	../Game/Camera.cpp			    \
	main.cpp

EXECUTABLE	= editor

all: 
	$(CC) TrackEditor.cpp -o $(EXECUTABLE) $(CFLAGS) -I../Common/ -I../Game $(shell pkg-config --cflags sdl2 SDL2_ttf SDL2_image) $(SOURCES) $(LDFLAGS)

clean:
	rm -rf *.o *.dSYM
	rm -f $(EXECUTABLE)