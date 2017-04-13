//seprod5a
//File: graph class header file
//This file has the data members and all of the member functions
//for the graph class that handles everything related to the graph
#include <iostream>
#include <fstream>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <stack>
#include "node.h"
#include "edge.h"

using namespace std;

typedef int WeightType;
typedef int NodeType;

int const MaxNumNodex = 9999;

typedef int NodeWeight;
typedef int EdgeWeight;


class graph
{
  public:
   graph();
	//constructor that creates empty graph
   graph(int n);
	//creates a graph that has n nodes and no edges
   graph(ifstream &fin);
	//constructs a new graph from fin
   graph(const graph &);
	//graph copy constructor
   graph &operator=(const graph &);  
	//graph assignment operator

   void addEdge(int i, int j, NodeWeight w = 0);
	//adds an edge to a graph
   void removeEdge(int i, int j);
	//removes an edge from a graph

   int addNode(NodeWeight w = 0);
	//adds a node to a graph with weight w
   int addNode(node n);
	//adds a copy of the node

   void setEdgeWeight(int i, int j, EdgeWeight w = 0);
	//sets the edge weight of specific node to weight w
   EdgeWeight getEdgeWeight(int i, int j) const;
	//gets the weight of an edge

   NodeWeight getTotalNodeWeight();
	//gets the total weight of a node
   EdgeWeight getTotalEdgeWeight();
	//gets the total weight of an edge

   void setNodeWeight(int i, NodeWeight w = 0);
	//sets the weight of a node i to weight w
   NodeWeight getNodeWeight(int i) const;
	//gets the weight of node i

   bool isEdge(NodeType i, NodeType j) const;
	//returns true if there is an edge from i to j
   int numNodes() const;
	//the number of nodes in a graph
   int numEdges() const;
	//returns the number of edges
   
   node &getNode(int);
   const node &getNode(int) const;
   edge &getEdge(int i,int j);
   const edge &getEdge(int i, int j) const;

   void printNodes() const;
	//prints all of the nodes
   void printEdges() const;
	//prints all of the edges

   void mark(int i);
	//makrs node i
   void mark(int i, int j);
	//marks edge i, j
   void unMark(int i);
	//marks node i
   void unMark(int i, int j);
	//unmarks node i, j
   bool isMarked(int i) const;
	//if a node is marked
   bool isMarked(int i, int j) const;
	//if edge i, j is marked
   void clearMark();
	//clears a mark
   bool allNodesMarked();
	//if all of the nodes in a graph are marked

   void visit(int i);
	//visits node i
   void visit(int i, int j);
	//visits edge i, j
   void unVisit(int i);
	//unvisits node i
   void unVisit(int i, int j);
	//unvisits node i, j
   bool isVisited(int i, int j) const;
	//if an edge i, j is visited
   bool isVisited(int i) const;
	//if a node i is visited
   void clearVisit();
	//clears all visits
   bool allNodesVisited();
	//if all nodes are visited

  private:
   matrix<edge> edges;
   vector<node> nodes;
   int NumEdges;

};
