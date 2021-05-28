#include "Node.h"
#include <cmath>
#include "Pathfinding.h"
float Node::get_UBC()
{
	if (!parent_node)
		return 0;
	return value+score*10000 /*+ c_puct  * sqrt(parent_node->visit_count) / (1 + visit_count)*/;
}

void Node::call_estimate(bool*p)
{
	Estimate(p, game_map.data());
}