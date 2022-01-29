all: program

program: main.o Interpreter.o
	g++ -o program main.o Interpreter.o

main.o: main.cpp
	g++ -c main.cpp

Interpreter.o: Interpreter.cpp Interpreter.h
	g++ -c Interpreter.cpp

clean:
	rm *.o program