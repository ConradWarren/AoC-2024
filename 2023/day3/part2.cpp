#include "../core.h" 

void Mark(std::vector<std::string>& grid, int y, int x, int id, std::vector<std::vector<int>>& marked){

	for(int i = x; i < grid[y].size() && grid[y][i] >= '0' && grid[y][i] <= '9'; i++){	
		marked[y][i] = id;  
	}

	for(int i = x-1; i >= 0 && grid[y][i] >= '0' && grid[y][i] <= '9'; i--){	
		marked[y][i] = id;  
	}
}

int main(void){

	std::vector<std::string> inputs = core::Read_Data<std::vector<std::string>>("input.txt");  
	std::vector<std::vector<int>> marked(inputs.size(), std::vector<int>(inputs[0].size(), -1)); 


	std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {-1, -1}, {1, 1}, {1, -1}, {-1,1}}; 
	int id = 1;

	for(int i = 0; i < inputs.size(); i++){ 
		
		for(int j = 0; j < inputs[i].size(); j++){
			if(inputs[i][j] != '*') continue; 

			for(int z = 0; z < directions.size(); z++){
				
				int y = i + directions[z].first; 
				int x = j + directions[z].second; 

				if(y < 0 || y >= inputs.size() || x < 0 || x >= inputs[y].size()) continue; 

				if(inputs[y][x] >= '0' && inputs[y][x] <= '9' && marked[y][x] == -1) Mark(inputs, y, x, id++, marked);
			}
		}
	} 

	std::unordered_map<int, std::pair<int, int>> id_num_map;  

	for(int i = 0; i < inputs.size(); i++){

		long long current = 0; 
		int last_id_seen = -1;
		for(int j = 0; j < inputs[i].size(); j++){
			
			if(marked[i][j] != -1){ 
				last_id_seen = marked[i][j];
				current *= 10; 
				current += inputs[i][j] - '0';
			}else if(last_id_seen != -1){ 
				id_num_map[last_id_seen] = {current, -1}; 
				last_id_seen = -1;
				current = 0; 
			}
		} 

		if(last_id_seen != -1){
			id_num_map[last_id_seen] = {current, -1};	
		}
	} 

	long long result = 0; 
	for(int i = 0; i < inputs.size(); i++){ 
		
		for(int j = 0; j < inputs[i].size(); j++){
			if(inputs[i][j] != '*') continue;  

			id = i * inputs[i].size() + j; 
	
			int count = 0; 
			long long ratio = 1; 
			for(int z = 0; z < directions.size(); z++){
				
				int y = i + directions[z].first; 
				int x = j + directions[z].second; 

				if(y < 0 || y >= inputs.size() || x < 0 || x >= inputs[y].size()) continue; 

				if(marked[y][x] == -1) continue; 
				
				if(id_num_map[marked[y][x]].second != id){
					count++; 
					ratio *= id_num_map[marked[y][x]].first; 
					id_num_map[marked[y][x]].second = id;
				}
			}
			if(count >= 2) result += ratio;
		}
	}

	std::cout<<result<<'\n'; 
	return 0;
}
