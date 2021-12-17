#pragma once
#include "Board.h"
constexpr auto c_puct = 1;

class Node :public Board
{
public:
	Node(Node* old,
		std::vector<char>_last_move)
		:Board(old->game_map, old->next_three, old->score, _last_move)
	{
		is_root = false;
		parent_node = old;
		depth = old->depth + 1;
	}
	Node() :// generate random start status
		is_root(true),
		parent_node(nullptr),
		depth(1)
	{}

	Node(std::vector<char> game_map,
		std::vector<char> next_three)
		:Board(game_map, next_three),
		is_root(true),
		parent_node(nullptr),
		depth(1)
	{}

public:
	float get_UBC();
public:
	Node* parent_node = nullptr;
	Node* real_move = nullptr;
	std::vector<Node*> children;
	bool is_root;
	unsigned char visit_count = 0;
	unsigned char depth;
public:
	void call_estimate(bool*);
private:
	void get_connectivity();
};

