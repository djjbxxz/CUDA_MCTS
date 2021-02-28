#pragma once
#include <vector>
#include"windows.h"
using namespace std;

class Node
{
public:
	Node(vector<vector<char>>_game_map, 
		vector<char>_last_move, 
		Node* _parent_node, 
		float _p, 
		vector<char>_next_three,
		int _score
	)
		:p(_p),score(_score),parent_node(_parent_node)
	{
		game_map=_game_map;
		last_move = _last_move;
		next_three = _next_three;
	}
	Node()  
	{
		game_map = vector<vector<char>>(9, vector<char>(9));
		last_move = vector<char>();
		next_three = get_random_color(3);
		score = 0;
		is_root = true;
	}

private:
	vector<char>get_random_color(char num);


private:
	vector<vector<char>>game_map;
	vector<char>last_move;
	vector<char>next_three;
	Node* parent_node=nullptr;
	Node* real_move=nullptr;
	float p;
	int score;
	bool is_root = false;
	int visit_count = 0;
};

