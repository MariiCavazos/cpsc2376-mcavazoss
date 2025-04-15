#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <sstream>
#include <string>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Shape {
public:
    virtual double getArea() const = 0;
    virtual ~Shape() {}
};

class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double getArea() const override {
        return width * height;
    }
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double getArea() const override {
        return M_PI * radius * radius;
    }
};

void printAllAreas(const std::vector<std::unique_ptr<Shape>>& shapes) {
    for (const auto& shape : shapes) {
        std::cout << "Area: " << shape->getArea() << std::endl;
    }
}

int main() {
    std::ifstream file("shapes.txt");
    if (!file) {
        std::cerr << "Failed to open shapes.txt\n";
        return 1;
    }

    std::vector<std::unique_ptr<Shape>> shapes;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "rectangle") {
            double w, h;
            iss >> w >> h;
            shapes.push_back(std::make_unique<Rectangle>(w, h));
        }
        else if (type == "circle") {
            double r;
            iss >> r;
            shapes.push_back(std::make_unique<Circle>(r));
        }
        else {
            std::cerr << "Unknown shape type: " << type << std::endl;
        }
    }

    printAllAreas(shapes);

    return 0;
}