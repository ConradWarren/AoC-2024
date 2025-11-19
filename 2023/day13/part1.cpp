#include "../core.h" 

bool is_valid_row(std::string& row, int idx_left, int idx_right){
	
	if(idx_right >= row.size() || idx_left < 0) return false;
	
	
	while(idx_left >= 0 && idx_right < row.size()){
			
		if(row[idx_left] != row[idx_right]){
			return false; 
				
		} 		
		
		idx_left--; 
		idx_right++;
	}
	return true; 
} 

bool is_valid_column(std::vector<std::string>& grid,int coloumn_idx, int idx_top, int idx_bottom){
	
	if(idx_bottom >= grid.size() || idx_top < 0) return false;
	
	while(idx_top >= 0 && idx_bottom < grid.size()){
		
		if(grid[idx_bottom][coloumn_idx] != grid[idx_top][coloumn_idx]) return false; 

		idx_top--; 
		idx_bottom++;
	}
		
	return true; 
}

std::pair<int, int> get_point_row(std::string& row, int idx_left, int idx_right){
	
	if(idx_right >= row.size() || idx_left < 0) return {-1, -1};
	
	std::pair<int, int> result = {-1 ,-1};  	
	while(idx_left >= 0 && idx_right < row.size()){
			
		if(row[idx_left] != row[idx_right] && result.first == -1){
			result = {idx_left,idx_right}; 				
		}else if(row[idx_left] != row[idx_right]) {
			return {-1, -1}; 
		} 		
		
		idx_left--; 
		idx_right++;
	}
	return result; 
} 

std::pair<int, int> get_point_column(std::vector<std::string>& grid,int coloumn_idx, int idx_top, int idx_bottom){
	
	if(idx_bottom >= grid.size() || idx_top < 0) return {-1, -1};

	std::pair<int, int> result = {-1 ,-1};  		
	while(idx_top >= 0 && idx_bottom < grid.size()){
		
		if(grid[idx_bottom][coloumn_idx] != grid[idx_top][coloumn_idx] && result.first == -1){
			result = {idx_top, idx_bottom}; 
		} 
		else if(grid[idx_bottom][coloumn_idx] != grid[idx_top][coloumn_idx]){
			return {-1, -1}; 	
		}  

		idx_top--; 
		idx_bottom++;
	}
		
	return result; 
}

long long Get_Score(std::vector<std::string>& input){
		
	long long result = 0; 

	for(int i = 0; i < input.size(); i++){
		bool is_valid = true;
		for(int j = 0; j < input[0].size() && is_valid; j++){
			is_valid = is_valid_column(input, j, i, i+1);
		}
		if(is_valid) result += 100 * (i+1); 
	}

	for(int i = 0; i < input[0].size(); i++){
		bool is_valid = true; 
		for(int j = 0; j < input.size() && is_valid; j++){
			is_valid = is_valid_row(input[j], i, i+1);
		}
		if(is_valid) result += (i+1); 
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
			std::cout<<input[i]<<'\n';
		}else{
			std::cout<<"\nchecking grid\n";
			result += Get_Score(current_grid); 
			
			current_grid.clear(); 
		}
	}

	if(!current_grid.empty()){
		std::cout<<"cecking grid\n";
		result += Get_Score(current_grid);  
	}
	std::cout<<result<<'\n';
} 
