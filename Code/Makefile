GOAL = shoot_training
CC = gcc
FLAGS = -lm
OGL = -lGL -lGLU -lglut

$(GOAL): main.o rifle.o func.o hands.o image.o
	$(CC) -o $@ $^ $(FLAGS) $(OGL)

main.o: main.c rifle.h rifle.c func.h func.c hands.c hands.h image.c image.h
	$(CC) -o $@ $< -c

rifle.o: rifle.c rifle.h
	$(CC) -o $@ $< -c

func.o: func.c func.h
	$(CC) -o $@ $< -c

hands.o: hands.c hands.h
	$(CC) -o $@ $< -c

image.o: image.c image.h
	$(CC) -o $@ $< -c

.PHONY:
	clean

clean:
	rm -rf $(GOAL) *.o