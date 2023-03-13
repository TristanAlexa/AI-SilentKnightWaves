#include "Path.h"

Path::Path(const vector<Node*> nodes_)
{
	nodes = nodes_;
	currentNode = 0;
}

// Incrememnts the currentNode to evaluate while still in the valid list of nodes
void Path::incrementCurrentNode()
{
	if (!nodes.empty() && currentNode < nodes.size() - 1)
	{
		currentNode++;
	}
}

// Returns the x, y position values of the node currently being evaluated
Vec3 Path::getCurrentNodePos() {
	if (!nodes.empty()) {
		return nodes[currentNode]->getPosition();
	}
	else {
		return Vec3(0, 0, 0);
	}
}