#pragma once
#include "Board.h"
class Node :public Board
{
public:
	Node(Node *old,
		vector<char>_last_move,
		float _p)
		:Board(old->game_map, old->next_three, old->score, _last_move)
	{
		is_root = false;
		parent_node = old;
		p = _p;
	}
	Node() :// generate random start status
		is_root(true),
		p(0.f),
		parent_node(nullptr)
	{}
	~Node()
	{
		int a = 3;
	}


public:
	float get_UBC();
public:
	Node* parent_node = nullptr;
	Node* real_move = nullptr;
	vector<Node> children;
	float p;
	bool is_root;
	unsigned int visit_count = 0;
	float value = 0;
	static  Estimate_type estimate;
public:
	void call_estimate(float*);
	void create_child();

};

