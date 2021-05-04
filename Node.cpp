#include "stdafx.h"
#include "Node.h"
constexpr auto c_puct = 1;
float Node::get_UBC()
{
	if (!parent_node)
		return 0;
	return value + c_puct * p / (1 + visit_count + parent_node->visit_count);
}

void Node::call_estimate(float *p)
{
	estimate(p, game_map.data());
}