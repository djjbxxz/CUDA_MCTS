#include "stdafx.h"
#include "stdio.h"
#include "Board.h"
#include "Node.h"
#include "kernel.h"
#include "MCTS.h"
#include "Visualization.h"
#include <conio.h>

judge_type Board::judge = nullptr;
Estimate_type Node::estimate = nullptr;

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
		r[i] = densed % 8;
		densed /= 8;
	}
	return r;
}

int convert_to_densed(int index[4])
{
	return index[0] * 8 * 8 * 8 + index[1] * 8 * 8 + index[2] * 8 + index[3];
}

int main()
{
	//≥ı ºªØ 
	auto dll = Load_library();
	Node::estimate = dll.Estimate;
	Board::judge = dll.judge;
	rand_init();


	//Board a;
	//print_board(b);
	auto mcts = MCTS(new Node());
	for (int i = 0; i < 5000; i++)
	{
		mcts.select();
		mcts.expand();
		mcts.backup();
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
	
}