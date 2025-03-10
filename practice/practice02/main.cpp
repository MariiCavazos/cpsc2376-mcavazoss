#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>

double readBalanceFromFile(const std::string& filename);
void writeBalanceToFile(const std::string& filename, double balance);
void checkBalance(double balance);
void deposit(double& balance);
void withdraw(double& balance);
bool getValidMenuChoice(int& choice);

int main() {
    std::string filename = "account_balance.txt";
    double balance;

    balance = readBalanceFromFile(filename);

    std::cout << "Welcome to Your Bank Account!" << std::endl;

    while (true) {
        std::cout << "\nMenu:" << std::endl;
        std::cout << "1. Check Balance" << std::endl;
        std::cout << "2. Deposit Money" << std::endl;
        std::cout << "3. Withdraw Money" << std::endl;
        std::cout << "4. Exit" << std::endl;

        int choice;
        if (!getValidMenuChoice(choice)) {
            std::cout << "Invalid choice, please try again." << std::endl;
            continue;
        }

        switch (choice) {
        case 1:
            checkBalance(balance);
            break;
        case 2:
            deposit(balance);
            writeBalanceToFile(filename, balance);
            break;
        case 3:
            withdraw(balance);
            writeBalanceToFile(filename, balance);
            break;
        case 4:
            std::cout << "Exiting program. Thank you for using the bank!" << std::endl;
            return 0;
        default:
            std::cout << "Invalid choice, please try again." << std::endl;
        }
    }

    return 0;
}

double readBalanceFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "Initializing account with $100.00..." << std::endl;
        return 100.00;
    }

    double balance;
    file >> balance;
    if (file.fail()) {
        std::cout << "Error reading balance from file. Exiting." << std::endl;
        exit(1);
    }

    return balance;
}

void writeBalanceToFile(const std::string& filename, double balance) {
    std::ofstream file(filename);

    if (!file) {
        std::cout << "Error writing balance to file. Exiting." << std::endl;
        exit(1);
    }

    file << std::fixed << std::setprecision(2) << balance;
}

void checkBalance(double balance) {
    std::cout << "Your current balance is: $" << std::fixed << std::setprecision(2) << balance << std::endl;
}

void deposit(double& balance) {
    double amount;
    std::cout << "Enter deposit amount: ";
    std::cin >> amount;

    if (amount <= 0) {
        std::cout << "Error: Deposit amount must be positive." << std::endl;
    }
    else {
        balance += amount;
        std::cout << "Deposit successful. Your new balance is: $" << std::fixed << std::setprecision(2) << balance << std::endl;
    }
}

void withdraw(double& balance) {
    double amount;
    std::cout << "Enter withdrawal amount: ";
    std::cin >> amount;

    if (amount <= 0) {
        std::cout << "Error: Withdrawal amount must be positive." << std::endl;
    }
    else if (amount > balance) {
        std::cout << "Error: Insufficient funds. Your balance is $" << std::fixed << std::setprecision(2) << balance << "." << std::endl;
    }
    else {
        balance -= amount;
        std::cout << "Withdrawal successful. Your new balance is: $" << std::fixed << std::setprecision(2) << balance << std::endl;
    }
}

bool getValidMenuChoice(int& choice) {
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    return true;
}