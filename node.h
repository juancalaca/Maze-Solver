#include <iostream>
#include "d_except.h"

using namespace std;

typedef int NodeWeight;


class node
{
public:
	node();
	node(const node &);
	node &operator=(const node &);

	void setId(int i);
	int getId() const;

	void setWeight(NodeWeight);
	NodeWeight getWeight() const;

        void setNode(int id, NodeWeight w = 0, bool m = false, bool v = false);

	void mark();
	void unMark();
	bool isMarked() const;

	void visit();
	void unVisit();
	bool isVisited() const;
        
        friend ostream &operator<<(ostream &ostr, const node &n);

private:
	int id;
	NodeWeight weight;
	bool marked;
	bool visited;
};
