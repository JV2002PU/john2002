#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> // Required for using std::istringstream
#include <string>

class YourClass {
private:
    std::string firstString;
    std::string secondString;

public:
    YourClass(const std::string& first, const std::string& second)
        : firstString(first), secondString(second) {}

    // Overloading << operator to write object to a stream
    friend std::ostream& operator<<(std::ostream& output, const YourClass& obj) {
        output << obj.firstString << " " << obj.secondString;
        return output;
    }
};


int main() {
    std::vector<YourClass> objects; // Vector to store objects created from file lines
    std::ofstream file("output.txt");
    if (file.is_open()) {
        YourClass obj1("Hello", "World");
        YourClass obj2("C++", "Programming");

        // Writing objects to the file
        file << obj1 << std::endl;
        file << obj2 << std::endl;

        file.close();
        std::cout << "Data written to file." << std::endl;
    } else {
        std::cerr << "Unable to open the file." << std::endl;
        return 1;
    }
    return 0;
}

