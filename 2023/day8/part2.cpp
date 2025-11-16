#include "../core.h" 

std::pair<std::size_t, std::size_t> get_cycle(std::unordered_map<std::string, std::pair<std::string, std::string>>& graph, const std::string& starting_node, const std::string& directions){
		
	std::string node = starting_node;
	std::size_t current = 0; 

	while(node.back() != 'Z'){
			
		if(directions[current%directions.size()] == 'L'){
			node = graph[node].first;  
		}else{
			node = graph[node].second; 	
		}
		current++; 
	}
	
	
	std::pair<std::size_t, std::size_t> result = {current, 0}; 
	
	current = 0; 
	do{	
		if(directions[current%directions.size()] == 'L'){
			node = graph[node].first;  
		}else{
			node = graph[node].second; 	
		}
		current++;
	}while(node.back() != 'Z');

	result.second = current;
	return result; 
}

int main(void){
		
	std::vector<std::string> inputs = core::Read_Data<std::vector<std::string>>("input.txt"); 

	std::string directions = inputs.front();
	std::unordered_map<std::string, std::pair<std::string, std::string>> graph;
	std::unordered_map<std::string, int> last_accessed; 
	
	std::vector<std::string> starting_nodes; 
	for(int i = 2; i < inputs.size(); i++){
		
		std::vector<std::string> current = core::Split_String(inputs[i], {' ', '=', '(', ')', ','}); 

		graph[current[0]] = {current[1], current[2]}; 

		if(current[0].back() == 'A') starting_nodes.push_back(current[0]);  
	}

	std::size_t lcm = 1; 
	for(int i = 0; i < starting_nodes.size(); i++){
		
		std::pair<std::size_t, std::size_t> current_cycle = get_cycle(graph, starting_nodes[i], directions); 
		
		lcm = (lcm * current_cycle.second)/std::gcd(lcm, current_cycle.second); 		 	
	} 
	std::cout<<lcm<<'\n';

	return 0;
}
