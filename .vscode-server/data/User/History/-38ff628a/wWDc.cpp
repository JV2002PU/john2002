#include <iostream>
#include <string>
using namespace std;

class Person {
    static int count;
    string Name;
    int age;
    int id;

public:
    Person(string name, int age, int id) {
        this->Name = name;
        this->age = age;
        this->id = id;
        count++;
    }

    void GetInfo() {
        cout << "Name: " << Name << endl;
        cout << "age: " << age << endl;
        cout << "id: " << id << endl;
        cout << "count: " << count << endl;
    }

    ~Person() {
        --count;
    }

    friend ostream& operator<<(ostream& COUT, const Person& Aperson) {
        COUT << "Name: " << Aperson.Name << endl;
        COUT << "age: " << Aperson.age << endl;
        COUT << "id: " << Aperson.id << endl;
        COUT << "count: " << Aperson.count << endl;
        return COUT;
    }
};

int Person::count = 0;

int main() {
    Person Aperson = Person("petros", 23, 2000016);
    cout << Aperson;
}