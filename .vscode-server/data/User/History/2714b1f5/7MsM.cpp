#include <iostream>

int globalVar = 10;  // Καθολική μεταβλητή

void exampleFunction() {
    std::cout << "Global Variable: " << globalVar << std::endl;
}

int main() {
    exampleFunction();
    return 0;
}