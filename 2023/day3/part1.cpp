#include "../core.h" 

void Mark(std::vector<std::string>& grid, int y, int x, std::vector<std::vector<bool>>& marked){

	for(int i = x; i < grid[y].size() && grid[y][i] >= '0' && grid[y][i] <= '9'; i++){	
		marked[y][i] = true;  
	}

	for(int i = x-1; i >= 0 && grid[y][i] >= '0' && grid[y][i] <= '9'; i--){	
		marked[y][i] = true;  
	}
}

int main(void){

	std::vector<std::string> inputs = core::Read_Data<std::vector<std::string>>("input.txt");  
	std::vector<std::vector<bool>> marked(inputs.size(), std::vector<bool>(inputs[0].size(), false)); 


	std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {-1, -1}, {1, 1}, {1, -1}, {-1,1}};
	for(int i = 0; i < inputs.size(); i++){ 
		
		for(int j = 0; j < inputs[i].size(); j++){
			if(inputs[i][j] == '.' || (inputs[i][j] >= '0' && inputs[i][j] <= '9')) continue; 

			for(int z = 0; z < directions.size(); z++){
				
				int y = i + directions[z].first; 
				int x = j + directions[z].second; 

				if(y < 0 || y >= inputs.size() || x < 0 || x >= inputs[y].size()) continue; 

				if(inputs[y][x] >= '0' && inputs[y][x] <= '9') Mark(inputs, y, x, marked);
			}
		}
	} 

	long long result = 0; 
	for(int i = 0; i < inputs.size(); i++){

		long long current = 0;
		for(int j = 0; j < inputs[i].size(); j++){
			
			if(marked[i][j]){ 
				current *= 10; 
				current += inputs[i][j] - '0';
			}else{
				result += current; 
				current = 0; 
			}
		}
		result += current;
	}

	std::cout<<result<<'\n'; 
	return 0;
}
