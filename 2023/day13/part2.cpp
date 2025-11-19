#include "../core.h" 

int get_conflicts_row(std::string& row, int idx_left, int idx_right){
	
	if(idx_right >= row.size() || idx_left < 0) return 0;  
	
	int result = 0; 
	while(idx_left >= 0 && idx_right < row.size()){
			
		if(row[idx_left] != row[idx_right]){
			result++; 
		}

		idx_left--; 
		idx_right++;
	}
	return result; 
} 

int get_conflicts_column(std::vector<std::string>& grid,int coloumn_idx, int idx_top, int idx_bottom){
	
	if(idx_bottom >= grid.size() || idx_top < 0) return 0; 

	int result = 0;   		
	while(idx_top >= 0 && idx_bottom < grid.size()){
		
		if(grid[idx_bottom][coloumn_idx] != grid[idx_top][coloumn_idx]){
			result++;  
		} 
		  
		idx_top--; 
		idx_bottom++;
	}
		
	return result; 
}

long long Get_Score(std::vector<std::string>& input){
		
	long long result = 0; 

	for(int i = 0; i < input.size(); i++){
		
		int count = 0; 
		for(int j = 0; j < input[0].size(); j++){
			count += get_conflicts_column(input, j, i, i+1);
		}
		if(count == 1) return result += 100 * (i+1); 
	}

	for(int i = 0; i < input[0].size(); i++){
		
		int count = 0; 
		for(int j = 0; j < input.size(); j++){
			count += get_conflicts_row(input[j], i, i+1);
		}
		if(count == 1) result += (i+1); 
	}
	return result; 
}

int main(void){
	
	std::vector<std::string> input = core::Read_Data<std::vector<std::string>>("input.txt"); 
	long long result = 0; 
	
	std::vector<std::string> current_grid; 
	for(int i = 0; i < input.size(); i++){
		
		if(!input[i].empty()){
			current_grid.push_back(input[i]); 
		}else{
			result += Get_Score(current_grid);
			current_grid.clear(); 
		}
	}

	if(!current_grid.empty()){
		result += Get_Score(current_grid);  
	}
	std::cout<<result<<'\n';
} 
