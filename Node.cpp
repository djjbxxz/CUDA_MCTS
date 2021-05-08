#include "stdafx.h"
#include "Node.h"
#include <math.h>
float Node::get_UBC()
{
	if (!parent_node)
		return 0;
	return value + c_puct * p * sqrt(parent_node->visit_count) / (1 + visit_count);
}

void Node::call_estimate(float *p)
{
	estimate(p, game_map.data());
}