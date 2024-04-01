#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> // Required for using std::istringstream
#include <string>

class YourClass {

private:
    std::string firstString;
    std::string secondString;
};
public:
    YourClass(const std::string& first, const std::string& second) 
        : firstString(first), secondString(second) {
        // Your constructor code goes here
    }
    friend ofstream &operator >>(ofstream& output, const YourClass data){
        output <<data.firstString <<" " << data.secondString << endl;
    }

    // Your class methods go here, if any


int main() {
    std::vector<YourClass> objects; // Vector to store objects created from file lines
    YourClass A("MY","YOU");
    // Open the file
    std::ofstream file("example.txt");
    // Check if the file is open
    if (file.is_open()) {

        file << A;
        std::string line;

        // Read each line from the file and create objects
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string first, second;

            // Extract two strings separated by a space
            if (iss >> first >> second) {
                YourClass obj(first, second);
                objects.push_back(obj);
            } else {
                std::cerr << "Error reading line from the file: " << line << std::endl;
            }
        }

        // Close the file
        file.close();
    } else {
        std::cerr << "Unable to open the file ooooo." << std::endl;
        return 1; // Return an error code
    }

    // Now, the 'objects' vector contains instances of YourClass created from file lines

    return 0;
}

