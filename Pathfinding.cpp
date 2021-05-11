#include "Pathfinding.h"
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

bool Pathfinding::is_inList(Point point, vector<Point>list)
{
	for (int i = 0; i < list.size(); i++)
		if (list[i] == point)
			return true;
	return false;
}

bool Pathfinding::is_inList(Point point, list<Point>_list)
{
	for (list<Point>::iterator i = _list.begin(); i != _list.end(); i++)
		if (*i == point)
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

vector<Point> Pathfinding::getsurpoint_filter1(Point point, vector<Point>closelist)
{
	auto surrdingpoints = getsurrdingpoint(point);
	vector<Point> temp;
	for (int i = 0; i < surrdingpoints.size(); i++)
	{
		point = surrdingpoints[i];
		if (!(game_map(point) > 0 ||
			is_inList(point, closelist) ||
			is_scaned(point)))
			temp.push_back(surrdingpoints[i]);
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
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			is_scaned_map[i][j] = false;
}

void Pathfinding::GetBeginSet()
{
	for (int i = 0; i < emptyset.size(); i++)
	{
		init_scan_map();
		startset.push_back(Getedge(emptyset[i]));
	}
}

vector<Point> Pathfinding::Getedge(vector<Point>Pointset)
{
	auto edge = vector<Point>();
	Point surrdingpoint;
	for (auto point : Pointset)
	{
		auto surrdingpoints = getsurrdingpoint(point);
		for (int i = 0; i < surrdingpoints.size(); i++)
		{
			surrdingpoint = surrdingpoints[i];
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
	char x, y;
	for (int i = 0; i < 4; i++)
	{
		x = point.x + scan_direction[i][0];
		y = point.y + scan_direction[i][1];
		auto point = Point(x, y);
		if (!is_outofrange(point))
			temp.push_back(point);
	}
	return temp;
}

void Pathfinding::MakeResult()
{
	for (int i = 0; i < startset.size(); i++)
	{
		calculate(startset[i], emptyset[i]);
	}
}

void Pathfinding::calculate(vector<Point>start, vector<Point>end)
{
	for (int i = 0; i < start.size(); i++)
		for (int j = 0; j < end.size(); j++)
			p[start[i].x * 9 * 9 * 9 + start[i].y * 9 * 9 + end[j].x * 9 + end[j].y] = true;
}


void Estimate(bool* p, char* game_map)
{
	Pathfinding go(game_map, p);
}
