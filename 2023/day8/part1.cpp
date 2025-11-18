#include "../core.h" 

int main(void){
		
	std::vector<std::string> inputs = core::Read_Data<std::vector<std::string>>("input.txt"); 

	std::string directions = inputs.front();
	std::unordered_map<std::string, std::pair<std::string, std::string>> graph; 

	for(int i = 2; i < inputs.size(); i++){
		
		std::vector<std::string> current = core::Split_String(inputs[i], {' ', '=', '(', ')', ','}); 

		graph[current[0]] = {current[1], current[2]}; 
	}

	std::string node = "AAA"; 
	std::string target = "ZZZ";
	std::size_t result = 0;

	for(int i = 0; node != target; i++){
		
		if(directions[i%directions.size()] == 'L'){
			node = graph[node].first; 
		}else{
			node = graph[node].second; 
		}
		result++;
	}
	
	std::cout<<result<<'\n';
	return 0;
}
