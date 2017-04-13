// Project 5
// seprod5a
// File: Maze header file. This file is the maze class 
// with all of its data member and member function declarations

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include "graph.h"

using namespace std;

class maze
{
public:
        maze(ifstream &fin);
        void print(int,int,int,int);
        bool isLegal(int i, int j);
        
        void setMap(int i, int j, int n);
        int getMap(int i, int j) const;
        void mapMazeToGraph(graph &g);
		//maps the maze to a graph with vertices and edges
        void findPathRecursive(int i, int j, graph &g);
		//finds a path to finish the maze recursively
        void findPathNonRecursive(int i, int j, graph &g);
		//finds a path to finish the maze iteratively
        int getRows();
		//gets the number of rows
        int getCols();
		//gets the number of columns
        void printDirectionsNonRecursive();
		//prints the directions of the non-recursive maze
        
private:
        int rows; // number of rows in the maze
        int cols; // number of columns in the maze
        
        matrix<bool> value;
        matrix<int> map;      // Mapping from maze (i,j) values to node index values
        matrix<int> adjMat;     //adjacency matrix
        stack<node> s;
};