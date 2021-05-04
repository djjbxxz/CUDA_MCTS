//#include "stdafx.h"
//#include "kernel.h"
//
//
//__global__ void 
//cal_val( 
//	const float* value,
//	const float c_puct, 
//	const float* p,
//	const int* visit_count,
//	const int* parent_node_visitcount,
//	float* result)
//{
//	int i = threadIdx.x;
//	result[i] = value[i] + c_puct * p[i]* parent_node_visitcount[i] / (1 + visit_count[i] );
//}
//
//__global__ void 
//get_max(float* g_idata, int*index, unsigned int n)
//{
//	unsigned int tid = threadIdx.x;
//	unsigned idx = blockIdx.x * blockDim.x + threadIdx.x;
//	// convert global data pointer to the local point of this block
//	float* idata = g_idata + blockIdx.x * blockDim.x;
//	if (idx > n)
//		return;
//	//in-place reduction in global memory
//	for (int stride = 1; stride < blockDim.x; stride *= 2)
//	{
//		//convert tid into local array index
//		int index = 2 * stride * tid;
//		if (index < blockDim.x)
//		{
//			if (idata[index] < idata[index + stride])
//				idata[index] = idata[index + stride];
//
//		}
//		__syncthreads();
//	}
//	//write result for this block to global men
//	//if (tid == 0)
//	//	g_odata[blockIdx.x] = idata[0];
//}
//
//
////int ma1in()
////{
////	const int arraySize = 5;
////	const int a[arraySize] = { 1, 2, 3, 4, 5 };
////	const int b[arraySize] = { 10, 20, 30, 40, 50 };
////	int c[arraySize] = { 0 };
////
////	// Add vectors in parallel.
////	cudaError_t cudaStatus = addWithCuda(c, a, b, arraySize);
////	if (cudaStatus != cudaSuccess) {
////		fprintf(stderr, "addWithCuda failed!");
////		return 1;
////	}
////
////	printf("{1,2,3,4,5} + {10,20,30,40,50} = {%d,%d,%d,%d,%d}\n",
////		c[0], c[1], c[2], c[3], c[4]);
////
////	// cudaDeviceReset must be called before exiting in order for profiling and
////	// tracing tools such as Nsight and Visual Profiler to show complete traces.
////	cudaStatus = cudaDeviceReset();
////	if (cudaStatus != cudaSuccess) {
////		fprintf(stderr, "cudaDeviceReset failed!");
////		return 1;
////	}
////
////	return 0;
////}
//
//// Helper function for using CUDA to add vectors in parallel.
////cudaError_t addWithCuda(int* c, const int* a, const int* b, unsigned int size)
////{
////	int* dev_a = 0;
////	int* dev_b = 0;
////	int* dev_c = 0;
////	cudaError_t cudaStatus;
////
////	// Choose which GPU to run on, change this on a multi-GPU system.
////	cudaStatus = cudaSetDevice(0);
////	if (cudaStatus != cudaSuccess) {
////		fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
////		goto Error;
////	}
////
////	// Allocate GPU buffers for three vectors (two input, one output)    .
////	cudaStatus = cudaMalloc((void**)&dev_c, size * sizeof(int));
////	if (cudaStatus != cudaSuccess) {
////		fprintf(stderr, "cudaMalloc failed!");
////		goto Error;
////	}
////
////	cudaStatus = cudaMalloc((void**)&dev_a, size * sizeof(int));
////	if (cudaStatus != cudaSuccess) {
////		fprintf(stderr, "cudaMalloc failed!");
////		goto Error;
////	}
////
////	cudaStatus = cudaMalloc((void**)&dev_b, size * sizeof(int));
////	if (cudaStatus != cudaSuccess) {
////		fprintf(stderr, "cudaMalloc failed!");
////		goto Error;
////	}
////
////	// Copy input vectors from host memory to GPU buffers.
////	cudaStatus = cudaMemcpy(dev_a, a, size * sizeof(int), cudaMemcpyHostToDevice);
////	if (cudaStatus != cudaSuccess) {
////		fprintf(stderr, "cudaMemcpy failed!");
////		goto Error;
////	}
////
////	cudaStatus = cudaMemcpy(dev_b, b, size * sizeof(int), cudaMemcpyHostToDevice);
////	if (cudaStatus != cudaSuccess) {
////		fprintf(stderr, "cudaMemcpy failed!");
////		goto Error;
////	}
////
////	// Launch a kernel on the GPU with one thread for each element.
////	addKernel << <1, size >> > (dev_c, dev_a, dev_b);
////
////	// Check for any errors launching the kernel
////	cudaStatus = cudaGetLastError();
////	if (cudaStatus != cudaSuccess) {
////		fprintf(stderr, "addKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
////		goto Error;
////	}
////
////	// cudaDeviceSynchronize waits for the kernel to finish, and returns
////	// any errors encountered during the launch.
////	cudaStatus = cudaDeviceSynchronize();
////	if (cudaStatus != cudaSuccess) {
////		fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
////		goto Error;
////	}
////
////	// Copy output vector from GPU buffer to host memory.
////	cudaStatus = cudaMemcpy(c, dev_c, size * sizeof(int), cudaMemcpyDeviceToHost);
////	if (cudaStatus != cudaSuccess) {
////		fprintf(stderr, "cudaMemcpy failed!");
////		goto Error;
////	}
////
////Error:
////	cudaFree(dev_c);
////	cudaFree(dev_a);
////	cudaFree(dev_b);
////
////	return cudaStatus;
////}
////
