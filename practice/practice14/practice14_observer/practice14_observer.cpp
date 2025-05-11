#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <memory>
#include <numeric>
#include <iomanip>
#include <map>

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update(const std::string& studentName, double newGrade, const std::vector<double>& allGrades) = 0;
};

class ISubject {
public:
    virtual ~ISubject() = default;
    virtual void registerObserver(std::shared_ptr<IObserver> observer) = 0;
    virtual void removeObserver(std::shared_ptr<IObserver> observer) = 0;
    virtual void notifyObservers(const std::string& studentName, double newGrade, const std::vector<double>& allGrades) = 0;
};

class GradeBook : public ISubject {
private:
    std::list<std::weak_ptr<IObserver>> observers;
    std::map<std::string, std::vector<double>> studentGrades;

public:
    void registerObserver(std::shared_ptr<IObserver> observer) override {
        observers.push_back(observer);
        std::cout << "Observer registered." << std::endl;
    }

    void removeObserver(std::shared_ptr<IObserver> observer) override {
        observers.remove_if([&](const std::weak_ptr<IObserver>& wp) {
            return wp.expired() || wp.lock() == observer;
            });
        std::cout << "Observer removed." << std::endl;
    }

    void notifyObservers(const std::string& studentName, double newGrade, const std::vector<double>& allGrades) override {
        observers.remove_if([](const std::weak_ptr<IObserver>& wp) {
            return wp.expired();
            });

        for (auto& weakObserver : observers) {
            if (auto observer = weakObserver.lock()) {
                observer->update(studentName, newGrade, allGrades);
            }
        }
    }

    void addGrade(const std::string& studentName, double grade) {
        if (grade < 0 || grade > 100) {
            std::cout << "Invalid grade: " << grade << ". Grade must be between 0 and 100." << std::endl;
            return;
        }
        studentGrades[studentName].push_back(grade);
        std::cout << "\nGrade " << grade << " added for student " << studentName << "." << std::endl;
        notifyObservers(studentName, grade, studentGrades[studentName]);
    }

    const std::vector<double>& getGrades(const std::string& studentName) const {
        static const std::vector<double> empty_grades;
        auto it = studentGrades.find(studentName);
        if (it != studentGrades.end()) {
            return it->second;
        }
        return empty_grades;
    }
};

class AveragerObserver : public IObserver {
public:
    void update(const std::string& studentName, double newGrade, const std::vector<double>& allGrades) override {
        if (allGrades.empty()) {
            std::cout << "[Averager] No grades available for " << studentName << " to calculate average." << std::endl;
            return;
        }
        double sum = std::accumulate(allGrades.begin(), allGrades.end(), 0.0);
        double average = sum / allGrades.size();
        std::cout << "[Averager] Student: " << studentName
            << " - New Running Average: " << std::fixed << std::setprecision(2) << average
            << " (after " << allGrades.size() << " grades)" << std::endl;
    }
};

class NotifierObserver : public IObserver {
private:
    double threshold;

public:
    NotifierObserver(double alertThreshold) : threshold(alertThreshold) {}

    void update(const std::string& studentName, double newGrade, const std::vector<double>& allGrades) override {
        if (allGrades.empty()) return;

        double sum = std::accumulate(allGrades.begin(), allGrades.end(), 0.0);
        double average = sum / allGrades.size();

        if (average < threshold) {
            std::cout << "[Notifier] ALERT! Student: " << studentName
                << " - Average grade (" << std::fixed << std::setprecision(2) << average
                << "%) has dropped below threshold (" << threshold << "%)." << std::endl;
            std::cout << "[Notifier] Email sent to " << studentName << "@example.com" << std::endl;
        }
        if (newGrade < threshold) {
            std::cout << "[Notifier] NOTE! Student: " << studentName
                << " - Most recent grade (" << std::fixed << std::setprecision(2) << newGrade
                << "%) is below threshold (" << threshold << "%)." << std::endl;
        }
    }
};

int main() {
    auto gradeBook = std::make_shared<GradeBook>();

    auto averager = std::make_shared<AveragerObserver>();
    auto notifier = std::make_shared<NotifierObserver>(60.0);

    gradeBook->registerObserver(averager);
    gradeBook->registerObserver(notifier);

    std::string studentName;
    double grade;
    char cont = 'y';

    std::cout << "--- Grade System ---" << std::endl;

    std::cout << "Enter student name: ";
    std::getline(std::cin, studentName);

    while (tolower(cont) == 'y') {
        std::cout << "\nEnter grade for " << studentName << " (0-100): ";
        while (!(std::cin >> grade) || grade < 0 || grade > 100) {
            std::cout << "Invalid input. Please enter a number between 0 and 100: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        gradeBook->addGrade(studentName, grade);

        std::cout << "\nDo you want to add another grade for " << studentName << "? (y/n): ";
        std::cin >> cont;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "\n--- Adding grades for a new student ---" << std::endl;
    std::string studentName2 = "Jane Doe";
    gradeBook->addGrade(studentName2, 95.0);
    gradeBook->addGrade(studentName2, 88.0);

    std::cout << "\nExiting Grade System." << std::endl;

    return 0;
}
