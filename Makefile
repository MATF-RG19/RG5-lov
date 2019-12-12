PROGRAM = Lov
CC      = gcc
CFLAGS  = -g -ansi -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): main.o image.o models.o
	$(CC) $(LDFLAGS) -o $(PROGRAM) image.o main.o models.o $(LDLIBS)

.PHONY: clean dist

models.o: models.c models.h
	$(CC) $(CFLAGS) -c models.c -o models.o

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
