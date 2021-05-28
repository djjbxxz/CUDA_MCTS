#pragma once
#include "GameControler.h"

class Board
{

public:
	Board(
		std::vector<char>_game_map,
		std::vector<char>_next_three,
		int _score,
		std::vector<char>_last_move
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

		last_move = std::vector<char>(4, -1);
		next_three = get_random_colors(3);
	}

	Board(std::vector<char>_game_map, std::vector<char>_next_three)
	{
		game_map = _game_map;

		last_move = std::vector<char>(4, -1);
		next_three = _next_three;
	}
public:
	std::vector<char>game_map;
	std::vector<char>last_move;
	std::vector<char>next_three;
	bool is_end = false;
	int score = 0;
	Return_message* result;

private:
	std::vector<char>get_random_color(char num);
	std::vector<char>init_game_map();
	std::vector<char>get_empty_index(std::vector<char> game_map);
	std::vector<char>get_random_colors(char num);
	char get_a_random_color();
};

