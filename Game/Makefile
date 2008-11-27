CC		= g++
CFLAGS	= -c#-c -Wall -pipe -g -W -O2
LDFLAGS	= $(shell allegro-config --frameworks)
SOURCES	= \
	../Common/AllegroSystem.cpp		\
	../Common/AllegroScreen.cpp		\
	../Common/AllegroKeyboard.cpp	\
	../Common/SuperMode7.cpp		\
	../Common/ObjectSize.cpp		\
	../Common/Vector.cpp			\
	Camera.cpp			\
	../Common/Track.cpp				\
	main.cpp 						\
	Game.cpp						\
	Player.cpp

OBJECTS		= $(SOURCES:.cpp=.o)
EXECUTABLE	= newgame

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ -I../Common/

clean:
	rm *.o

distclean: clean
	rm -f newgame
