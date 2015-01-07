CFLAGS=-Wall -g

all: ex19 othergame

othergame: object.o lib.o

ex19: object.o lib.o

test: clean all
	./test

clean:
	rm -f ex19
	rm -f othergame
	rm object.o
	rm lib.o
