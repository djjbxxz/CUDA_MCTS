#include "Visualization.h"
#include <iostream>
#include <sstream>
#include <string.h>
#include <conio.h>
#define circlesize 20
using namespace visual;
int Show_node::color[8] = {
	0xFFFFFF,
	0x009C08,
	0xED1C24,
	0x000084,
	0xB5A518,
	0x18C6F7,
	0xC618C6,
	0x943100
};

void Show_node::draw()
{
	init();
	drawlines();
	drawtchess();
	drawnextThree();
	drawscore();
	drawlastmove();
	getch();
}

void Show_node::drawlines()
{
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	for (int i = 100; i <= 550; i += 50)
		line(50, i, 500, i);
	for (int i = 50; i <= 500; i += 50)
		line(i, 100, i, 550);
	setlinestyle(PS_DASH, 2);
	for (int i = 200; i <= 350; i += 50)
		line(i, 50, i, 100);
	line(200, 50, 350, 50);
}

void Show_node::init()
{
	initgraph(550, 600);
	setbkcolor(WHITE);
	cleardevice();
}

void Show_node::drawtchess()
{
	for (int i = 0; i < 81; i++)
		if (game_map[i] > 0)
			_plotchess(to_coord(i, game_map[i]));
}

void Show_node::drawnextThree()
{
	setlinestyle(PS_SOLID, 3);
	for (int i = 0; i < 3; i++)
	{
		setlinecolor(color[next_three[i]]);
		setfillcolor(color[next_three[i]]);
		fillcircle(225 + 50 * i, 75, circlesize);
	}

}

void Show_node::drawscore()
{
	settextcolor(BLACK);
	string s1("score:");
	s1 += to_string(score);
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 27;						// 设置字体高度为 48
	_tcscpy_s(f.lfFaceName, _T("Consolas"));		// 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式
	outtextxy(375, 62, _T(s1.c_str()));
}

void Show_node::drawlastmove()
{
	if (node->real_move)
	{
		settextcolor(BLACK);

		TCHAR S[] = _T("S");
		TCHAR E[] = _T("E");

		
		outtextxy(70 + node->real_move->last_move[1] * 50, 105 + node->real_move->last_move[0] * 50, S);
		outtextxy(70 + node->real_move->last_move[3] * 50, 105 + node->real_move->last_move[2] * 50, E);

	}
}

visual::Point Show_node::to_coord(char index, char color)
{
	char x = index % 9;
	char y = (index / 9) % 9;
	return { x,y,color };
}

void Show_node::_plotchess(visual::Point point)
{
	setlinestyle(PS_SOLID, 3);
	setlinecolor(color[point.color]);
	setfillcolor(color[point.color]);
	fillcircle(75 + point.x * 50, 125 + point.y * 50, circlesize);

}
