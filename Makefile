CXXFLAGS = -Wall -Werror

all: graph.o node.o edge.o maze.o main.o
	g++ graph.o node.o edge.o maze.o main.o -o main

graph.o: d_matrix.h d_except.h node.h edge.h graph.cpp graph.h
	g++ $(CXXFLAGS) -c graph.cpp -o graph.o

node.o: d_except.h node.cpp node.h
	g++ $(CXXFLAGS) -c node.cpp -o node.o

edge.o: edge.cpp edge.h
	g++ $(CXXFLAGS) -c edge.cpp -o edge.o

maze.o: d_except.h d_matrix.h graph.h maze.cpp maze.h
	g++ $(CXXFLAGS) -c maze.cpp -o maze.o

main.o:	maze.h main.cpp
	g++ $(CXXFLAGS) -c main.cpp -o main.o

default: all

clean:
	rm *.o main
