#include <iostream>
#include <vector>
#include <iterator>
#include <limits>

int main() {
    std::vector<int> numbers;
    
    int n;

    std::cout << "Enter number of integers you want to input: ";
    
    while (!(std::cin >> n) || n <= 0) {
        std::cout << "Invalid input. Please enter a positive integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Enter " << n << " integers:\n";

    int value;
    
    for (int i = 0; i < n; ++i) {
        std::cout << "Integer " << (i + 1) << ": ";
        
        while (!(std::cin >> value)) {
            std::cout << "Invalid input. Please enter an integer: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        numbers.push_back(value);
    }

    std::cout << "You entered: ";
    
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    
    std::cout << std::endl;

    int evenSum = 0;
    
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        if (*it % 2 == 0) {
            evenSum += *it;
        }
    }

    std::cout << "Sum of even numbers: " << evenSum << std::endl;

    return 0;
}