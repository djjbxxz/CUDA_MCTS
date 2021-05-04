#pragma once
#include "windows.h"

typedef void (*Estimate_type)(float* p, char* game_map);
typedef int (*judge_type)(char* map, char* comingcolor, char* move);
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
	judge_type judge;
	Estimate_type Estimate;
private:
	Estimate_type load_Estimate();
	judge_type load_judge();
	HMODULE P, G;
};

