#include "GameControler.h"

#define WEIGHT_OVER_5 9999
#define WEIGHT_UNDER_5_LINEDS 40
#define WEIGHT_UNDER_5_EMPTY_CHESS 8
#define WEIGHT_UNDER_5_BLOCK_CHESS -20
#define WEIGHT_EACH_MARGIN_CHESS -2

void GameControler::go()
{
	init_random();
	Move();

	//Scanpoint(Point(*(move + 2), *(move + 3)));
	Scan_all();
	//计算相连度
	//connectivity
	value = get_value();
	AddScoreAndEliminate(true);
	if (score == 0)
	{
		if (!LayChess())
			score = -1;
		Scan_all();
		AddScoreAndEliminate(false);
	}
}

void GameControler::init_random()
{
	LARGE_INTEGER seed;
	QueryPerformanceFrequency(&seed);
	QueryPerformanceCounter(&seed);
	srand(seed.QuadPart);
}

char GameControler::get_game_map(const Point point)
{
	if (point.x < 0 || point.x>8 || point.y < 0 || point.y>8)
		return -1;
	return *(game_map + 9 * point.x + point.y);
}

void GameControler::set_game_map(Point point, int color)
{
	*(game_map + 9 * point.x + point.y) = color;
}

void GameControler::Move()
{
	auto start = Point(*move, *(move + 1));
	auto end = Point(*(move + 2), *(move + 3));
	set_game_map(end, get_game_map(start));
	set_game_map(start, 0);
}

void GameControler::Scan_all()
{
	lineds.clear();
	for (char i = 0; i < 9; i++)
		for (char j = 0; j < 9; j++)
			if (get_game_map({ i, j }) != 0)
				ScanLined({ i, j }, 4);
}

void GameControler::Scanpoint(Point point)
{
	lineds.clear();
	ScanLined(point, 4);
}

void GameControler::ScanLined(const Point point, const int directionnum)
{
	Point new_point;
	for (int i = 0; i < directionnum; i++)
	{
		auto lined = vector<Point>();
		for (int j = 0; j <= 4; j += 4)
		{
			new_point = point;
			while (true)
			{
				new_point = new_point + scan_direction[i + j];
				if (get_game_map(new_point) != get_game_map(point))
					break;
				lined.push_back({ new_point.x, new_point.y });
			};
		}
		if (lined.size() >= 1)
		{
			lined.push_back(point);
			if (!check_if_repeat(lined))
				lineds.push_back(lined);
		}
	}
}

void GameControler::AddScoreAndEliminate(bool add_score)
{
	for (auto points : lineds)
	{
		if (points.size() < 5)
			continue;
		for (auto point : points)
		{
			if (add_score && get_game_map(point) != 0)
				score += 2;
			set_game_map(point, 0);
		}
	}
}

bool GameControler::LayChess()
{
	auto empty = GetEmpty();
	int randomlocation;
	for (int i = 0; i < 3; i++)
	{
		if (empty.size() == 0)
			return false;
		randomlocation = rand() % empty.size();
		set_game_map(empty[randomlocation], *(comingcolor + i));
		remove(empty, randomlocation);
		*(comingcolor + i) = rand() % 7 + 1;
	}
	return true;
}

vector<Point> GameControler::GetEmpty()
{
	vector<Point>empty;
	for (char i = 0; i < 9; i++)
		for (char j = 0; j < 9; j++)
			if (get_game_map({ i, j }) == 0)
				empty.push_back({ i, j });
	return empty;
}

void GameControler::remove(vector<Point>& a, int index)
{
	a.erase(begin(a) + index);
}

int GameControler::get_value()
{
	int value = 0;
	for (int i = 0; i < lineds.size(); i++)
	{
		int size = lineds[i].size();
		int still_need = 5 - lineds[i].size();
		if (still_need <= 0)
		{
			//4
			value += WEIGHT_OVER_5 * size;
			continue;
		}
		auto direction = lineds[i][1] - lineds[i][0];
		auto color = get_game_map(lineds[i][0]);
		bool change_direction = true;

		Point point = lineds[i][0];
		int empty_count = 0;
		int block_chess_count = 0;

		while (still_need > 0)
		{
			point = point + direction;

			if (get_game_map(point) == color)
			{
				continue;
			}
			else if (get_game_map(point) == -1)
			{
				//墙
				if (!change_direction)
				{
					//3
					break;
				}
				else
				{
					//换方向
					direction = -direction;
					point = lineds[i][0];
					change_direction = false;
					continue;
				}
			}
			else
			{
				if (get_game_map(point) == 0)
				{
					//2
					empty_count++;
				}
				else
				{
					//其他颜色子
					block_chess_count++;
				}
				still_need--;
				continue;
			}
		}
		if (!change_direction && still_need > 0)
			value -= size *  WEIGHT_EACH_MARGIN_CHESS;
		else
			value += size * size * size * size * WEIGHT_UNDER_5_LINEDS
			+ size * size*empty_count * WEIGHT_UNDER_5_EMPTY_CHESS
			+ size * size * size* size * size * block_chess_count * WEIGHT_UNDER_5_BLOCK_CHESS;
	}
	return value;
}

bool GameControler::check_if_repeat(vector<Point> points)
{
	for (int i = 0; i < lineds.size(); i++)
	{
		auto temp = points;
		for (vector<Point>::iterator it = temp.begin(); it != temp.end();)
			if (is_in_list(lineds[i], *it))
				it = temp.erase(it);
			else
				it++;
		if (temp.size() == 0)
			return true;
	}
	return false;
}

bool GameControler::is_in_list(vector<Point> points, Point point)
{
	for (int i = 0; i < points.size(); i++)
		if (point == points[i])
			return true;
	return false;
}

Return_message* GameControler::get_result()
{
	return new Return_message(score, value);
}

Return_message* judge(char* map, char* comingcolor, char* move)
{
	auto go = GameControler(map, comingcolor, move);
	return go.get_result();
}
