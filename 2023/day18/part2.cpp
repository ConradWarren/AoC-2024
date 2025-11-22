#include "../core.h"

long long Get_Num(const std::string& hex_str){
	
	long long current = 0; 
	for(int i = 0; i < hex_str.size(); i++){
		
		current *= 16;
		if(std::isdigit(hex_str[i])){
			current += hex_str[i] - '0';	
		}else{
			current += hex_str[i] - 'a' + 10;
		}
	}
	
	return current;
}

int main(void){
	
	std::vector<std::string> input = core::Read_Data<std::vector<std::string>>("input.txt"); 
	
	std::vector<std::pair<char, long long>> nums(input.size()); 

	for(int i = 0; i< nums.size(); i++){
		std::vector<std::string> strings = core::Split_String(input[i], {' ', ')', '('});
		nums[i] = {strings.back().back(), Get_Num(std::string(strings.back().begin()+1, strings.back().end() - 1))};
	}

	int y = 0; 
	int x = 0; 
	
	long long interior = 0;
	long long perimiter = 0; 
	for(int i = 0; i < nums.size(); i++){
		
		long long delta_y = 0; 
		long long delta_x = 0;
		
		if(nums[i].first == '3'){
			delta_y = -1;
		}else if(nums[i].first == '1'){
			delta_y = 1;
		}else if (nums[i].first == '0') {
			delta_x = 1; 
		}else{
			delta_x = -1;
		}

		long long next_y = y + delta_y * nums[i].second; 
		long long next_x = x + delta_x * nums[i].second; 
		
		interior += x * next_y - y * next_x;
		perimiter += nums[i].second; 
		y = next_y; 
		x = next_x; 
	}
	long long area = (std::abs(interior)/2) + perimiter/2 + 1;
	std::cout<<area<<'\n';
	return 0; 
}
