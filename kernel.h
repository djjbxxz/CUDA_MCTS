#pragma once
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include "Node.h"
#include <thrust/functional.h>
#include <thrust/sequence.h>
#include <thrust/sort.h>

#define c_puct 0.5
// My formula:  c_puct* value +  parent_count/vis_count   ~=	a*b*c/d

typedef thrust::tuple<float, float, float> Float3;
struct DotProduct : public thrust::unary_function<Float3, float>
{
	__host__ __device__
		float operator()(const Float3& a) const
	{
		return  c_puct * thrust::get<0>(a) + thrust::get<1>(a) / thrust::get<2>(a);
	}
};

// method2
//struct saxpy_functor
//{
//	const float a;
//
//	saxpy_functor(float _a) : a(_a) {}
//
//	__host__ __device__
//		float operator()(const float& x, const float& y) const {
//		return a * x + y;
//	}
//};

class CUDA_accelerator
{
public:
	CUDA_accelerator(std::vector<Node*>* leaves) :working_on(leaves)
	{
		num = working_on->size();
	}
public:
	int get_max_UBC_index();
private:
	void collect_data();
	void compute();


private:
	std::vector<Node*>*			working_on;
	size_t						num;
	thrust::device_vector<float>value_device;
	thrust::device_vector<float>visit_count_device;
	thrust::device_vector<float>parent_visit_count_device;
	thrust::device_vector<float>result;
	//thrust::device_vector<float>temp_result;
	int max_index;
};