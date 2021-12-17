#pragma once
#ifndef DEBUG
#define DEBUG
#endif
#include "GameControler.h"

class Board
{
public:
	Board(
		std::vector<char>_game_map,
		std::vector<char>_next_three,
		int _score,
		std::vector<char>_last_move
	) ://call from expand()
		score(_score),
		game_map(_game_map),
		last_move(_last_move),
		next_three(_next_three)
	{
		auto result = judge(game_map.data(), next_three.data(), last_move.data());
		if (result->score == -1)
			is_end = true;
		else
			score += result->score;
		connectivity = result->connectivity;
		Q_value = score * 1e3 + connectivity;
		delete result;
#ifdef DEBUG
		game_map_ptr = game_map.data();
#endif
	}
	Board()  // generate random start status
	{
		game_map = init_game_map();

		last_move = std::vector<char>(4, -1);
		next_three = get_random_colors(3);
#ifdef DEBUG
		game_map_ptr = game_map.data();
#endif
	}

	Board(std::vector<char>_game_map, std::vector<char>_next_three)
	{//given start
		game_map = _game_map;

		last_move = std::vector<char>(4, -1);
		next_three = _next_three;
#ifdef DEBUG
		game_map_ptr = game_map.data();
#endif
	}
public:
	std::vector<char>game_map;
	std::vector<char>last_move;
	std::vector<char>next_three;
	bool is_end = false;
	int score = 0;
	int connectivity = 0;
	int Q_value = 0;
#ifdef DEBUG
	char* game_map_ptr;
#endif

private:
	std::vector<char>get_random_color(char num);
	std::vector<char>init_game_map();
	std::vector<char>get_empty_index(std::vector<char> game_map);
	std::vector<char>get_random_colors(char num);
	char get_a_random_color();
};

