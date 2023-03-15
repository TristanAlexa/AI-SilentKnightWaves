#ifndef NODE_H
#define NODE_H
#include "MMath.h"

using namespace MATH;
class Node {

private:
	int label;
	Vec3 pos;

public:
	// Node is used as an object for the graph and data structures
	// Each node contains its own label and position
	Node(int label_, Vec3 pos_)
	{
		label = label_;
		pos = pos_;
	}
	~Node() {}
	int getLabel() { return label; }
	Vec3 getPosition() { return pos; }
};
#endif;
