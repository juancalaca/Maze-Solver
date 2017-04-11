#include "maze.h"

void maze::setMap(int i, int j, int n)
// Set mapping from maze cell (i,j) to graph node n. 
{
}

//int maze ::getMap(int i, int j) const
// Return mapping of maze cell (i,j) in the graph.
//{
//}

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
   fin >> rows;
   fin >> cols;

   char x;

   value.resize(rows,cols);
   for (int i = 0; i <= rows-1; i++)
      for (int j = 0; j <= cols-1; j++)
      {
	 fin >> x;
	 if (x == 'O')
            value[i][j] = true;
	 else
	    value[i][j] = false;
      }

   map.resize(rows,cols);
}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
   cout << endl;

   if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
      throw rangeError("Bad value in maze::print");

   if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
      throw rangeError("Bad value in maze::print");

   for (int i = 0; i <= rows-1; i++)
   {
      for (int j = 0; j <= cols-1; j++)
      {
	 if (i == goalI && j == goalJ)
	    cout << "*";
	 else
	    if (i == currI && j == currJ)
	       cout << "+";
	    else
	       if (value[i][j])
		  cout << " ";
	       else
		  cout << "X";	  
      }
      cout << endl;
   }
   cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze.
{
   if (i < 0 || i > rows || j < 0 || j > cols)
      throw rangeError("Bad value in maze::isLegal");

   return value[i][j];
}

void maze::mapMazeToGraph(graph &g)
// Create a graph g that represents the legal moves in the maze m.
{
        for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                        if (value[i][j])
                                map[i][j] = g.addNode();
        
        for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                        if (value[i][j])
                        {
                                if ((i - 1) > 0 && map[i - 1][j] > 0)
                                        g.addEdge(map[i][j], map[i - 1][j]);
                                
                                if ((i + 1) < rows && map[i + 1][j] > 0)
                                        g.addEdge(map[i][j], map[i + 1][j]);
                                
                                if ((j - 1) > 0 && map[i][j - 1] > 0)
                                        g.addEdge(map[i][j], map[i][j - 1]);
                                
                                if ((j + 1) < cols && map[i][j + 1])
                                        g.addEdge(map[i][j], map[i][j + 1]);
                        }
}

void maze::findPathNonRecursive(int i, int j, graph g)
//find a path from the start to the end using a non-recursive method (stack)
{
	

}
