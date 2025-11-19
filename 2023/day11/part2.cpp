#include "../core.h" 

int main(void){
	
	std::vector<std::string> input = core::Read_Data<std::vector<std::string>>("input.txt"); 

	std::vector<int> expanded_rows(input.size(), 1); 
	std::vector<int> expanded_columns(input[0].size(), 1);
	
	std::vector<std::pair<int, int>> points; 
	for(int i = 0; i < input.size(); i++){
		
		for(int j = 0; j < input[0].size(); j++){
			
			if(input[i][j] == '#'){
				expanded_columns[j] = 0; 
				expanded_rows[i] = 0;
				points.push_back({i,j}); 
			}
		}
	}

	for(int i = 1; i < expanded_rows.size(); i++){
		expanded_rows[i] += expanded_rows[i-1]; 
	}
	for(int i = 1; i < expanded_columns.size(); i++){
		expanded_columns[i] += expanded_columns[i-1]; 
	}
	
	long long result = 0; 
	for(int i = 0; i < points.size(); i++){
		for(int j = i+1; j < points.size(); j++){
			
			result += std::abs(points[i].first - points[j].first) + std::abs(points[i].second - points[j].second); 	
			
			int max_row = std::max(points[i].first, points[j].first); 
			int min_row = std::min(points[i].first, points[j].first);

			if(max_row > 0){
				result += static_cast<long long>(expanded_rows[max_row-1] - expanded_rows[min_row])  * (1000000LL - 1); 
			} 

			int max_column = std::max(points[i].second, points[j].second); 
			int min_column = std::min(points[i].second, points[j].second);

			if(max_column > 0){
				result += static_cast<long long>(expanded_columns[max_column-1] - expanded_columns[min_column])  * (1000000LL - 1); 
			}
		}
	}
	std::cout<<result<<'\n';

	return 0; 
}
