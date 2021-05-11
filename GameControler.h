#pragma once
#include <vector>
#include"windows.h"

using namespace std;

struct Return_message
{
	int score;
	int value;
	Return_message(int _score, int _value) :score(_score), value(_value) {};
};

Return_message* judge(char* map, char* comingcolor, char* move);

struct Point
{
	char x, y;
	Point(char	_x, char _y) :x(_x), y(_y) {};
	Point() {}
	bool operator== (const Point a)
	{
		return x == a.x && y == a.y;
	};
	Point operator+ (const Point a)
	{
		return { x + a.x, y + a.y };
	}
	Point operator+(const char* a)
	{
		return { x + *a, y + *(a + 1) };
	}
	Point operator-(const Point a)//减法
	{
		return { x - a.x, y - a.y };
	}
	Point operator-()//取反
	{
		return { -x,-y };
	}
	Point operator+=(const Point a)
	{
		return { x + a.x,y + a.y };
	}
};

class GameControler
{
public:
	GameControler(char* _map, char* _comingcolor, char* _move) :move(_move), game_map(_map), comingcolor(_comingcolor) { go(); }
	void go();
	void init_random();
	char get_game_map(Point point);
	void set_game_map(Point, int);
	void Move();
	void Scan_all();
	void Scanpoint(Point);
	void ScanLined(Point, int);
	void AddScoreAndEliminate(bool);
	bool LayChess();
	vector<Point> GetEmpty();
	void remove(vector<Point>&, int index);
	int get_value();
	bool check_if_repeat(vector<Point> points);
	bool is_in_list(vector<Point>points, Point point);
	Return_message* get_result();


private:
	char* game_map;
	char* comingcolor;
	char* move;
	int score=0;
	int value;
	const char scan_direction[8][2] = { {1,0},{0,1},{1,-1},{1,1},
										{-1,0},{0,-1},{-1,1},{-1,-1} };
	vector<vector<Point>>lineds;//2个以上的都算
};