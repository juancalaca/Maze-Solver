//seprod5a
//File: edge class header file
//this file handles the edge class and all of its data members
//and member functions
//(class was separated from original graph.h header file for clarity
#include <iostream>

using namespace std;

typedef int EdgeWeight;


class edge
{
public:
	edge();
	edge(int, int, EdgeWeight = 0);
	edge(const edge &);
	edge &operator=(const edge &);

	void setWeight(EdgeWeight);
	EdgeWeight getWeight() const;

	int getSource() const;
	int getDest() const;

	void setValid();
	void setInvalid();
	bool isValid() const;

	void mark();
	void unMark();
	bool isMarked() const;

	void visit();
	void unVisit();
	bool isVisited() const;

	void setEdge(int, int, EdgeWeight);
        friend ostream &operator<<(ostream &ostr, const edge &e);

private:
	int source;
	int dest;
	EdgeWeight weight;
	bool valid;         // equals true if edge is valid, otherwise the
	bool visited;
	bool marked;
	// edge is invalid
};
