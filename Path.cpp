#include "Path.h"

Path::Path(vector<Node*> nodes_)
{
	nodes = nodes_;
	currentNode = 0;// initialize current node to be the first in the nodes vector
}

void Path::incrementCurrentNode()
{
	// increment current node while in range
	if (!nodes.empty() && currentNode < nodes.size() - 1)
	{
		currentNode++;
	}
}

// make sure node vector is not empty before trying to retrieve the position
Vec3 Path::getCurrentNodePos() {
	if (!nodes.empty()) {
		return nodes[currentNode]->getPosition();
	}
	else {
		// handle the case when the vector is empty, e.g. return a default position
		cout << "Cannot retrieve current Node Position. Vector of nodes in path may be empty" << endl;
		return Vec3(0, 0, 0);
	}
}