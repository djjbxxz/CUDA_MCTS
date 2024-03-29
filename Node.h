#pragma once
#include "Board.h"
constexpr auto c_puct = 1;

class Node :public Board
{
public:
	Node(Node *old,
		vector<char>_last_move)
		:Board(old->game_map, old->next_three, old->score, _last_move)
	{
		is_root = false;
		parent_node = old;
		value = result->value;
	}
	Node() :// generate random start status
		is_root(true),
		parent_node(nullptr)
	{}

public:
	float get_UBC();
public:
	Node* parent_node = nullptr;
	Node* real_move = nullptr;
	vector<Node*> children;
	bool is_root;
	unsigned int visit_count = 0;
	float value = 0;
public:
	void call_estimate(bool*);

};

