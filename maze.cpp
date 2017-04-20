// Project 5
// seprod5b
//
// File: Maze function declaration file. This file contains all the
// defined functions of class maze.

#include "maze.h"

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
        // add node if cell (i,j) is a legal cell in maze
        // store node index in map matrix
        for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                        if (value[i][j])
                                map[i][j] = g.addNode();
        
        // add edge if move is legal and within boundaries of maze
        for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                        if (value[i][j])
                        {
                                // move up
                                if ((i - 1) >= 0 && value[i-1][j])
                                        g.addEdge(map[i][j], map[i - 1][j]);
                                
                                // move down
                                if ((i + 1) < rows && value[i+1][j])
                                        g.addEdge(map[i][j], map[i + 1][j]);
                                
                                // move left
                                if ((j - 1) >= 0 && value[i][j-1])
                                        g.addEdge(map[i][j], map[i][j - 1]);
                                
                                // move right
                                if ((j + 1) < cols && value[i][j+1])
                                        g.addEdge(map[i][j], map[i][j + 1]);
                        }
}

void maze::findPathNonRecursive(int i, int j, graph &g)
//find a path from the start to the end using a non-recursive method (stack)
{
        if (i < 0 || i > rows || j < 0 || j > cols)
                throw rangeError("Bad value in maze::findPathNonRecursive");
        
        // clear stack s for path
        while(!s.empty())
                s.pop();
        
        g.clearVisit();                 // unvisit all nodes
        s.push(g.getNode(map[i][j]));   // push starting node into stack
        g.visit(map[i][j]);             // visit starting node
        found = false;                  // initialize found
        
        // find paths until found or stack is empty
        while (!s.empty() || !found)
        {
                bool shPop = true; // bool should pop if no unvisited neighbors or no neighbors
                node v = s.top();  // current node
                
                // check if target node is reached
                if (v.getId() == map[rows-1][cols-1])
                {
                        found = true;
                        break;
                        
                }
                
                // find neighbors of v
                int nodeId = v.getId();
                for (int i = 0; i < g.numNodes(); i++)
                {
                        node test = g.getNode(i);
                        if (g.isEdge(nodeId, i))
                        {
                                node w = g.getNode(i);
                                
                                // unvisited neighbor
                                if (!w.isVisited())
                                {
                                        s.push(w); // push into stack
                                        g.visit(w.getId()); // visitnode
                                        i = g.numNodes(); // break for loop
                                        shPop = false; // should pop false because v has neighbor
                                }
				
                        }
                }
                
                if (shPop) s.pop(); // pop if no neighbors or no unvisited neighbors
        }

        // print directions if found otherwise no path
        if (found)
        {
                printPathNonRecursive();
        }
        else // empty stack and print
        {
                cout << "No path was found" << endl;
                while (!s.empty()) s.pop(); // empty stack
        }
        
        
}

void maze::initializePathRecursive(int i, int j, graph &g)
// helper function initializes parameters for finding path recursively
{
        // check if starting node is legal
        if (i < 0 || i > rows || j < 0 || j > cols)
                throw rangeError("Bad value in maze::initializePathRecursive");
        
        g.clearVisit(); // unvisit all nodes
        pred.resize(g.numNodes()); // resize vector pred to fit all nodes
        node startingNode = g.getNode(map[i][j]); // get starting node
        found = false; // initially target not found
        findPathRecursive(startingNode, g, found); // start recursive path
}

void maze::findPathRecursive(node x, graph &g, bool &found)
//solves the maze recursively
{
        int nodeId = x.getId(); // store id of current node x
        
        // base case: current node x is target node
        if (nodeId == map[rows-1][cols-1])
        {
                found = true;
                return;
        }
        else
        {
                g.visit(nodeId); // visit current node x
                // find all neighbors of node x
                for (int i = 0; i < g.numNodes(); i++)
                {
                        if (g.isEdge(nodeId, i))
                        {
                                node w = g.getNode(i);
                                
                                // unvisited neighbor
                                if (!w.isVisited() && !found)
                                {
                                        pred[w.getId()] = nodeId; // store predecessor information
                                        
                                        //call findPathRecursive on unvisited node w neighbor of node x
                                        findPathRecursive(w, g, found);
                                }
                                
                        }
                }
                
        }
        
}

void maze::printPathNonRecursive()
//prints the directions that solve the maze
{
        stack<node> path; // stack that stores nodes in order of path
        stack<node> directions; // stack that stores nodes in order of path

        // empty stack s
        // store path from starting node (top element in path) to target node in stack path
        while (!s.empty())
        {
                path.push(s.top());
                directions.push(s.top());
                s.pop();
        }
        
        
        cout << "------------------------------------------------------" << endl;
        cout << "                        PATH DIRECTIONS" << endl;
        
        // print directions
        while (!directions.empty())
        {
                node v = directions.top();
                directions.pop();
                if (directions.empty()) break;
                node w = directions.top();
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
                                                r = rows;
                                                c = cols;
                                        }
                }
                
                if ((i - 1) > 0 && map[i - 1][j] == w.getId())
                        cout << "Go up" << endl;
                
                if ((i + 1) < rows && map[i + 1][j] == w.getId())
                        cout << "Go down" << endl;
                
                if ((i - 1) > 0 && map[i][j - 1] == w.getId())
                        cout << "Go left" << endl;
                
                if ((i + 1) < cols && map[i][j + 1] == w.getId())
                        cout << "Go right" << endl;
                
        }
        
        cout << "------------------------------------------------------" << endl;
        cout << "                        PATH" << endl;
        
        // print path
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
                                                r = rows;
                                                c = cols;
                                        }
                }
                
                print(rows - 1, cols - 1, i, j);
        }
}

void maze::printPath(int sI, int sJ)
// prints frame by frame of path
// parameter (sI,sJ) indices of starting node for path
// precondition: pred vector is populated with path information
{
        stack<int> path; // stack that stores node indices in order of path
        stack<int> directions; // stack that stores node indices in order of path
        int i = pred.size() - 1; // initialize i with index of target in pred vector
        path.push(map[rows-1][cols-1]); // first push into stack target node index
        
        // reconstruct path from pred vector information
        // until we reach starting node
        while (path.top() != map[sI][sJ])
        {
                path.push(pred[i]); // push index into stack
                directions.push(pred[i]); // push index into stack
                i = path.top();     // check predecessor of pushed node index
        }
        
        cout << "------------------------------------------------------" << endl;
        cout << "               PATH DIRECTIONS" << endl;
        
        //print directions
        int r, c;
        while (!directions.empty())
        {
                i = directions.top();
                directions.pop();
                int w;
                if (directions.empty())
                {
                        w = map[rows-1][cols-1];
                }
                else
                        w = directions.top();
                if (i == 0)
                {
                        r = 0;
                        c = 0;
                }
                else
                {
                        for (int k = 0; k < rows; k++)
                                for (int l = 0; l < cols; l++)
                                        if (map[k][l] == i)
                                        {
                                                r = k;
                                                c = l;
                                                l = cols;
                                                k = rows;
                                        }
                }
                
                if ((r - 1) > 0 && map[r - 1][c] == w)
                        cout << "Go up" << endl;
                
                if ((r + 1) < rows && map[r + 1][c] == w)
                        cout << "Go down" << endl;
                
                if ((c - 1) > 0 && map[r][c - 1] == w)
                        cout << "Go left" << endl;
                
                if ((c + 1) < cols && map[r][c + 1] == w)
                        cout << "Go right" << endl;
        }
        
        // print path
        cout << "------------------------------------------------------" << endl;
        cout << "                        PATH" << endl;
        while (!path.empty())
        {
                i = path.top();
                path.pop();
                if (i == 0)
                {
                        r = 0;
                        c = 0;
                }
                else
                {
                        for (int k = 0; k < rows; k++)
                                for (int l = 0; l < cols; l++)
                                        if (map[k][l] == i)
                                        {
                                                r = k;
                                                c = l;
                                                l = cols;
                                                k = rows;
                                        }
                }
                
                print(rows - 1, cols - 1, r, c);
        }
}

bool maze::findShortestPath1(int startR, int startC, int destR, int destC, graph &g)
//find shortest path using BFS algorithm
//parameters startR and startC, coordinates of starting node
//parameters endR and endC, coordingates of target node
{
        queue<node> q;
        g.clearVisit();                         //unvisit all nodes
        q.push(g.getNode(map[startR][startC])); //push starting node into queue q
        g.visit(map[startR][startC]);           //visit starting node
        pred.resize(g.numNodes());              //reset pred vector
        
        //run BFS until queue empty or target found
        while (!q.empty())
        {
                node v = q.front(); // get front node
                
                // find all neighbors of v
                for (int i = 0; i < g.numNodes(); i++)
                {
                        if (g.isEdge(v.getId(), i))
                        {
                                node w = g.getNode(i);
                                
                                //neighbor w is unvisited
                                if (!w.isVisited())
                                {
                                        q.push(w); //push into queue
                                        pred[w.getId()] = v.getId(); //store parent information
                                        g.visit(w.getId()); // visit node
                                        
                                        // target node found return true
                                        if (w.getId() == map[destR][destC])
                                        {
                                                return true;
                                        }
                                }
                        }
                }
                q.pop(); //pop queue
        }
        
        return false; // target not found
}

bool maze::findShortestPath2(int startR, int startC, int endR, int endC, graph &g)
//find shortest path using Dijkstra's algorithm
//parameters startR and startC, coordinates of starting node
//parameters endR and endC, coordingates of target node
{
        priority_queue<node> pq;
        pq.push(g.getNode(map[startR][startC])); //push starting node into priority queue
        
        //push all nodes into priority queue
        for (int i = 0; i < g.numNodes(); i++)
        {
                if (i == map[startR][startC]) continue; //starting node already pushed
                g.setNodeWeight(i, 9999999); //set all other node weights to "infinity"
                pq.push(g.getNode(i));  //push node into priority queue
        }
        pred.resize(g.numNodes()); //reset pred vector
        
        //run algorithm until pq empty or target found
        while (!pq.empty())
        {
                node v = pq.top(); //get top node
                pq.pop(); //pop top node
                
                if (v.getId() == map[endR][endC]) //target found
                        return true;
                else //target not found
                        g.visit(v.getId()); //visit top node
                
                        // find neighbors of node v
                        for (int i = 0; i < g.numNodes(); i++)
                        {
                                if (g.isEdge(v.getId(), i))
                                {
                                        node w = g.getNode(i);
                                        
                                        //neighbor w is unvisited
                                        if (!w.isVisited())
                                        {
                                                // update weight information
                                                int weight = min(w.getWeight(), v.getWeight() + g.getEdgeWeight(v.getId(), w.getId()));
                                                
                                                // if new shortest path change weight and parent info
                                                if (weight != w.getWeight())
                                                {
                                                        g.setNodeWeight(w.getId(), weight);
                                                        pred[w.getId()] = v.getId();
                                                        sortPriorityQueue(pq, g); //sort priority queue
                                                }
                                        }
                                }
                                
                        }
        }
        
        return false; //target not found
}

void maze::sortPriorityQueue(priority_queue<node> &pq, graph& g)
// sorts priority queue for Dijkstra's Algorithm purposes
{
        //empty queue
        while (!pq.empty())
                pq.pop();
        
        //fill in priority queue with unvisited nodes
        for (int i = 0; i < g.numNodes(); i++)
        {
                if (g.isVisited(i)) continue;
                pq.push(g.getNode(i));
        }
}