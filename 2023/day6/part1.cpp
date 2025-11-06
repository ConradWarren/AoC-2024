#include "../core.h" 

int main(void){ 

	std::vector<std::vector<int>> input = core::Read_Data<std::vector<std::vector<int>>>("input.txt"); 
		
	int result = 1; 
	for(int i = 0; i < input[0].size(); i++){
		
		int time_limit = input[0][i]; 
		int target_distance = input[1][i];
		int count = 0; 

		for(int j = 1; j < time_limit; j++){
			
			int distance = j * (time_limit - j); 

			if(distance > target_distance){
				count++; 
			}
		}
		result *= count;
	}		
	std::cout<<result<<'\n'; 

	return 0;
}
