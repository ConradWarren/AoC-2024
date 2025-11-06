#include "../core.h" 

int main(void){ 

	std::vector<std::string> input = core::Read_Data<std::vector<std::string>>("input.txt"); 

	std::string time_str = ""; 
	std::string distance_str = ""; 
	std::copy_if(input.front().begin(), input.front().end(), std::back_inserter(time_str), [](char x){return x >= '0' && x <= '9';}); 
	std::copy_if(input.back().begin(), input.back().end(), std::back_inserter(distance_str), [](char x){return x >= '0' && x <= '9';});	

	long long time_limit = std::stoll(time_str); 
	long long distance = std::stoll(distance_str);  

	long long det = time_limit * time_limit - distance * 4LL; 
	double det_sqrt = std::sqrt(det); 

	double root1 = (-static_cast<double>(time_limit) - det_sqrt)/(-2.0); 
	double root2 = (-static_cast<double>(time_limit) + det_sqrt)/(-2.0); 

	std::cout<<static_cast<long long>(std::abs(root2 - root1)); 
	return 0;
}
