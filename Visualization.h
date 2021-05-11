#pragma once
#include <easyx.h>
#include "Node.h"

namespace visual 
{
	struct Point
	{
		char x, y, color;
		Point(char _x, char _y, char _color=0) :x(_x), y(_y), color(_color) {};
		Point() {};
	};
}
class Show_node
{
public:
	Show_node(Node* _node)
	{
		game_map = _node->game_map;
		next_three = _node->next_three;
		score = _node->score;
		node = _node;
		draw();
	}
private:
	void init();
	void draw();
	void drawlines();
	void drawtchess();
	void drawnextThree();
	void drawscore();
	void drawlastmove();
	visual::Point to_coord(char index, char color);
private:
	void _plotchess(visual::Point);
private:
	static int color[8];
private:
	Node* node;
	vector<char>game_map;
	vector<char>next_three;
	int score;
};