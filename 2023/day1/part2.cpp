#include "../core.h" 

int main(void){

	std::vector<std::string> input = core::Read_Data<std::vector<std::string>>("input.txt"); 
	std::vector<std::string> digits = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	
	long long result = 0;
	for(int i = 0; i < input.size(); i++){
		
		int num1 = -1;
		int num2 = -1;

		for(int j = 0; j < input[i].size(); j++){	
			
			if(input[i][j] >= '0' && input[i][j] <= '9'){
				num1 = (num1 == -1) ? input[i][j] - '0' : num1; 
				num2 = input[i][j] - '0'; 
				continue;
			} 

			for(int z = 0; z < digits.size(); z++){
				
				if(input[i].substr(j, digits[z].size()) != digits[z]) continue; 

				num1 = (num1 == -1) ? z + 1 : num1; 
				num2 = z + 1;
			}
		}
		
		result += num1 * 10 + num2;
	}

	std::cout<<result<<'\n';

	return 0; 
}
