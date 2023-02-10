#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include "Node.h"
#include <iostream>

using namespace std;

class Graph
{
private:
	// a lit of the nodes
	// Could use STL vector, but map matches some textbooks
	map<int, Node*> node;

	// A 2D matrix of the connection costs // (not efficient)
	// indexed by ints the node label
	vector < vector< float > >cost;

public:
	Graph(); //not the map
	~Graph();
	bool OnCreate(vector <Node*> nodes_);
	// Size of the map
	int numNodes(); 

	// Given a particular integer, grabs the node pointer of the label
	Node* getNode(int label) { return node[label]; } 

	void addWeightConnection(int fromNode, int toNode, float weight);

	// Vector of ints which are the labels of the node pointers
	vector<int> neighbours(int fromNode); 
	vector<int> Dijkstra(int start, int goal);

};
#endif;
