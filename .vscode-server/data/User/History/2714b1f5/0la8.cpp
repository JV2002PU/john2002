#include <iostream>

  // Καθολική μεταβλητή

void exampleFunction() {
    std::cout << "Global Variable: " << globalVar << std::endl;
}

int main() {
    int globalVar = 10;
    exampleFunction();
    return 0;
}