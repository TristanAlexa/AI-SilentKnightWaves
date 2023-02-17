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

// It will be useful for the A* pathfinding algorithm.
struct NodeAndPriority
{
public:

	// member variables
	Node* node;
	float priority;

	// constructors
	// We'll use the "universal" constructor when needed.
	// See: https://learn.microsoft.com/en-us/cpp/cpp/initializing-classes-and-structs-without-constructors-cpp?view=msvc-170
};

// create struct with one operation, for use in the comparisons needed by the priority queue
struct ComparePriority
{
	bool operator()(NodeAndPriority const& lhs, NodeAndPriority const& rhs)
	{
		// make it a min queue: lowest value of priority at top of the queue
		return lhs.priority > rhs.priority;
	}
};

vector<int> Graph::Dijkstra(int start, int goal)
{
	float new_cost;
	float priority;
	Node* current = node[start];

	// Set up priority queue
	priority_queue < NodeAndPriority, deque<NodeAndPriority>, ComparePriority> frontier;
	frontier.push(NodeAndPriority {current, 0.0f});

	// tracking solution path
	// Node with label 5 ====> Node[5]: intergers are the labels of the node
	vector<int> came_from;
	came_from.resize(numNodes());

	// cost so far storage
	map<int, float> cost_so_far;  // a dictionary that matches the node label to a float
	cost_so_far[start] = 0.0f;

	// implement the algorithm

	// loop through the frontier, while not empty
	while (!frontier.empty())
	{
		// get the top node, from frontier and pop it off

		//if its the goal then break out of the loop

		// for the neighbours of current node
		{
			// calculate the new cost

			//if next is not an index in cost_so_far, or new cost is lower

			{
				// found a better path, so update data structures
			}
		}
	}

	// follow the breadcrumbs in came_from to produce path
	vector<int> path = {};

	// do something
	
	return path;
}
