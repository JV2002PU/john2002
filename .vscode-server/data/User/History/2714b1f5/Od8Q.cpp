#include <iostream>

  // Καθολική μεταβλητή

void exampleFunction(int a) {
    std::cout << "Global Variable: " << a << std::endl;
}

int main() {
    int globalVar = 10;
    exampleFunction(globalVar);
    return 0;
}