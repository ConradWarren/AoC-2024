#include "../core.h"

enum {right = 0, down = 1, left = 2, up = 3};

int Breadth_First_Search(const std::vector<std::string>& grid, int y, int x, int dir){

	std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	std::vector<std::vector<std::vector<bool>>> seen(grid.size(), std::vector<std::vector<bool>>(grid[0].size(), std::vector<bool>(4, false)));	

	std::queue<std::pair<int,int>> node_queue;

	node_queue.push({-1, down});

	while(!node_queue.empty()){
		
		y = (node_queue.front().first == -1) ? y : node_queue.front().first / grid[0].size(); 
		x = (node_queue.front().first == -1) ? x : node_queue.front().first % grid[0].size();
		dir = node_queue.front().second; 
		node_queue.pop();

		int ty = y + directions[dir].first; 
		int tx = x + directions[dir].second; 

		if(ty >= grid.size() || tx >= grid[0].size() || ty < 0 || tx < 0) continue; 
			
		int next_dir = -1;	
		if(grid[ty][tx] == '/'){
			next_dir = (dir == right) ? up : next_dir; 	
			next_dir = (dir == up) ? right : next_dir; 	
			next_dir = (dir == left) ? down : next_dir; 	
			next_dir = (dir == down) ? left : next_dir; 	
		}else if(grid[ty][tx] == '\\'){
			next_dir = (dir == right) ? down : next_dir; 	
			next_dir = (dir == up) ? left : next_dir; 	
			next_dir = (dir == left) ? up : next_dir; 	
			next_dir = (dir == down) ? right : next_dir; 	
		}else if(grid[ty][tx] == '.'){
			next_dir = dir; 
		}else if(grid[ty][tx] == '-' && (dir == left || dir == right)){
			next_dir = dir; 
		}else if(grid[ty][tx] == '|' && (dir == up || dir == down)){
			next_dir = dir; 
		} 

		if(next_dir != -1 && !seen[ty][tx][next_dir]){
			seen[ty][tx][next_dir] = true; 
			node_queue.push({ty * grid[0].size() + tx, next_dir});
			continue; 
		}else if(next_dir != -1){
			continue; 
		}
		
		if(dir == up || dir == down){
			if(!seen[ty][tx][left]){
				seen[ty][tx][left] = true;
				node_queue.push({ty * grid[0].size() + tx, left});
			}
			if(!seen[ty][tx][right]){
				seen[ty][tx][right] = true;
				node_queue.push({ty * grid[0].size() + tx, right});
			}
		}else{
			if(!seen[ty][tx][down]){
				seen[ty][tx][down] = true;
				node_queue.push({ty * grid[0].size() + tx, down});
			}
			if(!seen[ty][tx][up]){
				seen[ty][tx][up] = true;
				node_queue.push({ty * grid[0].size() + tx, up});
			}
		}
	}
	
	int result = 0;
	for(int i = 0; i < grid.size(); i++){
		for(int j = 0; j < grid[0].size(); j++){
			
			bool is_valid = false; 
			for(int z = 0; z < directions.size(); z++){
				is_valid = is_valid || seen[i][j][z]; 
			}
			
			if(is_valid) result++;
			
		}
	}
	return result;
}


int main(void){
	
	std::vector<std::string> input = core::Read_Data<std::vector<std::string>>("input.txt"); 
	
	int result = 0; 
	for(int i = 0; i < input[0].size(); i++){
		int current = Breadth_First_Search(input, -1, i, down);
		result = std::max(current, result); 
		current = Breadth_First_Search(input, input.size(), i, up); 
		result = std::max(current, result); 
	}
	for(int i = 0; i < input.size(); i++){
		int current = Breadth_First_Search(input, i, -1, right);
		result = std::max(current, result); 
		current = Breadth_First_Search(input, i, input[0].size(), left); 
		result = std::max(current, result); 
	}
	std::cout<<result<<'\n';
	return 0; 
}
