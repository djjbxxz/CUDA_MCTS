#include "stdafx.h"
#include "MCTS.h"
#include "Visualization.h"
#include <Algorithm>
constexpr float decay_rate = 0.5;
#define THREAD_MAX_NUM 6
mutex mutex_leaves;
vector<Node*> MCTS::leaves = vector<Node*>();
void delete_node(Node* node)
{
	for (size_t i = 0; i < node->children.size(); i++)
		delete_node(node->children[i]);
	delete node;
}

bool MCTS::select()
{
	if (root->is_end)
		return false;
	float max = 0.0;
	size_t max_index = 0;
	float ubc;
	for (size_t i = 0; i < leaves.size(); i++)
	{
		ubc = leaves[i]->get_UBC();
		if (ubc > max)
		{
			max = ubc;
			max_index = i;
		}
	}
	if (max_index < leaves.size())
	{
		current_node = leaves[max_index];
		leaves.erase(leaves.begin() + max_index);
		current_node->visit_count++;
		return true;
	}
	else
		return false;

}


bool  comp(const Node* a, const Node* b) {
	return a->value > b->value;
}


void MCTS::expand()
{
	current_node->visit_count++;
	Node* new_node;
	bool p[6561];
	for (int i = 0; i < 6561; i++)
		p[i] = false;
	current_node->call_estimate(p);
	vector< future<Node*> > results;
	{
	ThreadPool executor{ THREAD_MAX_NUM };
	for (int i = 0; i < 6561; i++)
		if (p[i])
		{
			results.emplace_back(
				executor.enqueue
				(create_new_node, current_node, i));
		}
	}
	for (auto&& result : results)
	{
		auto temp = result.get();
		current_node->children.emplace_back(temp);
		MCTS::leaves.push_back(temp);
	}
}

void MCTS::backup()
{
	if (current_node->is_root)
		return;
	for (size_t i = 0; i < current_node->children.size(); i++)
	{
		current_node->value += current_node->children[i]->value * decay_rate;
	}
	auto update_node = current_node;
	while (!update_node->is_root)
	{
		update_node->parent_node->value += update_node->value * decay_rate;
		update_node = update_node->parent_node;
	}
}


bool  sort_children(const Node* a, const Node* b) {
	return a->value > b->value;
}

bool MCTS::play()
{
	if (!root->children.size())
		return false;
	sort(root->children.begin(),
		root->children.end(), sort_children);
	root->real_move = root->children[0];
	for (size_t i = 1; i < root->children.size(); i++)//删除除real_move以外其它子节点
		delete_node(root->children[i]);


	root = root->children[0];
	current_node = nullptr;
	leaves.clear();
	leaves.push_back(root);
	return true;
}

Node* MCTS::create_new_node(Node* parent_node, int i)
{
	return new Node(parent_node, convert_to_index(i));
}