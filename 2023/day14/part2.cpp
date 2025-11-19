#include "../core.h" 

class Trie{

public:
	Trie* arr[256]; 
	int id;	
	Trie(int _id): id(_id){
		arr['.'] = nullptr; 
		arr['#'] = nullptr; 
		arr['O'] = nullptr; 
	}
};

int Add_to_Trie(Trie* root, std::vector<std::string>& grid, int id){
	
	Trie* current = root;
	bool is_valid = true; 
	for(int i = 0; i < grid.size(); i++){
		
		for(int j = 0; j < grid[0].size(); j++){
			
			if(current->arr[grid[i][j]] == nullptr){
				current->arr[grid[i][j]] = new Trie(id);
				is_valid = false; 
			}

			current = current->arr[grid[i][j]]; 
		}
	}

	if(is_valid) return current->id; 
	
	return -1; 
}


void Cycle(std::vector<std::string>& grid){
	
		
	for(int j = 0; j < grid[0].size(); j++){
		
		int edge = 0; 
		for(int i = 0; i < grid.size(); i++){
			
			if(grid[i][j] == 'O'){
				std::swap(grid[edge][j], grid[i][j]); 
				edge++; 
			}else if(grid[i][j] == '#'){
				edge = i + 1; 
			}	
		}
	}

	for(int i = 0; i < grid.size(); i++){
		
		int edge = 0; 
		for(int j = 0; j < grid[0].size(); j++){
			
			if(grid[i][j] == 'O'){
				std::swap(grid[i][j], grid[i][edge]);	
				edge++; 
			}else if(grid[i][j] == '#'){
				edge = j + 1; 
			}
		}
	}
	
	for(int j = 0; j < grid[0].size(); j++){
		
		int edge = grid.size()-1; 
		for(int i = grid.size()-1; i >= 0; i--){
			
			if(grid[i][j] == 'O'){
				std::swap(grid[edge][j], grid[i][j]); 
				edge--; 
			}else if(grid[i][j] == '#'){
				edge = i - 1; 
			}	
		}
	}

	for(int i = 0; i < grid.size(); i++){
		
		int edge = grid[0].size()-1; 
		for(int j = grid[0].size()-1; j >= 0; j--){
			
			if(grid[i][j] == 'O'){
				std::swap(grid[i][j], grid[i][edge]);	
				edge--; 
			}else if(grid[i][j] == '#'){
				edge = j - 1; 
			}
		}
	}	
}

long long Get_Load(std::vector<std::string>& grid){
	
	long long result = 0; 
	for(int j = 0; j < grid[0].size(); j++){
		for(int i = 0; i < grid.size(); i++){
			
			if(grid[i][j] == 'O'){
				result += grid.size() - i; 
			}
		}
	}
	return result; 
}

int main(void){
	
	std::vector<std::string> grid = core::Read_Data<std::vector<std::string>>("input.txt"); 
	
	constexpr std::size_t limit = 1e9; 
	
	Trie root = Trie(-1); 
	Add_to_Trie(&root, grid, 0); 
	std::unordered_map<int, long long> load_map;
	load_map[0] = Get_Load(grid); 

	long long result = -1;
	for(int i = 0; i < limit && result == -1; i++){
		
		Cycle(grid); 

		int cycle_num = Add_to_Trie(&root, grid, i+1);
		
		if(cycle_num != -1){
			
			int cycle_length = i+1 - cycle_num;
			int remaining_cycles = (limit - i-1)%cycle_length; 
			result = load_map[cycle_num + remaining_cycles];  
		}else{
			load_map[i+1] = Get_Load(grid); 
		}

	}

	std::cout<<result<<'\n';
	return 0; 
}
