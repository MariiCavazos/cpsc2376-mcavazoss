#include <iostream>
#include <vector>
#include <limits> // For std::numeric_limits

// Function to print the vector
void printVector(const std::vector<int>& vec) {
    if (vec.empty()) {
        std::cout << "The vector is empty!" << std::endl;
        return;
    }
    std::cout << "Vector contents: ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// Function to double the elements in the vector
void doubleVector(std::vector<int>& vec) {
    for (int& num : vec) {
        num *= 2;
    }
    std::cout << "Vector has been doubled." << std::endl;
}

// Function to calculate the sum of the vector
int calculateSum(const std::vector<int>& vec) {
    int sum = 0;
    for (int num : vec) {
        sum += num;
    }
    return sum;
}

// Function to print multiples of a user-defined value
void printMultiples(const std::vector<int>& vec, int value) {
    std::cout << "Multiples of " << value << ": ";
    bool found = false;
    for (int num : vec) {
        if (num % value == 0) {
            std::cout << num << " ";
            found = true;
        }
    }
    if (!found) {
        std::cout << "No multiples found." << std::endl;
    }
    else {
        std::cout << std::endl;
    }
}

// Function to handle incorrect input (non-integer input)
int getIntInput() {
    int input;
    while (true) {
        std::cin >> input;
        if (std::cin.fail()) {
            std::cout << "Invalid input! Please enter a valid number: ";
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
        }
        else {
            return input;
        }
    }
}

int main() {
    std::vector<int> numbers;
    int choice;
    int num, value;

    do {
        std::cout << "\nMenu:" << std::endl;
        std::cout << "1. Add an item to the vector" << std::endl;
        std::cout << "2. Print the vector" << std::endl;
        std::cout << "3. Double the vector" << std::endl;
        std::cout << "4. Find the sum of the vector" << std::endl;
        std::cout << "5. Print multiples of a user-defined value" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        choice = getIntInput(); // Using the getIntInput function to handle input validation

        switch (choice) {
        case 1:
            std::cout << "Enter a number to add to the vector: ";
            num = getIntInput(); // Handle input for the number to add
            numbers.push_back(num);
            std::cout << num << " has been added to the vector." << std::endl;
            break;

        case 2:
            printVector(numbers);
            break;

        case 3:
            doubleVector(numbers);
            break;

        case 4:
            std::cout << "The sum of the vector is: " << calculateSum(numbers) << std::endl;
            break;

        case 5:
            std::cout << "Enter a value to find multiples of: ";
            value = getIntInput();
            printMultiples(numbers, value);
            break;

        case 6:
            std::cout << "Exiting program..." << std::endl;
            break;

        default:
            std::cout << "Invalid choice! Please try again." << std::endl;
        }
    } while (choice != 6);

    return 0;
}