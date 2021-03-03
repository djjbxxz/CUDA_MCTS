#include "Load_library.h"
Estimate_type Load_library::load_Estimate()
{
	auto PathFinding = LoadLibrary("DLL/PathFindingDllforPython.dll");
	if (PathFinding)
	{
		P = PathFinding;
		Estimate_type Estimate_func = (Estimate_type)GetProcAddress(PathFinding, "Estimate");
		return Estimate_func;
	}
	else
		return Estimate_type();
}

judge_type Load_library::load_judge()
{
	auto GameControler = LoadLibrary("DLL/GameControlerDLL.dll");
	if (GameControler)
	{
		G = GameControler;
		auto judge_func = (judge_type)GetProcAddress(GameControler, "judge");
		return judge_func;
	}
	else
		return judge_type();
}
