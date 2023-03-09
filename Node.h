#ifndef NODE_H
#define NODE_H
#include "MMath.h"

using namespace MATH;
class Node {

private:
	int label;
	Vec3 pos;

public:
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
