#include "../core.h" 

int main(void){

	std::vector<std::string> input = core::Read_Data<std::vector<std::string>>("input.txt"); 

	long long result = 0; 
	int id = 1; 


	for(int i = 0; i < input.size(); i++){
		
		std::vector<std::string> current = core::Split_String(input[i], {':', ';', ','}); 
		
		int green_max = 0; 
		int blue_max = 0; 
		int red_max = 0; 
		for(int j = 1; j < current.size() ; j++){ 


			std::vector<std::string> pair = core::Split_String(current[j], {' '}); 
			
			if(pair[1] == "red") red_max = std::max(std::stoi(pair[0]), red_max);
			if(pair[1] == "blue") blue_max = std::max(std::stoi(pair[0]), blue_max);
			if(pair[1] == "green") green_max = std::max(std::stoi(pair[0]), green_max);

		} 
		result += red_max * blue_max * green_max; 

	}

	std::cout<<result<<"\n";

	return 0; 
}
