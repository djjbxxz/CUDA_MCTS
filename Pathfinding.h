#pragma once
#include <vector>
#include <list>
#include "GameControler.h"

void Estimate(bool* p, char* game_map);



class Pathfinding
{
public:
	Pathfinding(char* _game_map, bool* _p) :game_map_var(_game_map), p(_p) { go(); }
	void GetEmptySet();
	void go();

	std::vector<Point> get_reachable_point(Point);
	std::vector<Point> getsurpoint_filter1(Point, std::vector<Point>&);
	void mark_as_scaned(Point);
	bool is_scaned(Point);
	void init_scan_map();
	void GetBeginSet();
	std::vector<Point> Getedge(const std::vector<Point>&);
	bool is_outofrange(Point);
	int game_map(Point);
	std::vector<Point> getsurrdingpoint(Point);
	void MakeResult();
	void calculate(std::vector<Point>&, std::vector<Point>&);
private:
	static bool is_inList(Point, const std::vector<Point>&);
	static bool is_inList(Point, const std::list<Point>&);
private:
	char* game_map_var;
	bool* p;
	bool calculate_p[6561];
	std::vector<std::vector<Point>>emptyset;
	std::vector<std::vector<Point>>startset;
	bool is_scaned_map[9][9];
	const Point scan_direction[4] = { {-1,0},{0,-1},{1,0},{0,1} };
};