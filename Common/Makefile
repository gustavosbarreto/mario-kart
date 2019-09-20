CC		= g++
CFLAGS	= -c -Wall -pipe -g -W -O2
INC	= $(shell pkg-config --cflags allegro)
LIB	= $(shell pkg-config --libs allegro)

all: 
	$(CC) $(CFLAGS) *.cpp $(INC) $(LIB)

clean:
	rm -f *.o