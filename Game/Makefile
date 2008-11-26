CC		= g++
CFLAGS	= -c#-c -Wall -pipe -g -W -O2
LDFLAGS	= $(shell allegro-config --frameworks)
SOURCES	= \
	AllegroSystem.cpp		\
	AllegroScreen.cpp		\
	AllegroKeyboard.cpp		\
	main.cpp 				\
	Game.cpp				\
	Player.cpp				\
	Camera.cpp				\
	Track.cpp				\
	SuperMode7.cpp			\
	ObjectSize.cpp			\
	ObjectPoint.cpp

OBJECTS		= $(SOURCES:.cpp=.o)
EXECUTABLE	= newgame

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o
