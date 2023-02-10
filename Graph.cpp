#include "Graph.h"

Graph::Graph()
{

}
bool Graph::OnCreate(vector<Node*> nodes_)
{
	// given a list of nodes, initialize a matrix of costs with 0.0f weights
	int numNodes = nodes_.size();
	cost.resize(numNodes);

	for (int i = 0; i < numNodes; i++)
	{
		// add nodes to the internal list (set up mapping of nodes)
		if (i != nodes_[i]->getLabel())
		{
			std::cerr << " Node with label 'i' not in the 'i' position for" << i << endl;
			return false;
		}
		// nodes_[i]->label might not be i
		node[i] = nodes_[i];

		// Set up the connections
		cost[i].resize(numNodes);


		for (int j = 0; j < numNodes; j++)
		{
			// initialize coneection
			cost[i][j] = 0.0f;

		}
	}
	return true;
}



Graph::~Graph()
{
	// Node instances are created (new) elsewhere, another class is responsible for the memory clean up
}

int Graph::numNodes()
{
	return node.size();
}

void Graph::addWeightConnection(int fromNode, int toNode, float weight)
{
	// [i][j]
	cost[fromNode][toNode] = weight;
}

vector<int> Graph::neighbours(int fromNode)
{
	//declare and initialize empty set of int
	vector<int> result = {};
	for (int j = 0; j < numNodes(); j++)
	{
		if (cost[fromNode][j] > 0.0f)
		{
			result.push_back(j);
		}
	}
	return result;
}

vector<int> Graph::Dijkstra(int start, int goal)
{
	return {};
}
