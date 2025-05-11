#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	std::vector<int> nums{ 1, 2, 3, 4, 5 };
	auto v = std::find(nums.begin(), nums.end(),4);
	
	if (v == nums.end()) {
		std::cout << "Not found" << std::endl;
	}
	else {
		std::cout << "Found: " << *v << std::endl;
	}
	
	std::cout << *v << std::endl;
}