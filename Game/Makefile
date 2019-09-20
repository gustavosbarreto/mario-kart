CC		= g++
CFLAGS	= -c -Wall -pipe -g -W -O2
LDFLAGS	= $(shell pkg-config --libs allegro)

SOURCES	= \
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
	$(CC) $(CFLAGS) -c $< -o $@ -I../Common/ 

clean:
	rm -f *.o
	rm -f $(EXECUTABLE)
