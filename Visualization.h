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
	Show_node()
	{
		window = initgraph(550, 600);
	}

public:
	void draw(Node* _node);
private:
	void init();
	void draw_item();
	void drawlines();
	void drawtchess();
	void drawnextThree();
	void drawscore();
	void drawlastmove();
	void _show(Node* _node);
	visual::Point to_coord(char index, char color);
private:
	void _plotchess(visual::Point);
private:
	static int color[8];
	static HWND window;
private:
	Node* node;
	vector<char>game_map;
	vector<char>next_three;
	int score;
};