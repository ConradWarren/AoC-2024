#include "../core.h" 

class Rule{
	public:
		
		int trait; 
		int val; 
		bool is_less_than; 
		std::string next; 
		bool is_defualt;
};
	
bool Is_Accepted(std::unordered_map<std::string, std::vector<Rule>>& workflow_map, std::vector<int>& values, const std::string& id){
	
	
	if(id == "A") return true; 
	if(id == "R") return false; 


	for(auto& rule : workflow_map[id]){
		
		if(rule.is_defualt){
			return Is_Accepted(workflow_map, values, rule.next); 
		}
		
		if(rule.is_less_than && values[rule.trait] < rule.val){
			return Is_Accepted(workflow_map, values, rule.next); 
		}

		if(!rule.is_less_than && values[rule.trait] > rule.val){
			return Is_Accepted(workflow_map, values, rule.next); 
		}
	} 
	return false; 
}

int main(void){

	std::vector<std::string> input = core::Read_Data<std::vector<std::string>>("input.txt");

	std::unordered_map<std::string, std::vector<Rule>> workflow_map; 
	
	int idx = -1;
	for(int i = 0; i < input.size(); i++){
		
		if(input[i].empty()){
			idx = i+1; 
			break;
		}
		std::vector<std::string> line = core::Split_String(input[i], {'{','}',','}); 

		std::string id = line.front();

		for(int j = 1; j + 1< line.size(); j++){
			Rule current = Rule(); 
			current.trait = line[j][0]; 
			current.is_less_than = line[j][1] == '<';
			current.is_defualt = false; 			
			auto itr = std::find(line[j].begin(), line[j].end(), ':');
			current.val = std::stoi(std::string(line[j].begin()+2, itr)); 
			current.next = std::string(itr + 1, line[j].end()); 
			workflow_map[id].push_back(current); 

		} 
		Rule last_rule = Rule(); 
		last_rule.next = line.back(); 
		last_rule.is_defualt = true; 
		workflow_map[id].push_back(last_rule); 
	}
	
	
	long long result = 0; 
	for(int i = idx; i < input.size(); i++){
	
		std::vector<int> values(256, 0); 

		std::vector<std::string> current = core::Split_String(input[i], {'{','}',',', '='});
		
		long long sum = 0;	
		for(int j = 0; j <current.size(); j += 2){
			values[current[j][0]] = std::stoi(current[j+1]);
			sum += std::stoi(current[j+1]); 

		}

		if(Is_Accepted(workflow_map, values, "in")){
			result += sum; 
		} 
	}
	std::cout<<result<<'\n';
	return 0; 
}
