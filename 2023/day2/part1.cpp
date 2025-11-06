#include "../core.h" 

int main(void){

	std::vector<std::string> input = core::Read_Data<std::vector<std::string>>("input.txt"); 
	constexpr int red_limit = 12;
	constexpr int blue_limit = 14; 
	constexpr int green_limit = 13; 

	long long result = 0; 
	int id = 1; 


	for(int i = 0; i < input.size(); i++){
		
		std::vector<std::string> current = core::Split_String(input[i], {':', ';', ','}); 
		bool is_valid = true;
			
		for(int j = 1; j < current.size() && is_valid; j++){ 


			std::vector<std::string> pair = core::Split_String(current[j], {' '}); 

			is_valid = is_valid && (pair[1] != "red" || std::stoi(pair[0]) <= red_limit); 
			is_valid = is_valid && (pair[1] != "blue" || std::stoi(pair[0]) <= blue_limit); 
			is_valid = is_valid && (pair[1] != "green" || std::stoi(pair[0]) <= green_limit); 	
		}

		if(is_valid) result += id; 
		id++;
	}

	std::cout<<result<<"\n";

	return 0; 
}
