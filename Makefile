CXX=g++

CXXFLAGS= -std=c++17 -Wall -g

all: main

main: main.o AVL.o Tree25.o
	g++ -o main main.o AVL.o Tree25.o -lstdc++fs

main.o: main.cpp

AVL.o: AVL.cpp

Tree25.o: Tree25.cpp

clean:
	rm -rf *.o main output.txt
