#pragma once
#include "Load_library.h"
#include <vector>
using namespace std;

class Board
{//�洢������Ϣ����Ϸ�߼�����
	
public:
	Board(
		vector<char>_game_map,
		vector<char>_next_three,
		int _score,
		vector<char>_last_move
	):
		score(_score),
		game_map(_game_map),
		last_move(_last_move),
		next_three(_next_three)
	{
		call_judge();
	}
	Board()  // generate random start status
	{
		game_map = init_game_map();

		last_move = vector<char>(4, -1);
		next_three = get_random_colors(3);
	}
public:
	static judge_type judge;
	vector<char>game_map;
	vector<char>last_move;
	vector<char>next_three;
	bool is_end = false;
	int score = 0;

private:
	vector<char>get_random_color(char num);
	vector<char>init_game_map();
	vector<char>get_empty_index(vector<char> game_map);
	vector<char>get_random_colors(char num);
	char get_a_random_color();
	void call_judge();
};

