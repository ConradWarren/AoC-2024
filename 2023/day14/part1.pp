#include "../core.h" 

int main(void){
	
	std::vector<std::string> grid = core::Read_Data<std::vector<std::string>>("input.txt"); 
	
	long long result = 0; 
	for(int j = 0; j < grid[0].size(); j++){
		
		int edge = 0; 
		for(int i = 0; i < grid.size(); i++){
			
			if(grid[i][j] == 'O'){
				result += grid.size()-edge; 
				edge++; 
			}else if(grid[i][j] == '#'){
				edge = i + 1; 
			}	
		}
	}
	std::cout<<result<<'\n';

	return 0; 
}
