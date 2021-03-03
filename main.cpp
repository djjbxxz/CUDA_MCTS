#include "Node.h"
#include "Load_library.h"
void rand_init()
{
	LARGE_INTEGER seed;
	QueryPerformanceFrequency(&seed);
	QueryPerformanceCounter(&seed);
	srand(seed.QuadPart);
}


int main(int argc, char** argv)
{
	//auto node = Node();
	auto dll = Load_library();
	dll.Estimate;
	dll.judge;
}