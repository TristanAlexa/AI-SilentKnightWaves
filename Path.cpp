#include "Path.h"

Path::Path()
{
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
