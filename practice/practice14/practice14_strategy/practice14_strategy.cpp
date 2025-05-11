#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

class IFilterStrategy {
public:
    virtual ~IFilterStrategy() = default;
    virtual void process(std::string& text) const = 0;
};

class ReverseStrategy : public IFilterStrategy {
public:
    void process(std::string& text) const override {
        std::reverse(text.begin(), text.end());
    }
};

class UppercaseStrategy : public IFilterStrategy {
public:
    void process(std::string& text) const override {
        std::transform(text.begin(), text.end(), text.begin(), ::toupper);
    }
};

class RemoveVowelsStrategy : public IFilterStrategy {
public:
    void process(std::string& text) const override {
        std::string result = "";
        std::string vowels = "aeiouAEIOU";
        for (char c : text) {
            if (vowels.find(c) == std::string::npos) {
                result += c;
            }
        }
        text = result;
    }
};

class CensorBadWordsStrategy : public IFilterStrategy {
private:
    std::vector<std::string> badWords = { "badword1", "examplebad", "test" };

    void replaceAll(std::string& str, const std::string& from, const std::string& to) const {
        if (from.empty())
            return;
        size_t start_pos = 0;
        while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length();
        }
    }

public:
    void process(std::string& text) const override {
        for (const auto& badWord : badWords) {
            std::string censor(badWord.length(), '*');
            std::string lowerText = text;
            std::transform(lowerText.begin(), lowerText.end(), lowerText.begin(), ::tolower);

            std::string lowerBadWord = badWord;
            std::transform(lowerBadWord.begin(), lowerBadWord.end(), lowerBadWord.begin(), ::tolower);

            size_t pos = 0;
            while ((pos = lowerText.find(lowerBadWord, pos)) != std::string::npos) {
                text.replace(pos, badWord.length(), censor);
                lowerText.replace(pos, badWord.length(), censor);
                pos += censor.length();
            }
        }
    }
};

class TextProcessor {
private:
    std::unique_ptr<IFilterStrategy> strategy;

public:
    TextProcessor(std::unique_ptr<IFilterStrategy> initialStrategy = nullptr)
        : strategy(std::move(initialStrategy)) {
    }

    void setStrategy(std::unique_ptr<IFilterStrategy> newStrategy) {
        strategy = std::move(newStrategy);
    }

    void applyFilter(std::string& text) const {
        if (strategy) {
            strategy->process(text);
        }
        else {
            std::cout << "No strategy set." << std::endl;
        }
    }
};

int displayMenuAndGetChoice() {
    std::cout << "\nSelect a text filter strategy:\n";
    std::cout << "1. Reverse Text\n";
    std::cout << "2. Uppercase Text\n";
    std::cout << "3. Remove Vowels\n";
    std::cout << "4. Censor Bad Words\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
    int choice;
    while (!(std::cin >> choice) || choice < 0 || choice > 4) {
        std::cout << "Invalid input. Please enter a number between 0 and 4: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}

int main() {
    std::string inputText;
    std::string originalText;

    std::cout << "Enter a sentence: ";
    std::getline(std::cin, inputText);
    originalText = inputText;

    TextProcessor processor;
    int choice;

    do {
        inputText = originalText;
        std::cout << "\nOriginal text: " << inputText << std::endl;
        choice = displayMenuAndGetChoice();

        switch (choice) {
        case 1:
            processor.setStrategy(std::make_unique<ReverseStrategy>());
            break;
        case 2:
            processor.setStrategy(std::make_unique<UppercaseStrategy>());
            break;
        case 3:
            processor.setStrategy(std::make_unique<RemoveVowelsStrategy>());
            break;
        case 4:
            processor.setStrategy(std::make_unique<CensorBadWordsStrategy>());
            break;
        case 0:
            std::cout << "Exiting program." << std::endl;
            continue;
        default:
            std::cerr << "Invalid choice. Please try again." << std::endl;
            continue;
        }

        if (choice != 0) {
            processor.applyFilter(inputText);
            std::cout << "Processed text: " << inputText << std::endl;
        }

        if (choice != 0) {
            char reprocessChoice;
            std::cout << "\nDo you want to try another strategy with the original sentence? (y/n): ";
            std::cin >> reprocessChoice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (tolower(reprocessChoice) != 'y') {
                choice = 0;
                std::cout << "Exiting program." << std::endl;
            }
        }

    } while (choice != 0);

    return 0;
}