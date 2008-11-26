CC		= g++
CFLAGS	= -c#-c -Wall -pipe -g -W -O2
LDFLAGS	= $(shell allegro-config --frameworks)
SOURCES	= \
	../Common/AllegroSystem.cpp		\
	../Common/AllegroScreen.cpp		\
	../Common/AllegroKeyboard.cpp	\
	../Common/SuperMode7.cpp		\
	../Common/ObjectSize.cpp		\
	../Common/Track.cpp				\
	../Common/Camera.cpp			\
	main.cpp						\
	TrackEditor.cpp

OBJECTS		= $(SOURCES:.cpp=.o)
EXECUTABLE	= TrackEditor

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ -I../Common/

clean:
	rm *.o

distclean: clean
	rm -f TrackEditor