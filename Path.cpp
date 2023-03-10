#include "Path.h"

Path::Path(vector<Node*> nodes_)
{
	nodes = nodes_;
	currentNode = 0;
}

void Path::incrementCurrentNode()
{
	// increment current node while in range
	if (currentNode < nodes.size() - 1)
	{
		currentNode++;
	}
}
