#include <iostream>
#include <string>
#include <vector>

class Person {
private:
    static int count;
    std::string name;
    int age;

public:
    Person() : name("Unknown"), age(0) {
        count++;
    }

    Person(std::string n, int a) : name(n), age(a) {
        count++;
    }

    ~Person() {
        count--;
    }

    const std::string& getName() const {
        return name;
    }

    friend std::ostream& operator<<(std::ostream& out, const Person& person) {
        out << "Name: " << person.name << ", Age: " << person.age;
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Person& person) {
        std::cout << "Enter name: ";
        in >> person.name;
        std::cout << "Enter age: ";
        in >> person.age;
        return in;
    }

    static int getCount() {
        return count;
    }
};

int Person::count = 0;

class Secretary {
private:
    std::vector<Person*> persons;

public:
    Secretary() {}

    ~Secretary() {
        for (Person* p : persons) {
            delete p;
        }
        persons.clear();
    }

    void operator+=(Person* p) {
        persons.push_back(p);
    }

    friend std::ostream& operator<<(std::ostream& out, const Secretary& secretary) {
        for (const Person* p : secretary.persons) {
            out << *p << std::endl;
        }
        return out;
    }

    bool findPerson(const std::string& nameToFind) const {
        for (const Person* p : persons) {
            if (p->getName() == nameToFind) {
                return true;
            }
        }
        return false;
    }

    Secretary(const Secretary& other) {
        for (const Person* p : other.persons) {
            persons.push_back(new Person(*p));
        }
    }

    Secretary& operator=(const Secretary& other) {
        if (this != &other) {
            for (Person* p : persons) {
                delete p;
            }
            persons.clear();
            for (const Person* p : other.persons) {
                persons.push_back(new Person(*p));
            }
        }
        return *this;
    }
};

int main() {
    Secretary department;

    Person* person1 = new Person("Alice", 25);
    Person* person2 = new Person("Bob", 30);

    department += person1;
    department += person2;

    std::cout << "Persons in the department:" << std::endl;
    std::cout << department << std::endl;

    std::cout << "Total Persons: " << Person::getCount() << std::endl;

    delete person1;
    delete person2;

    return 0;
}
