#pragma once
#include <vector>
//#include < cuda.h >
#include "windows.h"
//#include "cuda_runtime.h"
//#include "device_launch_parameters.h"
#include <iostream>



//#define  SHARED 	__device__ __managed__

using namespace std;
int convert_to_densed(int index[4]);
vector<char> convert_to_index(int densed);