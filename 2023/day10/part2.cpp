#include "../core.h"

int Get_Loop_Size(std::vector<std::string>& grid, int y, int x, std::vector<int>& outputs){

	
	std::vector<std::pair<int, int>> directions = {{-1,0}, {1,0}, {0, 1},{0,-1}}; 
	
	int target_y = y; 
	int target_x = x; 
	std::vector<std::vector<int>> seen(grid.size(), std::vector<int>(grid[0].size(), -1)); 
	
	int result = -1;
	int area = 0;

	for(int i = 0; i < directions.size(); i++){
		
		int current_dir = i;  
		int current_dist = 0;
		int current_area = 0; 
		y = target_y;  
		x = target_x;

		do{
			
			int ty = y + directions[current_dir].first; 	
			int tx = x + directions[current_dir].second;	
			
			if(ty < 0 || ty >= grid.size() || tx < 0 || tx >= grid[0].size()){ 
				current_dist = -1;
				break;
			} 
			current_area += (x * ty) - (y * tx); 
			
			if(seen[ty][tx] == i){
				current_dist = -1;
				break; 
			}
			seen[ty][tx] = i;

			if(ty == target_y && tx == target_x) break; 
	
			if(outputs[static_cast<int>(grid[ty][tx]) * 4 + current_dir] == -1){
				current_dist = -1; 
				break; 
			} 

			current_dir = outputs[static_cast<int>(grid[ty][tx])*4 + current_dir]; 
			current_dist++;
						
			y = ty; 
			x = tx;

		}while(y != target_y || x != target_x);

		if(current_dist > result){
			area = (std::abs(current_area) - current_dist + 1)/2;
			result = current_dist; 
		}

	}
	return area; 
}

enum{
	up = 0, down = 1, right = 2, left = 3
};
int main(void){ 

	std::vector<std::string> grid = core::Read_Data<std::vector<std::string>>("input.txt"); 
	
	std::vector<int> outputs(256 * 4, -1); 
	std::vector<std::pair<int, int>> directions = {{-1,0}, {1,0}, {0, 1},{0,-1}}; 
 
	outputs[static_cast<int>('|') * 4 + up] = up; 
	outputs[static_cast<int>('|') * 4 + down] = down;
	outputs[static_cast<int>('-') * 4 + right] = right;
	outputs[static_cast<int>('-') * 4 + left] = left;
	outputs[static_cast<int>('L') * 4 + down] = right;
	outputs[static_cast<int>('L') * 4 + left] = up;
	outputs[static_cast<int>('J') * 4 + down] = left;
	outputs[static_cast<int>('J') * 4 + right] = up;
	outputs[static_cast<int>('7') * 4 + right] = down;
	outputs[static_cast<int>('7') * 4 + up] = left;
	outputs[static_cast<int>('F') * 4 + left] = down;
	outputs[static_cast<int>('F') * 4 + up] = right;
	
	int result = 0;

	for(int i = 0; i < grid.size() * grid[0].size(); i++){
		
		if(grid[i/grid[0].size()][i%grid[0].size()] != 'S') continue;
		
		result = Get_Loop_Size(grid, i/grid[0].size(), i%grid[0].size(), outputs); 	
		break; 
	}

	std::cout<<result<<'\n';
	return 0; 
}
