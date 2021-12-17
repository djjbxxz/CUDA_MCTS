#pragma once
#include "MCTS.h"
#include "init_random.h"
#include "threadpool.h"

ThreadPool executor{ THREAD_MAX_NUM };

bool get_move(
	std::vector<char>& last_move,
	const std::vector<char>& game_map,
	const std::vector<char>& next_three)
{
	auto mcts = MCTS(new Node(game_map, next_three),3);
	if (mcts.do_MCTS(5) != -1)
	{
		last_move = mcts.root->last_move;
		return true;
	}
	else
		return false;
}

void RefreshChessBoardStatus(std::vector<char>& map, std::vector<char>& next_three)
{
	for (int i = 0; i < 81; i++)
		map[i] = *(char*)(0x00430040 + i);

	for (int i = 0; i < 3; i++)
		next_three[i] = *(char*)(0x00430150 + i);
}

bool Move(const std::vector<char> move)
{
	POINT mouse;
	RECT rect;

	HWND hWinmine = FindWindowW(nullptr, L"五彩连珠珠 ");
	GetCursorPos(&mouse);
	GetWindowRect(hWinmine, &rect);
	SetCursorPos(rect.left + 165 + 36 * move[1], rect.top + 109 + 36 * move[0]);//起点
	mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//单击
	Sleep(100);
	SetCursorPos(rect.left + 165 + 36 * move[3], rect.top + 109 + 36 * move[2]);//终点
	mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//单击
	return true;
}


DWORD WINAPI all_start(PVOID pParam)
{
	init_random();
	while (true) {
		auto map = std::vector<char>(81, 0);
		auto next_three = std::vector<char>(3, -1);
		auto last_move = std::vector<char>(4, -1);
		RefreshChessBoardStatus(map, next_three);

		if (get_move(last_move, map, next_three))
			Move(last_move);
		Sleep(1000);
	}
}