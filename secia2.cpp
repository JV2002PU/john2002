#include <iostream>
#include <vector>
#include "Person.h" // Include the header file for Person if defined separately

class Secretary {
private:
    std::vector<Person*> persons; // Using a vector of pointers to Person objects

public:
    // Constructors and Destructor
    Secretary() {}
    ~Secretary() {
        // Clean up dynamically allocated memory in the vector
        for (Person* p : persons) {
            delete p;
        }
        persons.clear();
    }

    // Overloading the addition operator to add a Person
    void operator+=(Person* p) {
        persons.push_back(p);
    }

    // Overloading input and output operators
    friend std::istream& operator>>(std::istream& input, Secretary& secretary) {
        // Logic to input data for Secretary
        // For example, adding Persons to the Secretary
        // This might involve reading data from the input stream and creating Person objects
        return input;
    }

    friend std::ostream& operator<<(std::ostream& output, const Secretary& secretary) {
        // Output logic for Secretary
        // For example, displaying details of Persons in the Secretary
        for (const Person* p : secretary.persons) {
            output << *p << std::endl; // Assuming the Person class has an overloaded << operator
        }
        return output;
    }

    // Finding a specific Person
    bool findPerson(const std::string& nameToFind) const {
        for (const Person* p : persons) {
            if (p->getName() == nameToFind) {
                return true;
            }
        }
        return false;
    }

    // Copy Constructor
    Secretary(const Secretary& other) {
        for (const Person* p : other.persons) {
            this->persons.push_back(new Person(*p)); // Assuming Person has a copy constructor
        }
    }

    // Assignment Operator Overloading
    Secretary& operator=(const Secretary& other) {
        if (this != &other) {
            // Clean up current state
            for (Person* p : persons) {
                delete p;
            }
            persons.clear();

            // Copy data from 'other'
            for (const Person* p : other.persons) {
                this->persons.push_back(new Person(*p)); // Assuming Person has a copy constructor
            }
        }
        return *this;
    }
};
