#include "../core.h"

int main(void){

	std::string input = core::Read_Data<std::string>("input.txt");

	std::vector<std::string> sequences = core::Split_String(input, {',', '\n'}); 

	long long result = 0; 
	for(int i = 0; i < sequences.size(); i++){
		
		long long current = 0; 
		for(int j = 0; j < sequences[i].size(); j++){
			current += sequences[i][j];
			current *= 17; 
			current %= 256;  
		}
		result += current; 
	}

	std::cout<<result<<'\n';

	return 0;
}
