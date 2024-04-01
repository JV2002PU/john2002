#include <iostream>

  // Καθολική μεταβλητή

void exampleFunction(int) {
    std::cout << "Global Variable: " << globalVar << std::endl;
}

int main() {
    int globalVar = 10;
    exampleFunction(globalVar);
    return 0;
}