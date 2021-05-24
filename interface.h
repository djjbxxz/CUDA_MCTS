#pragma once

#include "main.cpp"
#include "Node.cpp"
#include "Board.cpp"
#include "Pathfinding.cpp"
#include "GameControler.cpp"
#include "MCTS.cpp"

void get_move(
	vector<char>& last_move,
	const vector<char>& game_map,
	const vector<char>& next_three)
{
	auto mcts = MCTS(new Node(game_map, next_three));
	do_MCTS(mcts, 400);
	last_move = mcts.root->real_move->last_move;
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

	HWND hWinmine = FindWindowW(NULL, L"五彩连珠珠 ");
	GetCursorPos(&mouse);
	GetWindowRect(hWinmine, &rect);
	SetCursorPos(rect.left + 165 + 36 * move[1], rect.top + 109 + 36 * move[0]);//起点
	mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//单击
	Sleep(100);
	SetCursorPos(rect.left + 165 + 36 * move[3], rect.top + 109 + 36 * move[2]);//终点
	mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//单击
	return true;
}
