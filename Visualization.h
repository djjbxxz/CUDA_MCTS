#pragma once
#include <easyx.h>
#include "Node.h"
struct Point
{
	char x, y,color=0;
	Point(char _x, char _y,char _color) :x(_x), y(_y),color(_color) {};
	Point() {};
};

class Visual
{
public:
	Visual(Node node)
	{
		game_map = node.game_map;
		next_three = node.next_three;
		score = node.score;
		draw();
	}
private:
	void init();
	void draw();
	void drawlines();
	void drawtchess();
	void drawnextThree();
	void drawscore();
	Point to_coord(char index,char color);
private:
	void _plotchess(Point);
private:
	static int color[8];
private:
	vector<char>game_map;
	vector<char>next_three;
	int score;
};