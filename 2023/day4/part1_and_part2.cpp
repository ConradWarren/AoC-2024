#include "../core.h" 

int main(void){

	std::vector<std::string> inputs = core::Read_Data<std::vector<std::string>>("input.txt"); 
	std::vector<int> delta(inputs.size(), 0); 

	int current_count = 1; 
	long long result1 = 0;
	long long result2 = 0; 
	for(int i = 0; i < inputs.size(); i++){ 

		current_count += delta[i];
		
		std::vector<std::string> current = core::Split_String(inputs[i], {':', '|'}); 

		std::vector<int> nums1 = core::Split_Nums<std::vector<int>>(current[1]); 
		std::vector<int> nums2 = core::Split_Nums<std::vector<int>>(current[2]); 

		std::unordered_set<int> winning_nums; 

		for(int j = 0; j < nums1.size(); j++){
			winning_nums.insert(nums1[j]);
		}

		int count = 0;
		for(int j = 0; j < nums2.size(); j++){
			
			if(winning_nums.find(nums2[j]) != winning_nums.end()) count++;
		}

		if(count > 0) result1 += 1LL << (count - 1); 

		if(count > 0 && i + 1 < delta.size()){
			delta[i+1] += current_count; 
		}
		if(count > 0 && i + count + 1 < delta.size()){
			delta[i + count + 1] -= current_count; 
		} 
		result2 += current_count; 
	} 

	std::cout<<result1<<'\n'; 
	std::cout<<result2<<'\n';

	return 0;
}
