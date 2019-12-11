GOAL = shoot_training
CC = gcc
FLAGS = -lm
OGL = -lGL -lGLU -lglut

$(GOAL): main.o rifle.o func.o
	$(CC) -o $@ $^ $(FLAGS) $(OGL)

main.o: main.c rifle.h rifle.c func.h func.c
	$(CC) -o $@ $< -c

rifle.o: rifle.c rifle.h
	$(CC) -o $@ $< -c

func.o: func.c func.h
	$(CC) -o $@ $< -c


.PHONY:
	clean

clean:
	rm -rf $(GOAL) *.o
