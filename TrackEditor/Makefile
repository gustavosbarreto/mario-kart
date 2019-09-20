CC		= g++
CFLAGS	= -Wall -pipe -g -W -O2
LDFLAGS	= $(shell allegro-config --libs)
SOURCES	= \
	../Common/AllegroSystem.cpp		\
	../Common/AllegroScreen.cpp		\
	../Common/AllegroKeyboard.cpp	\
	../Common/SuperMode7.cpp		\
	../Common/ObjectSize.cpp		\
	../Common/Track.cpp				\
	../Game/Camera.cpp			    \
	main.cpp						\
	TrackEditor.h

EXECUTABLE	= editor

all: 
	$(CC) TrackEditor.cpp -o $(EXECUTABLE) $(CFLAGS) -I../Common/ -I../Game $(SOURCES) $(LDFLAGS)

clean:
	rm -f *.o
	rm -f $(EXECUTABLE)