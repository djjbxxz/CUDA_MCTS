#pragma once
#include "Node.h"
#include "kernel.h"
#include "Visualization.h"
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
	void select_CUDA();
	void select();
	void expand();
	void backup();
	void play();
public:
	Node *root;
	Node *current_node;
	vector<Node*> leaves;
public:
	//static   judge_type judge;
};
