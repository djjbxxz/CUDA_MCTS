#include "GameControler.h"

#define WEIGHT_OVER_5 9999
#define WEIGHT_UNDER_5_LINEDS 50
#define WEIGHT_UNDER_5_EMPTY_CHESS 8
#define WEIGHT_UNDER_5_BLOCK_CHESS -20
#define WEIGHT_EACH_MARGIN_CHESS -2

bool is_in_list(vector<Point>& points, Point point)
{
	for (int i = 0; i < points.size(); i++)
		if (point == points[i])
			return true;
	return false;
}

bool operator==(vector<Point>& a, vector<Point>& b)
{
	for (size_t a_it = 0; a_it < a.size(); a_it++)
		if (!is_in_list(b, a[a_it]))
			return false;
	for (size_t b_it = 0; b_it < a.size(); b_it++)
		if (!is_in_list(a, b[b_it]))
			return false;
	return true;
}

void GameControler::go()
{
	Move();

	Scan_all();
	value = get_value();
	AddScoreAndEliminate(true);
	if (score == 0)
	{
		auto temp = PlaceChess();
		if (!temp.size())
			score = -1;
		Scanpoints(temp);
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

char GameControler::get_game_map(const Point& point)
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

void GameControler::Scanpoints(vector<Point>& points)
{
	lineds.clear();
	for (size_t i = 0; i < points.size(); i++)
		ScanLined(points[i], 8);
}

void GameControler::ScanLined(Point point, const int directionnum)
{
	Point* new_point;
	for (int i = 0; i < directionnum; i++)
	{
		auto lined = vector<Point>();
		new_point = &point;
		while (true)
		{
			new_point = &((*new_point) + scan_direction[i]);
			if (get_game_map(*new_point) != get_game_map(point))
				break;
			lined.push_back({ new_point->x, new_point->y });
		};
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

vector<Point> GameControler::PlaceChess()
{
	vector<Point>pointsPlaced;
	auto empty = GetEmpty();
	int randomlocation;
	for (int i = 0; i < 3; i++)
	{
		if (empty.size() == 0)
			return vector<Point>();
		randomlocation = rand() % empty.size();
		pointsPlaced.push_back(empty[randomlocation]);
		set_game_map(empty[randomlocation], *(comingcolor + i));
		remove(empty, randomlocation);
		*(comingcolor + i) = rand() % 7 + 1;
	}
	return pointsPlaced;
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
	//TODO:将周围的empty优先纳入可能的5子，先于block_chess
	// 撞到block_chess后换方向搜，标记 change_direction = true，留下标记，下次若回来从这里开始搜
	int value = 0;
	for (int i = 0; i < lineds.size(); i++)
	{
		size_t size = lineds[i].size();
		size_t still_need = 5 - lineds[i].size();
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
			value -= size * WEIGHT_EACH_MARGIN_CHESS;
		else
			value += size * size * size * size * WEIGHT_UNDER_5_LINEDS
			+ size * size * empty_count * WEIGHT_UNDER_5_EMPTY_CHESS
			+ size * size * size * size * size * block_chess_count * WEIGHT_UNDER_5_BLOCK_CHESS;
	}
	return value;
}

bool GameControler::check_if_repeat(vector<Point>& points)
{
	for (int i = 0; i < lineds.size(); i++)
		if (points == lineds[i])
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
