#include "Board.h"
using namespace std;
vector<char> Board::get_random_color(char num)
{
	vector<char>random_color;
	random_color.resize(num);
	for (char i = 0; i < num; i++)
		random_color[i]=rand() % 7+1;
	return random_color;
}

vector<char> Board::init_game_map()
{
	vector<char>game_map(81, 0);
	for (char i = 0; i < 5; i++)
	{
		auto empty_list = get_empty_index(game_map);
		auto index = empty_list[rand() % empty_list.size()];
		auto color = get_a_random_color();
		game_map[index] = color;
	}
	return game_map;
}

vector<char> Board::get_empty_index(vector<char> game_map)
{
	vector<char>empty_list;
	for (char i = 0; i < game_map.size(); i++)
		if (game_map[i] == 0)
			empty_list.push_back(i);
	return empty_list;
}

vector<char> Board::get_random_colors(char num)
{
	vector<char> list;
	for (char i = 0; i < num; i++)
		list.push_back(get_a_random_color());
	return list;
}


char Board::get_a_random_color()
{
	return rand()%7+1;
}

