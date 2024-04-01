#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Student {
public:
    std::string name;
    int age;
    int year;

    Student(const std::string& n, int a, int y) : name(n), age(a), year(y) {}

    void saveToFile(const std::string& filename) const {
        std::ofstream outputFile(filename, std::ios::app); // Open file in append mode
        if (outputFile.is_open()) {
            outputFile << name << " " << age << " " << year << std::endl;
            outputFile.close();
            std::cout << "Data written to file." << std::endl;
        } else {
            std::cerr << "Unable to open file!" << std::endl;
        }
    }

    static std::vector<Student> readFromFile(const std::string& filename) {
        std::vector<Student> students;
        std::ifstream inputFile(filename);
        if (inputFile.is_open()) {
            std::string line;
            while (std::getline(inputFile, line)) {
                std::istringstream iss(line);
                std::string name;
                int age, year;
                if (iss >> name >> age >> year) {
                    students.emplace_back(name, age, year);
                }
            }
            inputFile.close();
        } else {
            std::cerr << "Unable to open file!" << std::endl;
        }
        return students;
    }
};


int main() {
    // Creating some sample students
    std::vector<Student> students = {
        {"John Doe", 20, 3},
        {"Alice Smith", 22, 4},
        {"Bob Johnson", 21, 3}
    };

    // Saving students' data to a file named "students.txt"
    for (const auto& student : students) {
        student.saveToFile("students.txt");
    }

    // Reading students' data back from the file
    std::vector<Student> retrievedStudents = Student::readFromFile("students.txt");
    for (const auto& student : retrievedStudents) {
        std::cout << "Name: " << student.name << ", Age: " << student.age << ", Year: " << student.year << std::endl;
    }

    return 0;
}