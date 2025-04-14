#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <limits>

int main() {
    std::vector<int> numbers;
    int n;

    std::cout << "Enter the number of elements: ";
    while (!(std::cin >> n) || n <= 0) {
        std::cout << "Invalid input. Please enter a positive integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    int value;
    std::cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; i++) {
        while (!(std::cin >> value)) {
            std::cout << "Invalid input. Please enter an integer: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        numbers.push_back(value);
    }

    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    int product = std::accumulate(numbers.begin(), numbers.end(), 1, std::multiplies<int>());
    auto maxIt = std::max_element(numbers.begin(), numbers.end());
    auto minIt = std::min_element(numbers.begin(), numbers.end());

    std::cout << "Sum of elements: " << sum << std::endl;
    std::cout << "Product of elements: " << product << std::endl;
    std::cout << "Maximum element: " << *maxIt << std::endl;
    std::cout << "Minimum element: " << *minIt << std::endl;

    return 0;
}