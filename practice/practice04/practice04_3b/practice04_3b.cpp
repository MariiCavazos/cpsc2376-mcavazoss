#include <iostream> 
#include <deque>
#include <string>
#include <sstream>
#include <limits>

int main() {
    std::deque<std::string> textEdits; 
    int choice;

    while (true) {
        std::cout << "\n1. Add Text\n";
        std::cout << "2. Undo Last Edit\n";
        std::cout << "3. Show Content\n";
        std::cout << "4. Exit\n";
        std::cout << "Choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice, please try again." << std::endl;
            continue;
        }

        std::cin.ignore(); 

        switch (choice) {
        case 1: {
            std::string text;
            std::cout << "Enter text: ";
            std::getline(std::cin, text);

            if (text.empty()) {
                std::cout << "Error: Cannot add empty text!" << std::endl;
            }
            else {
                textEdits.push_back(text);
                std::cout << "Text added successfully!" << std::endl;
            }
            break;
        }
        case 2: {
            if (!textEdits.empty()) {
                textEdits.pop_back();
                std::cout << "Undo successful!" << std::endl;
            }
            else {
                std::cout << "No edits to undo!" << std::endl;
            }
            break;
        }
        case 3: {
            if (textEdits.empty()) {
                std::cout << "No content available!" << std::endl;
            }
            else {
                std::stringstream content;
                for (const auto& line : textEdits) {
                    content << line << " ";
                }
                std::cout << "Current Content: " << content.str() << std::endl;
            }
            break;
        }
        case 4: {
            std::cout << "Thanks! Goodbye!" << std::endl;
            return 0;
        }
        default: {
            std::cout << "Invalid input, please try again." << std::endl;
            break;
        }
        }
    }
}