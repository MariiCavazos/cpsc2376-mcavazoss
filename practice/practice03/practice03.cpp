#include <iostream>
#include <vector>
#include <stdexcept>

class MathUtils {
public:
    // Corrected: includes 'end' and handles if start > end
    static int sumRange(int start, int end) {
        if (start > end) return 0;
        int sum = 0;
        for (int i = start; i <= end; i++) {
            sum += i;
        }
        return sum;
    }

    // Corrected: fixed loop range and checks for negative numbers
    static bool containsNegative(const std::vector<int>& numbers) {
        for (size_t i = 0; i < numbers.size(); i++) {
            if (numbers[i] < 0) {
                return true;
            }
        }
        return false;
    }

    // Corrected: handles empty list with exception, and avoids out-of-bounds access
    static int findMax(const std::vector<int>& numbers) {
        if (numbers.empty()) {
            throw std::invalid_argument("Empty vector provided to findMax.");
        }

        int maxVal = numbers[0];
        for (size_t i = 1; i < numbers.size(); i++) {
            if (numbers[i] > maxVal) {
                maxVal = numbers[i];
            }
        }
        return maxVal;
    }
};

int main() {
    std::cout << "Sum from 1 to 5: " << MathUtils::sumRange(1, 5) << std::endl;

    std::vector<int> values = { 3, -1, 5, 7 };

    std::cout << "Contains negative? "
        << (MathUtils::containsNegative(values) ? "Yes" : "No") << std::endl;

    try {
        std::cout << "Max value: " << MathUtils::findMax(values) << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}