#include "../core.h" 

enum{right = 0, down = 1, left = 2, up = 3};

int Get_Min(std::vector<std::vector<int>>& grid){
	
	std::vector<std::pair<int, int>> directions = {{0,1}, {1,0}, {0, -1}, {-1, 0}};
	
	std::vector<std::vector<int>> min_loss(grid.size() * grid[0].size(), std::vector<int>(directions.size() * 11, INT_MAX));  
	std::priority_queue<std::array<int, 4>, std::vector<std::array<int,4>>, std::greater<>> node_queue; 

	min_loss[0][right * 4] = 0; 
	min_loss[0][down * 4] = 0;
	
	node_queue.push({0, 0, right, 0}); 
	node_queue.push({0, 0, down, 0});
	
	while(!node_queue.empty()){
		
		int cost = node_queue.top()[0];
		int y = node_queue.top()[1]/grid[0].size(); 
		int x = node_queue.top()[1]%grid[0].size(); 
		int dir = node_queue.top()[2]; 
		int moves = node_queue.top()[3]; 
		
		//std::cout<<y<<" "<<x<<" "<<dir<<std::endl;
		node_queue.pop(); 
		if(cost > min_loss[y * grid[0].size() + x][dir * 11 + moves]) continue;

		int ty = y + directions[(dir+1)%4].first; 	
		int tx = x + directions[(dir+1)%4].second; 

		if(moves >= 4 && 0 <= tx && tx < grid[0].size() && 0 <= ty && ty < grid.size() && cost + grid[ty][tx] < min_loss[ty * grid[0].size() + tx][((dir + 3)%4)*11 + 1]){ 
			min_loss[ty * grid[0].size() + tx][((dir+1)%4)*11 + 1] = cost + grid[ty][tx]; 
			node_queue.push({cost + grid[ty][tx], ty * (int)grid[0].size() + tx, (dir + 1)%4, 1}); 
		}

		ty = y + directions[(dir + 3)%4].first; 	
		tx = x + directions[(dir + 3)%4].second; 

		if(moves >= 4 && 0 <= tx && tx < grid[0].size() && 0 <= ty && ty < grid.size() && cost + grid[ty][tx] < min_loss[ty * grid[0].size() + tx][((dir + 3)%4)*11 + 1]){ 
			min_loss[ty * grid[0].size() + tx][((dir+3)%4)*11 + 1] = cost + grid[ty][tx]; 
			node_queue.push({cost + grid[ty][tx], ty * (int)grid[0].size() + tx, (dir + 3)%4, 1}); 
		} 

		if(moves == 10) continue; 

		ty = y + directions[dir].first;
		tx = x + directions[dir].second; 

		if(0 <= tx && tx < grid[0].size() && 0 <= ty && ty < grid.size() && cost + grid[ty][tx] < min_loss[ty * grid[0].size() + tx][dir*11 + moves + 1]){ 
			min_loss[ty * grid[0].size() + tx][dir * 11 + moves + 1] = cost + grid[ty][tx]; 
			node_queue.push({cost + grid[ty][tx], ty * (int)grid[0].size() + tx, dir, moves + 1}); 
		} 	
	}
	
	int result = INT_MAX;
	for(int i = 0; i < min_loss.back().size(); i++){
		
		if(i%11 < 4) continue; 

		result = std::min(min_loss.back()[i], result);
	}
	return result; 
}


int main(void){
	
	std::vector<std::string> input = core::Read_Data<std::vector<std::string>>("input.txt"); 
	
	std::vector<std::vector<int>> grid(input.size(), std::vector<int>(input[0].size()));
	
	for(int i = 0; i < input.size(); i++){
		std::transform(input[i].begin(), input[i].end(), grid[i].begin(), [](char x){return x - '0';});
	}	
	std::cout<<Get_Min(grid)<<'\n';
	
	return 0;
}
