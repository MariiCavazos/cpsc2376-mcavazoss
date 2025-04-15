#include <iostream>

int main() {
    float redPotion{ 0.0f };
    float bluePotion{ 0.0f };
    float* flask{ nullptr };
    std::string potionChoice;
    float amountToAdd;

    while (true) {
        std::cout << "Which potion would you like to add liquid to? (Red/Blue) or type 'Done' to exit: ";
        std::cin >> potionChoice;

        if (potionChoice == "Done") {
            break;
        }

        if (potionChoice == "Red") {
            flask = &redPotion;
        }
        else if (potionChoice == "Blue") {
            flask = &bluePotion;
        }
        else {
            std::cout << "Invalid potion choice. Please choose Red or Blue.\n";
            continue;
        }

        std::cout << "How many milliliters to add: ";
        std::cin >> amountToAdd;

        *flask += amountToAdd;

        std::cout << "Red Potion: " << redPotion << " mL\n";
        std::cout << "Blue Potion: " << bluePotion << " mL\n";
    }

    return 0;
}