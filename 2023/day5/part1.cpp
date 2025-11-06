#include "../core.h" 

long long Get_Min_Dest(long long num, int idx, std::vector<std::vector<std::vector<long long>>>& maps){

	if(idx >= maps.size()){
		return num; 
	} 

	int count = 0; 
	long long result = (1LL << 55); 

	for(int i = 0; i < maps[idx].size(); i++){

		if(maps[idx][i][1] <= num && maps[idx][i][1] + maps[idx][i][2] > num){
			count++; 

			long long current = Get_Min_Dest(maps[idx][i][0] + (num - maps[idx][i][1]), idx + 1, maps); 
			result = std::min(result, current); 
		}
	}
	
	if(count == 0){
		long long current = Get_Min_Dest(num, idx + 1, maps); 
		result = std::min(result ,current); 
	}
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

	for(int i = 0; i < seeds.size(); i++){
		long long current = Get_Min_Dest(seeds[i], 0, map_arr); 
		result = std::min(result, current); 
	}
	std::cout<<result<<'\n';

	return 0; 
}
