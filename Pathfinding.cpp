#include "Pathfinding.h"
using namespace std;
void Pathfinding::GetEmptySet()
{
	init_scan_map();
	for (char i = 0; i < 9; i++)
		for (char j = 0; j < 9; j++)
			if (game_map({ i, j }) == 0 && is_scaned_map[i][j] == false)
				emptyset.push_back(get_reachable_point({ i, j }));
}

void Pathfinding::go()
{
	GetEmptySet();
	GetBeginSet();
	MakeResult();
}

bool Pathfinding::is_inList(Point point, const vector<Point>& list)
{
	for (auto i : list)
		if (i == point)
			return true;
	return false;
}

bool Pathfinding::is_inList(Point point, const list<Point>& _list)
{

	for (auto i : _list)
		if (i == point)
			return true;
	return false;
}

vector<Point> Pathfinding::get_reachable_point(Point point)
{
	vector<Point>openlist;
	auto closelist = vector<Point>();
	Point curpoint;
	openlist.push_back(point);
	while (!openlist.empty())
	{
		curpoint = openlist.back();
		mark_as_scaned(point);
		openlist.pop_back();
		closelist.push_back(curpoint);
		auto surrpoints = getsurpoint_filter1(curpoint, closelist);
		if (!surrpoints.empty())
		{
			openlist.insert(openlist.end(), surrpoints.begin(), surrpoints.end());
			for (auto point : surrpoints)
				mark_as_scaned(point);
		}
	}
	return closelist;
}

vector<Point> Pathfinding::getsurpoint_filter1(Point point, vector<Point>& closelist)
{
	auto surrdingpoints = getsurrdingpoint(point);
	vector<Point> temp;
	for (auto surrdingpoint : surrdingpoints)
	{
		point = surrdingpoint;
		if (!(game_map(point) > 0 ||
			is_inList(point, closelist) ||
			is_scaned(point)))
			temp.push_back(surrdingpoint);
	}
	return temp;
}

void Pathfinding::mark_as_scaned(Point point)
{
	is_scaned_map[point.x][point.y] = true;
}

bool Pathfinding::is_scaned(Point point)
{
	return is_scaned_map[point.x][point.y];
}

void Pathfinding::init_scan_map()
{
	for (auto& i : is_scaned_map)
		for (bool& j : i)
			j = false;
}

void Pathfinding::GetBeginSet()
{
	for (const auto& i : emptyset)
	{
		init_scan_map();
		startset.push_back(Getedge(i));
	}
}

vector<Point> Pathfinding::Getedge(const vector<Point>& Pointset)
{
	auto edge = vector<Point>();
	Point surrdingpoint;
	for (auto point : Pointset)
	{
		auto surrdingpoints = getsurrdingpoint(point);
		for (auto i : surrdingpoints)
		{
			surrdingpoint = i;
			if (!is_scaned(surrdingpoint) && !is_inList(surrdingpoint, Pointset))
			{
				edge.push_back(surrdingpoint);
				mark_as_scaned(surrdingpoint);
			}
		}
	}
	return edge;
}

bool Pathfinding::is_outofrange(Point point)
{
	if (point.x < 0 || point.x>8 ||
		point.y < 0 || point.y>8)
		return true;
	else
		return false;
}

int Pathfinding::game_map(Point point)
{
	return *(game_map_var + 9 * point.x + point.y);
}

vector<Point> Pathfinding::getsurrdingpoint(Point point)
{
	auto temp = vector<Point>();
	Point new_point;
	for (auto i : scan_direction)
	{
		new_point = point + i;
		if (!is_outofrange(new_point))
			temp.push_back(new_point);
	}
	return temp;
}

void Pathfinding::MakeResult()
{
	for (int i = 0; i < startset.size(); i++)
		calculate(startset[i], emptyset[i]);
}

void Pathfinding::calculate(vector<Point>& start, vector<Point>& end)
{
	for (auto& i : start)
		for (auto& j : end)
			p[i.x * 9 * 9 * 9 + i.y * 9 * 9 + j.x * 9 + j.y] = true;
}


void Estimate(bool* p, char* game_map)
{
	Pathfinding go(game_map, p);
}
