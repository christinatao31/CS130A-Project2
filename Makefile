CXX=g++

CXXFLAGS= -std=c++1z -Wall -g

all: main

main: main.o AVL.o 
	g++ -o main main.o AVL.o 	

main.o: main.cpp

AVL.o: AVL.cpp

clean:
	rm -rf *.o main output.txt



	jun
excellent
near
airport
stayed
hotel
times
recently
th
may
find
luxurious