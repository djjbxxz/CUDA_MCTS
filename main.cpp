#include "Node.h"

void rand_init()
{
	LARGE_INTEGER seed;
	QueryPerformanceFrequency(&seed);
	QueryPerformanceCounter(&seed);
	srand(seed.QuadPart);
}

int main(int argc, char** argv)
{


}