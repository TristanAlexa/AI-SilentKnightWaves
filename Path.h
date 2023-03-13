#ifndef PATH_H
#define PATH_H

#include <vector>
#include "MMath.h"
#include "Node.h"
using namespace std;
using namespace MATH;
class Path
{
private:
	vector<Node*> nodes; 
	int currentNode;

public:
	Path(const vector<Node*> nodes_);
	~Path() {}

	// Incrememnts the currentNode to evaluate while still in the valid list of nodes
	void incrementCurrentNode(); 

	// Returns the x, y position values of the node currently being evaluated
	Vec3 getCurrentNodePos();
};
#endif;