// Project 5

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
		void findPathRecursive(int i, int j, graph g);
		void findPathNonRecursive(int i, int j, graph g);
        
private:
        int rows; // number of rows in the maze
        int cols; // number of columns in the maze
        
        matrix<bool> value;
        matrix<int> map;      // Mapping from maze (i,j) values to node index values
};