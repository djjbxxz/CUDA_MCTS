#include "stdafx.h"
#include "MCTS.h"
#include "kernel.h"
constexpr auto decay_rate = 0.5;
//void MCTS::select_CUDA()
//{
//	auto num_leaf = leaves.size();
//	//prepare data
//	auto value = new float[num_leaf];
//	auto p = new float[num_leaf];
//	auto visit_count = new int[num_leaf];
//	auto parent_visit_count = new int[num_leaf];
//	for (size_t i = 0; i < num_leaf; i++)
//	{
//		value[i] = leaves[i].value;
//		p[i] = leaves[i].p;
//		visit_count[i] = leaves[i].visit_count;
//		parent_visit_count[i] = leaves[i].parent_node ? leaves[i].parent_node->visit_count : 0;
//	}
//
//	//CUDA malloc
//	float* d_value;
//	cudaMalloc(&d_value, num_leaf * sizeof(float));
//	float* d_p;
//	cudaMalloc(&d_p, num_leaf * sizeof(float));
//	int* d_visit_count;
//	cudaMalloc(&d_visit_count, num_leaf * sizeof(int));
//	int* d_parent_visit_count;
//	cudaMalloc(&d_parent_visit_count, num_leaf * sizeof(int));
//	float* d_result;
//	cudaMalloc(&d_result, num_leaf * sizeof(float));
//	cudaDeviceSynchronize();
//
//	//copy to device
//	cudaMemcpy(d_value, value, num_leaf * sizeof(float), cudaMemcpyHostToDevice);
//	cudaMemcpy(d_p, p, num_leaf * sizeof(float), cudaMemcpyHostToDevice);
//	cudaMemcpy(d_visit_count, visit_count, num_leaf * sizeof(int), cudaMemcpyHostToDevice);
//	cudaMemcpy(d_parent_visit_count, parent_visit_count, num_leaf * sizeof(int), cudaMemcpyHostToDevice);
//	cudaDeviceSynchronize();
//	//execute kernel
//	//cal_val<<<1,num_leaf>>>(d_value, 0.1f, d_p, d_visit_count, d_parent_visit_count,d_result);
//	// delete host memory
//	delete[] value;
//	delete[] p;
//	delete[] visit_count;
//	delete[] parent_visit_count;
//	//wait for execution
//	cudaDeviceSynchronize();
//
//	cudaFree(d_value);
//	cudaFree(d_p);
//	cudaFree(d_visit_count);
//	cudaFree(d_parent_visit_count);
//
//	/*auto result = new float[num_leaf];
//	cudaMemcpy(result, d_result, num_leaf * sizeof(float), cudaMemcpyDeviceToHost);*/
//	//for (size_t i = 0; i < num_leaf; i++)
//	//	cout << result[i] << endl;
//
//	auto max = new int;
//
//	//current_node = leaves[?];
//}

void MCTS::select()
{
	if (root->is_end)
		return;
	float max = 0.0;
	size_t max_index = 0;
	float ubc;
	for (size_t i = 0; i < leaves.size(); i++)
	{
		ubc = leaves[i]->get_UBC();
		if (ubc > max)
		{
			max = ubc;
			max_index = i;
		}
	}
	//保存
	current_node = leaves[max_index];

	//从叶子列表中删除
	leaves.erase(leaves.begin() + max_index);
	current_node->visit_count++;
}

void MCTS::expand()
{
	Node* new_node;
	float p[6561];
	for (int i = 0; i < 6561; i++)
		p[i] = 1;
	//获取所有可行走法
	current_node->call_estimate(p);
	for (int i = 0; i < 6561; i++)
		//创建子节点
		if (p[i] > 0)
		{
			new_node = new Node(current_node, convert_to_index(i), p[i]);
			if (!new_node->is_end)
				leaves.push_back(new_node);
			current_node->children.push_back(*new_node);
		}
}

void MCTS::backup()
{
	for (size_t i = 0; i < current_node->children.size(); i++)
	{
		current_node->value += current_node->children[i].value * decay_rate;
	}
	auto update_node = *current_node;
	while (update_node.parent_node)
	{
		update_node.parent_node->value += update_node.value * decay_rate;
		update_node = *update_node.parent_node;
	}
}
