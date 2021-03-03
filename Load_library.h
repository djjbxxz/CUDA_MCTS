#pragma once
#include"windows.h"
typedef void (*Estimate_type)(float* p, int* game_map);
typedef int (*judge_type)(int* map, int* comingcolor, int* move);
class Load_library
{
public:
	Load_library()
	{
		Estimate = load_Estimate();
		judge = load_judge();
	}

	~Load_library()
	{
		FreeLibrary(P);
		FreeLibrary(G);
	}
public:
	Estimate_type Estimate;
	judge_type judge;
private:
	Estimate_type load_Estimate();
	judge_type load_judge();
	HMODULE P, G;
};

