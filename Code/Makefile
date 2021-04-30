GOAL = shoot_training
CC = g++
FLAGS = -lm
OGL = -lGL -lGLU -lglut

$(GOAL): main.o rifle.o func.o hands.o image.o
	$(CC) -o $@ $^ $(FLAGS) $(OGL)

main.o: main.cpp rifle.hpp rifle.cpp func.hpp func.cpp hands.cpp hands.hpp image.cpp image.hpp
	$(CC) -o $@ $< -c

rifle.o: rifle.cpp rifle.hpp
	$(CC) -o $@ $< -c

func.o: func.cpp func.hpp
	$(CC) -o $@ $< -c

hands.o: hands.cpp hands.hpp
	$(CC) -o $@ $< -c

image.o: image.cpp image.hpp
	$(CC) -o $@ $< -c

.PHONY:
	clean

clean:
	rm -rf $(GOAL) *.o