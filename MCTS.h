#pragma once
#include "Node.h"
#include "iostream"
class MCTS
{
public:
	MCTS(
		Node *_root,
		unsigned char _max_depth
	):
		max_depth(_max_depth),
		root(_root)
	{
		leaves.push_back(root);
	}
public:
	int do_MCTS(int iteration_each_step);
private:
	static Node* create_new_node(Node* parent_node, int i);
	bool select();
	void expand();
	void backup();
	bool play();

private:
	static std::vector<char> convert_to_index(int densed);
public:
	Node *root;
	Node *current_node;
	unsigned char max_depth;
	static std::vector<Node*> leaves;
};
