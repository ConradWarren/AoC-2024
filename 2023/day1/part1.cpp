#include "../core.h" 

int main(void){

	std::vector<std::string> input = core::Read_Data<std::vector<std::string>>("input.txt"); 	
	
	long long result = 0;
	for(int i = 0; i < input.size(); i++){
		
		int num1 = -1;
		int num2 = -1;

		for(int j = 0; j < input[i].size(); j++){	
			
			if(input[i][j] < '0' || input[i][j] > '9') continue; 

			if(num1 == -1) num1 = input[i][j] - '0'; 
			num2 = input[i][j] - '0';
		}
		
		if(num1 == -1 || num2 == -1){ 
			
			std::cout<<input[i]<<'\n';
		}
		result += num1 * 10 + num2;
	}

	std::cout<<result<<'\n';

	return 0; 
}
