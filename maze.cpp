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
        adjMat.resize(rows, cols);
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
                                {
                                        g.addEdge(map[i][j], map[i - 1][j]);
                                        adjMat[i][j] = 1;
                                }
                                
                                if ((i + 1) < rows && map[i + 1][j] > 0)
                                {
                                        g.addEdge(map[i][j], map[i + 1][j]);
                                        adjMat[i][j] = 1;
                                }
                                
                                if ((j - 1) > 0 && map[i][j - 1] > 0)
                                {
                                        g.addEdge(map[i][j], map[i][j - 1]);
                                        adjMat[i][j] = 1;
                                }
                                
                                if ((j + 1) < cols && map[i][j + 1])
                                {
                                        g.addEdge(map[i][j], map[i][j + 1]);
                                        adjMat[i][j] = 1;
                                }
                        }
}

void maze::findPathNonRecursive(int i, int j, graph &g)
//find a path from the start to the end using a non-recursive method (stack)
{
        g.clearVisit();
        s.push(g.getNode(map[i][j]));
        g.visit(map[i][j]);
        bool found = false;
        
        while (!s.empty() || !found)
        {
                bool shPop = true;
                node v = s.top();
                if (v.getId() == map[rows-1][cols-1])
                {
                        found = true;
                        break;
                        
                }
                
                int nodeId = v.getId();
                for (int i = 0; i < g.numNodes(); i++)
                {
                        if (g.isEdge(nodeId, i))
                        {
                                node w = g.getNode(i);
                                if (!w.isVisited())
                                {
                                        s.push(w);
                                        g.visit(w.getId());
                                        i = g.numNodes();
                                        shPop = false;
                                }
				

				int I, J;	
                                if (nodeId == 0)
                                 {
                                 	I = 0;
                                 	J = 0;
                                 }
                                 else
                                 {
                                 	for (int r = 0; r < rows; r++)
                                 		for (int c = 0; c < cols; c++)
                                 			if (map[r][c] == nodeId)
                                 			{
                                 				I = r;
                                 				J = c;
                                 			}
                                 }
                                 
                                 if ((I - 1) > 0 && map[I - 1][J] == w.getId())
                                 cout << "Go up" << endl;
                                 
                                 if ((I + 1) < rows && map[I + 1][J] == w.getId())
                                 cout << "Go down" << endl;
                                 
                                 if ((J - 1) > 0 && map[I][J - 1] == w.getId())
                                 cout << "Go left" << endl;
                                 
                                 if ((J + 1) < cols && map[I][J + 1] == w.getId())
                                 cout << "Go right" << endl;
                        }
                }
                
                if (shPop) s.pop();
        }

        if (found) printDirectionsNonRecursive();
        
        
}

int maze::getCols()
//gets the number of columns
{
        return cols;
}

int maze::getRows()
//gets the number of rows
{
        return rows;
}

void maze::printDirectionsNonRecursive()
//prints the directions that solve the maze
{
        stack<node> path;
        
        while (!s.empty())
        {
                path.push(s.top());
                s.pop();
        }
        
        while (!path.empty())
        {
                node v = path.top();
                path.pop();
                int i, j;
                if (v.getId() == 0)
                {
                        i = 0;
                        j = 0;
                }
                else
                {
                        for (int r = 0; r < rows; r++)
                                for (int c = 0; c < cols; c++)
                                        if (map[r][c] == v.getId())
                                        {
                                                i = r;
                                                j = c;
                                        }
                }
                
                print(rows - 1, cols - 1, i, j);
        }
}

void maze::findPathRecursive(int &i, int j, graph g)
//sovles the maze recursively
{
	
		


}
