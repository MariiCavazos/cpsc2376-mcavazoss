#include <iostream>
#include <iomanip>
#include <limits>

template <typename T>
T calculate(T num1, T num2, char operation) {
    switch (operation) {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        if (num2 != 0)
            return num1 / num2;
        else {
            std::cerr << "Error: Division by zero is not allowed!" << std::endl;
            return 0;
        }
    default:
        std::cerr << "Invalid operation!" << std::endl;
        return 0;
    }
}

template <typename T>
bool isValidNumber(T& number) {
    std::cin >> number;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}

int main() {
    char continueChoice;

    do {
        double num1, num2;
        char operation;

        std::cout << "Enter first number (e.g., 5 or 5.5): ";
        while (!isValidNumber(num1)) {
            std::cout << "Invalid input. Please enter a valid number: ";
        }

        std::cout << "Enter second number (e.g., 2 or 2.0): ";
        while (!isValidNumber(num2)) {
            std::cout << "Invalid input. Please enter a valid number: ";
        }

        std::cout << "Choose an operation (+, -, *, /): ";
        while (true) {
            std::cin >> operation;
            if (operation == '+' || operation == '-' || operation == '*' || operation == '/') {
                break;
            }
            else {
                std::cout << "Invalid! Please enter one of (+, -, *, /): ";
            }
        }

        std::cout << "Calculation complete. ";

        if (num1 == static_cast<int>(num1) && num2 == static_cast<int>(num2)) {
            int result = calculate(static_cast<int>(num1), static_cast<int>(num2), operation);
            std::cout << "Result: " << result << std::endl;
        }
        else {
            double result = calculate(num1, num2, operation);
            std::cout << "Result: " << std::fixed << std::setprecision(2) << result << std::endl;
        }

        std::cout << "Would you like to perform another calculation? (y/n): ";
        std::cin >> continueChoice;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (continueChoice == 'y' || continueChoice == 'Y');

    std::cout << "Thank you!! Goodbye!\n";
    return 0;
}
