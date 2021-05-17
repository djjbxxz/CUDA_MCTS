#pragma once
#include "Node.h"
#include "Visualization.h"
#include "threadpool.h"
class MCTS
{
public:
	MCTS(Node *_root)
	{
		root = _root;
		//for (int i = 0; i <40000000; i++)//40 million at most
		leaves.push_back(root);
	}
public:
	bool select();
	void expand();
	void backup();
	bool play();
private:
	static Node* create_new_node(Node* parent_node, int i);

public:
	Node *root;
	Node *current_node;
	static vector<Node*> leaves;
public:
	//static   judge_type judge;
};
