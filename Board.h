#pragma once
#include "GameControler.h"
#include <vector>
using namespace std;

class Board
{

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
		result = judge(game_map.data(), next_three.data(), last_move.data());
		if (result->score == -1)
			is_end = true;
		else
			score += result->score;
	}
	Board()  // generate random start status
	{
		game_map = init_game_map();

		last_move = vector<char>(4, -1);
		next_three = get_random_colors(3);
	}

	Board(vector<char>_game_map, vector<char>_next_three)  
	{
		game_map = _game_map;

		last_move = vector<char>(4, -1);
		next_three = _next_three;
	}
public:
	vector<char>game_map;
	vector<char>last_move;
	vector<char>next_three;
	bool is_end = false;
	int score = 0;
	Return_message* result;

private:
	vector<char>get_random_color(char num);
	vector<char>init_game_map();
	vector<char>get_empty_index(vector<char> game_map);
	vector<char>get_random_colors(char num);
	char get_a_random_color();
};

