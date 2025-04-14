#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>

int main() {
    std::vector<int> numbers;
    int n, value;

    std::cout << "Enter number of elements: ";
    while (!(std::cin >> n) || n <= 0) {
        std::cout << "Invalid input. Enter a positive integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; i++) {
        while (!(std::cin >> value)) {
            std::cout << "Invalid input. Enter an integer: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        numbers.push_back(value);
    }

    std::cout << "Squared values: ";
    std::for_each(numbers.begin(), numbers.end(), [](int num) {
        std::cout << (num * num) << " ";
        });
    std::cout << std::endl;

    int sumOfSquares = std::accumulate(numbers.begin(), numbers.end(), 0, [](int total, int num) {
        return total + (num * num);
        });

    std::cout << "Sum of squared values: " << sumOfSquares << std::endl;

    return 0;
}