#include <iostream>
#include <fstream>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <stack>

using namespace std;

typedef int WeightType;
typedef int NodeType;

int const MaxNumNodex = 9999;

typedef int NodeWeight;
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

private:
	int source;
	int dest;
	EdgeWeight weight;
	bool valid;         // equals true if edge is valid, otherwise the
	bool visited;
	bool marked;
	// edge is invalid
};
