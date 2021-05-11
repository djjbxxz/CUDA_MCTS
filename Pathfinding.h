#pragma once
#include <vector>
#include <list>
#include "GameControler.h"

void Estimate(bool* p, char* game_map);

using namespace std;


class Pathfinding
{
public:
	Pathfinding(char* _game_map, bool* _p) :game_map_var(_game_map), p(_p) { go(); }
	void GetEmptySet();
	void go();
	bool is_inList(Point, vector<Point>);
	bool is_inList(Point, list<Point>);
	vector<Point> get_reachable_point(Point);
	vector<Point> getsurpoint_filter1(Point, vector<Point>);
	void mark_as_scaned(Point);
	bool is_scaned(Point);
	void init_scan_map();
	void GetBeginSet();
	vector<Point> Getedge(vector<Point>);
	bool is_outofrange(Point);
	int game_map(Point);
	vector<Point> getsurrdingpoint(Point);
	void MakeResult();
	void calculate(vector<Point>, vector<Point>);
private:
	char* game_map_var;
	bool* p;
	bool calculate_p[6561];
	vector<vector<Point>>emptyset;
	vector<vector<Point>>startset;
	bool is_scaned_map[9][9];
	const char scan_direction[4][2] = { {-1,0},{0,-1},{1,0},{0,1} };
};