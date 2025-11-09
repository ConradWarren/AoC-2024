#include "../core.h" 

int Get_Type(const std::vector<int>& nums){

	std::array<int, 15> counts{}; 
	int joker_count = 0; 

	for(int i = 0; i < nums.size(); i++){
		if(nums[i] == 1) joker_count++; 	
		else counts[nums[i]]++; 
		
	} 

	bool has_five = false; 
	bool has_quad = false; 
	bool has_full_house = false; 
	bool has_tripple = false; 	
	bool has_two_pair = false;
	bool has_pair = false; 

	for(int i = 0; i < counts.size(); i++){
		
		if(counts[i] == 5) has_five = true; 
		else if(counts[i] == 4) has_quad = true; 
		else if(counts[i] == 3) has_tripple = true;
		else if(counts[i] == 2 && has_pair) has_two_pair = true; 
		else if(counts[i] == 2) has_pair = true; 
	} 

	if(has_tripple && has_pair) has_full_house = true; 

	if(has_quad && joker_count) has_five = true; 
	else if(has_tripple && joker_count == 2) has_five = true; 
	else if(joker_count >= 4) has_five = true; 
	else if(has_pair && joker_count == 3) has_five = true;  

	else if(joker_count == 3 || (has_pair && joker_count == 2)) has_quad = true;
	else if(joker_count == 1 && has_tripple) has_quad = true; 
	
	else if(joker_count == 1 && has_two_pair) has_full_house = true; 
	
	else if(joker_count == 2) has_tripple = true; 
	else if(joker_count == 1 && has_pair) has_tripple = true; 

	else if(joker_count == 1) has_pair = true; 	
	
	if(has_five) return 6; 
	if(has_quad) return 5; 
	if(has_full_house) return 4; 
	if(has_tripple) return 3; 
	if(has_two_pair) return 2; 
	if(has_pair) return 1; 

	return 0; 
}


int main(void){

	std::vector<std::string> input = core::Read_Data<std::vector<std::string>>("input.txt");

	std::vector<std::pair<int, std::pair<std::vector<int>, int>>> hands(input.size());

	for(int i = 0; i < input.size(); i++){
		std::vector<std::string> current = core::Split_String(input[i], {' '}); 

		std::vector<int> nums(current[0].size());
		for(int j = 0; j < nums.size(); j++){
			if(current[0][j] >= '2' && current[0][j] <= '9') nums[j] = current[0][j] - '0'; 
			else if(current[0][j] == 'T') nums[j] = 10; 
			else if(current[0][j] == 'J') nums[j] = 1; 
			else if(current[0][j] == 'Q') nums[j] = 12; 
			else if(current[0][j] == 'K') nums[j] = 13;
			else nums[j] = 14;
		}
		hands[i] = {Get_Type(nums), {nums, std::stoll(current[1])}};
	} 

	std::sort(hands.begin(), hands.end()); 
	
	std::size_t result = 0; 
	for(std::size_t i = 0; i < hands.size(); i++){
		result += (i+1) * hands[i].second.second;
	} 


	std::cout<<result<<'\n';
	return 0; 
}
