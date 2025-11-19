#include "../core.h"

long long Get_Count(std::string& str, std::vector<int>& nums, int idx, int idx_target, std::vector<long long>& cache){

	if(idx >= str.size() && idx_target >= nums.size()) return 1;
	if(idx >= str.size()) return 0; 	
	
	if(cache[idx * (nums.size() + 1) + idx_target] != -1) return cache[idx * (nums.size() + 1) + idx_target];

	long long skip = (str[idx] == '.' || str[idx] == '?') ? Get_Count(str, nums, idx + 1, idx_target, cache) : 0;

	if(idx_target >= nums.size()) return cache[idx * (nums.size() + 1) + idx_target] = skip;  	
				
	if(idx + nums[idx_target] > str.size()) return cache[idx * (nums.size() + 1) + idx_target] = skip; 
	
	for(int i = idx; i < idx + nums[idx_target]; i++){
		if(str[i] == '.') return cache[idx * (nums.size() + 1) + idx_target] = skip; 	
	}
	if(idx + nums[idx_target] < str.size() && str[idx + nums[idx_target]] == '#') return cache[idx * (nums.size() + 1) + idx_target] = skip; 
	long long take = Get_Count(str, nums, idx+nums[idx_target]+1, idx_target + 1, cache); 

	return cache[idx * (nums.size() + 1) + idx_target] = skip + take; 
}  

int main(void){
	
	std::vector<std::string> input = core::Read_Data<std::vector<std::string>>("input.txt"); 
	std::vector<std::string> sequences(input.size()); 
	std::vector<std::vector<int>> nums(input.size()); 

	for(int i = 0; i < input.size(); i++){
		std::vector<std::string> current = core::Split_String(input[i], {' '});

		sequences[i] = current[0];
		
		nums[i] = core::Split_Nums<std::vector<int>>(current[1]);
	}

	long long result = 0; 
	for(int i = 0; i < input.size(); i++){
		
		std::vector<long long> cache((nums[i].size() + 1) * sequences[i].size(), -1); 
			
		
		long long current = Get_Count(sequences[i], nums[i], 0, 0, cache);
		result += current; 
		
	}

	std::cout<<result<<'\n';
	return 0; 
}
