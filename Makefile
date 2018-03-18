CXX=g++

CXXFLAGS= -std=c++17 -Wall -g

all: main

main: main.o avl.o Tree25.o
	g++ -o main main.o avl.o Tree25.o -lstdc++fs 	

main.o: main.cpp

avl.o: avl.cpp

Tree25.o: Tree25.cpp

clean:
	rm -rf *.o main output.txt
