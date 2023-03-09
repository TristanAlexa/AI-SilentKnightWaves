#include "Path.h"

Path::Path(){}

Path::Path(vector<Node*> nodes_)
{
	nodes = nodes_;
}

void Path::incrementCurrentNode(int currentNode_)
{
	// increment current node while in range
	if (currentNode_ < nodes.size() - 1)
	{
		currentNode_++;
	}
}
