//seprod5a
//File: node class header file
//this file contains all of the function declarations for the node class
//that handles manipulating nodes
#include <iostream>
#include "d_except.h"

using namespace std;

typedef int NodeWeight;


class node
{
public:
	node();
	//node constructor
	node(const node &);
	//node copy constructor
	node &operator=(const node &);
	//overloaded assignment operator

	void setId(int i);
	//sets the ID of a node
	int getId() const;
	//gets the ID of a node

	void setWeight(NodeWeight);
	//sets the weight of a node
	NodeWeight getWeight() const;
	//gets the weight of a node

        void setNode(int id, NodeWeight w = 0, bool m = false, bool v = false);
		//initializes a node

	void mark();
	//marks a node
	void unMark();
	//unmarks a node
	bool isMarked() const;
	//if the node is marked

	void visit();
	//sets visit to true
	void unVisit();
	//sets visit to false
	bool isVisited() const;
	//if the node has been visited or not
        
        friend ostream &operator<<(ostream &ostr, const node &n);
        
        friend bool operator<(const node &lhs, const node &rhs);

private:
	int id;
	NodeWeight weight;
	bool marked;
	bool visited;
};
