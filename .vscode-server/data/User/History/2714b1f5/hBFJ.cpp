#include <iostream>

// Συνάρτηση που επιστρέφει αναφορά σε int
int& getNumber() {
    static int number = 42; // Μια στατική μεταβλητή για το παράδειγμα
    return number;
}

int main() {
    int result = getNumber();
    
    std::cout << "Initial value: " << result << std::endl;

    getNumber() = 100; // Αλλάζουμε την τιμή χρησιμοποιώντας την αναφορά

    std::cout << "New value: " << getNumber() << std::endl;

    return 0;
}