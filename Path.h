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

	// tracks progress of character along path
	int currentNode = 0; 

public:
	Path(vector<Node*> nodes_);
	~Path() {};

	// incrememnts the currentNode while still in the valid list of nodes
	void incrementCurrentNode();

	// returns the x, y values of the node position created in the scene (the pos of the middle of each tile)
	Vec3 getCurrentNodePos() { return nodes[currentNode]->getPosition(); } 
};
#endif;