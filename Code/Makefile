PROGRAM 	= shoot_training
CC 			= gcc
CFLAGS 		= -g -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS 	= -lGL -lGLU -lglut -lm
LDLIBS 		= -L/usr/X11R6/lib -L/usr/pkg/lib

$(PROGRAM): main.o
	$(CC) $(LDLIBS) -o $(PROGRAM) main.o $(LDFLAGS)

.PHONY:beauty clean dist

beauty:
	-indent -kr -nut $(PROGRAM).c
	-rm *~ *BAK
clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)