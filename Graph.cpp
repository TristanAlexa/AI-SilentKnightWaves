#include "Graph.h"

Graph::Graph()
{

}

// Initializes the matrix of costs and sets up the mapping of nodes
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
	// Node instances are created (new) in the scene
	// So do the memory clean up in the scene OnDestroy()
}

int Graph::numNodes()
{
	return node.size();
}

// Defines the cost (how difficult) it is to move from one node to another
void Graph::addWeightConnection(int fromNode, int toNode, float weight)
{
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

// Returns the shortest and lowest costing path between the two passed in nodes
vector<Node*> Graph::Dijkstra(int start, int goal)
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

	/*  While PQ != empty, loop through the neighbours of the current node being evaluated, and calculate the new cost of each neighbour
		Nodes are added to the PQ, if not beeen visisted, or if the new cost is == or < the previous cost*/
	while (!frontier.empty())
	{
		current = frontier.top().node;
		frontier.pop();

		if (current->getLabel() == goal)
		{
			break;
		}

		vector<int> neighbours = this->neighbours(current->getLabel());
		for (int i = 0; i < neighbours.size(); i++)
		{
			int next = neighbours[i];
			new_cost = cost_so_far[current->getLabel()] + cost[current->getLabel()][next];
			if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next])
			{
				cost_so_far[next] = new_cost;
				priority = new_cost;
				frontier.push(NodeAndPriority{ node[next], priority });
				came_from[next] = current->getLabel();
			}
		}
	}

	// The returned path is the list of nodes added to the came_from vector from keeping track of the nodes we kept
	vector<Node*> path = {};

	if (came_from[goal] != 0)
	{
		int current = goal;
		while (current != start)
		{
			path.insert(path.begin(), getNode(current));
			current = came_from[current];
		}
		path.insert(path.begin(), getNode(start));
	}
	
	return path;
}
