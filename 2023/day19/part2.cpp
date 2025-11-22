#include "../core.h" 

class Rule{
	public:
		int trait; 
		int val; 
		bool is_less_than; 
		std::string next; 
		bool is_defualt;
};
	
long long Count(std::unordered_map<std::string, std::vector<Rule>>& workflow_map, std::vector<std::pair<int,int>>& values, const std::string& id){
	
	
	if(id == "R") return 0; 
	if(id == "A"){
		
		long long current = 1; 
		current *= values['x'].second - values['x'].first + 1;
		current *= values['m'].second - values['m'].first + 1;
		current *= values['a'].second - values['a'].first + 1;
		current *= values['s'].second - values['s'].first + 1;
		
		return current; 
	}	


	long long result = 0; 	
	for(auto& rule : workflow_map[id]){
		
		if(rule.is_defualt){
			return Count(workflow_map, values, rule.next) + result; 
		}
		
		if(rule.is_less_than && values[rule.trait].second < rule.val){
			return Count(workflow_map, values, rule.next) + result; 
		}else if(rule.is_less_than && values[rule.trait].first < rule.val){
			std::vector<std::pair<int, int>> next_values = values; 
			next_values[rule.trait].second = rule.val - 1;

			result += Count(workflow_map, next_values, rule.next);
			values[rule.trait].first = rule.val;
		}

		if(!rule.is_less_than && values[rule.trait].first > rule.val){
			return Count(workflow_map, values, rule.next) + result; 
		}else if(!rule.is_less_than && values[rule.trait].second > rule.val){
			std::vector<std::pair<int, int>> next_values = values; 
			next_values[rule.trait].first = rule.val + 1;
			result += Count(workflow_map, next_values, rule.next);
			values[rule.trait].second = rule.val;
		}
	} 
	return result; 
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
	
	std::vector<std::pair<int, int>> values(256, {1, 4000}); 	
	long long result = Count(workflow_map, values, "in"); 
	std::cout<<result<<'\n';
	return 0; 
}
