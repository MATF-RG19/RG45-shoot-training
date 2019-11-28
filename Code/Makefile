GOAL = shoot_training
CC = gcc
FLAGS = -lm
OGL = -lGL -lGLU -lglut

$(GOAL): main.o rifle.o
	$(CC) -o $@ $^ $(FLAGS) $(OGL)

main.o: main.c rifle.h rifle.c
	$(CC) -o $@ $< -c

rifle.o: rifle.c rifle.h
	$(CC) -o $@ $< -c

.PHONY:
	clean

clean:
	rm -rf $(GOAL) *.o
