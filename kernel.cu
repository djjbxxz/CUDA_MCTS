#include "kernel.h"

int CUDA_accelerator::get_max_UBC_index()
{
	collect_data();
	compute();
	return max_index;
}
//for DEBUG
void check_container_device(thrust::device_vector<float> container,int print_num=3)
{
	thrust::host_vector<float> t(print_num);
	cout << "calculated device result:";
	for (int i = 0; i < print_num; i++)
	{
		t[i] = container[i];
		cout << t[i] << "    ";
	}
	cout << endl;
}
//for DEBUG
void check_container_host(thrust::host_vector<float> container, int print_num = 3)
{
	cout << "calculated host result:";
	for (int i = 0; i < print_num; i++)
	{
		cout << container[i] << "    ";
	}
	cout << endl;
}

void CUDA_accelerator::compute()
{
	 //My formula:  c_puct* value +  parent_count/vis_count   ~=	a*b*c/d
	thrust::transform(	
		thrust::make_zip_iterator(thrust::make_tuple(value_device.begin(), parent_visit_count_device.begin(), visit_count_device.begin())),
		thrust::make_zip_iterator(thrust::make_tuple(value_device.end(), parent_visit_count_device.end(), visit_count_device.end())),
		result.begin(),
		DotProduct());

	//// method2
	////My formula : c_puct * value + parent_count / vis_count   ~= a * b * c / d

	//thrust::transform(
	//	parent_visit_count_device.begin(), parent_visit_count_device.end(),
	//	visit_count_device.begin(),
	//	temp_result.begin(), thrust::divides<float>());


	////c_puct* value + temp_result   ~= AX + B


	//	thrust::transform(
	//		value_device.begin(), value_device.end(),
	//		visit_count_device.begin(),
	//		visit_count_device.begin(),
	//		saxpy_functor(c_puct));



	//get_max_index
	thrust::device_vector<int>index(num);
	thrust::sequence(index.begin(), index.end());
	thrust::sort_by_key(result.begin(), result.end(), index.begin(), thrust::greater<float>());
	max_index = index[0];
	

}

void CUDA_accelerator::collect_data()
{
	thrust::host_vector<float>	value_host;
	thrust::host_vector<float>	visit_count_host;
	thrust::host_vector<float>	parent_visit_count_host;
	for (size_t i = 0; i < num; i++)
	{
		value_host.push_back((*working_on)[i]->value);
		visit_count_host.push_back((*working_on)[i]->visit_count);

		//注意有无父节点
		parent_visit_count_host.push_back((*working_on)[i]->parent_node->visit_count);
	}
	value_device = value_host;
	visit_count_device = visit_count_host;
	parent_visit_count_device = parent_visit_count_host;
	result = thrust::device_vector<float>(num);
}
