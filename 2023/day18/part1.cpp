#include "../core.h"

int main(void){
	
	std::vector<std::string> input = core::Read_Data<std::vector<std::string>>("input.txt"); 
	
	std::vector<std::pair<char, int>> nums(input.size()); 

	for(int i = 0; i< nums.size(); i++){
		std::vector<std::string> strings = core::Split_String(input[i], {' '});
		nums[i] = {strings.front().front(), std::stoi(strings[1])}; 
	}

	int y = 0; 
	int x = 0; 
	
	long long interior = 0;
	long long perimiter = 0; 
	for(int i = 0; i < nums.size(); i++){
		
		int delta_y = 0; 
		int delta_x = 0;
		
		if(nums[i].first == 'U'){
			delta_y = -1;
		}else if(nums[i].first == 'D'){
			delta_y = 1;
		}else if (nums[i].first == 'R') {
			delta_x = 1; 
		}else{
			delta_x = -1;
		}

		int next_y = y + delta_y * nums[i].second; 
		int next_x = x + delta_x * nums[i].second; 
		
		interior += x * next_y - y * next_x;
		perimiter += nums[i].second; 
		y = next_y; 
		x = next_x; 
	}
	long long area = (std::abs(interior)/2) + perimiter/2 + 1;
	std::cout<<area<<'\n';
	return 0; 
}
