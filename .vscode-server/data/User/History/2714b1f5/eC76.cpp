#include <iostream>

void exampleFunction() {
    static int count = 0;  // Στατική μεταβλητή
    count++;
    std::cout << "Count: " << count << std::endl;
}

int main() {
    exampleFunction();
    exampleFunction();
    return 0;
}