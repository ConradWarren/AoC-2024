#include "../core.h" 


long long Gen_Diff(const std::vector<long long>& nums){

	if(nums.size() == 2){
		return nums.front() - nums.back();  
	}
	
	std::vector<long long> next(nums.size() - 1); 
	bool is_const = true; 
	for(int i = nums.size()-2; i >= 0; i--){	
		next[i] = nums[i] - nums[i+1]; 
		is_const = (is_const && next[i] == next.back()); 
	}
	
	if(is_const) return next.front(); 

	return next.front() + Gen_Diff(next); 
} 


int main(void){
	
	std::vector<std::vector<long long>> nums = core::Read_Data<std::vector<std::vector<long long>>>("input.txt"); 
	
	long long sum = 0; 
	for(int i = 0; i < nums.size(); i++){
		sum += nums[i].front() + Gen_Diff(nums[i]); 
	}		
	std::cout<<sum<<'\n';


	return 0; 
}
