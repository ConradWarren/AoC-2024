#include "../core.h" 

enum{right = 0, down = 1, left = 2, up = 3};

int Get_Min(std::vector<std::vector<int>>& grid){
	
	std::vector<std::pair<int, int>> directions = {{0,1}, {1,0}, {0, -1}, {-1, 0}};
	
	std::vector<std::vector<int>> min_loss(grid.size() * grid[0].size(), std::vector<int>(directions.size() * 4, INT_MAX));  
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
		
		node_queue.pop(); 
		if(cost > min_loss[y * grid[0].size() + x][dir * 4 + moves]) continue;

		int ty = y + directions[(dir+1)%4].first; 	
		int tx = x + directions[(dir+1)%4].second; 

		if(0 <= tx && tx < grid[0].size() && 0 <= ty && ty < grid.size() && cost + grid[ty][tx] < min_loss[ty * grid[0].size() + tx][((dir + 3)%4)*4 + 1]){ 
			min_loss[ty * grid[0].size() + tx][((dir+1)%4)*4 + 1] = cost + grid[ty][tx]; 
			node_queue.push({cost + grid[ty][tx], ty * (int)grid[0].size() + tx, (dir + 1)%4, 1}); 
		}

		ty = y + directions[(dir + 3)%4].first; 	
		tx = x + directions[(dir + 3)%4].second; 

		if(0 <= tx && tx < grid[0].size() && 0 <= ty && ty < grid.size() && cost + grid[ty][tx] < min_loss[ty * grid[0].size() + tx][((dir + 3)%4)*4 + 1]){ 
			min_loss[ty * grid[0].size() + tx][((dir+3)%4)*4 + 1] = cost + grid[ty][tx]; 
			node_queue.push({cost + grid[ty][tx], ty * (int)grid[0].size() + tx, (dir + 3)%4, 1}); 
		} 

		if(moves == 3) continue; 

		ty = y + directions[dir].first;
		tx = x + directions[dir].second; 

		if(0 <= tx && tx < grid[0].size() && 0 <= ty && ty < grid.size() && cost + grid[ty][tx] < min_loss[ty * grid[0].size() + tx][dir*4 + moves + 1]){ 
			min_loss[ty * grid[0].size() + tx][dir * 4 + moves + 1] = cost + grid[ty][tx]; 
			node_queue.push({cost + grid[ty][tx], ty * (int)grid[0].size() + tx, dir, moves + 1}); 
		} 	
	}
	
	return *std::min_element(min_loss.back().begin(), min_loss.back().end());
}


int main(void){
	
	std::vector<std::string> input = core::Read_Data<std::vector<std::string>>("input.txt"); 
	
	std::vector<std::vector<int>> grid;
	for(int i = 0; i < input.size(); i++){
		std::vector<int> current; 
		std::transform(input[i].begin(), input[i].end(), std::back_inserter(current), [](auto x){return x - '0';});
		grid.push_back(current); 
	}
	
	std::cout<<Get_Min(grid)<<'\n';
	
	return 0;
}
