#include "stdafx.h"
#include "stdio.h"
#include "Board.h"
#include "Node.h"
#include "kernel.h"
#include "MCTS.h"
#include "Visualization.h"
#include <conio.h>
#include "Pathfinding.h"
#include "GameControler.h"
#include <Algorithm>

using namespace visual;

void rand_init()
{
	LARGE_INTEGER seed;
	QueryPerformanceFrequency(&seed);
	QueryPerformanceCounter(&seed);
	srand(seed.QuadPart);
}

//void print_board(Node a)
//{
//	//print next_three
//	cout << "      ";
//	for (int i = 0; i < a.next_three.size(); i++)
//		cout << int(a.next_three[i]) << " ";
//	cout << endl;
//	//print game_map
//	for (char i = 0; i < a.game_map.size(); i++)
//	{
//		cout << int(a.game_map[i]) << " ";
//		if ((i + 1) % 9 == 0)cout << endl;
//	}
//}

vector<char> convert_to_index(int densed)
{
	auto r = vector<char>(4, 0);
	for (int i = 3; i >= 0; i--)
	{
		r[i] = densed % 9;
		densed /= 9;
	}
	return r;
}

int convert_to_densed(int index[4])
{
	return index[0] * 8 * 8 * 8 + index[1] * 8 * 8 + index[2] * 8 + index[3];
}



int main()
{
	rand_init();


	// test  game_map
	vector<char>_game_map(81, 0);
	_game_map[0] = 1;
	_game_map[1] = 1;
	_game_map[2] = 1;
	_game_map[3] = 1;

	_game_map[8] = 1;
	_game_map[17] = 1;

	auto node = new Node();
	//node->game_map = _game_map;//debug地图
	auto mcts = MCTS(node);


	for (int j = 0; j < 100; j++)
	{
		for (int i = 0; i < 1; i++)
		{
			//mcts.select_CUDA();
			mcts.select();
			mcts.expand();
			mcts.backup();

		}
		mcts.play();
		Show_node(mcts.root->parent_node);
	}


	//Node start;
	//SHARED MCTS mcts(start);

	//printf("%d\n", start.test);

	////test(start, mcts);

	//printf("%d\n", start.test);

	//test << <1, 1 >> > (start, mcts);

	//printf("%d\n", start.test);

	//test << <1, 3 >> > (start, mcts);

	//printf("%d\n", start.test);
	return 0;
}