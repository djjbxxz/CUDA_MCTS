#include "Node.h"

vector<char> Node::get_random_color(char num)
{
	vector<char>random_color;
	random_color.reserve(num);
	for (char i = 0; i < num; i++)
		random_color.push_back(rand() % 8);
	return random_color;
}
