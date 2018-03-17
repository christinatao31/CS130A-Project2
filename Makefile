CXX=g++

CXXFLAGS= -std=c++1z -Wall -g

all: main

main: main.o avl.o
	g++ -o main main.o avl.o -lstdc++fs 	

main.o: main.cpp

avl.o: avl.cpp

clean:
	rm -rf *.o main output.txt
