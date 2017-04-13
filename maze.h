// Project 5
// seprod5a
//
// File: Maze header file. This file is the maze class 
// with all of its data member and member function declarations. This class
// maps a maze to a graph object and uses the DFS non-recursive and recursive
// approach to reach exit which is defined as the right hand lower corner.
// It also prints the path to exit, if found, frame by frame as well as directions.

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include "graph.h"
#include <vector>

using namespace std;

class maze
{
public:
        maze(ifstream &fin);
                //initializes maze by reading values from fin
        void print(int,int,int,int);
                //prints out maze with goal and current cell marked
        bool isLegal(int i, int j);
                //return the value stored at the (i,j) entry in the maze
        void mapMazeToGraph(graph &g);
		//maps the maze to a graph with vertices and edges
        void findPathNonRecursive(int i, int j, graph &g);
		//finds a path to finish the maze iteratively
        void initializePathRecursive(int i, int j, graph &g);
                //helper function to find path recursively
        void findPathRecursive(node x, graph &g, bool &found);
                //finds a path to finish the maze recursively
        void printPathNonRecursive();
		//prints the directions of the non-recursive maze
        void printPathRecursive(int,int);
                //prints the directions of the found path using recursive approach
        bool Found() {return found;};
                //returns data member found
        
private:
        int rows; // number of rows in the maze
        int cols; // number of columns in the maze
        
        matrix<bool> value;     // Cell information for possible maze paths
        matrix<int> map;        // Mapping from maze (i,j) values to node index values
        stack<node> s;          // stack for non-recursive path find approach
        vector<int> pred;       // hold predecessor information to reconstruct path
        bool found;             // bool variable becomes true when exit is found
};