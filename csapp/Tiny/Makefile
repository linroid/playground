CC = gcc
CFLAGS = -O2 -Wall -I .

LIB = -lpthread

all: tiny cgi

tiny: main.c io.c tiny.c http.c
	$(CC) $(CFLAGS) -o tiny main.c io.c tiny.c http.c $(LIB)

cgi:
	(cd cgi-bin; make)

clean:
	rm -f *.o tiny *~
	(cd cgi-bin; make clean)

