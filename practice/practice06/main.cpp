#include <iostream>
#include "Fraction.h"
#include "MixedFraction.h"

void displayMenu() {
    std::cout << "Options:\n";
    std::cout << "1. Enter a fraction manually\n";
    std::cout << "2. Add a fraction\n";
    std::cout << "3. Subtract a fraction\n";
    std::cout << "4. Multiply by a fraction\n";
    std::cout << "5. Divide by a fraction\n";
    std::cout << "6. Display as Mixed Fraction\n";
    std::cout << "7. Clear Fraction\n";
    std::cout << "8. Exit\n";
}

int getValidIntegerInput() {
    int input;
    while (true) {
        std::cin >> input;
        if (std::cin.fail()) {
            std::cin.clear();  
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Invalid input. Please enter a valid integer: ";
        }
        else {
            return input;
        }
    }
}

int getValidDenominator() {
    int denominator;
    while (true) {
        std::cin >> denominator;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Denominator cannot be non-numeric. Enter again: ";
        }
        else if (denominator == 0) {
            std::cout << "Denominator cannot be zero. Enter a valid denominator: ";
        }
        else {
            return denominator;
        }
    }
}

int main() {
    Fraction currentFraction;

    while (true) {
        std::cout << "Current Fraction: " << currentFraction << std::endl;
        displayMenu();
        int choice = getValidIntegerInput();

        if (choice == 8) break;

        if (choice == 1) {
            int num, den;
            std::cout << "Enter numerator: ";
            num = getValidIntegerInput();
            std::cout << "Enter denominator: ";
            den = getValidDenominator();
            try {
                currentFraction = Fraction(num, den);
            }
            catch (const std::invalid_argument& e) {
                std::cout << e.what() << std::endl;
            }
        }
        else if (choice >= 2 && choice <= 5) {
            int num, den;
            std::cout << "Enter numerator: ";
            num = getValidIntegerInput();
            std::cout << "Enter denominator: ";
            den = getValidDenominator();

            try {
                Fraction other(num, den);
                if (choice == 2) currentFraction = currentFraction + other;
                else if (choice == 3) currentFraction = currentFraction - other;
                else if (choice == 4) currentFraction = currentFraction * other;
                else if (choice == 5) currentFraction = currentFraction / other;
            }
            catch (const std::invalid_argument& e) {
                std::cout << e.what() << std::endl;
            }
        }
        else if (choice == 6) {
            try {
                MixedFraction mixed(currentFraction);
                std::cout << "Mixed Fraction: " << mixed << std::endl;
            }
            catch (const std::invalid_argument& e) {
                std::cout << "Error converting to mixed fraction: " << e.what() << std::endl;
            }
        }
        else if (choice == 7) {
            currentFraction = Fraction();
        }
        else {
            std::cout << "Invalid choice. Please enter a valid option (1-8).\n";
        }
    }
    return 0;
}