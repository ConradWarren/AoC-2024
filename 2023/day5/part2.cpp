#include "../core.h" 

long long Get_Min_Dest(long long low, long long high, int idx, std::vector<std::vector<std::vector<long long>>>& maps){

	if(low > high){
		return 1LL << 50; 
	}
	if(idx >= maps.size()){
		return low; 
	} 

	int count = 0; 
	long long result = (1LL << 55); 

	for(int i = 0; i < maps[idx].size() && low <= high; i++){
		
		long long low_range = maps[idx][i][1]; 
		long long high_range = maps[idx][i][1] + maps[idx][i][2]-1; 

		long long low_intersection = std::max(low, low_range); 
		long long high_intersection = std::min(high, high_range); 

		if(low_intersection > high_intersection) continue; 

		long long current = Get_Min_Dest(maps[idx][i][0] + low_intersection - maps[idx][i][1],maps[idx][i][0] + high_intersection - maps[idx][i][1], idx + 1, maps);
		result = std::min(result, current); 

		if(low_intersection == low && high_intersection == high){
			return result; 
		}
		
		current = Get_Min_Dest(low, low_intersection - 1, idx, maps); 
		result = std::min(result, current); 
		current = Get_Min_Dest(high_intersection + 1, high, idx, maps);
		result = std::min(result, current); 

		return result; 
	}

	long long current = Get_Min_Dest(low, high, idx+1, maps); 
	result = std::min(current, result); 
	
	return result; 
}
int main(void){
	
	std::vector<std::string> inputs = core::Read_Data<std::vector<std::string>>("input.txt"); 

	std::vector<long long> seeds = core::Split_Nums<std::vector<long long>>(inputs.front());

	int idx = 0; 
	std::vector<std::vector<std::vector<long long>>> map_arr(7); 
	for(int i = 3; i < inputs.size(); i++){

		if(inputs[i].empty()){
			i++; 
			idx++; 
			continue; 
		}

		std::vector<long long> nums = core::Split_Nums<std::vector<long long>>(inputs[i]); 

		map_arr[idx].push_back(nums); 
	} 

	long long result = (1LL << 50); 

	for(int i = 0; i + 1 < seeds.size(); i += 2){
		long long current = Get_Min_Dest(seeds[i], seeds[i] + seeds[i+1] - 1, 0, map_arr); 
		result = std::min(result, current); 
	}
	std::cout<<result<<'\n';

	return 0; 
}
