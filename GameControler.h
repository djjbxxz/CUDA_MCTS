#pragma once
#include <vector>

struct Return_message
{
	int score;
	int connectivity;
	Return_message(int _score, int _value) :score(_score), connectivity(_value) {};
};

Return_message* judge(char* map, char* comingcolor, char* move);

struct Point
{
	char x, y;
	Point(char	_x, char _y) :x(_x), y(_y) {};
	Point() {}
	bool operator== (const Point &a)
	{
		return x == a.x && y == a.y;
	};
	Point operator+ (const Point &a)
	{
		return { x + a.x, y + a.y };
	}
	Point operator-(const Point &a)//减法
	{
		return { x - a.x, y - a.y };
	}
	Point operator-()//取反
	{
		return { -x,-y };
	}
	Point operator+=(const Point &a)
	{
		return { x + a.x,y + a.y };
	}
};

class GameControler
{
public:
	GameControler(char* _map, char* _comingcolor, char* _move) :move(_move), game_map(_map), comingcolor(_comingcolor) { go(); }
	void go();
	char get_game_map(const Point &point);
	void set_game_map(Point, int);
	void Move();
	void Scan_all();
	void Scanpoints(std::vector<Point>&);
	void AddScoreAndEliminate(bool);
	std::vector<Point> PlaceChess();
	std::vector<Point> GetEmpty();
	void remove(std::vector<Point>&, int index);
	int get_value();
	bool check_if_repeat(std::vector<Point> &points);
	Return_message* get_result();

private:
	void ScanLined(Point point);
	void Scanpoint(Point& point);
private:
	char* game_map;
	char* comingcolor;
	char* move;
	int score=0;
	int connectivity;
	const Point scan_direction[8] = { {1,0},{0,1},{1,-1},{1,1},
										{-1,0},{0,-1},{-1,1},{-1,-1} };
	std::vector<std::vector<Point>>lineds;//2个以上的都算
};